#ifndef MAP_H
#define MAP_H
#include <vector>
#include <string>
#include "data_struct.h"
#include <iostream>

/* Implementación de un hashmap a través de arreglo open-hashing */
class HashMap {
private:

    // Función de hasheo para user_id
    size_t h1(unsigned long long user_id) {
        return 0;
    }

    // Función de hasheo para username
    size_t h2(std::string username) {
        return 0;
    }
public:
    std::vector<data_struct> Tabla;
    HashMap() {
        this->Tabla = std::vector<data_struct>(20, data_struct("na", 0, "na", 0, 0, 0, "na"));
    }
    
    unsigned long long hashFunction(std::string user_id) {

       size_t m = 49157, a = 45382, b = 11923;
    
       unsigned long long userid = std::stoull(user_id);

       return (a * userid + b) % m;
    }

    data_struct get(std::string username) {
        size_t idx = h2(username);
        return Tabla[idx];
    }

    data_struct get(unsigned long long user_id) {
        size_t idx = h1(user_id);
        return Tabla[idx];
    }

    void put(std::string username, data_struct value) {
        size_t idx = h2(username);
    }

    void put(unsigned long long user_id, data_struct value) {
        size_t idx = h1(user_id);
    }

    

    
};

class HashMapLinear : public HashMap {

HashMapLinear(){}

data_struct get(std::string userId) {
        unsigned long long idx = hashFunction(userId), p;
        size_t m = 49157;

        for ( p = 0; p < m; p++) {
            if() {

            }
        }
        
    }


data_struct put(std::string userId, data_struct value) {
    unsigned long long idx = hashFunction(userId);

}

};


#endif
