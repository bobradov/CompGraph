//+----------------------------------------------------------
//|
//| Perform some tests of FunctionGraph classes
//|
//+----------------------------------------------------------

#include "FunctionGraph.h"
#include "FunctionIter.h"
#include <iostream>

int main(int argc, char** argv) {

    

    
    auto cf1 = std::make_unique<FG::ConstField>("cf1", 1.0);
    auto vf1 = std::make_unique<FG::VarField>("vf1", "x", 2.0);
    auto sf1 = std::make_unique<FG::Sum>("sf1", move(cf1), move(vf1));
    
    
    const double res1 = sf1->evaluate();
    std::cout << "Got res1: " << res1 << std::endl;

    
    //vf1->set(4.0);
    const double res2 = sf1->evaluate();
    std::cout << "Got res2: " << res2 << std::endl;

    auto cf2 = std::make_unique<FG::ConstField>("cf2", 7.0);
    auto pf1 = std::make_unique<FG::Product>("pf1", 
                                            move(sf1), move(cf2));

    const double res3 = pf1->evaluate();
    std::cout << "Got res3: " << res3 << std::endl;

    // Test dependencies:
    //std::cout << "cf1 depends on x:" << cf1->depends_on("x") << std::endl;
    //std::cout << "sf1 depends on x:" << sf1->depends_on("x") << std::endl;
    std::cout << "pf1 depends on x:" << pf1->depends_on("x") << std::endl;
    
    double xref;
    pf1->assign_var("x", xref);
    std::cout << "got xref: " << xref << std::endl;

    pf1->DFS();

    /*
    pf1->assign_var("x", 10.0);
    const double res4 = pf1->evaluate();
    std::cout << "Got res4: " << res4 << std::endl;
    */

   FG::FunctionIter fiter(pf1.get());
   for(FG::FunctionGraph *fp = fiter.begin(); 
            fp != fiter.end(); 
            fp = ++fiter) 
            {
               // std::cout << "checking depth ..." << std::endl;
                const int cur_depth = fiter.get_depth();
               // std::cout << " done checking depth." << std::endl;
                std::cout << "iter: " << fp->get_name() 
                          << " depth: " << cur_depth
                          << std::endl;
            }
    
   
}