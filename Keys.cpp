//
// Created by Eitan on 10/12/2019.
//

#include "Keys.h"
os_key::os_key(int os_num, int key) : os_num(os_num),key_num(key) {}
bool os_key:: operator<(os_key const &b) {
    if(this->os_num == b.os_num) {
        return (this->key_num > b.key_num);
    }
    return this->os_num < b.os_num;
}
bool os_key::operator>(os_key const &b) {
    if(this->os_num == b.os_num) {
        return (this->key_num < b.key_num);
    }
    return this->os_num > b.os_num;
}
bool os_key::operator == (os_key const&b){
    return (this->key_num == b.key_num);
}
int os_key::getKey() {
    return key_num;
}
int os_key::getOsNum() {
    return os_num;
}
int_key::int_key(int input):key_num(input) {}
bool int_key::operator<(int_key const &b) {
    return this->key_num < b.key_num;
}
bool int_key::operator>(int_key const &b) {
    return this->key_num > b.key_num;
}
bool int_key::operator==(int_key const&b){
    return (this->key_num == b.key_num);
}
int int_key::getKey() {
    return key_num;
}
