#include "../inc/map.h"



template<typename KeyType, typename ValueType>
Entry<KeyType, ValueType>::Entry(KeyType key, ValueType value) : key(key), value(value) { };


template<typename KeyType, typename ValueType>
Entry<KeyType, ValueType>::Entry() : key(), value() { };

/* TODO: Ver una manera de reservar memoria sin constructores default para los mapas. */
//template<>
//Entry<std::string, data_struct>::Entry(std::string key, data_struct value) :
//    key(""), value(data_struct("", 0, "", 0, 0, 0, "")) {}
//
//template<>
//Entry<unsigned long long, data_struct>::Entry(unsigned long long key, data_struct value) :
//    key(0), value(data_struct("", 0, "", 0, 0, 0, "")) {}



//template<typename KeyType, typename ValueType>
//size_t HashMap<KeyType, ValueType>::hash(KeyType key) {
//    unsigned long long k = 0;
//    if constexpr (std::is_same_v<KeyType, unsigned long long>) {
//        k = key;
//    } else if constexpr (std::is_same_v<KeyType, std::string>) {
//        /* Calcularemos el haschode del string x_0 ... x_d como el polinomio
//         * x_d * alpha ^ 0 + x_d-1 * alpha^1 ... x_0 * alpha ^d
//         */
//
//        /* Ojo que esto puede hacer overflow */
//
//        /* Utilizamos alpha = 33 como recomendado en el ppt del curso. */
//        /* se calcula de manera recursiva como: */
//        size_t alpha = 33;
//        unsigned long long k = 0;
//        
//        for (auto &ch : key) {
//            k = (alpha * k + int(ch));
//        }
//    } else {
//        return 0;
//    }
//    /* mult mod prime con a, b menores a m (tamaño de la tabla, número primo, quizás). */
//
//    /* Para N ~ 40000 */
//    // size_t a = 45382, b = 11923;
//
//    /* Para N ~ 20000*/
//
//    size_t a = 18193, b = 5618;
//    return size_t((a * k + b) % N);
//}



template<>
size_t HashMap<unsigned long long, data_struct>::hash(unsigned long long key) {
    size_t a = 18193, b = 5618;
    return size_t((a * key + b) % N);
}

template<>
size_t HashMap<std::string, data_struct>::hash(std::string key) {
    /* Calcularemos el haschode del string x_0 ... x_d como el polinomio
    * x_d * alpha ^ 0 + x_d-1 * alpha^1 ... x_0 * alpha ^d
    */

    /* Ojo que esto puede hacer overflow */

    /* Utilizamos alpha = 33 como recomendado en el ppt del curso. */
    /* se calcula de manera recursiva como: */
    size_t alpha = 33;
    unsigned long long sum = 0;

    for (auto &ch : key) {
        sum = (alpha * sum + int(ch));
    }

    size_t a = 18193, b = 5618;
    return size_t((a * sum + b) % N);
}

template struct Entry<unsigned long long, data_struct>;
template struct Entry<std::string, data_struct>;

template class HashMap<unsigned long long, data_struct>;
template class HashMap<std::string, data_struct>;

