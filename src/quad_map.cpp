#include "../inc/quad_map.h"
#include <optional>



template<typename KeyType, typename ValueType>
QuadMap<KeyType, ValueType>::QuadMap() : 
    table(this->N), mirror(this->N, Empty) { }


template<typename KeyType, typename ValueType>
std::optional<ValueType> QuadMap<KeyType, ValueType>::get(KeyType key) {
    size_t idx = this->hash(key);
    for (size_t i = 0; i < this->N; ++i) {
        if (mirror[idx] == Empty) break;
        else if ((mirror[idx] == Occupied) && (table[idx].key == key)) return table[idx].value;
        idx = (idx + 2 * i + 1) % this->N;
    }
    return std::nullopt;
}

template<typename KeyType, typename ValueType>
std::optional<ValueType> QuadMap<KeyType, ValueType>::put(KeyType key, ValueType value) {
    /* Esto es más o menos ineficiente, pero funciona */
    std::optional<ValueType> find = get(key);
    /* La clave ya se encuentra ingresada. */
    if (find) {
        return find.value();
    }
    
    size_t idx = this->hash(key);
    for (size_t i = 0; i < this->N; ++i) {
        if ((mirror[idx] == Empty) || (mirror[idx] == Available)) {
            table[idx] = Entry<KeyType, ValueType>(key, value);
            mirror[idx] = Occupied;
            ++this->n;
            break;
        }
        idx = (idx + 2 * i + 1) % this->N;
    }
    return std::nullopt;
}


template<typename KeyType, typename ValueType>
ValueType QuadMap<KeyType, ValueType>::remove(KeyType key) {}

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
