//
// Created by yarde on 12/11/2019.
//
#include "library1.h"
#include "DS.h"
#include <new>
void *Init(){
    try {
        dataSystem *new_system = new dataSystem();
        return new_system;
    }
    catch(std::bad_alloc &){

        return nullptr;
    }
}

StatusType AddDataCenter(void *DS, int dataCenterID, int numOfServers){
    dataSystem* temp_ds = static_cast<dataSystem*>(DS);
    return temp_ds->m_AddDataCenter(DS, dataCenterID, numOfServers);
}
StatusType RemoveDataCenter(void *DS, int dataCenterID){
    dataSystem* temp_ds = static_cast<dataSystem*>(DS);
    return temp_ds->m_RemoveDataCenter(DS, dataCenterID);
}
StatusType RequestServer(void *DS, int dataCenterID, int serverID, int os, int *assignedID){
    dataSystem* temp_ds = static_cast<dataSystem*>(DS);
    return temp_ds->m_RequestServer(DS, dataCenterID, serverID, os, assignedID);
}
StatusType FreeServer(void *DS, int dataCenterID, int serverID){
    dataSystem* temp_ds = static_cast<dataSystem*>(DS);
    return temp_ds->m_FreeServer(DS, dataCenterID, serverID);
}
StatusType GetDataCentersByOS(void *DS, int os, int **dataCenters, int* numOfDataCenters){
    dataSystem* temp_ds = static_cast<dataSystem*>(DS);
    return temp_ds->m_GetDataCenterByOS(DS, os, dataCenters, numOfDataCenters);
}
void Quit(void** DS){
    dataSystem *temp_ds = static_cast<dataSystem *>(*DS);
    temp_ds->Quit(DS);
    //*DS = nullptr;
}




