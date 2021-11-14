//
// Created by Eitan on 10/12/2019.
//

#include "DataCenter.h"
#include <iostream>
using std::cout;
using std::endl;

int main() {
    DataCenter data_center1 = new dataCenter(dataCenter(2,20));
    cout << "check 1: key:" << data_center1->getKey() << endl;
    cout << "check 2: servers:" << data_center1->getNum() << endl;
    cout << "check 3: linux:" << data_center1->getLinuxNum() << endl;
    cout << "check 4: windows:" << data_center1->getWindowsNum() << endl;
    cout << "check 5: linux key:" << data_center1->getLinuxKey()->getKey() << "," << data_center1->getLinuxKey()->getOsNum() << endl;
    cout << "check 6: windows key:" << data_center1->getWindowsKey()->getKey() << "," << data_center1->getWindowsKey()->getOsNum() << endl;
    cout << "check 7: key:" << data_center1->getIntKey()->getKey() << endl;
    data_center1->getServerByNum(13)->setUsed(true);
    data_center1->getServerByNum(18)->setOS(Windows);
    cout << "check 8: Servers:" << endl;
    for(int i=0;i<data_center1->getNum();i++){
        cout << data_center1->getServerByNum(i)->getnum() << "," << data_center1->getServerByNum(i)->isWindows() << "," << data_center1->getServerByNum(i)->isUsed() << endl;
    }
}