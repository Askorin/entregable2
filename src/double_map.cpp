#include <vector>
#include <string>
#include "../inc/data_struct.h"
#include "../inc/double_map.h"

// Mismo caso que en HashLinear, tabla espejo de disponibilidad de espacios.
DoubleHash::DoubleHash() : table(N, data_struct("", 0, "", 0, 0, 0, "")), mirror(N, Empty), n(0) { }

//Segunda función Hash, con q un numero primo.
size_t DoubleHash::d1(unsigned long long id)
{ 
    int q = 6827; 
    return q - (id % q);
}


data_struct DoubleHash::get(std::string username) {
    size_t hash1 = HashMap::hashUsername(username);
    size_t hash2 = d1(hashUsername(username));
    size_t idx;

    for (size_t i = 0; i < N; ++i)
    {
        idx = (hash1 + i*hash2) % N;

        if(mirror[idx] == Empty)
        {
            data_struct empty("",0,"",0,0,0,"");
            empty.setValid(false);
            return empty;
        }
        else if ((mirror[idx] == Occupied) && (table[idx].username == username))
        {
            data_struct tmp = table[idx];
            return tmp;
        }
    }

};

data_struct DoubleHash::get(unsigned long long userId)
{
    size_t hash1 = HashMap::hashId(userId);
    size_t hash2 = d1(userId);
    size_t idx;

    for (size_t i = 0; i < N; ++i)
    {
        idx = (hash1 + i*hash2) % N;

        if(mirror[idx] == Empty)
        {
            data_struct empty("",0,"",0,0,0,"");
            empty.setValid(false);
            return empty;
        }
        else if ((mirror[idx] == Occupied) && (table[idx].user_id == userId))
        {
            data_struct tmp = table[idx];
            return tmp;
        }
    }
}


void DoubleHash::put(std::string username, data_struct value) {
    data_struct elem = get(username);

    if (elem.valid) {
        return;
    }

    size_t hash1 = HashMap::hashUsername(username);
    size_t hash2 = d1(hashUsername(username));
    size_t idx;

    for (size_t i = 0; i < N; ++i) {
        idx = (hash1 + i * hash2) % N;
        if ((mirror[idx] == Empty) || (mirror[idx] == Available)) {
            table[idx] = value;
            mirror[idx] = Occupied;
            return;
        }
    }
};

void DoubleHash::put(unsigned long long userid, data_struct value)
{
    data_struct elem = get(userid);

    if (elem.valid) {
        return;
    }

    size_t hash1 = HashMap::hashId(userid);
    size_t hash2 = d1(userid);
    size_t idx;

    for (size_t i = 0; i < N; ++i) {
        idx = (hash1 + i * hash2) % N;
        if ((mirror[idx] == Empty) || (mirror[idx] == Available)) {
            
            table[idx] = value;
            mirror[idx] = Occupied;
            return;
        }
    }
}

data_struct DoubleHash::remove(std::string username) { };

data_struct DoubleHash::remove(unsigned long long userid)
{
    unsigned long long hash1 = HashMap::hashId(userid);
    unsigned long long hash2 = d1(userid);
    unsigned long long idx = hash1;

    for (size_t i = 0; i < N; i++) 
    {
        if (mirror[idx] == Occupied && table[idx].user_id == userid) 
        {
            mirror[idx] = Available;
            data_struct tmp = table[idx];
            return tmp;
        }
        
        idx = (hash1 + i * hash2) % N;

    }
}

size_t DoubleHash::size() {
    return n;
}

bool DoubleHash::isEmpty() {
    return n == 0;
}

