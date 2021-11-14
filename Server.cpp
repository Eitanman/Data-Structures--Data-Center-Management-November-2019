//
// Created by Eitan on 06/12/2019.
//

#include "Server.h"


/////////////////////////////Server////////////////////////////////////

//for future use:
/*
 * Node temp_node = this->node->getPrevious();
    (this->node->getNext())->setPrevious(temp_node);
    temp_node->setNext(this->node->getNext());
 */


int server::getnum(){
    return this->num;
}

bool server::isUsed(){
    return this->in_use;
}

bool server::isWindows(){
    return this->operating_system;
}

Node server::getNode() {
    return this->node;
}

void server::setUsed(bool use){
//change the nodes status
    this->in_use = use;
}

void server::setOS (OS os){
    this->operating_system = os;
}

void server::setNodeNext(Node n){
    this->node->setNext(n);
}

void server::setNodePrev(Node n){
    this->node->setPrevious(n);
}