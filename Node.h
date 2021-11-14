//
// Created by Eitan on 06/12/2019.
//

#ifndef EX1_NODE_H
#define EX1_NODE_H



typedef class node{
private:
    int server_num;
    node* previous;
    node* next;
public:
    node(int server_num):
            server_num(server_num), previous(nullptr), next(nullptr) {};
    node(const node& n) = default;
    ~node() {};//Deletes a single node. That is, its pointers
    int getServerNum();
    node* getPrevious();
    node* getNext();
    void setPrevious(node* n);
    void setNext(node* n);
    //friend server::server(int num, bool in_use, OS operating_system);
} *Node;

#endif //EX1_NODE_H
