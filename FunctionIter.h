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

    //typedef std::pair<FunctionGraph*, int> stack_elem;

    using stack_elem = std::tuple<FunctionGraph*, 
                                  int, FunctionGraph*>;

    class FunctionIter {
            public:
                FunctionIter(FunctionGraph *root_);
                
                // Support for Iterator API
                FunctionIter &operator++();
                FunctionGraph *operator*();
                FunctionGraph *operator*() const;
                bool operator==(FunctionIter const &other) const;
                bool operator!=(FunctionIter const &other) const;

                // Depth of tree at current search
                int get_depth() const;

                // Parent of current node
                FunctionGraph *get_parent() const;


            private:
                FunctionIter &next();
                FunctionGraph *cur_ptr;
                FunctionGraph *root;
                std::stack<stack_elem> rec_stack;

    };

};

#endif