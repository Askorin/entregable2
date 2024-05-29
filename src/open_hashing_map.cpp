#include "../inc/open_hashing_map.h"



OpenHashingMap::OpenHashingMap() {
    this->table = std::vector(N, std::vector<data_struct>{});
    this->n = 0;
}

data_struct OpenHashingMap::get(std::string username) {
    
    size_t idx = HashMap::hashUsername(username);
    for (size_t i = 0; i < table[idx].size(); ++i) {
        if (table[idx][i].username == username) return table[idx][i];
    }
    /* En este caso no encontramos nada */
    data_struct retVal("", 0, "", 0, 0, 0, "");
    retVal.setValid(false);
    return retVal;
}

/* Para userid */
data_struct OpenHashingMap::get(unsigned long long user_id) {
    size_t idx = HashMap::hashId(user_id);
    for (size_t i = 0; i < table[idx].size(); ++i) {
        if (table[idx][i].user_id == user_id) return table[idx][i];
    }
    /* En este caso no encontramos nada */
    data_struct retVal("", 0, "", 0, 0, 0, "");
    retVal.setValid(false);
    return retVal;
}

/* Para username */
void OpenHashingMap::put(std::string username, data_struct value) {
    size_t idx = HashMap::hashUsername(username);
    for (size_t i = 0; i < table[idx].size(); ++i) {
        if (table[idx][i].username == username) return;
    }
    table[idx].push_back(value);
    ++n;
};

/* Para userid */
void OpenHashingMap::put(unsigned long long user_id, data_struct value) {
    size_t idx = HashMap::hashId(user_id);
    for (size_t i = 0; i < table[idx].size(); ++i) {
        if (table[idx][i].user_id == user_id) return;
    }
    table[idx].push_back(value);
    ++n;
};

/* Para username */
data_struct OpenHashingMap::remove(std::string username) {
    size_t idx = HashMap::hashUsername(username);

    for (size_t i = 0; i < table[idx].size(); ++i) {
        data_struct valor = table[idx][i];
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
    size_t idx = HashMap::hashId(userid);

    for (size_t i = 0; i < table[idx].size(); ++i) {
        data_struct valor = table[idx][i];
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
