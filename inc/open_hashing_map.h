#ifndef OPEN_HASHING_MAP_H
#define OPEN_HASHING_MAP_H
#include "data_struct.h"
#include "map.h"
#include <iostream>
#include <optional>
#include <string>
#include <vector>

/*
 * Mapa derivado de HashMap implemenado a través de encadenamiento separado,
 * con std::vector
 */
template <typename KeyType, typename ValueType>
class OpenHashingMap : public HashMap<KeyType, ValueType> {
  private:
    /* La tabla guarda "cadenas", vectores que albergan las Entry's. */
    std::vector<std::vector<Entry<KeyType, ValueType>>> table;

  public:
    OpenHashingMap();

    std::optional<ValueType> get(KeyType key) override;

    std::optional<ValueType> put(KeyType key, ValueType value) override;

    /* Retorna la table, ya no está en uso. */
    std::vector<std::vector<Entry<KeyType, ValueType>>> getTable();

    /* Método auxiliar, retorna el total de espacio reservado para Entry's */
    size_t getCap();

    // ValueType remove(KeyType key) override;
};

#endif
