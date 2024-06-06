#ifndef QUAD_MAP_H
#define QUAD_MAP_H
#include "data_struct.h"
#include "map.h"
#include <iostream>
#include <optional>
#include <string>
#include <vector>


/*
 * Mapa derivado de HashMap implemenado a través de un std::vector de Entry's, resuelve
 * colisiones con probing cuadrático.
 */
template <typename KeyType, typename ValueType>
class QuadMap : public HashMap<KeyType, ValueType> {
  private:
    std::vector<Entry<KeyType, ValueType>> table;
    std::vector<int> mirror;

  public:
    enum Status { Empty, Available, Occupied };

    QuadMap();

    std::optional<ValueType> get(KeyType key) override;

    std::optional<ValueType> put(KeyType key, ValueType value) override;

    // ValueType remove(KeyType key) override;
};

#endif
