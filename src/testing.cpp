#include "../inc/testing.h"
#include "../inc/map.h"
#include "../inc/data_parsing.h"
#include "../inc/open_hashing_map.h"
#include "../inc/quad_map.h"
#include "../inc/hash_linear.h"
#include <chrono>
#include <random>
#include <algorithm>
#include <iterator>


using namespace std;

double insertionTimer(HashMap& mapa, vector<data_struct> datos, bool isUserId, size_t count) {

    chrono::duration<double, milli> delta;
    if (isUserId) {
        auto start = chrono::high_resolution_clock::now();
        for (size_t i = 0; i < count; ++i) {
            mapa.put(datos[i].user_id, datos[i]);
        }
        auto end = chrono::high_resolution_clock::now();
        delta = chrono::duration<double, std::milli>(end - start);
    } else {
        auto start = chrono::high_resolution_clock::now();
        for (size_t i = 0; i < count; ++i) {
            mapa.put(datos[i].username, datos[i]);
        }
        auto end = chrono::high_resolution_clock::now();
        delta = chrono::duration<double, milli>(end - start);
    }

    // auto delta = chrono::duration_cast<chrono::milliseconds>(end - start);
    /* milisegundos tipo double */

    return delta.count();
}

double insertionTimer(unordered_map<unsigned long long, data_struct>& mapa, vector<data_struct> datos, size_t count) {

    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        mapa.insert({datos[i].user_id, datos[i]});
    }
    auto end = chrono::high_resolution_clock::now();

    // auto delta = chrono::duration_cast<chrono::milliseconds>(end - start);
    /* milisegundos tipo double */
    auto delta = chrono::duration<double, milli>(end - start);

    return delta.count();
}

double insertionTimer(unordered_map<string, data_struct>& mapa, vector<data_struct> datos, size_t count) {

    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        mapa.insert({datos[i].username, datos[i]});
    }
    auto end = chrono::high_resolution_clock::now();

    // auto delta = chrono::duration_cast<chrono::milliseconds>(end - start);
    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);

    return delta.count();
}

double searchTimer(HashMap& mapa, vector<data_struct> datos, bool isUserId, size_t count) {

    chrono::duration<double, milli> delta;
    if (isUserId) {
        auto start = chrono::high_resolution_clock::now();
        for (size_t i = 0; i < count; ++i) {
            mapa.get(datos[i].user_id);
        }
        auto end = chrono::high_resolution_clock::now();
        delta = chrono::duration<double, std::milli>(end - start);
    } else {
        auto start = chrono::high_resolution_clock::now();
        for (size_t i = 0; i < count; ++i) {
            mapa.get(datos[i].username);
        }
        auto end = chrono::high_resolution_clock::now();
        delta = chrono::duration<double, milli>(end - start);
    }

    // auto delta = chrono::duration_cast<chrono::milliseconds>(end - start);
    /* milisegundos tipo double */

    return delta.count();
}


double searchTimer(unordered_map<unsigned long long, data_struct>& mapa, vector<data_struct> datos, size_t count) {
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        mapa.find(datos[i].user_id);
    }

    auto end = chrono::high_resolution_clock::now();

    // auto delta = chrono::duration_cast<chrono::milliseconds>(end - start);
    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);
    return delta.count();

}

void insertionTimeTest(vector<data_struct> datos) {
    OpenHashingMap abierto;
    HashLinear linear;
    QuadMap quad;
    unordered_map<unsigned long long, data_struct> stl;

    vector<size_t> cuentas = {1000, 5000, 10000, 15000, datos.size()};
    /* 
     * Los datos se guardaran en cuatro filas, cada una con las columnas:
     * tipo_mapa, cuentas_1000, cuentas_5000 ... 
     */
    vector<vector<string>> data_experimento = vector<vector<string>>(4, vector<string>(cuentas.size() + 1, ""));
    data_experimento[0][0] = "hashing_abierto";
    data_experimento[1][0] = "hashing_cerrado_lineal";
    data_experimento[2][0] = "hashing_cerrado_cuadratico";
    data_experimento[3][0] = "stl";
    

    size_t c = 1;
    for (auto cuenta : cuentas) {
        double tiempoAbierto = 0, tiempoLinear = 0, tiempoQuad = 0, tiempoStl = 0;
        size_t nExperimentos = 10;
        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Mapas que usaremos para user_id */
            abierto = OpenHashingMap();
            linear = HashLinear();
            quad = QuadMap();
            stl = unordered_map<unsigned long long, data_struct>();

            /* Tiempo de inserción con llaves de user_id */
            tiempoAbierto += insertionTimer(abierto, datos, true, cuenta); 
            tiempoLinear += insertionTimer(linear, datos, true, cuenta); 
            tiempoQuad += insertionTimer(quad, datos, true, cuenta); 
            tiempoStl += insertionTimer(stl, datos, cuenta);
        }

        tiempoAbierto /= nExperimentos;
        tiempoLinear /= nExperimentos;
        tiempoQuad /= nExperimentos;
        tiempoStl /= nExperimentos;
        data_experimento[0][c] = to_string(tiempoAbierto);
        data_experimento[1][c] = to_string(tiempoLinear);
        data_experimento[2][c] = to_string(tiempoQuad);
        data_experimento[3][c] = to_string(tiempoStl);

        ++c;

        cout << "############################################" << endl;
        cout << "#                                          #" << endl;
        cout << "#            TIEMPOS CON USERID            #" << endl;
        cout << "#                                          #" << endl;
        cout << "############################################" << endl;

        cout << "****" << "Primeros " << cuenta << " elementos" << "****" << endl;
        cout << "---- Tiempo de inserción para hashing abierto ----" << endl;
        cout << tiempoAbierto << " ms\n\n";
        cout << "---- Tiempo de inserción para hashing cerrado, probing lineal ----" << endl;
        cout << tiempoLinear << " ms\n\n";
        cout << "---- Tiempo de inserción para hashing cerrado, probing cuadrático ----" << endl;
        cout << tiempoQuad << " ms\n\n";
        cout << "---- Tiempo de inserción para mapa de la STL ----" << endl;
        cout << tiempoStl << " ms\n\n\n";
    }

    
    write_data({"mapa", "1", "5", "10", "15", "20"}, 
            data_experimento, "../resultados/inserciones.csv");

    // cout << "############################################" << endl;
    // cout << "#                                          #" << endl;
    // cout << "#           TIEMPOS CON USERNAME           #" << endl;
    // cout << "#                                          #" << endl;
    // cout << "############################################" << endl;
    // for (auto cuenta : cuentas) {
    //     /* Mapas que usaremos para user_name */
    //     abierto = OpenHashingMap();
    //     linear = HashLinear();
    //     quad = QuadMap();
    //     stl = unordered_map<unsigned long long, data_struct>();

    //     /* Tiempo de inserción con llaves de username */
    //     double tiempoAbierto = insertionTimer(abierto, datos, false, cuenta); 
    //     double tiempoLinear = insertionTimer(linear, datos, false, cuenta); 
    //     double tiempoQuad = insertionTimer(quad, datos, false, cuenta); 
    //     double tiempoStl = insertionTimer(stl, datos, cuenta);


    //     cout << "****" << "Primeros " << cuenta << " elementos" << "****" << endl;
    //     cout << "---- Tiempo de inserción para hashing abierto ----" << endl;
    //     cout << tiempoAbierto << " ms\n\n";
    //     cout << "---- Tiempo de inserción para hashing cerrado, probing lineal ----" << endl;
    //     cout << tiempoLinear << " ms\n\n";
    //     cout << "---- Tiempo de inserción para hashing cerrado, probing cuadrático ----" << endl;
    //     cout << tiempoQuad << " ms\n\n";
    //     cout << "---- Tiempo de inserción para mapa de la STL ----" << endl;
    //     cout << tiempoStl << " ms\n\n";
    // }


}


void searchTimeTestTipo1(vector<data_struct> datos) {
    OpenHashingMap abierto;
    HashLinear linear;
    QuadMap quad;
    unordered_map<unsigned long long, data_struct> stl;

    vector<size_t> cuentas = {1000, 5000, 10000, 15000, datos.size()};
    /* 
     * Los datos se guardaran en cuatro filas, cada una con las columnas:
     * tipo_mapa, cuentas_1000, cuentas_5000 ... 
     */
    vector<vector<string>> data_experimento = vector<vector<string>>(4, vector<string>(cuentas.size() + 1, ""));
    data_experimento[0][0] = "hashing_abierto";
    data_experimento[1][0] = "hashing_cerrado_lineal";
    data_experimento[2][0] = "hashing_cerrado_cuadratico";
    data_experimento[3][0] = "stl";

    size_t c = 1;
    for (auto cuenta : cuentas) {
        /* Creamos un subconjunto aleatorio del dataset de {cuenta} elementos */
        // sample(datos.begin(), datos.end(), back_inserter(subset), cuenta, std::mt19937{random_device{}()});
        //

        /* Mapas que usaremos para user_id */
        abierto = OpenHashingMap();
        linear = HashLinear();
        quad = QuadMap();
        stl = unordered_map<unsigned long long, data_struct>();

        /* TODO: Hacer función insertData para dejar de repetir codigo de insercion */
        /* Insertamos los datos */
        for (size_t i = 0; i < cuenta; ++i) {
            abierto.put(datos[i].user_id, datos[i]);
            linear.put(datos[i].user_id, datos[i]);
            quad.put(datos[i].user_id, datos[i]);
        }

        for (size_t i = 0; i < cuenta; ++i) {
            stl.insert({datos[i].user_id, datos[i]});
        }


        double tiempoAbierto = 0, tiempoLinear = 0, tiempoQuad = 0, tiempoStl = 0;
        size_t nExperimentos = 10;
        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Tiempo de busqueda con llaves de user_id */
            tiempoAbierto += searchTimer(abierto, datos, true, cuenta); 
            tiempoLinear += searchTimer(linear, datos, true, cuenta); 
            tiempoQuad += searchTimer(quad, datos, true, cuenta); 
            tiempoStl += searchTimer(stl, datos, cuenta);
        }

        tiempoAbierto /= nExperimentos;
        tiempoLinear /= nExperimentos;
        tiempoQuad /= nExperimentos;
        tiempoStl /= nExperimentos;
        data_experimento[0][c] = to_string(tiempoAbierto);
        data_experimento[1][c] = to_string(tiempoLinear);
        data_experimento[2][c] = to_string(tiempoQuad);
        data_experimento[3][c] = to_string(tiempoStl);

        ++c;

        cout << "############################################" << endl;
        cout << "#                                          #" << endl;
        cout << "#            TIEMPOS CON USERID            #" << endl;
        cout << "#                                          #" << endl;
        cout << "############################################" << endl;

        cout << "****" << "Primeros " << cuenta << " elementos" << "****" << endl;
        cout << "---- Tiempo de busqueda para hashing abierto ----" << endl;
        cout << tiempoAbierto << " ms\n\n";
        cout << "---- Tiempo de busqueda para hashing cerrado, probing lineal ----" << endl;
        cout << tiempoLinear << " ms\n\n";
        cout << "---- Tiempo de busqueda para hashing cerrado, probing cuadrático ----" << endl;
        cout << tiempoQuad << " ms\n\n";
        cout << "---- Tiempo de busqueda para mapa de la STL ----" << endl;
        cout << tiempoStl << " ms\n\n\n";
    }

    write_data({"mapa", "1", "5", "10", "15", "20"}, 
            data_experimento, "../resultados/busquedas1.csv");
}


void searchTimeTestTipo2(vector<data_struct> datos) {
    OpenHashingMap abierto;
    HashLinear linear;
    QuadMap quad;
    unordered_map<unsigned long long, data_struct> stl;

    vector<size_t> cuentas = {1000, 5000, 10000, 15000, datos.size()};
    /* 
     * Los datos se guardaran en cuatro filas, cada una con las columnas:
     * tipo_mapa, cuentas_1000, cuentas_5000 ... 
     */
    vector<vector<string>> data_experimento = vector<vector<string>>(4, vector<string>(cuentas.size() + 1, ""));
    data_experimento[0][0] = "hashing_abierto";
    data_experimento[1][0] = "hashing_cerrado_lineal";
    data_experimento[2][0] = "hashing_cerrado_cuadratico";
    data_experimento[3][0] = "stl";

    size_t c = 1;
    for (auto cuenta : cuentas) {
        /* Creamos un subconjunto aleatorio del dataset de {cuenta} elementos */
        // sample(datos.begin(), datos.end(), back_inserter(subset), cuenta, std::mt19937{random_device{}()});
        //

        /* Mapas que usaremos para user_id */
        abierto = OpenHashingMap();
        linear = HashLinear();
        quad = QuadMap();
        stl = unordered_map<unsigned long long, data_struct>();

        /* TODO: Hacer función insertData para dejar de repetir codigo de insercion */
        /* Insertamos los datos */
        for (size_t i = 0; i < cuenta; ++i) {
            abierto.put(datos[i].user_id, datos[i]);
            linear.put(datos[i].user_id, datos[i]);
            quad.put(datos[i].user_id, datos[i]);
        }

        for (size_t i = 0; i < cuenta; ++i) {
            stl.insert({datos[i].user_id, datos[i]});
        }


        double tiempoAbierto = 0, tiempoLinear = 0, tiempoQuad = 0, tiempoStl = 0;
        size_t nExperimentos = 10;
        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Tiempo de busqueda con llaves de user_id */
            tiempoAbierto += searchTimer(abierto, datos, true, cuenta); 
            tiempoLinear += searchTimer(linear, datos, true, cuenta); 
            tiempoQuad += searchTimer(quad, datos, true, cuenta); 
            tiempoStl += searchTimer(stl, datos, cuenta);
        }

        tiempoAbierto /= nExperimentos;
        tiempoLinear /= nExperimentos;
        tiempoQuad /= nExperimentos;
        tiempoStl /= nExperimentos;
        data_experimento[0][c] = to_string(tiempoAbierto);
        data_experimento[1][c] = to_string(tiempoLinear);
        data_experimento[2][c] = to_string(tiempoQuad);
        data_experimento[3][c] = to_string(tiempoStl);

        ++c;

        cout << "############################################" << endl;
        cout << "#                                          #" << endl;
        cout << "#            TIEMPOS CON USERID            #" << endl;
        cout << "#                                          #" << endl;
        cout << "############################################" << endl;

        cout << "****" << "Primeros " << cuenta << " elementos" << "****" << endl;
        cout << "---- Tiempo de busqueda para hashing abierto ----" << endl;
        cout << tiempoAbierto << " ms\n\n";
        cout << "---- Tiempo de busqueda para hashing cerrado, probing lineal ----" << endl;
        cout << tiempoLinear << " ms\n\n";
        cout << "---- Tiempo de busqueda para hashing cerrado, probing cuadrático ----" << endl;
        cout << tiempoQuad << " ms\n\n";
        cout << "---- Tiempo de busqueda para mapa de la STL ----" << endl;
        cout << tiempoStl << " ms\n\n\n";
    }

    write_data({"mapa", "1", "5", "10", "15", "20"}, 
            data_experimento, "../resultados/busquedas.csv");
}

void testFuncionamiento(vector<data_struct> datos) {
    OpenHashingMap abierto{};
    HashLinear linear{};
    QuadMap quad{};

    for (size_t i = 0; i < datos.size(); ++i) {
        abierto.put(datos[i].user_id, datos[i]);
        linear.put(datos[i].user_id, datos[i]);
        quad.put(datos[i].user_id, datos[i]);
    }

    for (size_t i = 0; i < datos.size(); ++i) {
        data_struct datoAbierto = abierto.get(datos[i].user_id);
        data_struct datoLinear = abierto.get(datos[i].user_id);
        data_struct datoQuad = abierto.get(datos[i].user_id);
        if (!(datoAbierto == datos[i])) {
            cout << "En abierto, error para:\n";
            cout << datos[i];
            break;
        }
        if (!(datoLinear  == datos[i])) {
            cout << "En linear, error para:\n";
            cout << datos[i];
            break;
        }
        if (!(datoQuad  == datos[i])) {
            cout << "En quad, error para:\n";
            cout << datos[i];
            break;
        }

        // cout << datos[i] << endl;
    }
}

 


