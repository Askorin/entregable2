#ifndef QUAD_MAP_H
#define QUAD_MAP_H
#include "map.h"
#include <vector>
#include <string>
#include "data_struct.h"
#include <iostream>



class QuadMap : public HashMap {
private:
    std::vector<data_struct> table;
    std::vector<int> mirror;
    // Función de hasheo para username
    size_t hashUsername(std::string username);

    // Función de hasheo para username
    size_t hashId(unsigned long long id);


    size_t n;

public:
    enum Status 
    {
        Empty,
        Available,
        Occupied
    };

    QuadMap();

    /* Para username */
    data_struct get(std::string username) override;

    /* Para userid */
    data_struct get(unsigned long long user_id) override;

    /* Para username */
    void put(std::string username, data_struct value) override;

    /* Para userid */
    void put(unsigned long long user_id, data_struct value) override;

    /* Para username */
    data_struct remove(std::string username) override;

    /* Para userid */
    data_struct remove(unsigned long long userid) override;

    size_t size() override;

    bool isEmpty() override;

};

#endif
