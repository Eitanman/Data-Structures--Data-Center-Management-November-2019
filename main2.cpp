#include <iostream>
using std::cout;
using std::endl;
#include "List.h"

int main() {
    Node* node_array = new Node[20];
    for(int i=0;i<20;i++) {
        Node temp_node = new node(node(i));
        node_array[i] = temp_node;
    }
    for(int j=1; j<19;j++){
        node_array[j-1]->setNext(node_array[j]);
        node_array[j]->setNext(node_array[j+1]);
        node_array[j]->setPrevious(node_array[j-1]);
        node_array[j+1]->setPrevious(node_array[j]);
    }
    List temp_list = new list(list(node_array[0],node_array[19]));
    for(Node temp= temp_list->getLast(); temp!=nullptr ; temp = temp->getPrevious()){
        cout << temp->getServerNum() << endl;
    }
    delete temp_list;
    return 0;
}