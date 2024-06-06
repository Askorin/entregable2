#include "../inc/hash_linear.h"
#include <optional>
#include <string>
#include <vector>

template <typename KeyType, typename ValueType>
HashLinear<KeyType, ValueType>::HashLinear()
    : table(this->N), mirror(this->N, Empty) {}

template <typename KeyType, typename ValueType>
std::optional<ValueType> HashLinear<KeyType, ValueType>::get(KeyType key) {
    size_t idx = this->hash(key);
    for (size_t i = 0; i < this->N; ++i) {
        if (mirror[idx] == Empty)
            break;
        else if ((mirror[idx] == Occupied) && (table[idx].key == key))
            return table[idx].value;
        idx = (idx + 1) % this->N;
    }
    return std::nullopt;
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> HashLinear<KeyType, ValueType>::put(KeyType key,
                                                             ValueType value) {

    size_t availableIdx = 0;
    bool availableFound = false;
    size_t idx = this->hash(key);
    for (size_t i = 0; i < this->N; ++i) {

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

        idx = (idx + 1) % this->N;
    }

    if (availableFound) {
        //std::cout << "Valor: \n" << value << std::endl;
        //std::cout << "En: " << availableIdx << std::endl;
        mirror[availableIdx] = Occupied;
        table[availableIdx] = Entry<KeyType, ValueType>(key, value);
        ++this->n;
    }
    return std::nullopt;
}

// template<typename KeyType, typename ValueType>
// ValueType HashLinear<KeyType, ValueType>::remove(KeyType key) {}

// data_struct HashLinear::remove(unsigned long long userid)
//{
//     size_t idx = HashMap::hashId(userid);
//
//     for (size_t p = 0; p < N; p++)
//     {
//         if(mirror[idx] == Empty)
//         {
//             data_struct empty("",0,"",0,0,0,"");
//             empty.setValid(false);
//             return empty;
//         }
//         else if ((mirror[idx] == Occupied) && (table[idx].user_id == userid))
//         {
//             data_struct tmp = table[idx];
//             mirror[idx] = Available;
//             --n;
//             return tmp;
//         }
//
//         idx = (idx + 1) % N;
//     }
// }

template class HashLinear<unsigned long long, dataStruct>;
template class HashLinear<std::string, dataStruct>;
