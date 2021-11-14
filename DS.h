//
// Created by Eitan on 04/12/2019.
//

#ifndef EX1_DS_H
#define EX1_DS_H

#include "DataCenter.h"
#include "Tree.h"
#include "library1.h"

typedef class dataSystem {
private:
    tree<DataCenter,int_key*> int_tree;
    tree<DataCenter,os_key*> windows_tree;
    tree<DataCenter,os_key*> linux_tree;
    StatusType installWindows(DataCenter data_center ,Server server);
    StatusType installLinux(DataCenter data_center ,Server server);
public:
    dataSystem() = default;
    dataSystem(const dataSystem& ds) = delete;
    ~dataSystem();
    void* m_Init();
    StatusType m_AddDataCenter(void * DS, int dataCenterID, int numOfServers);
    StatusType m_RemoveDataCenter(void *DS, int dataCenterID);
    StatusType m_RequestServer(void* DS, int dataCenterID , int serverID,int os,int* assignedID);
    StatusType m_FreeServer(void *DS, int dataCenterID,int serverID);
    StatusType m_GetDataCenterByOS(void *DS, int os, int **dataCenters, int* numOfDataCenters);
    void Quit(void **DS);
} *DataSystem;
#endif //EX1_DS_H
