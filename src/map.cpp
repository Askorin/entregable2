#include "../inc/map.h"

template <typename KeyType, typename ValueType>
Entry<KeyType, ValueType>::Entry(KeyType key, ValueType value)
    : key(key), value(value) {}

template <typename KeyType, typename ValueType>
Entry<KeyType, ValueType>::Entry() : key(), value() {}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>::HashMap() : n(0) {}

template <typename KeyType, typename ValueType>
size_t HashMap<KeyType, ValueType>::multMod(unsigned long long key) {
    return size_t((18193 * key + 5618) % N);
}

template <typename KeyType, typename ValueType>
unsigned long long HashMap<KeyType, ValueType>::polyRoll(std::string key) {
    /* Calcularemos el haschode del string x_0 ... x_d como el polinomio
     * x_d * alpha ^ 0 + x_d-1 * alpha^1 ... x_0 * alpha ^d
     */

    /* Ojo que esto puede hacer overflow */

    /* Utilizamos alpha = 33 como recomendado en el ppt del curso. */
    /* se calcula de manera recursiva como: */
    size_t alpha = 33;
    unsigned long long sum = 0;

    for (auto& ch : key) {
        sum = (alpha * sum + int(ch));
    }
    return sum;
}

template <>
size_t HashMap<unsigned long long, dataStruct>::hash(unsigned long long key) {
    return multMod(key);
}

template <> size_t HashMap<std::string, dataStruct>::hash(std::string key) {
    return multMod(polyRoll(key));
}

template <typename KeyType, typename ValueType>
double HashMap<KeyType, ValueType>::getLoadFactor() {
    return double(n) / N;
}

template <typename KeyType, typename ValueType>
size_t HashMap<KeyType, ValueType>::size() {
    return n;
}

template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::isEmpty() {
    return n == 0;
}

template struct Entry<unsigned long long, dataStruct>;
template struct Entry<std::string, dataStruct>;

template class HashMap<unsigned long long, dataStruct>;
template class HashMap<std::string, dataStruct>;
