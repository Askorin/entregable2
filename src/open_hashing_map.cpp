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

OpenHashingMap::OpenHashingMap() {
    this->table = std::vector(N, std::vector<data_struct>());
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
}

/* Para username */
void OpenHashingMap::put(std::string username, data_struct value) {
    size_t idx = hashUsername(username);
    std::vector<data_struct> chain = table[idx];


    // if (chain.size() > 3) {
    //     std::cout << "Tratando de ingresar: \n";
    //     std::cout << value << "\n\n";
    //     std::cout << "---- Hasheados a idx " << idx << " ----\n\n";
    // }
    for (auto entry : chain) {
        // if (chain.size() > 3) {
        //     std::cout << entry << "\n\n";
        // }
        if (entry.username == username) return;
    }

    table[idx].push_back(value);
    ++n;
};

/* Para userid */
void OpenHashingMap::put(unsigned long long user_id, data_struct value) {
};

/* Para username */
void OpenHashingMap::remove(std::string username) {
    size_t idx = hashUsername(username);
    std::vector<data_struct> chain = table[idx];
    for (size_t i = 0; i < chain.size(); ++i) {
        if (chain[i].username == username) {
            table[idx].erase(table[idx].begin() + i);
            --n;
            return;
        }
    }
};

/* Para userid */
void OpenHashingMap::remove(unsigned long long userid) {
};

size_t OpenHashingMap::size() {
    return n;
};

bool OpenHashingMap::isEmpty() {
    return n == 0;
};
