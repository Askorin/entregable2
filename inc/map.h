#ifndef MAP_H
#define MAP_H
#include <vector>
#include <string>
#include "data_struct.h"
#include <iostream>
#include <optional>

template<typename KeyType, typename ValueType>
struct Entry {
    KeyType key;
    ValueType value;
    Entry();
    Entry(KeyType key, ValueType val);
};

template<typename KeyType, typename ValueType>
class HashMap {
protected:
    size_t N = 19913;
    size_t hash(KeyType key);
public:

    HashMap() {};

    virtual std::optional<ValueType> get(KeyType key) = 0;

    virtual void put(KeyType key, ValueType value) = 0;

    virtual ValueType remove(KeyType key) = 0;

    virtual size_t size() = 0;

    virtual bool isEmpty() = 0;
};

#endif
