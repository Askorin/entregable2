#include "../inc/testing.h"
#include "../inc/map.h"
#include "../inc/data_parsing.h"
#include "../inc/open_hashing_map.h"
#include "../inc/quad_map.h"
#include "../inc/hash_linear.h"
#include "../inc/double_map.h"
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

double searchTimer(unordered_map<string, data_struct>& mapa, vector<data_struct> datos, size_t count) {
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        mapa.find(datos[i].username);
    }

    auto end = chrono::high_resolution_clock::now();

    // auto delta = chrono::duration_cast<chrono::milliseconds>(end - start);
    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);
    return delta.count();

}

void insertionTimeTest(vector<data_struct> datos, size_t nExperimentos) {
    OpenHashingMap abierto;
    HashLinear linear;
    QuadMap quad;
    DoubleHash doble;
    unordered_map<unsigned long long, data_struct> stlUl;
    unordered_map<string, data_struct> stlString;

    vector<size_t> cuentas = {1000, 5000, 10000, 15000, datos.size()};
    /* 
     * Los datos se guardaran en cuatro filas, cada una con las columnas:
     * tipo_mapa, cuentas_1000, cuentas_5000 ... 
     */
    vector<vector<string>> data_experimento = vector<vector<string>>(5, vector<string>(cuentas.size() + 1, ""));
    data_experimento[0][0] = "hashing_abierto";
    data_experimento[1][0] = "hashing_cerrado_lineal";
    data_experimento[2][0] = "hashing_cerrado_cuadratico";
    data_experimento[3][0] = "hashing_cerrado_doble";
    data_experimento[4][0] = "stl";
    

    size_t c = 1;
    for (auto cuenta : cuentas) {
        double tiempoAbierto = 0, tiempoLinear = 0, tiempoQuad = 0, tiempoStl = 0, tiempoDoble = 0;
        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Mapas que usaremos para user_id */
            abierto = OpenHashingMap();
            linear = HashLinear();
            quad = QuadMap();
            doble = DoubleHash();
            stlUl = unordered_map<unsigned long long, data_struct>();

            /* Tiempo de inserción con llaves de user_id */
            tiempoAbierto += insertionTimer(abierto, datos, true, cuenta); 
            tiempoLinear += insertionTimer(linear, datos, true, cuenta); 
            tiempoQuad += insertionTimer(quad, datos, true, cuenta); 
            tiempoDoble += insertionTimer(doble, datos, true, cuenta); 
            tiempoStl += insertionTimer(stlUl, datos, cuenta);
        }

        tiempoAbierto /= nExperimentos;
        tiempoLinear /= nExperimentos;
        tiempoQuad /= nExperimentos;
        tiempoDoble /= nExperimentos;
        tiempoStl /= nExperimentos;
        data_experimento[0][c] = to_string(tiempoAbierto);
        data_experimento[1][c] = to_string(tiempoLinear);
        data_experimento[2][c] = to_string(tiempoQuad);
        data_experimento[3][c] = to_string(tiempoDoble);
        data_experimento[4][c] = to_string(tiempoStl);

        ++c;
    }

    
    write_data({"mapa", "1", "5", "10", "15", "20"}, 
            data_experimento, "../resultados/inserciones_id.csv");

    c = 1;
    for (auto cuenta : cuentas) {
        double tiempoAbierto = 0, tiempoLinear = 0, tiempoQuad = 0, tiempoStl = 0, tiempoDoble = 0;
        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Mapas que usaremos para username */
            abierto = OpenHashingMap();
            linear = HashLinear();
            quad = QuadMap();
            doble = DoubleHash();
            stlString = unordered_map<string, data_struct>();

            /* Tiempo de inserción con llaves de username */
            tiempoAbierto += insertionTimer(abierto, datos, false, cuenta); 
            tiempoLinear += insertionTimer(linear, datos, false, cuenta); 
            tiempoQuad += insertionTimer(quad, datos, false, cuenta); 
            tiempoDoble += insertionTimer(doble, datos, false, cuenta); 
            tiempoStl += insertionTimer(stlString, datos, cuenta);
        }

        tiempoAbierto /= nExperimentos;
        tiempoLinear /= nExperimentos;
        tiempoQuad /= nExperimentos;
        tiempoDoble /= nExperimentos;
        tiempoStl /= nExperimentos;
        data_experimento[0][c] = to_string(tiempoAbierto);
        data_experimento[1][c] = to_string(tiempoLinear);
        data_experimento[2][c] = to_string(tiempoQuad);
        data_experimento[3][c] = to_string(tiempoDoble);
        data_experimento[4][c] = to_string(tiempoStl);

        ++c;
    }
    write_data({"mapa", "1", "5", "10", "15", "20"}, 
            data_experimento, "../resultados/inserciones_username.csv");

}


void searchTimeTestTipo1(vector<data_struct> datos, size_t nExperimentos) {
    OpenHashingMap abierto;
    HashLinear linear;
    QuadMap quad;
    DoubleHash doble;
    unordered_map<unsigned long long, data_struct> stlUl;
    unordered_map<string, data_struct> stlString;

    vector<size_t> cuentas = {1000, 5000, 10000, 15000, datos.size()};
    /* 
     * Los datos se guardaran en cuatro filas, cada una con las columnas:
     * tipo_mapa, cuentas_1000, cuentas_5000 ... 
     */
    vector<vector<string>> data_experimento = vector<vector<string>>(5, vector<string>(cuentas.size() + 1, ""));
    data_experimento[0][0] = "hashing_abierto";
    data_experimento[1][0] = "hashing_cerrado_lineal";
    data_experimento[2][0] = "hashing_cerrado_cuadratico";
    data_experimento[3][0] = "hashing_cerrado_doble";
    data_experimento[4][0] = "stl";

    size_t c = 1;
    for (auto cuenta : cuentas) {
        /* Creamos un subconjunto aleatorio del dataset de {cuenta} elementos */
        // sample(datos.begin(), datos.end(), back_inserter(subset), cuenta, std::mt19937{random_device{}()});
        //

        /* Mapas que usaremos para user_id */
        abierto = OpenHashingMap();
        linear = HashLinear();
        quad = QuadMap();
        doble = DoubleHash();
        stlUl = unordered_map<unsigned long long, data_struct>();

        /* TODO: Hacer función insertData para dejar de repetir codigo de insercion */
        /* Insertamos los datos */
        for (size_t i = 0; i < cuenta; ++i) {
            abierto.put(datos[i].user_id, datos[i]);
            linear.put(datos[i].user_id, datos[i]);
            quad.put(datos[i].user_id, datos[i]);
            doble.put(datos[i].user_id, datos[i]);
        }

        for (size_t i = 0; i < cuenta; ++i) {
            stlUl.insert({datos[i].user_id, datos[i]});
        }


        double tiempoAbierto = 0, tiempoLinear = 0, tiempoQuad = 0, tiempoStl = 0, tiempoDoble = 0;
        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Tiempo de busqueda con llaves de user_id */
            tiempoAbierto += searchTimer(abierto, datos, true, cuenta); 
            tiempoLinear += searchTimer(linear, datos, true, cuenta); 
            tiempoQuad += searchTimer(quad, datos, true, cuenta); 
            tiempoDoble += searchTimer(doble, datos, true, cuenta);
            tiempoStl += searchTimer(stlUl, datos, cuenta);
        }

        tiempoAbierto /= nExperimentos;
        tiempoLinear /= nExperimentos;
        tiempoQuad /= nExperimentos;
        tiempoDoble /= nExperimentos;
        tiempoStl /= nExperimentos;
        data_experimento[0][c] = to_string(tiempoAbierto);
        data_experimento[1][c] = to_string(tiempoLinear);
        data_experimento[2][c] = to_string(tiempoQuad);
        data_experimento[3][c] = to_string(tiempoDoble);
        data_experimento[4][c] = to_string(tiempoStl);

        ++c;

    }

    write_data({"mapa", "1", "5", "10", "15", "20"}, 
            data_experimento, "../resultados/busquedas1_id.csv");


    /* Para username */
    c = 1;
    for (auto cuenta : cuentas) {
        /* Creamos un subconjunto aleatorio del dataset de {cuenta} elementos */
        // sample(datos.begin(), datos.end(), back_inserter(subset), cuenta, std::mt19937{random_device{}()});
        //

        /* Mapas que usaremos para username */
        abierto = OpenHashingMap();
        linear = HashLinear();
        quad = QuadMap();
        doble = DoubleHash();
        stlString = unordered_map<string, data_struct>();

        /* TODO: Hacer función insertData para dejar de repetir codigo de insercion */
        /* Insertamos los datos */
        for (size_t i = 0; i < cuenta; ++i) {
            abierto.put(datos[i].username, datos[i]);
            linear.put(datos[i].username, datos[i]);
            quad.put(datos[i].username, datos[i]);
            doble.put(datos[i].username, datos[i]);
        }

        for (size_t i = 0; i < cuenta; ++i) {
            stlString.insert({datos[i].username, datos[i]});
        }


        double tiempoAbierto = 0, tiempoLinear = 0, tiempoQuad = 0, tiempoStl = 0, tiempoDoble = 0;
        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Tiempo de busqueda con llaves de username */
            tiempoAbierto += searchTimer(abierto, datos, false, cuenta); 
            tiempoLinear += searchTimer(linear, datos, false, cuenta); 
            tiempoQuad += searchTimer(quad, datos, false, cuenta); 
            tiempoDoble += searchTimer(doble, datos, false, cuenta);
            tiempoStl += searchTimer(stlString, datos, cuenta);
        }

        tiempoAbierto /= nExperimentos;
        tiempoLinear /= nExperimentos;
        tiempoQuad /= nExperimentos;
        tiempoDoble /= nExperimentos;
        tiempoStl /= nExperimentos;
        data_experimento[0][c] = to_string(tiempoAbierto);
        data_experimento[1][c] = to_string(tiempoLinear);
        data_experimento[2][c] = to_string(tiempoQuad);
        data_experimento[3][c] = to_string(tiempoDoble);
        data_experimento[4][c] = to_string(tiempoStl);

        ++c;

    }


    write_data({"mapa", "1", "5", "10", "15", "20"}, 
            data_experimento, "../resultados/busquedas1_username.csv");
}


void searchTimeTestTipo2(vector<data_struct> datos, size_t nExperimentos) {
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
    }

    write_data({"mapa", "1", "5", "10", "15", "20"}, 
            data_experimento, "../resultados/busquedas.csv");
}

bool testFuncionamiento(vector<data_struct> datos) {
    OpenHashingMap abierto{};
    HashLinear linear{};
    QuadMap quad{};
    DoubleHash doble{};

    cout << "### Testing de funcionamiento ###\n";
    for (size_t i = 0; i < datos.size(); ++i) {
        abierto.put(datos[i].user_id, datos[i]);
        linear.put(datos[i].user_id, datos[i]);
        quad.put(datos[i].user_id, datos[i]);
        doble.put(datos[i].user_id, datos[i]);
    }
    cout << "X Inserciones para userid\n";

    for (size_t i = 0; i < datos.size(); ++i) {
        data_struct datoAbierto = abierto.get(datos[i].user_id);
        data_struct datoLinear = abierto.get(datos[i].user_id);
        data_struct datoQuad = abierto.get(datos[i].user_id);
        data_struct datoDoble = doble.get(datos[i].user_id);
        if (!(datoAbierto == datos[i])) {
            cout << "En abierto, error para:\n";
            cout << datos[i];
            return false;
        }
        if (!(datoLinear == datos[i])) {
            cout << "En linear, error para:\n";
            cout << datos[i];
            return false;
        }
        if (!(datoQuad == datos[i])) {
            cout << "En quad, error para:\n";
            cout << datos[i];
            return false;
        }
        if (!(datoDoble == datos[i])) {
            cout << "En doble, error para:\n";
            cout << datos[i];
            return false;
        }
    }

    cout << "X Búsquedas para userid\n";

    /* Ahora para username */
    abierto = OpenHashingMap();
    linear = HashLinear();
    quad = QuadMap();
    doble = DoubleHash();

    for (size_t i = 0; i < datos.size(); ++i) {
        abierto.put(datos[i].username, datos[i]);
        linear.put(datos[i].username, datos[i]);
        quad.put(datos[i].username, datos[i]);
        doble.put(datos[i].username, datos[i]);
    }


    cout << "X Inserciones para username\n";

    for (size_t i = 0; i < datos.size(); ++i) {
        data_struct datoAbierto = abierto.get(datos[i].username);
        data_struct datoLinear = abierto.get(datos[i].username);
        data_struct datoQuad = abierto.get(datos[i].username);
        data_struct datoDoble = doble.get(datos[i].username);
        if (!(datoAbierto == datos[i])) {
            cout << "En abierto, error para:\n";
            cout << datos[i];
            return false;
        }
        if (!(datoLinear == datos[i])) {
            cout << "En linear, error para:\n";
            cout << datos[i];
            return false;
        }
        if (!(datoQuad == datos[i])) {
            cout << "En quad, error para:\n";
            cout << datos[i];
            return false;
        }
        if (!(datoDoble == datos[i])) {
            cout << "En doble, error para:\n";
            cout << datos[i];
            return false;
        }
    }


    cout << "X Búsquedas para username\n";
    cout << "### Test de funcionamiento listo ###\n";

    return true;
}

 


