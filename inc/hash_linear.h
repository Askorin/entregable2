#ifndef HASH_LINEAR_H
#define HASH_LINEAR_H
#include "../inc/data_struct.h"
#include "../inc/map.h"
#include <string>
#include <vector>

/*
 * Mapa derivado de HashMap implemenado a través de un std::vector de Entry's, resuelve
 * colisiones con probing lineal.
 */
template <typename KeyType, typename ValueType>
class HashLinear : public HashMap<KeyType, ValueType> {
  private:
    std::vector<Entry<KeyType, ValueType>> table;
    /* Este vector guarda disponibilidades, con el enumerador Status */
    std::vector<int> mirror;

  public:
    /* Enumerador para llevar registro de la disponibilidad de un bucket. */
    enum Status { Empty, Available, Occupied };

    HashLinear();

    std::optional<ValueType> get(KeyType key) override;

    std::optional<ValueType> put(KeyType key, ValueType value) override;

    // ValueType remove(KeyType key) override;
};

#endif
