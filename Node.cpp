//
// Created by Eitan on 06/12/2019.
//

#include "Node.h"



//////////////////////////////Node///////////////////////////

int node::getServerNum(){
    return this->server_num;
}

node* node::getPrevious(){
    return this->previous;
}

node* node::getNext(){
    return this->next;
}

void node::setPrevious(node* n){
    this->previous = n;
}

void node::setNext(node* n){
    this->next = n;
}

