#ifndef HASH_LINEAR_H
#define HASH_LINEAR_H
#include "../inc/data_struct.h"
#include "../inc/map.h"
#include <string>
#include <vector>

template <typename KeyType, typename ValueType>
class HashLinear : public HashMap<KeyType, ValueType> {
  private:
    std::vector<Entry<KeyType, ValueType>> table;
    std::vector<int> mirror;

  public:
    enum Status { Empty, Available, Occupied };

    HashLinear();

    std::optional<ValueType> get(KeyType key) override;

    std::optional<ValueType> put(KeyType key, ValueType value) override;

    // ValueType remove(KeyType key) override;
};

#endif
