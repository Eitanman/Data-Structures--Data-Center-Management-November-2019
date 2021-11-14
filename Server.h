//
// Created by Eitan on 06/12/2019.
//

#ifndef EX1_SERVER_H
#define EX1_SERVER_H

#include "List.h"

typedef enum {Linux = 0,Windows = 1}OS;

typedef class server{
private:
    int num;
    bool in_use;
    OS operating_system;
    Node node;
public:
    server(int num, bool in_use, OS operating_system):
    num(num),in_use(in_use),operating_system(operating_system),node(nullptr){
        node = new class node(num);
    };
    server(const server& s) = default;
    ~server(){delete node;};//Deletes a certain server. Will happen through the array in the DC when its deleted
    int getnum();
    bool isUsed();
    bool isWindows();
    Node getNode();
    void setUsed(bool use);
    void setOS (OS os);
    void setNode(Node n){node=n;};
    void setNodeNext(Node n);
    void setNodePrev(Node n);
} *Server;

#endif //EX1_SERVER_H
