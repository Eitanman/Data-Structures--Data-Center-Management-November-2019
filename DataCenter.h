//
// Created by Eitan on 04/12/2019.
//

#ifndef EX1_DATACENTER_H
#define EX1_DATACENTER_H

#include <stdbool.h>
#include "Server.h"
#include "Keys.h"
#include <exception>

typedef class dataCenter {
private:
    Int_Key key;
    int servers_num;
    OS_Key windows_num;
    OS_Key linux_num;
    list windows_list;
    list linux_list;
    Server* server_array;
    Node getWindowsListFirst();
    Node getLinuxListFirst();
    //friend StatusType dataSystem::installWindows(DataCenter data_center ,Server server);
    //friend StatusType dataSystem::installLinux(DataCenter data_center ,Server server);
    friend class dataSystem;
    bool setWindowsKey(int new_windows_num);
    bool setLinuxKey(int new_linux_num);
    void setNewKey(OS_Key new_key, OS os);
public:
    dataCenter(int key, int servers_num);
    dataCenter(const dataCenter& dc) = default;
    ~dataCenter();
    int getKey();
    int getNum();
    int getWindowsNum();
    int getLinuxNum();
    Int_Key getIntKey();
    OS_Key getWindowsKey();
    OS_Key getLinuxKey();
    void addWindowsList(Node n);
    void addLinuxList(Node n);
    Node getWindowsListLast();
    Node getLinuxListLast();
    void removeFromWindowsList(Node n);
    void removeFromLinuxList(Node n);
    Server getServerByNum(int num);
    class BadParametersDC: public std::exception {};
    class BadAllocationDC: public std::exception {};

}*DataCenter;

//

#endif //EX1_DATACENTER_H
