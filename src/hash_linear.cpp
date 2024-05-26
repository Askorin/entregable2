#include <vector>
#include <string>
#include "../inc/data_struct.h"
#include "../inc/hash_linear.h"

/*Se crea vector mirror que servirá para saber si las posiciones estan vacias o disponibles.*/    
HashLinear::HashLinear() : table(N, data_struct("", 0, "", 0, 0, 0, "")), mirror(N, Empty), n(0) { }

data_struct HashLinear::get(std::string username) {
    unsigned long long idx = HashMap::hashUsername(username);

    for (size_t p = 0; p < N; p++)
    {

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

        else
        {
            idx = (idx + 1) % N;
        }
    }
}

data_struct HashLinear::get(unsigned long long userId) 
{
    unsigned long long idx = HashMap::hashId(userId);

    for (size_t p = 0; p < N; p++)
    {

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

        else
        {
            idx = (idx + 1) % N;
        }
    }
}


void HashLinear::put(std::string username, data_struct value) {
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
    
    size_t idx = HashMap::hashUsername(username);
    for (size_t p = 0; p < N; p++)
    {
        if((mirror[idx] == Empty) || (mirror[idx] == Available)) 
        {
            table[idx] = value;
            mirror[idx] = Occupied;
            ++n;
            return;
        }
        idx = (idx + 1) % N;
    }
}

void HashLinear::put(unsigned long long userid, data_struct value) 
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
    
    size_t idx = HashMap::hashId(userid);
    for (size_t p = 0; p < N; p++)
    {
        if((mirror[idx] == Empty) || (mirror[idx] == Available)) 
        {
            table[idx] = value;
            mirror[idx] = Occupied;
            ++n;
            return;
        }
        idx = (idx + 1) % N;
    }
}

data_struct HashLinear::remove(std::string username) { }

data_struct HashLinear::remove(unsigned long long userid) 
{
    unsigned long long idx = HashMap::hashId(userid);

    for (size_t p = 0; p < N; p++)
    {
        if(mirror[idx] == Empty)
        {
            data_struct empty("",0,"",0,0,0,"");
            empty.setValid(false);
            return empty;
        }
        else if ((mirror[idx] == Occupied) && (table[idx].user_id == userid))
        {
            data_struct tmp = table[idx];
            mirror[idx] = Available;
            --n;
            return tmp;
        }

        idx = (idx + 1) % N;
    }
}


size_t HashLinear::size() {
    return n;
}

bool HashLinear::isEmpty() {
    return n == 0;
}

