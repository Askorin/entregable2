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
    DoubleHash() :mirror(49157, Empty) {}

    // Primera función Hash
    unsigned long long h1(unsigned long long user_id)
    { 
        size_t m = 49157, a = 45382, b = 11923;

        return (a * user_id + b) % m;
    }

    //Segunda función Hash, con q un numero primo.
    unsigned long long d1(unsigned long long user_id)
    { 
        int q = 6827; 

        return q - (user_id % q);
    }

       data_struct get(unsigned long long userId) 
    {
        unsigned long long idx = h1(userId);
        unsigned long long hash1 = h1(userId);
        unsigned long long hash2 = d1(userId);

        int p = 0, Max = 49157;

        for (p; p < Max; p++)
        {

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

            else
            {
                idx = (hash1 + p*hash2) % Max;
            }
        }
    }

    void put (unsigned long long user_id, data_struct value)
    {
        unsigned long long idx = h1(user_id);

        if(mirror[idx] = Occupied)
        {
            unsigned long long hash1 = h1(user_id);
            unsigned long long hash2 = d1(user_id);

            for (size_t i = 0, Max = 49157; i < Max; i++)
            {
                idx = (hash1 + i*hash2) % Max;
                
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
        unsigned long long hash1 = h1(userid);
        unsigned long long hash2 = d1(userid);
        unsigned long long idx = hash1;
        int Max = 49157;

        for (int i = 0; i < Max; i++) 
        {
            if (mirror[idx] == Occupied && table[idx].user_id == userid) 
            {
                mirror[idx] = Available;
                data_struct tmp = table[idx];
                return tmp;
            }
            
            idx = (hash1 + i * hash2) % Max;

        }
        

    }

    


};