//
// Created by Eitan on 10/12/2019.
//
#ifndef EX1_KEYS_H
#define EX1_KEYS_H

typedef class int_key{
private:
    int key_num;
public:
    explicit int_key(int input);
    bool operator<(int_key const &b);
    bool operator>(int_key const &b);
    bool operator==(int_key const&b);
    int getKey();
} *Int_Key;

typedef class os_key {
private:
    int os_num;
    int key_num;
public:
    os_key(int os_num,int key);
    os_key(const os_key& w) = default;
    ~os_key() = default;
    bool operator<(os_key const &b);
    bool operator>(os_key const &b);
    bool operator==(os_key const&b);
    int getKey();
    int getOsNum();
} *OS_Key;
#endif //EX1_KEYS_H
