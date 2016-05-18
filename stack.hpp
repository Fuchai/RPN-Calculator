//
//  stack.hpp
//  CS253
//
//  Created by Jason Hu on 4/12/16.
//  Copyright © 2016 Jason Hu. All rights reserved.
//

#ifndef stack_hpp
#define stack_hpp

#include <stdio.h>
#include <iostream>
#include <list>
#include "linkedlist.hpp"

template <class T>
class Stack_Impl{
    
public:
    
    typedef my_iter<T> iterator;

    Stack_Impl(); //constructor
    
    iterator push(T newobj); //push method
    T pop();
    
    bool isEmpty() const;
    typename std::list<T>::size_type size();

    iterator begin();
    iterator end();
    T top() const;
    
private:
    Linklist<T> stackholder;
};

// two operators
template <class T> Stack_Impl<T>& operator<< (Stack_Impl<T>& stack,T newobj);

template <class T> Stack_Impl<T>& operator>> (Stack_Impl<T>& stack,T& receiver);

// constructor
template <class T> Stack_Impl <T> ::Stack_Impl() {}

// push
template <class T> typename Stack_Impl<T>::iterator Stack_Impl<T>::push(T newobj) {
    stackholder.push_back(newobj);
    return stackholder.end();
} // returns the iterator

// pop
template <class T> T Stack_Impl<T>::pop() {
    T ret = stackholder.back();
    stackholder.pop_back();
    return ret;
}

// peak
template <class T> T Stack_Impl<T>::top() const {
    return stackholder.back();
}

// empty
template <class T> bool Stack_Impl<T>::isEmpty() const {
    return stackholder.empty();
}

// two operators
template <class T> Stack_Impl<T>& operator<< (Stack_Impl<T>& stack,T newobj){
    stack.push(newobj);
    return stack;
}

template <class T>  Stack_Impl<T>& operator>> (Stack_Impl<T>& stack,T& receiver){
    receiver=stack.pop();
    return stack;
}

template <class T> typename std::list<T>::size_type Stack_Impl<T>::size(){
    return stackholder.size();
}

template <class T>  typename Stack_Impl<T>::iterator Stack_Impl<T>::begin(){
    return stackholder.begin();
}

template <class T>  typename Stack_Impl<T>::iterator Stack_Impl<T>::end(){
    return stackholder.end();
}

#endif /* stack_hpp */
