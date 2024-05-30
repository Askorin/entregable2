#ifndef OPEN_HASHING_MAP_H
#define OPEN_HASHING_MAP_H
#include "map.h"
#include <vector>
#include <string>
#include "data_struct.h"
#include <iostream>
#include <optional>


template<typename KeyType, typename ValueType>
class OpenHashingMap : public HashMap<KeyType, ValueType> {
private:
    //std::vector<std::vector<ValueType>> table;
    std::vector<std::vector<Entry<KeyType, ValueType>>> table;
    size_t n;

public:
    
    OpenHashingMap();

     
    /* Para username */
    std::optional<ValueType> get(KeyType key) override;

    /* Para username */
    void put(KeyType key, ValueType value) override;

    ///* Para userid */
    //void put(unsigned long long user_id, data_struct value) override;

    ///* Para username */
    ValueType remove(KeyType key) override;

    ///* Para userid */
    //data_struct remove(unsigned long long userid) override;

    size_t size() override;

    bool isEmpty() override;

};


#endif
