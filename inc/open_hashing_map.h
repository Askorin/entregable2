#ifndef OPEN_HASHING_MAP_H
#define OPEN_HASHING_MAP_H
#include "data_struct.h"
#include "map.h"
#include <iostream>
#include <optional>
#include <string>
#include <vector>

template <typename KeyType, typename ValueType>
class OpenHashingMap : public HashMap<KeyType, ValueType> {
  private:
    std::vector<std::vector<Entry<KeyType, ValueType>>> table;

  public:
    OpenHashingMap();

    std::optional<ValueType> get(KeyType key) override;

    std::optional<ValueType> put(KeyType key, ValueType value) override;

    std::vector<std::vector<Entry<KeyType, ValueType>>> getTable();

    size_t getCap();

    // ValueType remove(KeyType key) override;
};

#endif
