//+----------------------------------------------------------
//|
//| Perform some tests of FunctionGraph classes
//|
//+----------------------------------------------------------

#include "FunctionGraph.h"
#include <iostream>

int main(int argc, char** argv) {

    

    
    auto cf1 = std::make_shared<FG::ConstField>(1.0);
    auto vf1 = std::make_shared<FG::VarField>("x", 2.0);
    auto sf1 = std::make_shared<FG::Sum>(cf1, vf1);
    
    
    const double res1 = sf1->evaluate();
    std::cout << "Got res1: " << res1 << std::endl;

    /*
    vf1->set(4.0);
    const double res2 = sf1->evaluate();
    std::cout << "Got res2: " << res2 << std::endl;

    auto cf2 = std::make_shared<FG::ConstField>(7.0);
    auto pf1 = std::make_shared<FG::Product>(sf1, cf2);

    const double res3 = pf1->evaluate();
    std::cout << "Got res3: " << res3 << std::endl;

    // Test dependencies:
    std::cout << "cf1 depends on x:" << cf1->depends_on("x") << std::endl;
    std::cout << "sf1 depends on x:" << sf1->depends_on("x") << std::endl;
    std::cout << "pf1 depends on x:" << pf1->depends_on("x") << std::endl;
    */


}