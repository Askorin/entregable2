#include <vector>
#include <string>
#include "../inc/data_struct.h"
#include "../inc/map.h"

class HashLinear : public HashMap {
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

    /*Se crea vector mirror que servirá para saber si las posiciones estan vacias o disponibles.*/    
    HashLinear() :mirror(49157, Empty) {}

    unsigned long long h1(unsigned long long user_id)
    {
        size_t m = 49157, a = 45382, b = 11923;

        return (a * user_id + b) % m;
    }

    data_struct get(unsigned long long userId) 
    {
        unsigned long long idx = h1(userId);
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
                idx = (idx + 1) % Max;
            }
        }
    }

    void put(unsigned long long userid, data_struct value) 
    {
        unsigned long long idx = h1(userid);
        int p = 0, Max = 49157;
        for (p; p < Max; p++)
        {
            if(mirror[idx] == Empty || mirror[idx] == Available) 
            {
                table[idx] = value;
                mirror[idx] = Occupied;
            }
            idx = (idx + 1) % Max;
        }
    }

    data_struct remove(unsigned long long userid) 
    {
        unsigned long long idx = h1(userid);

        if(mirror[idx] == Occupied){

            data_struct tmp = get(userid);
            mirror[idx] = Available;
            return tmp;
        }

        else
        {
                data_struct empty(0,0,0,0,0,0,0);
                empty.setValid(false);
                return empty;
        }

              
    }

    

};
