#ifndef HASH_LINEAR_H
#define HASH_LINEAR_H
#include <vector>
#include <string>
#include "../inc/data_struct.h"
#include "../inc/map.h"

template<typename KeyType, typename ValueType>
class HashLinear : public HashMap<KeyType, ValueType> {
private:
    std::vector<Entry<KeyType, ValueType>> table;
    std::vector<int> mirror;

    size_t n;

public:
    enum Status 
    {
        Empty,
        Available,
        Occupied
    };

    HashLinear();

    std::optional<ValueType> get(KeyType key) override;
    /* Para username */
    void put(KeyType key, ValueType value) override;

    ///* Para username */
    ValueType remove(KeyType key) override;

    size_t size() override;

    bool isEmpty() override;

};

#endif
