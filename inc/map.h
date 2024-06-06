#ifndef MAP_H
#define MAP_H
#include "data_struct.h"
#include <iostream>
#include <optional>
#include <string>
#include <vector>

template <typename KeyType, typename ValueType> struct Entry {
    KeyType key;
    ValueType value;
    Entry();
    Entry(KeyType key, ValueType val);
};

template <typename KeyType, typename ValueType> class HashMap {
  protected:
    size_t N = 19913;
    size_t n;
    size_t hash(KeyType key);
    size_t multMod(unsigned long long key);
    unsigned long long polyRoll(std::string key);

  public:
    HashMap();

    virtual std::optional<ValueType> get(KeyType key) = 0;

    virtual std::optional<ValueType> put(KeyType key, ValueType value) = 0;

    // virtual ValueType remove(KeyType key) = 0;
    //

    size_t getMaxCapacity();

    size_t size();

    bool isEmpty();

    /* Para profiling más que nada. */
    double getLoadFactor();
};

#endif
