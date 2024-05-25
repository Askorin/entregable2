#include "../inc/open_hashing_map.h"


size_t OpenHashingMap::hashUsername(std::string username) {
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

size_t OpenHashingMap::hashId(unsigned long long id) {
    /* mult mod prime con a, b menores a m (tamaño de la tabla, número primo, quizás). */
    size_t a = 45382, b = 11923;
    
    return (a * id + b) % N;

}

OpenHashingMap::OpenHashingMap() {
    this->table = std::vector(N, std::vector<data_struct>{});
    this->n = 0;
}

data_struct OpenHashingMap::get(std::string username) {
    size_t idx = hashUsername(username);
    std::vector<data_struct> chain = table[idx];
    for (auto entry : chain) {
        if (entry.username == username) return entry;
    }
    /* En este caso no encontramos nada */
    data_struct retVal("", 0, "", 0, 0, 0, "");
    retVal.setValid(false);
    return retVal;
}

/* Para userid */
data_struct OpenHashingMap::get(unsigned long long user_id) {
    size_t idx = hashId(user_id);
    std::vector<data_struct> chain = table[idx];
    for (auto entry : chain) {
        if (entry.user_id == user_id) return entry;
    }
    /* En este caso no encontramos nada */
    data_struct retVal("", 0, "", 0, 0, 0, "");
    retVal.setValid(false);
    return retVal;
}

/* Para username */
void OpenHashingMap::put(std::string username, data_struct value) {
    size_t idx = hashUsername(username);
    std::vector<data_struct> chain = table[idx];

    for (auto entry : chain) {
        if (entry.username == username) return;
    }

    table[idx].push_back(value);
    ++n;
};

/* Para userid */
void OpenHashingMap::put(unsigned long long user_id, data_struct value) {
    size_t idx = hashId(user_id);
    std::vector<data_struct> chain = table[idx];

    for (auto entry : chain) {
        if (entry.user_id == user_id) return;
    }

    table[idx].push_back(value);
    ++n;
};

/* Para username */
data_struct OpenHashingMap::remove(std::string username) {
    size_t idx = hashUsername(username);

    std::vector<data_struct> chain = table[idx];
    for (size_t i = 0; i < chain.size(); ++i) {
        data_struct valor = chain[i];
        if (valor.username == username) {
            table[idx].erase(table[idx].begin() + i);
            --n;
            return valor;
        }
    }

    data_struct retVal("", 0, "", 0, 0, 0, "");
    retVal.setValid(false);
    return retVal;
};

/* Para userid */
data_struct OpenHashingMap::remove(unsigned long long userid) {
    size_t idx = hashId(userid);

    std::vector<data_struct> chain = table[idx];
    for (size_t i = 0; i < chain.size(); ++i) {
        data_struct valor = chain[i];
        if (valor.user_id == userid) {
            table[idx].erase(table[idx].begin() + i);
            --n;
            return valor;
        }
    }

    data_struct retVal("", 0, "", 0, 0, 0, "");
    retVal.setValid(false);
    return retVal;

};

size_t OpenHashingMap::size() {
    return n;
};

bool OpenHashingMap::isEmpty() {
    return n == 0;
};
