#ifndef QUAD_MAP_H
#define QUAD_MAP_H
#include "map.h"
#include <vector>
#include <string>
#include "data_struct.h"
#include <iostream>
#include <optional>



template<typename KeyType, typename ValueType>
class QuadMap : public HashMap<KeyType, ValueType> {
private:
    std::vector<Entry<KeyType, ValueType>> table;
    std::vector<int> mirror;

public:
    enum Status 
    {
        Empty,
        Available,
        Occupied
    };

    QuadMap();

    std::optional<ValueType> get(KeyType key) override;

    std::optional<ValueType> put(KeyType key, ValueType value) override;

    ValueType remove(KeyType key) override;
};

#endif
