#include "../inc/quad_map.h"
#include <cmath>


QuadMap::QuadMap() : table(N, data_struct("", 0, "", 0, 0, 0, "")), mirror(N, Empty), n(0) { }

data_struct QuadMap::get(std::string username) {
    size_t idx = HashMap::hashUsername(username);
    data_struct returnValue("", 0, "", 0, 0, 0, "");
    returnValue.setValid(false);

    for (size_t i = 0; i < N; i++) {
        if (mirror[idx] == Empty) {
            break;
        } else if ((mirror[idx] == Occupied) && (table[idx].username == username)) {
            returnValue = table[idx];
            returnValue.setValid(true);
            break;
        }
        idx = (idx + 2 * i + 1) % N;
    }
    
    return returnValue;
}

/* Para userid */
data_struct QuadMap::get(unsigned long long user_id) {
    size_t idx = HashMap::hashId(user_id);
    data_struct returnValue("", 0, "", 0, 0, 0, "");
    returnValue.setValid(false);

    for (size_t i = 0; i < N; i++) {

        if (mirror[idx] == Empty) {
            break;
        } else if ((mirror[idx] == Occupied) && (table[idx].user_id == user_id)) {
            returnValue = table[idx];
            returnValue.setValid(true);
            break;
        }
        idx = (idx + 2 * i + 1) % N;
    }
    
    return returnValue;

}

/* Para username */
void QuadMap::put(std::string username, data_struct value) {

    /* Esto es más o menos ineficiente, pero funciona */
    data_struct elem = get(username);
    
    /* 
     * En este caso la clave ya estaba ingresada en el mapa, por ahora
     * no modificaremos su valor ni nada, solo la devolveremos.
     */
    if (elem.valid) {
        return;
    }

    /* 
     * En caso contrario, nos aseguramos de que la clave no está duplicada,
     * podemos explorar dónde colocarla.
     */

    size_t idx = HashMap::hashUsername(username);

    for (size_t i = 0; i < N; i++) {
        if ((mirror[idx] == Empty) || (mirror[idx] == Available)) {
            table[idx] = value;
            mirror[idx] = Occupied;
            ++n;
            break;
        }
        idx = (idx + 2 * i + 1) % N;
    }
};

/* Para userid */
void QuadMap::put(unsigned long long user_id, data_struct value) {
    /* Esto es más o menos ineficiente, pero funciona */
    data_struct elem = get(user_id);
    
    /* 
     * En este caso la clave ya estaba ingresada en el mapa, por ahora
     * no modificaremos su valor ni nada, solo la devolveremos.
     */
    if (elem.valid) {
        return;
    }

    /* 
     * En caso contrario, nos aseguramos de que la clave no está duplicada,
     * podemos explorar dónde colocarla.
     */

    size_t idx = HashMap::hashId(user_id);

    for (size_t i = 0; i < N; i++) {
        if ((mirror[idx] == Empty) || (mirror[idx] == Available)) {
            table[idx] = value;
            mirror[idx] = Occupied;
            ++n;
            break;
        }
        idx = (idx + 2 * i + 1) % N;
    }
        
};

/* Para username */
data_struct QuadMap::remove(std::string username) {
    size_t idx = HashMap::hashUsername(username);
    data_struct returnValue("", 0, "", 0, 0, 0, "");
    returnValue.setValid(false);

    for (size_t i = 0; i < N; i++) {
        if (mirror[idx] == Empty) {
            break;
        } else if ((mirror[idx] == Occupied) && (table[idx].username == username)) {
            returnValue = table[idx];
            returnValue.setValid(true);
            mirror[idx] = Available;
            --n;
            break;
        }
        idx = (idx + 2 * i + 1) % N;
    }
    
    return returnValue;

};

/* Para userid */
data_struct QuadMap::remove(unsigned long long user_id) {
    size_t idx = HashMap::hashId(user_id);
    data_struct returnValue("", 0, "", 0, 0, 0, "");
    returnValue.setValid(false);

    for (size_t i = 0; i < N; i++) {
        if (mirror[idx] == Empty) {
            break;
        } else if ((mirror[idx] == Occupied) && (table[idx].user_id == user_id)) {
            returnValue = table[idx];
            returnValue.setValid(true);
            mirror[idx] = Available;
            --n;
            break;
        }
        idx = (idx + 2 * i + 1) % N;
    }
    
    return returnValue;
};

size_t QuadMap::size() {
    return n;
};

bool QuadMap::isEmpty() {
    return n == 0;
}
