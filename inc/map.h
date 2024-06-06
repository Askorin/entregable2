#ifndef MAP_H
#define MAP_H
#include "data_struct.h"
#include <iostream>
#include <optional>
#include <string>
#include <vector>


/*
 * Clase Entry que alberga tuplas (llave, valor). Para uso en HashMaps.
 */
template <typename KeyType, typename ValueType> struct Entry {
    KeyType key;
    ValueType value;
    Entry();
    Entry(KeyType key, ValueType val);
};



/*
 * Clase base de un HashMap. Tiene soporte para llaves uint64 y string.
 */
template <typename KeyType, typename ValueType> class HashMap {
  protected:
    /* Bucket size hardcodeado a un número primo apto */
    size_t N = 19913;
    /* Cantidad de elementos ingresados al mapa. */
    size_t n;
    /* Método que permite hashear una llave */
    size_t hash(KeyType key);
    /* Función multmod, para hashear uint64 */
    size_t multMod(unsigned long long key);
    /* Función de acumulación polinomial, para hashear strings */
    unsigned long long polyRoll(std::string key);

  public:
    HashMap();

    /* Método get(), se comporta según la ADT del curso, con std::optional. */
    virtual std::optional<ValueType> get(KeyType key) = 0;

    /* Método put(), se comporta según la ADT del curso, con std::optional. */
    virtual std::optional<ValueType> put(KeyType key, ValueType value) = 0;

    // virtual ValueType remove(KeyType key) = 0;
    //

    /* Método getter para N */
    size_t getMaxCapacity();

    /* Método getter para n */
    size_t size();

    bool isEmpty();

    /* Retorna el factor de carga del mapa. */
    double getLoadFactor();
};

#endif
