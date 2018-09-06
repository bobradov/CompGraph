//+----------------------------------------------------------
//|
//| FunctionIter.cpp
//|
//| Implementation of FunctionIter methods.
//|
//|
//+----------------------------------------------------------


#include "FunctionIter.h"

using namespace FG;


FunctionIter::FunctionIter(FunctionGraph *root_) : root(root_) {
        rec_stack.push(stack_elem(root, 0));
}


FunctionGraph *FunctionIter::begin() {
    return root;
}

FunctionGraph *FunctionIter::end() {
    return nullptr;
}

FunctionGraph* FunctionIter::next() {
    if (rec_stack.empty()) return end();

    int cur_depth = rec_stack.top().second;
    cur_ptr = rec_stack.top().first;
    rec_stack.pop();
   
    
    for(auto it  = cur_ptr->args.begin();
             it != cur_ptr->args.end();
           ++it) {
                rec_stack.push(stack_elem(it->get(), 
                                cur_depth+1));
    }
    
    // Did we find any next elements?
    // They're either on the stack from a previous search,
    // or they just got added.
    // If neither, the stack is empty.
    // If no next elements, return end
    // Otherwise, return the first of the new elements.
    if (rec_stack.empty()) 
        return end();
    else {
        cur_ptr = rec_stack.top().first;
        return cur_ptr;
    }
    
   return cur_ptr;
}

FunctionGraph *FunctionIter::operator++() {
    return this->next();
}

int FunctionIter::get_depth() const {
    return rec_stack.top().second;
}

