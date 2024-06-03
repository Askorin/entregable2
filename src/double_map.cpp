#include <vector>
#include "../inc/double_map.h"

//Segunda función Hash, con q un numero primo.
/* TODO: Redifinir para manejar genericos y weas */
template<typename KeyType, typename ValueType>
size_t DoubleHash<KeyType, ValueType>::d1(unsigned long long id) { 
    int q = 6827; 
    return q - (id % q);
}


template<typename KeyType, typename ValueType>
DoubleHash<KeyType, ValueType>::DoubleHash() : 
    table(this->N), mirror(this->N, Empty) { }



template<typename KeyType, typename ValueType>
std::optional<ValueType> DoubleHash<KeyType, ValueType>::get(KeyType key) {
    size_t hash1 = this->hash(key);
    size_t hash2 = d1(this->hash(key));
    size_t idx;

    for (size_t i = 0; i < this->N; ++i) {
        idx = (hash1 + i*hash2) % this->N;
        if (mirror[idx] == Empty) break;
        else if ((mirror[idx] == Occupied) && (table[idx].key == key)) return table[idx].value;
    }
    return std::nullopt;
}

template<typename KeyType, typename ValueType>
std::optional<ValueType> DoubleHash<KeyType, ValueType>::put(KeyType key, ValueType value) {


    /* Esto es más o menos ineficiente, pero funciona */
    std::optional<ValueType> find = get(key);
    /* La clave ya se encuentra ingresada. */
    if (find) {
        return find.value();
    }

    size_t hash1 = this->hash(key);
    size_t hash2 = d1(this->hash(key));
    size_t idx;

    for (size_t i = 0; i < this->N; ++i) {
        idx = (hash1 + i * hash2) % this->N;
        if ((mirror[idx] == Empty) || (mirror[idx] == Available)) {
            table[idx] = Entry<KeyType, ValueType>(key, value);
            mirror[idx] = Occupied;
            ++this->n;
            break;
        }
    }
    return std::nullopt;
}

//template<typename KeyType, typename ValueType>
//ValueType DoubleHash<KeyType, ValueType>::remove(KeyType key) { };

//data_struct DoubleHash::remove(unsigned long long userid)
//{
//    unsigned long long hash1 = HashMap::hashId(userid);
//    unsigned long long hash2 = d1(userid);
//    unsigned long long idx = hash1;
//
//    for (size_t i = 0; i < N; i++) 
//    {
//        if (mirror[idx] == Occupied && table[idx].user_id == userid) 
//        {
//            mirror[idx] = Available;
//            data_struct tmp = table[idx];
//            return tmp;
//        }
//        
//        idx = (hash1 + i * hash2) % N;
//
//    }
//}


template class DoubleHash<unsigned long long, data_struct>;
template class DoubleHash<std::string, data_struct>;
