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
    std::vector<std::vector<Entry<KeyType, ValueType>>> table;

public:
    
    OpenHashingMap();

    std::optional<ValueType> get(KeyType key) override;

    std::optional<ValueType> put(KeyType key, ValueType value) override;

    ValueType remove(KeyType key) override;
};


#endif
