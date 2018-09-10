//+----------------------------------------------------------
//|
//| FunctionGraph.cpp
//|
//| Implementation of FunctionGraph methods.
//|
//|
//+----------------------------------------------------------


#include "FunctionGraph.h"
#include "FunctionIter.h"
#include <iostream>
#include <sstream>
#include <string>
#include <map>


using namespace FG;


//--- Base-class methods

FunctionGraph::FunctionGraph(const std::string &name_) :
                        name(name_) {
}


const std::set<std::string>& 
      FunctionGraph::get_dependency_set() const{
    return dependency_set;
}

bool FunctionGraph::depends_on(const std::string &var_) const {
    if(dependency_set.find(var_) != dependency_set.end()) {
        return true;
    } else {
        return false;
    }
}



// Function for assigning value to a variable 
// Recursisvely searches for a VarField with the same
// name as the argument
// Can only change values of VarFields, other function
// types (such as ConstField) are ignored.
// If multiple VarFields with the same name are used,
// only the first one with the matching name is modified.
// N.B. Probably should not allow multiple VarFields with
// the same name.

bool FunctionGraph::assign_var(const std::string &name_, 
                               double &val_) {

    std::cout << "in " << name << std::endl;
    auto var_cast_ptr = dynamic_cast<VarField*>(this);

    if( depends_on(name_) && var_cast_ptr != nullptr ) {
        std::cout << "Found it!" << std::endl;
        val_ = var_cast_ptr->get();
        return true;

    } else {
        for(auto &cur_dep_ref : args) {
            bool retval = cur_dep_ref->assign_var(name_, val_);
            if (retval) return true;
        }
    }
    return false; 
}


FunctionIter FunctionGraph::begin() {
    return FunctionIter(this);
}

FunctionIter FunctionGraph::end() {
    return FunctionIter(nullptr);
}

std::vector<std::unique_ptr<FunctionGraph>>::iterator 
FunctionGraph::argBegin() {
    return args.begin();
}

std::vector<std::unique_ptr<FunctionGraph>>::iterator 
FunctionGraph::argEnd() {
    return args.end();
}            
       
std::string FunctionGraph::toString() {


    std::ostringstream os;
    const int h_pad = 4;
    const int v_pad = 4;
    std::map<std::string, int> node_depth;
    node_depth[get_name()] = 0;

    for(FunctionIter fit = this->begin(); 
                     fit != this->end(); 
                   ++fit) 
    {
        const int cur_depth = fit.get_depth();
        FG::FunctionGraph* parent = fit.get_parent();
        std::string parent_name;
        if(parent == nullptr) 
            parent_name = "none";
        else
            parent_name = parent->get_name();

        // Record (name, depth) pair in node_depth map
        // Needed to look up depths of parents

        // Insert vertical lines
        // Insert at the correct horizontal position: depth-dep
        const std::string cur_name = (*fit)->get_name();
        if(cur_name != get_name()) {
            for(int i=0; i < v_pad; ++i) {
                for(int j=0; j < h_pad * (cur_depth-1); ++j) {
                    os << " ";
                }
                os << "|" << std::endl;
            }
        

            // Pad with "-" signs; n_pad for each depth level
            for(int i=0; i < h_pad * (cur_depth-1); ++i) os << " ";

            for(int i=0; i < h_pad-1; ++i) os << "-";
        }

        // Now actually add the node name
        os << (*fit)->get_name() << std::endl;
    }

    return os.str();
}

//--- ConstField class

ConstField::ConstField(const std::string &name_, 
                       const double &val_) : FunctionGraph(name_),  
                       value(val_) {
}

double ConstField::evaluate() const {
    return value;
}

//--- VarField class
VarField::VarField(const std::string &name_,
                   const std::string &var_name_,
                   const double &init_val) : 
                   FunctionGraph(name_),
                   var_name(var_name_), value(init_val) {
       dependency_set.insert(var_name_);                       
}

double VarField::evaluate() const {
    return value;
}

void VarField::set(const double &val_) {
    value = val_;
}


//--- Sum class
Sum::Sum(const std::string &name_,
         std::unique_ptr<FunctionGraph> &&fg1_, 
         std::unique_ptr<FunctionGraph> &&fg2_) :
         FunctionGraph(name_) {

    args.reserve(2);
    args.push_back(move(fg1_));
    args.push_back(move(fg2_));

     auto deps1 = args[0]->get_dependency_set();
     auto deps2 = args[1]->get_dependency_set();
     dependency_set.insert(deps1.begin(), deps1.end());
     dependency_set.insert(deps2.begin(), deps2.end());

}

double Sum::evaluate() const {
    double val1 = args[0]->evaluate();
    double val2 = args[1]->evaluate();
    return val1 + val2;
}

//--- Product class
Product::Product(const std::string &name_,
                 std::unique_ptr<FunctionGraph> &&fg1, 
                 std::unique_ptr<FunctionGraph> &&fg2) :
                 FunctionGraph(name_) {

    args.reserve(2);
    args.push_back(move(fg1));
    args.push_back(move(fg2));

     auto deps1 = args[0]->get_dependency_set();
     auto deps2 = args[1]->get_dependency_set();
     dependency_set.insert(deps1.begin(), deps1.end());
     dependency_set.insert(deps2.begin(), deps2.end());
     
}

double Product::evaluate() const {
    double val1 = args[0]->evaluate();
    double val2 = args[1]->evaluate();
    return val1 * val2;
}


