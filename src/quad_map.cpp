#include "../inc/quad_map.h"
#include <optional>



template<typename KeyType, typename ValueType>
QuadMap<KeyType, ValueType>::QuadMap() : 
    table(this->N), mirror(this->N, Empty) { }


template<typename KeyType, typename ValueType>
std::optional<ValueType> QuadMap<KeyType, ValueType>::get(KeyType key) {
    size_t idx = this->hash(key);
    for (size_t i = 1; i < this->N; ++i) {
        if (mirror[idx] == Empty) break;
        else if ((mirror[idx] == Occupied) && (table[idx].key == key)) return table[idx].value;
        idx = (idx + 2 * i - 1) % this->N;
    }
    return std::nullopt;
}

template<typename KeyType, typename ValueType>
std::optional<ValueType> QuadMap<KeyType, ValueType>::put(KeyType key, ValueType value) {
    size_t availableIdx = 0;
    bool availableFound = false;
    size_t idx = this->hash(key);
    for (size_t i = 1; i < this->N; ++i) {
        /* La clave ya se encuentra en el mapa, le cambiamos el valor y retornamos el valor anterior. */
        if ((mirror[idx] == Occupied) && (table[idx].key == key)) {
            Entry<KeyType, ValueType> prevEntry = table[idx];
            table[idx] = Entry<KeyType, ValueType>(key, value);
            return prevEntry.value;
        }

        /* 
         * Si encontramos un lugar vacío, la clave no se podría encontrar repetida más adelante,
         * entonces la insertamos acá de inmediato.
         */
        if (mirror[idx] == Empty) {
            /* 
             * En verdad no es de mucha importancia ocupar el spot que haya sido descubierto primero,
             * pero mejor hacerlo así, creo?
             */
            if (!availableFound) {
                availableFound = true;
                availableIdx = idx;
            }
            break;
        }

        /*
         * Si encontramos un lugar disponible, lo recordamos. Pero seguiremos buscando, ya que
         * puede ser que la llave se encuentre más adelante, si es que más adelante terminamos de 
         * buscar o encontramos Empty, la ubicaremos acá.
         */
        if (mirror[idx] == Available) {
            availableFound = true;
            availableIdx = idx;
        }

        idx = (idx + 2 * i - 1) % this->N;
    }
    if (availableFound) {
        mirror[availableFound] = Occupied;
        table[availableIdx] = Entry<KeyType, ValueType>(key, value);
        ++this->n;
    }
    return std::nullopt;
}


//template<typename KeyType, typename ValueType>
//ValueType QuadMap<KeyType, ValueType>::remove(KeyType key) {}

///* Para userid */
//data_struct QuadMap::remove(unsigned long long user_id) {
//    size_t idx = HashMap::hashId(user_id);
//    data_struct returnValue("", 0, "", 0, 0, 0, "");
//    returnValue.setValid(false);
//
//    for (size_t i = 0; i < N; i++) {
//        if (mirror[idx] == Empty) {
//            break;
//        } else if ((mirror[idx] == Occupied) && (table[idx].user_id == user_id)) {
//            returnValue = table[idx];
//            returnValue.setValid(true);
//            mirror[idx] = Available;
//            --n;
//            break;
//        }
//        idx = (idx + 2 * i + 1) % N;
//    }
//    
//    return returnValue;
//};


template class QuadMap<unsigned long long, data_struct>;
template class QuadMap<std::string, data_struct>;
