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
const std::set<std::string>& FunctionGraph::get_dependency_set() {
    return dependency_set;
}

bool FunctionGraph::depends_on(const std::string &var) {
    if(dependency_set.find(var) != dependency_set.end()) {
        return true;
    } else {
        return false;
    }
}

//--- ConstField class

ConstField::ConstField(const double &val) : value(val) {
}

double ConstField::evaluate() {
    return value;
}

//--- VarField class
VarField::VarField(const std::string &name,
                   const double &init_val) : var_name(name), 
                                             value(init_val) {
       dependency_set.insert(name);            
}

double VarField::evaluate() {
    return value;
}

void VarField::set(const double &val) {
    value = val;
}


//--- Sum class
Sum::Sum(std::shared_ptr<FG::FunctionGraph> fg1, 
         std::shared_ptr<FG::FunctionGraph> fg2) : 
 arg1(fg1), arg2(fg2) {
     auto deps1 = arg1->get_dependency_set();
     auto deps2 = arg2->get_dependency_set();
     dependency_set.insert(deps1.begin(), deps1.end());
     dependency_set.insert(deps2.begin(), deps2.end());
}

double Sum::evaluate() {
    double val1 = arg1->evaluate();
    double val2 = arg2->evaluate();
    return val1 + val2;
}

//--- Product class
Product::Product(std::shared_ptr<FG::FunctionGraph> fg1, 
         std::shared_ptr<FG::FunctionGraph> fg2) : 
 arg1(fg1), arg2(fg2) {
     auto deps1 = arg1->get_dependency_set();
     auto deps2 = arg2->get_dependency_set();
     dependency_set.insert(deps1.begin(), deps1.end());
     dependency_set.insert(deps2.begin(), deps2.end());
}

double Product::evaluate() {
    double val1 = arg1->evaluate();
    double val2 = arg2->evaluate();
    return val1 * val2;
}


