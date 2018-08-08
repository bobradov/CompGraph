//+----------------------------------------------------------
//|
//| FunctionGraph.cpp
//|
//| Implementation of FunctionGraph methods.
//|
//|
//+----------------------------------------------------------


#include "FunctionGraph.h"
#include <iostream>



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


FunctionIter::FunctionIter(FunctionGraph *root_) : root(root_) {
        rec_stack.push(root);
}

FunctionGraph* FunctionIter::next() {
    if (rec_stack.empty()) return nullptr;

    cur_ptr = rec_stack.top();
    rec_stack.pop();

    for(auto it  = cur_ptr->args.begin();
             it != cur_ptr->args.end();
           ++it) {
                     rec_stack.push(it->get());
    }

    return cur_ptr;
}

void FunctionGraph::DFS() {
    std::stack<FunctionGraph*> recstack;
    recstack.push(this);

    while(!recstack.empty()) {
        FunctionGraph *cur_ptr = recstack.top();
        std::cout << "At: " << cur_ptr->get_name() << std::endl;
        recstack.pop();
        for(auto it  = cur_ptr->args.begin();
                 it != cur_ptr->args.end();
                 ++it) {
                     recstack.push(it->get());
        }
    }
    
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


