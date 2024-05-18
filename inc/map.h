#ifndef MAP_H
#define MAP_H
#include <vector>
#include <string>
#include "data_struct.h"
#include <iostream>

class HashMap {
public:

    HashMap() {
    }
    /* Para username */
    virtual data_struct get(std::string username) = 0;

    /* Para userid */
    virtual data_struct get(unsigned long long user_id) = 0;

    /* Para username */
    virtual void put(std::string username, data_struct value) = 0;

    /* Para userid */
    virtual void put(unsigned long long user_id, data_struct value) = 0;

    /* Para username */
    virtual void remove(std::string username) = 0;

    /* Para userid */
    virtual void remove(unsigned long long userid) = 0;

    virtual size_t size() = 0;

    virtual bool isEmpty() = 0;
};


#endif
