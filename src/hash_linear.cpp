#include <optional>
#include <vector>
#include <string>
#include "../inc/hash_linear.h"


template<typename KeyType, typename ValueType>
HashLinear<KeyType, ValueType>::HashLinear() : 
    table(this->N), mirror(this->N, Empty) { }



template<typename KeyType, typename ValueType>
std::optional<ValueType> HashLinear<KeyType, ValueType>::get(KeyType key) {
    size_t idx = this->hash(key);
    for (size_t i = 0; i < this->N; ++i) {
        if (mirror[idx] == Empty) break;
        else if ((mirror[idx] == Occupied) && (table[idx].key == key)) return table[idx].value;
        idx = (idx + 1) % this->N;
    }
    return std::nullopt;
}

template<typename KeyType, typename ValueType>
std::optional<ValueType> HashLinear<KeyType, ValueType>::put(KeyType key, ValueType value) {
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
        idx = (idx + 1) % this->N;
    }
    return std::nullopt;
}


template<typename KeyType, typename ValueType>
ValueType HashLinear<KeyType, ValueType>::remove(KeyType key) {}


//data_struct HashLinear::remove(unsigned long long userid) 
//{
//    size_t idx = HashMap::hashId(userid);
//
//    for (size_t p = 0; p < N; p++)
//    {
//        if(mirror[idx] == Empty)
//        {
//            data_struct empty("",0,"",0,0,0,"");
//            empty.setValid(false);
//            return empty;
//        }
//        else if ((mirror[idx] == Occupied) && (table[idx].user_id == userid))
//        {
//            data_struct tmp = table[idx];
//            mirror[idx] = Available;
//            --n;
//            return tmp;
//        }
//
//        idx = (idx + 1) % N;
//    }
//}

template class HashLinear<unsigned long long, data_struct>;
template class HashLinear<std::string, data_struct>;
