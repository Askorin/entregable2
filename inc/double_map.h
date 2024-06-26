#ifndef HASH_DOUBLE_H
#define HASH_DOUBLE_H
#include "../inc/data_struct.h"
#include "../inc/map.h"
#include <string>
#include <vector>

/*
 * Mapa derivado de HashMap implemenado a través de un std::vector de Entry's, resuelve
 * colisiones con doble hashing
 */
template <typename KeyType, typename ValueType>
class DoubleHash : public HashMap<KeyType, ValueType> {
  private:
    std::vector<Entry<KeyType, ValueType>> table;
    std::vector<int> mirror;

    /* Segunda función de hasheo para resolver colisiones */
    size_t d1(KeyType key);

  public:
    enum Status { Empty, Available, Occupied };

    DoubleHash();

    std::optional<ValueType> get(KeyType key) override;

    std::optional<ValueType> put(KeyType key, ValueType value) override;

    // ValueType remove(KeyType key) override;
};

#endif
