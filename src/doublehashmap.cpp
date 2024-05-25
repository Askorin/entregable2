#include <vector>
#include <string>
#include "../inc/data_struct.h"
#include "../inc/map.h"

class DoubleHash : public HashMap {
    private:
        std::vector<data_struct> table;
        std::vector<int> mirror;
    
    public:

    enum Status 
    {
        Empty,
        Available,
        Occupied
    };
    // Mismo caso que en HashLinear, tabla espejo de disponibilidad de espacios.
    DoubleHash() : mirror(49157, Empty) {}

    //Segunda función Hash, con q un numero primo.
    size_t d1(unsigned long long user_id)
    { 
        int q = 6827; 
        return q - (user_id % q);
    }

    data_struct get(unsigned long long userId)
    {
        size_t idx;
        size_t hash1 = HashMap::hashId(userId);
        size_t hash2 = d1(userId);

        for (size_t p = 0; p < N; p++)
        {
            idx = (hash1 + p*hash2) % N;

            if(mirror[idx] == Empty)
            {
                data_struct empty(0,0,0,0,0,0,0);
                empty.setValid(false);
                return empty;
            }

            else if (table[idx].user_id == userId )
            {
                data_struct tmp = table[idx];
                return tmp;
            }
        }
    }

    void put (unsigned long long user_id, data_struct value)
    {
        unsigned long long idx = HashMap::hashId(user_id);

        if(mirror[idx] == Occupied)
        {
            unsigned long long hash1 = HashMap::hashId(user_id);
            unsigned long long hash2 = d1(user_id);

            for (size_t i = 0; i < N; i++)
            {
                idx = (hash1 + i*hash2) % N;
                
                if(mirror[idx] == Empty || mirror[idx] == Available)
                {
                    table[idx] = value;
                    mirror[idx] = Occupied;
                    return;
                }

            }
            
        }
    }

    data_struct remove(unsigned long long userid) 
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
};
