//
// Created by Eitan on 09/12/2019.
//


#include <iostream>
using std::cout;
using std::endl;
#include "Server.h"


int main() {
    Server* server_array = new Server[20];
    for(int i=0;i<20;i++) {
        Server temp_server = new server(server(i,true,Windows));
        server_array[i] = temp_server;
    }
    for(int j=0;j<20;j++){
        cout << server_array[j]->getnum() << "," << server_array[j]->isUsed() << "," << server_array[j]->isWindows() << endl;
    }
    for(int i=0;i<20;i+=3){
        Node temp_node = new node(node(i));
        server_array[i]->setNode(temp_node);
    }
    for(int d=3;d<16;d+=3){
        server_array[d-3]->setNodeNext(server_array[d]->getNode());
        server_array[d]->setNodeNext(server_array[d+3]->getNode());
        server_array[d]->setNodePrev(server_array[d-3]->getNode());
        server_array[d+3]->setNodePrev(server_array[d]->getNode());
    }
    List temp_list = new list(list(server_array[0]->getNode(),server_array[18]->getNode()));
    for(int d=0;d<20;d++){
        delete server_array[d];
    }
    for(Node n=temp_list->getFirst();n!= nullptr;n=n->getNext()){
        cout << n->getServerNum() << endl;
    }
    delete temp_list;
    return 0;
}
