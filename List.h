//
// Created by Eitan on 04/12/2019.
//

#ifndef EX1_LIST_H
#define EX1_LIST_H

#include "Node.h"


typedef class list {
private:
    Node first;
    Node last;
public:
    list(Node first = nullptr,Node last= nullptr):first(first), last(last){};
    list(const list& l) = default;
    ~list() = default;//new application: deletes only its pointers
    Node getFirst();
    Node getLast();
    void setFirst(Node n);
    void setLast(Node n);
} *List;


#endif //EX1_LIST_H
