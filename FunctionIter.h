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
                FunctionIter &next();
                FunctionIter &operator++();
                FunctionGraph *operator*();
                FunctionGraph *operator*() const;
                int get_depth() const;
                bool operator==(FunctionIter const &other) const;
                bool operator!=(FunctionIter const &other) const;

            private:
                FunctionGraph *cur_ptr;
                FunctionGraph *root;
                std::stack<stack_elem> rec_stack;

    };

};

#endif