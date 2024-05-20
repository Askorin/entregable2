#include "../inc/quad_map.h"


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
}

/* Para userid */
data_struct QuadMap::get(unsigned long long user_id) {
    size_t idx = hashId(user_id);
}

/* Para username */
void QuadMap::put(std::string username, data_struct value) {
    size_t idx = hashUsername(username);
};

/* Para userid */
void QuadMap::put(unsigned long long user_id, data_struct value) {
    size_t idx = hashId(user_id);
};

/* Para username */
data_struct QuadMap::remove(std::string username) {
    size_t idx = hashUsername(username);
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
