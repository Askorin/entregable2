#include "../inc/quad_map.h"
#include <cmath>


size_t QuadMap::hashUsername(std::string username) {
    /* Calcularemos el haschode del string x_0 ... x_d como el polinomio
     * x_d * alpha ^ 0 + x_d-1 * alpha^1 ... x_0 * alpha ^d
     */

    /* Ojo que esto puede hacer overflow */

    /* Utilizamos alpha = 33 como recomendado en el ppt del curso. */
    /* se calcula de manera recursiva como: */
    size_t alpha = 33;
    unsigned long long sum = 0;
    
    for (auto &ch : username) {
        sum = (alpha * sum + (int) ch);
    }


    /* mult mod prime con a, b menores a m (tamaño de la tabla, número primo, quizás). */
    size_t a = 45382, b = 11923;
    
    return (a * sum + b) % N;

}

size_t QuadMap::hashId(unsigned long long id) {
    /* mult mod prime con a, b menores a m (tamaño de la tabla, número primo, quizás). */
    size_t a = 45382, b = 11923;
    
    return (a * id + b) % N;

}

QuadMap::QuadMap() : table(49157, data_struct("", 0, "", 0, 0, 0, "")), mirror(49157, Empty), n(0) { }

data_struct QuadMap::get(std::string username) {
    size_t idx = hashUsername(username);
    data_struct returnValue("", 0, "", 0, 0, 0, "");
    returnValue.setValid(false);

    for (int i = 0; i < N; i++) {
        size_t newIdx = (idx + size_t(pow(i, 2))) % N;
        if (mirror[newIdx] == Empty) {
            break;
        } else if ((mirror[newIdx] == Occupied) & (table[newIdx].username == username)) {
            returnValue = table[newIdx];
            returnValue.setValid(true);
            break;
        }
    }
    
    return returnValue;
}

/* Para userid */
data_struct QuadMap::get(unsigned long long user_id) {
    size_t idx = hashId(user_id);
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

    size_t idx = hashUsername(username);

    for (int i = 0; i < N; i++) {
        size_t newIdx = (idx + size_t(pow(i, 2))) % N;
        if ((mirror[newIdx] == Empty) || (mirror[newIdx] == Available)) {
            table[newIdx] = value;
            mirror[newIdx] = Occupied;
            ++n;
            break;
        }
        
    }
    

};

/* Para userid */
void QuadMap::put(unsigned long long user_id, data_struct value) {
    size_t idx = hashId(user_id);
};

/* Para username */
data_struct QuadMap::remove(std::string username) {
    size_t idx = hashUsername(username);
    data_struct returnValue("", 0, "", 0, 0, 0, "");
    returnValue.setValid(false);

    for (int i = 0; i < N; i++) {
        size_t newIdx = (idx + size_t(pow(i, 2))) % N;
        if (mirror[newIdx] == Empty) {
            break;
        } else if ((mirror[newIdx] == Occupied) & (table[newIdx].username == username)) {
            returnValue = table[newIdx];
            returnValue.setValid(true);
            mirror[newIdx] = Available;
            --n;
            break;
        }
    }
    
    return returnValue;

};

/* Para userid */
data_struct QuadMap::remove(unsigned long long userid) {
    size_t idx = hashId(userid);
};

size_t QuadMap::size() {
    return n;
};

bool QuadMap::isEmpty() {
    return n == 0;
}
