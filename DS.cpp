//
// Created by Eitan on 04/12/2019.
//
#include "DS.h"
#include <iostream>
#include <ostream>
#include <new>
dataSystem::~dataSystem() {
    int num_data_centers = 0;
    DataCenter* data_array = new dataCenter*[num_data_centers];
    int_tree.reverseInorderGetData(int_tree.getRoot() ,data_array, &num_data_centers);
    for(int i=0;i<num_data_centers;i++){
        delete data_array[i];
    }
}

void* dataSystem::m_Init() {
    try {
        dataSystem *new_system = new dataSystem();
        return new_system;
    }
    catch(std::bad_alloc &){
        return nullptr;
    }
}
StatusType dataSystem::m_AddDataCenter(void * DS, int dataCenterID, int numOfServers) {
    if(numOfServers<=0 || DS == nullptr || dataCenterID <=0 ){
        return INVALID_INPUT;
    }
    try {
        DataCenter new_data_center = new dataCenter(dataCenterID, numOfServers);
        if (int_tree.isKeyInTree(new_data_center->getIntKey()) == 1) {
            delete new_data_center;
            return FAILURE;
        }
        int_tree.addVertex(new_data_center->getIntKey(), new_data_center);
        windows_tree.addVertex(new_data_center->getWindowsKey(),
                               new_data_center);
        linux_tree.addVertex(new_data_center->getLinuxKey(), new_data_center);
        return SUCCESS;
    }
    catch(std::bad_alloc &){
        return ALLOCATION_ERROR;
    }
}

StatusType dataSystem::m_RemoveDataCenter(void * DS, int dataCenterID) {
    if(DS == nullptr || dataCenterID<=0){
        return INVALID_INPUT;
    }
    dataSystem* temp_ds = static_cast<dataSystem*>(DS);
    int_key temp_key(dataCenterID);
    if(temp_ds->int_tree.isKeyInTree(&temp_key) == 0){
        return FAILURE;
    }
    DataCenter temp_data_center = temp_ds->int_tree.getDataByKey(&temp_key);
    os_key windows_os_key(temp_data_center->getWindowsNum(), dataCenterID);
    os_key linux_os_key(temp_data_center->getLinuxNum(), dataCenterID);
    temp_ds->int_tree.removeVertex(&temp_key);
    temp_ds->windows_tree.removeVertex(&windows_os_key);
    temp_ds->linux_tree.removeVertex(&linux_os_key);//will it work since it only iterates by the
    return SUCCESS;
}
StatusType dataSystem::m_FreeServer(void * DS, int dataCenterID, int serverID){
    if(serverID < 0 || DS == nullptr || dataCenterID<=0){
        return INVALID_INPUT;
    }
    dataSystem* temp_ds = static_cast<dataSystem*>(DS);
    int_key temp_key(dataCenterID);
    if(temp_ds->int_tree.isKeyInTree(&temp_key) == 0 ){
        return FAILURE;
    }
    //returns data by key
    DataCenter temp_center = temp_ds->int_tree.getDataByKey(&temp_key);
    int num_of_servers = temp_center->getNum();
    if(serverID>=num_of_servers){
        return INVALID_INPUT;
    }
    Server temp_server = temp_center->getServerByNum(serverID);
    if(temp_server->isUsed() == false){
        return FAILURE;
    }
    temp_server->setUsed(false);
    if(temp_server->isWindows() == true){
        temp_center->addWindowsList(temp_server->getNode());
    }
    else{
        temp_center->addLinuxList(temp_server->getNode());
    }
    return SUCCESS;
}
StatusType dataSystem::m_RequestServer(void * DS, int dataCenterID, int serverID, int os, int * assignedID) {
    if (serverID < 0 || DS == nullptr || dataCenterID <= 0 ||
        (os != 1 && os != 0) || assignedID == nullptr) {
        return INVALID_INPUT;
    }
    dataSystem *temp_ds = static_cast<dataSystem *>(DS);
    int_key temp_int_key(dataCenterID);
    if (temp_ds->int_tree.isKeyInTree(&temp_int_key) == 0) {
        return FAILURE;
    }
    DataCenter temp_data_center = temp_ds->int_tree.getDataByKey(&temp_int_key);
    if (temp_data_center->getLinuxListLast() == nullptr &&
        temp_data_center->getWindowsListLast() == nullptr) {
        return FAILURE;
    }//no free servers
    Server temp_server = temp_data_center->getServerByNum(serverID);
    if(temp_server == nullptr){
        return INVALID_INPUT;
    }
    OS curr_os = Linux;
    if (temp_server->isWindows()) {
        curr_os = Windows;
    }
    if (temp_server->isUsed() == false) {
        if (os == 1) {
            if (curr_os == Linux) {

                if (installWindows(temp_data_center, temp_server) == FAILURE) {
                    return FAILURE;
                }
                temp_data_center->removeFromLinuxList(temp_server->getNode());
            } else {
                temp_data_center->removeFromWindowsList(temp_server->getNode());
            }
            temp_server->setOS(Windows);
            temp_server->setUsed(true);
            *assignedID = serverID;
            return SUCCESS;
        }
        if (os == 0) {
            if (curr_os == Windows) {
                if (installLinux(temp_data_center, temp_server) == FAILURE) {
                    return FAILURE;
                }
                temp_data_center->removeFromWindowsList(temp_server->getNode());
            } else {
                temp_data_center->removeFromLinuxList(temp_server->getNode());
            }
            temp_server->setOS(Linux);
            temp_server->setUsed(true);
            *assignedID = serverID;
            return SUCCESS;
        }
    }
    // now server is already used
    Node temp_node = nullptr;
    if(os == Windows){
        temp_node = temp_data_center->windows_list.getLast();
        if(temp_node == nullptr){//if Linux, to Windows
            temp_node = temp_data_center->linux_list.getLast();
            int server_num = temp_node->getServerNum();
            Server first_prior = temp_data_center->getServerByNum(server_num);
            if (installWindows(temp_data_center, first_prior) == FAILURE) {
                return FAILURE;
            }
            first_prior->setUsed(true);
            first_prior->setOS(Windows);
            temp_data_center->removeFromLinuxList(temp_node);
            *assignedID = server_num;
            return SUCCESS;
        }
        //if windows, stays windows
        int server_num = temp_node->getServerNum();
        Server first_prior = temp_data_center->getServerByNum(server_num);
        first_prior->setUsed(true);
        temp_data_center->removeFromWindowsList(temp_node);
        *assignedID = server_num;
        return SUCCESS;
    }
    //if it reached here, than os=Linux
    temp_node = temp_data_center->linux_list.getLast();
    if(temp_node == nullptr){//if windows, to Linux
        temp_node = temp_data_center->windows_list.getLast();
        int server_num = temp_node->getServerNum();
        Server first_prior = temp_data_center->getServerByNum(server_num);
        if (installLinux(temp_data_center, first_prior) == FAILURE) {
            return FAILURE;
        }
        first_prior->setUsed(true);
        first_prior->setOS(Linux);
        temp_data_center->removeFromWindowsList(temp_node);
        *assignedID = server_num;
        return SUCCESS;
    }
    //if linux, stays linux
    int server_num = temp_node->getServerNum();
    Server first_prior = temp_data_center->getServerByNum(server_num);
    first_prior->setUsed(true);
    temp_data_center->removeFromLinuxList(temp_node);
    *assignedID = server_num;
    return SUCCESS;
}

StatusType dataSystem::installWindows(DataCenter data_center,Server server) {
    OS_Key temp_windows_key = data_center->getWindowsKey();
    OS_Key temp_linux_key = data_center->getLinuxKey();
    windows_tree.removeVertex(temp_windows_key);
    linux_tree.removeVertex(temp_linux_key);
    if(data_center->setWindowsKey(temp_windows_key->getOsNum()+1) == 0){
        return FAILURE;
    }
    if(data_center->setLinuxKey(temp_linux_key->getOsNum()-1) == 0){
        return FAILURE;
    }
    delete temp_windows_key;
    delete temp_linux_key;
    windows_tree.addVertex(data_center->getWindowsKey(), data_center);
    linux_tree.addVertex(data_center->getLinuxKey(), data_center);
    return SUCCESS;
}
StatusType dataSystem::installLinux(DataCenter data_center,Server server) {
    OS_Key temp_windows_key = data_center->getWindowsKey();
    OS_Key temp_linux_key = data_center->getLinuxKey();
    if(data_center->setWindowsKey(temp_windows_key->getOsNum()-1) == 0){
        return FAILURE;
    }
    if(data_center->setLinuxKey(temp_linux_key->getOsNum()+1) == 0){
        return FAILURE;
    }
    windows_tree.removeVertex(temp_windows_key);
    linux_tree.removeVertex(temp_linux_key);
    windows_tree.addVertex(data_center->getWindowsKey(), data_center);
    linux_tree.addVertex(data_center->getLinuxKey(), data_center);
    delete temp_linux_key;
    delete temp_windows_key;
    return SUCCESS;
}
StatusType dataSystem::m_GetDataCenterByOS(void * DS, int os, int ** dataCenters, int * numOfDataCenters) {
    if(DS == nullptr || dataCenters == nullptr || numOfDataCenters == nullptr || (os != 1 && os!=0)){
        return INVALID_INPUT;
    }
    dataSystem *temp_ds = static_cast<dataSystem *>(DS);
    if( temp_ds->int_tree.getRoot() == nullptr){ // tree is empty, we don't have any DATACENTERS
        return FAILURE;
    }
    *numOfDataCenters = 0;
    (temp_ds->int_tree).countInorder(numOfDataCenters, temp_ds->int_tree.getRoot());
    if(*numOfDataCenters == 0){
        return FAILURE;
    }
    *dataCenters = new int[*numOfDataCenters];
    if(os == 1){
        OS_Key* key_array = temp_ds->windows_tree.reverseInorder(*numOfDataCenters);
        for(int i=0;i<*numOfDataCenters;++i){
            (*dataCenters)[i] = key_array[i]->getKey();
        }
        delete [] key_array;
        return SUCCESS;
    }
    OS_Key* key_array = temp_ds->linux_tree.reverseInorder(*numOfDataCenters);
    for(int i=0;i<*numOfDataCenters;++i){
        (*dataCenters)[i] = key_array[i]->getKey();
    }
    delete [] key_array;
    return SUCCESS;
}
void dataSystem::Quit(void ** DS) {
    dataSystem *temp_ds = static_cast<dataSystem *>(*DS);
    delete temp_ds;
    *DS = nullptr;
}
