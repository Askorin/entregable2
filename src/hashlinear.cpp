#include <vector>
#include <string>
#include "../inc/data_struct.h"
#include "../inc/map.h"

class HashLinear : public HashMap {
private:
    std::vector<data_struct> table;
    std::vector<int> mirror;
    size_t n;

public:
    enum Status 
    {
        Empty,
        Available,
        Occupied
    };

    /*Se crea vector mirror que servirá para saber si las posiciones estan vacias o disponibles.*/    
    HashLinear() : table(49157, data_struct("", 0, "", 0, 0, 0, "")), mirror(49157, Empty), n(0) { }

    unsigned long long h1(unsigned long long user_id)
    {
        size_t a = 45382, b = 11923;

        return (a * user_id + b) % N;
    }


    data_struct get(std::string username) override { }

    data_struct get(unsigned long long userId) override
    {
        unsigned long long idx = h1(userId);
        int p = 0;

        for (p; p < N; p++)
        {

            if(mirror[idx] == Empty)
            {


                data_struct empty("",0,"",0,0,0,"");
                empty.setValid(false);
                return empty;
            }

            else if (mirror[idx] == Occupied & table[idx].user_id == userId)
            {
                data_struct tmp = table[idx];
                return tmp;
            }

            else
            {
                idx = (idx + 1) % N;
            }
        }
    }


    void put(std::string username, data_struct value) override { }

    void put(unsigned long long userid, data_struct value) override
    {
        /* Esto es más o menos ineficiente, pero funciona */
        data_struct elem = get(userid);
        
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
        
        size_t idx = h1(userid);
        int p = 0;
        for (p; p < N; p++)
        {
            if(mirror[idx] == Empty || mirror[idx] == Available) 
            {
                table[idx] = value;
                mirror[idx] = Occupied;
                ++n;
                return;
            }
            idx = (idx + 1) % N;
        }
    }

    data_struct remove(std::string username) override { }

    data_struct remove(unsigned long long userid) override 
    {
        unsigned long long idx = h1(userid);
        int p = 0;

        for (p; p < N; p++)
        {
            if(mirror[idx] == Empty)
            {
                data_struct empty("",0,"",0,0,0,"");
                empty.setValid(false);
                return empty;
            }
            else if (mirror[idx] == Occupied & table[idx].user_id == userid)
            {
                data_struct tmp = table[idx];
                mirror[idx] = Available;
                --n;
                return tmp;
            }

            idx = (idx + 1) % N;
        }
    }


    size_t size() override {
        return n;
    }

    bool isEmpty() override {
        return n == 0;
    }

};
