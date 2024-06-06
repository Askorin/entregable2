#include "../inc/double_map.h"
#include <vector>

/* Segunda función Hash */
template <> size_t DoubleHash<std::string, dataStruct>::d1(std::string key) {
    return 6827 - (this->polyRoll(key) % 6827);
}

template <>
size_t DoubleHash<unsigned long long, dataStruct>::d1(unsigned long long key) {
    return 6827 - (key % 6827);
}

template <typename KeyType, typename ValueType>
DoubleHash<KeyType, ValueType>::DoubleHash()
    : table(this->N), mirror(this->N, Empty) {}

template <typename KeyType, typename ValueType>
std::optional<ValueType> DoubleHash<KeyType, ValueType>::get(KeyType key) {
    size_t hash1 = this->hash(key);
    size_t hash2 = d1(key);
    size_t idx;

    for (size_t i = 0; i < this->N; ++i) {
        idx = (hash1 + i * hash2) % this->N;
        if (mirror[idx] == Empty)
            break;
        else if ((mirror[idx] == Occupied) && (table[idx].key == key))
            return table[idx].value;
    }
    return std::nullopt;
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> DoubleHash<KeyType, ValueType>::put(KeyType key,
                                                             ValueType value) {

    size_t hash1 = this->hash(key);
    size_t hash2 = d1(key);
    size_t idx;
    size_t availableIdx = 0;
    bool availableFound = false;
    for (size_t i = 0; i < this->N; ++i) {
        idx = (hash1 + i * hash2) % this->N;
        /* La clave ya se encuentra en el mapa, le cambiamos el valor y
         * retornamos el valor anterior. */
        if ((mirror[idx] == Occupied) && (table[idx].key == key)) {
            Entry<KeyType, ValueType> prevEntry = table[idx];
            table[idx] = Entry<KeyType, ValueType>(key, value);
            return prevEntry.value;
        }

        /*
         * Si encontramos un lugar vacío, la clave no se podría encontrar
         * repetida más adelante, entonces la insertamos acá de inmediato.
         */
        if (mirror[idx] == Empty) {
            /*
             * En verdad no es de mucha importancia ocupar el spot que haya sido
             * descubierto primero, pero mejor hacerlo así, creo?
             */
            if (!availableFound) {
                availableFound = true;
                availableIdx = idx;
            }
            break;
        }

        /*
         * Si encontramos un lugar disponible por primera vez, lo recordamos.
         * Pero seguiremos buscando, ya que puede ser que la llave se encuentre
         * más adelante, si es que más adelante terminamos de buscar o
         * encontramos Empty, la ubicaremos acá.
         */

        if (mirror[idx] == Available && !availableFound) {
            availableFound = true;
            availableIdx = idx;
        }
    }
    if (availableFound) {
        mirror[availableIdx] = Occupied;
        table[availableIdx] = Entry<KeyType, ValueType>(key, value);
        ++this->n;
    }
    return std::nullopt;
}

// template<typename KeyType, typename ValueType>
// ValueType DoubleHash<KeyType, ValueType>::remove(KeyType key) { };

// data_struct DoubleHash::remove(unsigned long long userid)
//{
//     unsigned long long hash1 = HashMap::hashId(userid);
//     unsigned long long hash2 = d1(userid);
//     unsigned long long idx = hash1;
//
//     for (size_t i = 0; i < N; i++)
//     {
//         if (mirror[idx] == Occupied && table[idx].user_id == userid)
//         {
//             mirror[idx] = Available;
//             data_struct tmp = table[idx];
//             return tmp;
//         }
//
//         idx = (hash1 + i * hash2) % N;
//
//     }
// }

template class DoubleHash<unsigned long long, dataStruct>;
template class DoubleHash<std::string, dataStruct>;
