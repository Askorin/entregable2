#ifndef HASH_DOUBLE_H
#define HASH_DOUBLE_H
#include "../inc/map.h"
#include <vector>
#include <string>
#include "../inc/data_struct.h"

template<typename KeyType, typename ValueType>
class DoubleHash : public HashMap<KeyType, ValueType> {
private:
    std::vector<Entry<KeyType, ValueType>> table;
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

    DoubleHash();

    std::optional<ValueType> get(KeyType key) override;
    void put(KeyType key, ValueType value) override;

    ValueType remove(KeyType key) override;

    size_t size() override;

    bool isEmpty() override;

};

#endif
