#ifndef HASH_LINEAR_H
#define HASH_LINEAR_H
#include <vector>
#include <string>
#include "../inc/data_struct.h"
#include "../inc/map.h"

class HashLinear : public HashMap {
private:
    std::vector<data_struct> table;
    std::vector<int> mirror;
    size_t n;

public:
    enum Status 
    {
        Empty,
        Available,
        Occupied
    };

    /*Se crea vector mirror que servirá para saber si las posiciones estan vacias o disponibles.*/    
    HashLinear();

    unsigned long long h1(unsigned long long user_id);

    data_struct get(std::string username) override;

    data_struct get(unsigned long long userId) override;

    void put(std::string username, data_struct value) override;

    void put(unsigned long long userid, data_struct value) override;

    data_struct remove(std::string username) override;

    data_struct remove(unsigned long long userid) override;

    size_t size() override;

    bool isEmpty() override;

};

#endif
