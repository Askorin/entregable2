#ifndef MAP_H
#define MAP_H
#include <vector>
#include <string>
#include "data_struct.h"
#include <iostream>



/* Implementación de un hashmap a través de arreglo open-hashing */
class HashMap {
private:
    std::vector<data_struct> arr;

    // Función de hasheo para user_id
    size_t h1(unsigned long long user_id) {
        return 0;
    }

    // Función de hasheo para username
    size_t h2(std::string username) {
        return 0;
    }
public:
    HashMap() {
        this->arr = std::vector<data_struct>(20, data_struct("na", 0, "na", 0, 0, 0, "na"));
    }

    data_struct get(std::string username) {
        size_t idx = h2(username);
        return arr[idx];
    }

    data_struct get(unsigned long long user_id) {
        size_t idx = h1(user_id);
        return arr[idx];
    }

    void put(std::string username, data_struct value) {
        size_t idx = h2(username);
    }

    void put(unsigned long long user_id, data_struct value) {
        size_t idx = h1(user_id);
    }

    
};


#endif
