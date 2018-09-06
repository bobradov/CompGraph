//+----------------------------------------------------------
//|
//| FunctionIter.h
//|
//| DFS-based iterator for a function graph.
//|
//|
//+----------------------------------------------------------


#ifndef FUNCTIONITER_H
#define FUNCTIONITER_H

#include "FunctionGraph.h"
#include <utility>


namespace FG {

    typedef std::pair<FunctionGraph*, int> stack_elem;

    class FunctionIter {
            public:
                FunctionIter(FunctionGraph *root_);
                FunctionGraph *begin();
                FunctionGraph *end();
                FunctionGraph *next();
                FunctionGraph *operator++();
                int get_depth() const;

            private:
                FunctionGraph *root;
                std::stack<stack_elem> rec_stack;
                FunctionGraph *cur_ptr;

    };

};

#endif