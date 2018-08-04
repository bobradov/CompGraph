//+----------------------------------------------------------
//|
//| FunctionGraph.cpp
//|
//| Implementation of FunctionGraph methods.
//|
//|
//+----------------------------------------------------------


#include "FunctionGraph.h"


using namespace FG;


//--- Base-class methods
const std::set<std::string>& 
      FunctionGraph::get_dependency_set() const{
    return dependency_set;
}

bool FunctionGraph::depends_on(const std::string &var) const {
    if(dependency_set.find(var) != dependency_set.end()) {
        return true;
    } else {
        return false;
    }
}

//--- ConstField class

ConstField::ConstField(const double &val) : value(val) {
}

double ConstField::evaluate() const {
    return value;
}

//--- VarField class
VarField::VarField(const std::string &name,
                   const double &init_val) : var_name(name), 
                                             value(init_val) {
       dependency_set.insert(name);            
}

double VarField::evaluate() const {
    return value;
}

void VarField::set(const double &val) {
    value = val;
}


//--- Sum class
Sum::Sum(std::shared_ptr<FunctionGraph> fg1, 
         std::shared_ptr<FunctionGraph> fg2)  {

    args.reserve(2);
    args.push_back(fg1);
    args.push_back(fg2);

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
Product::Product(std::shared_ptr<FunctionGraph> fg1, 
                 std::shared_ptr<FunctionGraph> fg2) {

    args.reserve(2);
    args.push_back(fg1);
    args.push_back(fg2);

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


