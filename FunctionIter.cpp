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
        cur_ptr = root;
        rec_stack.push(stack_elem(root, 0));
}


FunctionGraph *FunctionIter::operator*() {
    return this->cur_ptr;
}

FunctionGraph *FunctionIter::operator*() const{
    return this->cur_ptr;
}


bool FunctionIter::operator==(FunctionIter const &other) const {
    return cur_ptr == *other;
}

bool FunctionIter::operator!=(FunctionIter const &other) const {
    return !(cur_ptr == *other);
}




FunctionIter& FunctionIter::next() {
    if (rec_stack.empty()) {
        cur_ptr = nullptr;
        return *this;
    }

    int cur_depth = rec_stack.top().second;
    cur_ptr = rec_stack.top().first;
    rec_stack.pop();
   
    
    for(auto it  = cur_ptr->argBegin();
             it != cur_ptr->argEnd();
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
    if (rec_stack.empty()) {
        cur_ptr = nullptr;
        return *this;
    } else {
        cur_ptr = rec_stack.top().first;
        return *this;
    }
    
   return *this;
}

FunctionIter &FunctionIter::operator++() {
    return this->next();
}

int FunctionIter::get_depth() const {
    return rec_stack.top().second;
}

