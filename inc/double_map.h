#ifndef HASH_DOUBLE_H
#define HASH_DOUBLE_H
#include <vector>
#include <string>
#include "../inc/data_struct.h"
#include "../inc/map.h"

class DoubleHash : public HashMap {
private:
    std::vector<data_struct> table;
    std::vector<int> mirror;

    size_t n;

    size_t d1(unsigned long long id);


public:
    enum Status 
    {
        Empty,
        Available,
        Occupied
    };

    /*Se crea vector mirror que servirá para saber si las posiciones estan vacias o disponibles.*/    
    DoubleHash();

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
