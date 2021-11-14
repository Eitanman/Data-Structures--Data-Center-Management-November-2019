#include "DataCenter.h"//
#include <new>
// Created by Eitan on 04/12/2019.
//
////////////////////////DataCenter///////////////////////////////////////

dataCenter::dataCenter(int key, int servers_num):
    key(nullptr),servers_num(servers_num),windows_num(nullptr),linux_num(nullptr),windows_list(nullptr,nullptr),
    linux_list(nullptr,nullptr),server_array(nullptr)
    {
    //check parameters
    if ((key<=0)||(servers_num<=0)){
        throw BadParametersDC();
    }
    this->server_array = new Server[servers_num];
    if(!(this->server_array)){
        throw BadAllocationDC();
    }
    for(int i=0;i<servers_num;i++){
        Server temp = new server(server(i,false,Linux));
        if(!(temp)){
            throw BadAllocationDC();
        }
        this->server_array[i] = temp;
    }
    if(servers_num == 2){
        this->server_array[0]->setNodePrev(this->server_array[1]->getNode());
        this->server_array[1]->setNodeNext(this->server_array[0]->getNode());
    }
    for(int j=1; j<(servers_num-1);j++){
        this->server_array[j-1]->setNodePrev(server_array[j]->getNode());
        this->server_array[j]->setNodePrev(server_array[j+1]->getNode());
        this->server_array[j]->setNodeNext(server_array[j-1]->getNode());
        this->server_array[j+1]->setNodeNext(server_array[j]->getNode());
    }
    this->key = new int_key(key);//check if alright
    this->servers_num = servers_num;
    this->windows_num = new os_key(0,key);
    this->linux_num = new os_key(servers_num,key);
    this->linux_list = list(this->server_array[servers_num-1]->getNode(),this->server_array[0]->getNode());
    this->windows_list = list(nullptr,nullptr);
}

dataCenter::~dataCenter(){
    delete this->key;
    delete this->windows_num;
    delete this->linux_num;
    for(int j=0;j<servers_num;j++){
        delete server_array[j];
    }
//    delete &(this->windows_list);
//    delete &(this->linux_list);
}

int dataCenter::getKey(){
    return this->key->getKey();
}

int dataCenter::getNum(){
    return this->servers_num;
}

int dataCenter::getWindowsNum(){
    return this->windows_num->getOsNum();
}

int dataCenter::getLinuxNum(){
    return this->linux_num->getOsNum();
}

Int_Key dataCenter::getIntKey(){
    return this->key;
}

OS_Key dataCenter::getWindowsKey(){
    return this->windows_num;
}

OS_Key dataCenter::getLinuxKey(){
    return this->linux_num;
}

bool dataCenter::setWindowsKey(int new_windows_num){
    try {
        OS_Key new_windows = new os_key(new_windows_num,this->getKey());//see if it's alright
        setNewKey(new_windows, Windows);
        return 1;
    }
    catch (std::bad_alloc & ){
        return 0;
    }
}

bool dataCenter::setLinuxKey(int new_linux_num){
    try {
        OS_Key new_linux = new os_key(new_linux_num,this->getKey());//see if it's alright
        setNewKey(new_linux, Linux);
        return 1;
    }
    catch (std::bad_alloc & ){
        return 0;
    }
}

Node dataCenter::getWindowsListFirst(){
    if(this->windows_list.getFirst() == nullptr){
        return nullptr;
    }
    return this->windows_list.getFirst();
}
Node dataCenter::getWindowsListLast(){
    if(this->windows_list.getLast() == nullptr){
        return nullptr;
    }
    return this->windows_list.getLast();
}
Node dataCenter::getLinuxListFirst(){
    if(this->linux_list.getFirst() == nullptr){
        return nullptr;
    }
    return this->linux_list.getFirst();
}
Node dataCenter::getLinuxListLast(){
    if(this->linux_list.getLast() == nullptr){
        return nullptr;
    }
    return this->linux_list.getLast();
}
/*
void dataCenter::setWindowsListFirst(Node n){
    this->windows_list.setFirst(n);
}

void dataCenter::setWindowsListLast(Node n){
    this->windows_list.setLast(n);
}

void dataCenter::setLinuxListFirst(Node n){
    this->linux_list.setFirst(n);
}

void dataCenter::setLinuxListLast(Node n){
    this->windows_list.setLast(n);
}
*/
void dataCenter::addWindowsList(Node n){
    if(this->getWindowsListFirst() == nullptr){
        this->windows_list.setFirst(n);
        this->windows_list.setLast(n);
        return;
    }
    this->windows_list.getFirst()->setPrevious(n);
    n->setNext(this->windows_list.getFirst());
    this->windows_list.setFirst(n);
}

void dataCenter::addLinuxList(Node n){
    if(this->getLinuxListFirst() == nullptr){
        this->linux_list.setFirst(n);
        this->linux_list.setLast(n);
        return;
    }
    this->linux_list.getFirst()->setPrevious(n);
    n->setNext(this->linux_list.getFirst());
    this->linux_list.setFirst(n);
}

void dataCenter::removeFromWindowsList(Node n){
    if(this->windows_list.getFirst()== this->windows_list.getLast()){
        this->windows_list.setFirst(nullptr);
        this->windows_list.setLast(nullptr);
        return;
    }
    if(this->windows_list.getFirst()==n){
        this->windows_list.setFirst(this->windows_list.getFirst()->getNext());
        this->windows_list.getFirst()->setPrevious(nullptr);
        n->setNext(nullptr);
        return;
    }
    if(this->windows_list.getLast()==n){
        this->windows_list.setLast(this->windows_list.getLast()->getPrevious());
        this->windows_list.getLast()->setNext(nullptr);
        n->setPrevious(nullptr);
        return;
    }
    n->getNext()->setPrevious(n->getPrevious());
    n->getPrevious()->setNext(n->getNext());
    n->setNext(nullptr);
    n->setPrevious(nullptr);
}

void dataCenter::removeFromLinuxList(Node n){
    if(this->linux_list.getFirst()== this->linux_list.getLast()){
        this->linux_list.setFirst(nullptr);
        this->linux_list.setLast(nullptr);
        return;
    }
    if(this->linux_list.getFirst()==n){
        this->linux_list.setFirst(this->linux_list.getFirst()->getNext());
        this->linux_list.getFirst()->setPrevious(nullptr);
        n->setNext(nullptr);
        return;
    }
    if(this->linux_list.getLast()==n){
        this->linux_list.setLast(this->linux_list.getLast()->getPrevious());
        this->linux_list.getLast()->setNext(nullptr);
        n->setPrevious(nullptr);
        return;
    }
    n->getNext()->setPrevious(n->getPrevious());
    n->getPrevious()->setNext(n->getNext());
    n->setNext(nullptr);
    n->setPrevious(nullptr);
}

Server dataCenter::getServerByNum(int num){
    if((num>=this->servers_num)||(num<0)){
        return nullptr;
    }
    return this->server_array[num];
}
void dataCenter::setNewKey(OS_Key new_key, OS os) {
    if(os == Linux) {
        linux_num = new_key;
        return;
    }
    windows_num = new_key;
    return;
}