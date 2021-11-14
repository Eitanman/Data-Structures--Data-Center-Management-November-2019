//
// Created by Eitan on 04/12/2019.
//
#include "List.h"
//////////////////////////List//////////////////////////////


Node list::getLast(){
    return this->last;
}

Node list::getFirst(){
    return this->first;
}

void list::setFirst(Node n){
    this->first = n;
}

void list::setLast(Node n){
    this->last = n;
}
