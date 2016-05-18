//
//  Header.h
//  CS 253
//
//  Created by Jason Hu on 4/18/16.
//  Copyright © 2016 Jason Hu. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <assert.h>


// end begin push_back pop_back back empty size
template <class T> class Linklist;
template <class T> class my_iter;

template <class T>
class Node{
    
    friend class Linklist<T>;
    friend class my_iter<T>;
    
private:
    Node* next;
    Node* previous;
    T data;
    
public:
    // constructor
    Node(): next(nullptr), previous(nullptr), data(0){}
    Node(T obj, Node<T> & previous);
    
    void setNext(Node<T>*);
    void setPrev(Node<T>*);

};

// constructor
template <class T> Node<T>::Node(T obj, Node<T> & prevnode){
    data=obj;
    previous = & prevnode;
    next=nullptr;
    prevnode.setNext(this);
}

// helper
template <class T> void Node<T>::setNext(Node<T>* nxtnode){
    next=nxtnode;
}

template <class T> void Node<T>::setPrev(Node<T>* prevnode){
    previous=prevnode;
}




// iterator

template <class T> // a iterator that traverse over linked list and retrieve the data stored in each node (not the node itself).
class my_iter : public std::iterator<std::bidirectional_iterator_tag, T>{

    // Note that this iterator does not conform with bidirectional iterator standard. It's just for my particular program.

    friend class Linklist<T>;
private:
    Node<T> * pointee;
    Node<T> & getNode();

public:
    // constructor
    my_iter():pointee(nullptr){}
    my_iter(Node<T> * pass): pointee(pass){}
    // operator overload
    T& operator*();
    const T& operator *() const;
    Node<T>* operator->() { return pointee;}
    my_iter<T>& operator++();
    my_iter<T> operator++(int);
    my_iter<T>& operator--();
    my_iter<T> operator--(int);
    bool operator!=(my_iter<T> comp);
    my_iter<T>& operator=(my_iter<T>& assi);
    my_iter<T>& operator=(Node<T> * assi);
};

template <class T> Node<T> & my_iter<T>::getNode(){
    if (pointee==nullptr){
        static Node<T> a; // I have no idea how to get around it at the moment. Let's do static, since it will be invoked everytime.
        return a;
    }
    else return *pointee;
}

template <class T> T& my_iter<T>::operator*(){
    return pointee->data;
}

template <class T> const T& my_iter<T>::operator*() const {
    return pointee->data;
}

template <class T> my_iter<T>& my_iter<T>::operator++() {
    assert (pointee!=nullptr);
    pointee=pointee->next;
    return *this;
};

template <class T> my_iter<T> my_iter<T>::operator++(int){ // post increment does not return itself, but a copy.
    assert (pointee!=nullptr);
    my_iter<T> ret=*this;
    pointee=pointee->next;
    return ret;
}

template <class T> bool my_iter<T>::operator!=(my_iter<T> comp){
    return pointee!=comp.pointee;
}

template <class T> my_iter<T>& my_iter<T>::operator=(my_iter<T>& assi){
    if (&assi != this){
        pointee=assi.pointee;
    }
    return *this;
}

template <class T> my_iter<T>& my_iter<T>::operator--(){
    assert (pointee!=nullptr);
    pointee=pointee->previous;
    return *this;
}

template <class T> my_iter<T> my_iter<T>::operator--(int){
    assert (pointee!=nullptr);
    my_iter<T> ret=*this;
    pointee=pointee->previous;
    return ret;
}

template <class T> my_iter<T>& my_iter<T>::operator=(Node<T> * assi){
    pointee=assi;
    return *this;
}



// Linklist
template <class T>
class Linklist{
    
    typedef my_iter<T> iterator;
    friend class Node<T>;
    
private:
    iterator endnode; // the acutal end node not one past. endnode == &back() != *end()
    iterator beginnode;
    size_t length;

    
public:
    iterator begin() const { return beginnode; }
    iterator end() const { return iterator(); }
    const T back() const { return *endnode; }
    bool empty() const { return size()==0; }
    size_t size() const { return length; }
    void push_back(T obj);
    void pop_back();
    
    // constructor
    explicit Linklist(): beginnode(), endnode(),length(0) {}
    explicit Linklist(Node<T> * first) : beginnode(first), endnode(first), length(1){}
     ~Linklist();
};

template <class T> void Linklist<T>::push_back(T obj){
    Node<T> * newnode;
    newnode = new Node<T> (obj, endnode.getNode());
    endnode = newnode;
    length++;
    if (length==1){
        beginnode=newnode;
    }
}

template <class T> void Linklist<T>::pop_back(){ // consider poping the first one
    try {
        if (empty()) { throw std::domain_error("Empty");}
        Node<T>* prevnode = endnode->previous; // empty
        
        if (prevnode!=0){
            prevnode->next=nullptr;
            delete endnode.pointee;
            endnode = prevnode;
            length--;
        }
        else {
            delete endnode.pointee;
            beginnode = endnode = 0;
            length--;
        }

        
    } catch (...) {
        throw std::domain_error("Cannot pop the last element");
    }
}

template <class T> Linklist<T>::~Linklist(){
    while (length!=0){  // be careful about this condition, don't access NULL nodes, use list methods to check.
        Node<T> * todel = endnode.pointee;
        endnode--;
        length--;
        delete todel;
    }
}




#endif /* Header_h */
