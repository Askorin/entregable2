#include "../inc/open_hashing_map.h"
#include <optional>


template<typename KeyType, typename ValueType>
OpenHashingMap<KeyType, ValueType>::OpenHashingMap() :
    table(std::vector(this->N, std::vector<Entry<KeyType, ValueType>>())) {}

template<typename KeyType, typename ValueType>
std::optional<ValueType> OpenHashingMap<KeyType, ValueType>::get(KeyType key) {
    size_t idx = this->hash(key);
    for (size_t i = 0; i < table[idx].size(); ++i) {
        if (table[idx][i].key == key) return table[idx][i].value;
    }
    return std::nullopt;
}

template<typename KeyType, typename ValueType>
std::optional<ValueType> OpenHashingMap<KeyType, ValueType>::put(KeyType key, ValueType value) {
    size_t idx = this->hash(key);
    for (size_t i = 0; i < table[idx].size(); ++i) {
        if (table[idx][i].key == key) {
            Entry<KeyType, ValueType> prevEntry = table[idx][i];
            table[idx][i] = Entry<KeyType, ValueType>(key, value);
            return prevEntry.value;
        }
    }
    table[idx].push_back(Entry<KeyType, ValueType>(key, value));
    ++this->n;
    return std::nullopt;
}


template<typename KeyType, typename ValueType>
std::vector<std::vector<Entry<KeyType, ValueType>>> OpenHashingMap<KeyType, ValueType>::getTable() {
    return table;
}


template<typename KeyType, typename ValueType>
size_t OpenHashingMap<KeyType, ValueType>::getCap() {
    size_t cap = 0;
    for (auto& chain : table) {
        cap += chain.capacity();
    }
    return cap;
}



//template<typename KeyType, typename ValueType>
//ValueType OpenHashingMap<KeyType, ValueType>::remove(KeyType key) {}

//data_struct OpenHashingMap::remove(std::string username) {
//    size_t idx = HashMap::hashUsername(username);
//
//    for (size_t i = 0; i < table[idx].size(); ++i) {
//        data_struct valor = table[idx][i];
//        if (valor.username == username) {
//            table[idx].erase(table[idx].begin() + i);
//            --n;
//            return valor;
//        }
//    }
//
//    data_struct retVal("", 0, "", 0, 0, 0, "");
//    retVal.setValid(false);
//    return retVal;
//};
//
///* Para userid */
//data_struct OpenHashingMap::remove(unsigned long long userid) {
//    size_t idx = HashMap::hashId(userid);
//
//    for (size_t i = 0; i < table[idx].size(); ++i) {
//        data_struct valor = table[idx][i];
//        if (valor.user_id == userid) {
//            table[idx].erase(table[idx].begin() + i);
//            --n;
//            return valor;
//        }
//    }
//
//    data_struct retVal("", 0, "", 0, 0, 0, "");
//    retVal.setValid(false);
//    return retVal;
//
//};




template class OpenHashingMap<unsigned long long, data_struct>;
template class OpenHashingMap<std::string, data_struct>;
