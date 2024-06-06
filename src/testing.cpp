#include "../inc/testing.h"
#include "../inc/data_parsing.h"
#include "../inc/double_map.h"
#include "../inc/hash_linear.h"
#include "../inc/map.h"
#include "../inc/open_hashing_map.h"
#include "../inc/quad_map.h"
#include <algorithm>
#include <chrono>
#include <cmath>

using namespace std;

double insertionTimer(HashMap<unsigned long long, data_struct>& mapa,
                      vector<data_struct>& datos, size_t count) {

    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        auto volatile result = mapa.put(datos[i].user_id, datos[i]);
    }
    auto end = chrono::high_resolution_clock::now();

    /* milisegundos tipo double */
    auto delta = chrono::duration<double, milli>(end - start);

    return delta.count();
}

double insertionTimer(HashMap<string, data_struct>& mapa,
                      vector<data_struct>& datos, size_t count) {

    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        auto volatile result = mapa.put(datos[i].username, datos[i]);
    }
    auto end = chrono::high_resolution_clock::now();

    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);

    return delta.count();
}

double insertionTimer(unordered_map<unsigned long long, data_struct>& mapa,
                      vector<data_struct>& datos, size_t count) {

    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        auto volatile result = mapa.insert({datos[i].user_id, datos[i]});
    }
    auto end = chrono::high_resolution_clock::now();

    /* milisegundos tipo double */
    auto delta = chrono::duration<double, milli>(end - start);

    return delta.count();
}

double insertionTimer(unordered_map<string, data_struct>& mapa,
                      vector<data_struct>& datos, size_t count) {

    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        auto volatile result = mapa.insert({datos[i].username, datos[i]});
    }
    auto end = chrono::high_resolution_clock::now();

    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);

    return delta.count();
}

double searchTimer(HashMap<unsigned long long, data_struct>& mapa,
                   vector<data_struct>& datos, size_t count,
                   size_t idxComienzo) {
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = idxComienzo; i < idxComienzo + count; ++i) {
        auto volatile result = mapa.get(datos[i].user_id);
    }

    auto end = chrono::high_resolution_clock::now();

    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);
    return delta.count();
}

double searchTimer(HashMap<string, data_struct>& mapa,
                   vector<data_struct>& datos, size_t count,
                   size_t idxComienzo) {
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = idxComienzo; i < idxComienzo + count; ++i) {
        auto volatile result = mapa.get(datos[i].username);
    }

    auto end = chrono::high_resolution_clock::now();

    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);
    return delta.count();
}

double searchTimer(unordered_map<unsigned long long, data_struct>& mapa,
                   vector<data_struct>& datos, size_t count,
                   size_t idxComienzo) {
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = idxComienzo; i < idxComienzo + count; ++i) {
        auto volatile result = mapa.find(datos[i].user_id);
    }

    auto end = chrono::high_resolution_clock::now();

    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);
    return delta.count();
}

double searchTimer(unordered_map<string, data_struct>& mapa,
                   vector<data_struct>& datos, size_t count,
                   size_t idxComienzo) {
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = idxComienzo; i < idxComienzo + count; ++i) {
        auto volatile result = mapa.find(datos[i].username);
    }

    auto end = chrono::high_resolution_clock::now();

    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);
    return delta.count();
}

void insertionTimeTest(vector<data_struct>& datos, size_t nExperimentos,
                       vector<size_t> cuentas) {
    OpenHashingMap<unsigned long long, data_struct> abiertoUl;
    HashLinear<unsigned long long, data_struct> linearUl;
    QuadMap<unsigned long long, data_struct> quadUl;
    DoubleHash<unsigned long long, data_struct> dobleUl;
    unordered_map<unsigned long long, data_struct> stlUl;

    /*
     * Los datos se guardaran en cuatro filas, cada una con las columnas:
     * tipo_mapa, cuentas_1000, cuentas_5000 ...
     */
    vector<vector<string>> dataExperimento =
        vector<vector<string>>(5, vector<string>(cuentas.size() + 1, ""));
    dataExperimento[0][0] = "hashing_abierto";
    dataExperimento[1][0] = "hashing_cerrado_lineal";
    dataExperimento[2][0] = "hashing_cerrado_cuadratico";
    dataExperimento[3][0] = "hashing_cerrado_doble";
    dataExperimento[4][0] = "std::unordered_map";

    /* También habra otro vector con las desviaciones estándar. */
    vector<vector<string>> desviaciones(dataExperimento);

    size_t c = 1;
    for (auto cuenta : cuentas) {
        cout << "### Insertando, id, cuenta ###" << cuenta << endl;
        double promTiempoAbierto = 0, promTiempoLinear = 0, promTiempoQuad = 0,
               promTiempoDoble = 0, promTiempoStl = 0;

        double dvAbiertoL = 0, dvLinearL = 0, dvQuadL = 0, dvDobleL = 0,
               dvStlL = 0;

        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Mapas que usaremos para user_id */
            abiertoUl = OpenHashingMap<unsigned long long, data_struct>();
            linearUl = HashLinear<unsigned long long, data_struct>();
            quadUl = QuadMap<unsigned long long, data_struct>();
            dobleUl = DoubleHash<unsigned long long, data_struct>();
            stlUl = unordered_map<unsigned long long, data_struct>();

            /* Tiempo de inserción con llaves de user_id */
            double tiempoAbierto = insertionTimer(abiertoUl, datos, cuenta);
            double tiempoLinear = insertionTimer(linearUl, datos, cuenta);
            double tiempoQuad = insertionTimer(quadUl, datos, cuenta);
            double tiempoDoble = insertionTimer(dobleUl, datos, cuenta);
            double tiempoStl = insertionTimer(stlUl, datos, cuenta);

            promTiempoAbierto += tiempoAbierto;
            promTiempoLinear += tiempoLinear;
            promTiempoQuad += tiempoQuad;
            promTiempoDoble += tiempoDoble;
            promTiempoStl += tiempoStl;

            dvAbiertoL += pow(tiempoAbierto, 2);
            dvLinearL += pow(tiempoLinear, 2);
            dvQuadL += pow(tiempoQuad, 2);
            dvDobleL += pow(tiempoDoble, 2);
            dvStlL += pow(tiempoStl, 2);
        }

        promTiempoAbierto /= nExperimentos;
        promTiempoLinear /= nExperimentos;
        promTiempoQuad /= nExperimentos;
        promTiempoDoble /= nExperimentos;
        promTiempoStl /= nExperimentos;

        double dvAbierto =
            sqrt((dvAbiertoL - pow(promTiempoAbierto, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvLinear =
            sqrt((dvLinearL - pow(promTiempoLinear, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvQuad =
            sqrt((dvQuadL - pow(promTiempoQuad, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvDoble =
            sqrt((dvDobleL - pow(promTiempoDoble, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvStl = sqrt((dvStlL - pow(promTiempoStl, 2) * nExperimentos) /
                            (nExperimentos - 1));

        dataExperimento[0][c] = to_string(promTiempoAbierto);
        dataExperimento[1][c] = to_string(promTiempoLinear);
        dataExperimento[2][c] = to_string(promTiempoQuad);
        dataExperimento[3][c] = to_string(promTiempoDoble);
        dataExperimento[4][c] = to_string(promTiempoStl);

        desviaciones[0][c] = to_string(dvAbierto);
        desviaciones[1][c] = to_string(dvLinear);
        desviaciones[2][c] = to_string(dvQuad);
        desviaciones[3][c] = to_string(dvDoble);
        desviaciones[4][c] = to_string(dvStl);

        ++c;
    }

    vector<string> features = {"mapa"};
    for (auto cuenta : cuentas) {
        features.push_back(to_string(cuenta));
    }

    write_data(features, dataExperimento, "../resultados/inserciones_id.csv");

    write_data(features, desviaciones, "../resultados/dv_inserciones_id.csv");

    OpenHashingMap<string, data_struct> abiertoStr;
    HashLinear<string, data_struct> linearStr;
    QuadMap<string, data_struct> quadStr;
    DoubleHash<string, data_struct> dobleStr;
    unordered_map<string, data_struct> stlStr;

    c = 1;
    for (auto cuenta : cuentas) {
        cout << "### Insertando, usr, cuenta ###" << cuenta << endl;
        double promTiempoAbierto = 0, promTiempoLinear = 0, promTiempoQuad = 0,
               promTiempoDoble = 0, promTiempoStl = 0;

        double dvAbiertoL = 0, dvLinearL = 0, dvQuadL = 0, dvDobleL = 0,
               dvStlL = 0;
        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Mapas que usaremos para username */
            abiertoStr = OpenHashingMap<string, data_struct>();
            linearStr = HashLinear<string, data_struct>();
            quadStr = QuadMap<string, data_struct>();
            dobleStr = DoubleHash<string, data_struct>();
            stlStr = unordered_map<string, data_struct>();

            /* Tiempo de inserción con llaves de username */
            double tiempoAbierto = insertionTimer(abiertoStr, datos, cuenta);
            double tiempoLinear = insertionTimer(linearStr, datos, cuenta);
            double tiempoQuad = insertionTimer(quadStr, datos, cuenta);
            double tiempoDoble = insertionTimer(dobleStr, datos, cuenta);
            double tiempoStl = insertionTimer(stlStr, datos, cuenta);

            promTiempoAbierto += tiempoAbierto;
            promTiempoLinear += tiempoLinear;
            promTiempoQuad += tiempoQuad;
            promTiempoDoble += tiempoDoble;
            promTiempoStl += tiempoStl;

            dvAbiertoL += pow(tiempoAbierto, 2);
            dvLinearL += pow(tiempoLinear, 2);
            dvQuadL += pow(tiempoQuad, 2);
            dvDobleL += pow(tiempoDoble, 2);
            dvStlL += pow(tiempoStl, 2);
        }

        promTiempoAbierto /= nExperimentos;
        promTiempoLinear /= nExperimentos;
        promTiempoQuad /= nExperimentos;
        promTiempoDoble /= nExperimentos;
        promTiempoStl /= nExperimentos;

        double dvAbierto =
            sqrt((dvAbiertoL - pow(promTiempoAbierto, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvLinear =
            sqrt((dvLinearL - pow(promTiempoLinear, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvQuad =
            sqrt((dvQuadL - pow(promTiempoQuad, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvDoble =
            sqrt((dvDobleL - pow(promTiempoDoble, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvStl = sqrt((dvStlL - pow(promTiempoStl, 2) * nExperimentos) /
                            (nExperimentos - 1));

        dataExperimento[0][c] = to_string(promTiempoAbierto);
        dataExperimento[1][c] = to_string(promTiempoLinear);
        dataExperimento[2][c] = to_string(promTiempoQuad);
        dataExperimento[3][c] = to_string(promTiempoDoble);
        dataExperimento[4][c] = to_string(promTiempoStl);

        desviaciones[0][c] = to_string(dvAbierto);
        desviaciones[1][c] = to_string(dvLinear);
        desviaciones[2][c] = to_string(dvQuad);
        desviaciones[3][c] = to_string(dvDoble);
        desviaciones[4][c] = to_string(dvStl);

        ++c;
    }

    write_data(features, dataExperimento,
               "../resultados/inserciones_username.csv");

    write_data(features, desviaciones,
               "../resultados/dv_inserciones_username.csv");
}

void searchTimeTestTipo1(vector<data_struct>& datos, size_t nExperimentos,
                         vector<size_t> nBusquedas) {
    OpenHashingMap<unsigned long long, data_struct> abiertoUl;
    HashLinear<unsigned long long, data_struct> linearUl;
    QuadMap<unsigned long long, data_struct> quadUl;
    DoubleHash<unsigned long long, data_struct> dobleUl;
    unordered_map<unsigned long long, data_struct> stlUl;

    /*
     * Los datos se guardaran en cuatro filas, cada una con las columnas:
     * tipo_mapa, cuentas_1000, cuentas_5000 ...
     */
    vector<string> features = {"mapa"};
    vector<vector<string>> dataExperimento(
        5, vector<string>(nBusquedas.size() + 1));
    dataExperimento[0][0] = "hashing_abierto";
    dataExperimento[1][0] = "hashing_cerrado_lineal";
    dataExperimento[2][0] = "hashing_cerrado_cuadratico";
    dataExperimento[3][0] = "hashing_cerrado_doble";
    dataExperimento[4][0] = "std::unordered_map";

    /* También habra otro vector con las desviaciones estándar. */
    vector<vector<string>> desviaciones(dataExperimento);

    size_t c = 1;
    for (auto cuenta : nBusquedas) {
        cout << "### Buscando tipo 1, id, cuenta ###" << cuenta << endl;
        /* Mapas que usaremos para user_id */
        abiertoUl = OpenHashingMap<unsigned long long, data_struct>();
        linearUl = HashLinear<unsigned long long, data_struct>();
        quadUl = QuadMap<unsigned long long, data_struct>();
        dobleUl = DoubleHash<unsigned long long, data_struct>();
        stlUl = unordered_map<unsigned long long, data_struct>();

        /* Insertamos los datos */
        for (size_t i = 0; i < datos.size(); ++i) {
            abiertoUl.put(datos[i].user_id, datos[i]);
            linearUl.put(datos[i].user_id, datos[i]);
            quadUl.put(datos[i].user_id, datos[i]);
            dobleUl.put(datos[i].user_id, datos[i]);
            stlUl.insert({datos[i].user_id, datos[i]});
        }

        features.push_back(to_string(cuenta));

        double promTiempoAbierto = 0, promTiempoLinear = 0, promTiempoQuad = 0,
               promTiempoDoble = 0, promTiempoStl = 0;

        double dvAbiertoL = 0, dvLinearL = 0, dvQuadL = 0, dvDobleL = 0,
               dvStlL = 0;
        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Tiempo de busqueda con llaves de user_id */
            double tiempoAbierto = searchTimer(abiertoUl, datos, cuenta, 0);
            double tiempoLinear = searchTimer(linearUl, datos, cuenta, 0);
            double tiempoQuad = searchTimer(quadUl, datos, cuenta, 0);
            double tiempoDoble = searchTimer(dobleUl, datos, cuenta, 0);
            double tiempoStl = searchTimer(stlUl, datos, cuenta, 0);

            promTiempoAbierto += tiempoAbierto;
            promTiempoLinear += tiempoLinear;
            promTiempoQuad += tiempoQuad;
            promTiempoDoble += tiempoDoble;
            promTiempoStl += tiempoStl;

            dvAbiertoL += pow(tiempoAbierto, 2);
            dvLinearL += pow(tiempoLinear, 2);
            dvQuadL += pow(tiempoQuad, 2);
            dvDobleL += pow(tiempoDoble, 2);
            dvStlL += pow(tiempoStl, 2);
        }

        promTiempoAbierto /= nExperimentos;
        promTiempoLinear /= nExperimentos;
        promTiempoQuad /= nExperimentos;
        promTiempoDoble /= nExperimentos;
        promTiempoStl /= nExperimentos;

        double dvAbierto =
            sqrt((dvAbiertoL - pow(promTiempoAbierto, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvLinear =
            sqrt((dvLinearL - pow(promTiempoLinear, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvQuad =
            sqrt((dvQuadL - pow(promTiempoQuad, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvDoble =
            sqrt((dvDobleL - pow(promTiempoDoble, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvStl = sqrt((dvStlL - pow(promTiempoStl, 2) * nExperimentos) /
                            (nExperimentos - 1));

        dataExperimento[0][c] = to_string(promTiempoAbierto);
        dataExperimento[1][c] = to_string(promTiempoLinear);
        dataExperimento[2][c] = to_string(promTiempoQuad);
        dataExperimento[3][c] = to_string(promTiempoDoble);
        dataExperimento[4][c] = to_string(promTiempoStl);

        desviaciones[0][c] = to_string(dvAbierto);
        desviaciones[1][c] = to_string(dvLinear);
        desviaciones[2][c] = to_string(dvQuad);
        desviaciones[3][c] = to_string(dvDoble);
        desviaciones[4][c] = to_string(dvStl);

        ++c;
    }

    write_data(features, dataExperimento, "../resultados/busquedas1_id.csv");

    write_data(features, desviaciones, "../resultados/dv_busquedas1_id.csv");

    OpenHashingMap<string, data_struct> abiertoStr;
    HashLinear<string, data_struct> linearStr;
    QuadMap<string, data_struct> quadStr;
    DoubleHash<string, data_struct> dobleStr;
    unordered_map<string, data_struct> stlStr;
    /* Insertamos los datos */
    for (size_t i = 0; i < datos.size(); ++i) {
        abiertoStr.put(datos[i].username, datos[i]);
        linearStr.put(datos[i].username, datos[i]);
        quadStr.put(datos[i].username, datos[i]);
        dobleStr.put(datos[i].username, datos[i]);
        stlStr.insert({datos[i].username, datos[i]});
    }

    /* Para username */
    c = 1;
    for (auto cuenta : nBusquedas) {
        cout << "### Buscando tipo 1, usr, cuenta ###" << cuenta << endl;
        /* Mapas que usaremos para username */
        abiertoStr = OpenHashingMap<string, data_struct>();
        linearStr = HashLinear<string, data_struct>();
        quadStr = QuadMap<string, data_struct>();
        dobleStr = DoubleHash<string, data_struct>();
        stlStr = unordered_map<string, data_struct>();

        double promTiempoAbierto = 0, promTiempoLinear = 0, promTiempoQuad = 0,
               promTiempoDoble = 0, promTiempoStl;

        double dvAbiertoL = 0, dvLinearL = 0, dvQuadL = 0, dvDobleL = 0,
               dvStlL = 0;
        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Tiempo de busqueda con llaves de username */
            double tiempoAbierto = searchTimer(abiertoStr, datos, cuenta, 0);
            double tiempoLinear = searchTimer(linearStr, datos, cuenta, 0);
            double tiempoQuad = searchTimer(quadStr, datos, cuenta, 0);
            double tiempoDoble = searchTimer(dobleStr, datos, cuenta, 0);
            double tiempoStl = searchTimer(stlStr, datos, cuenta, 0);

            promTiempoAbierto += tiempoAbierto;
            promTiempoLinear += tiempoLinear;
            promTiempoQuad += tiempoQuad;
            promTiempoDoble += tiempoDoble;
            promTiempoStl += tiempoStl;

            dvAbiertoL += pow(tiempoAbierto, 2);
            dvLinearL += pow(tiempoLinear, 2);
            dvQuadL += pow(tiempoQuad, 2);
            dvDobleL += pow(tiempoDoble, 2);
            dvStlL += pow(tiempoStl, 2);
        }

        promTiempoAbierto /= nExperimentos;
        promTiempoLinear /= nExperimentos;
        promTiempoQuad /= nExperimentos;
        promTiempoDoble /= nExperimentos;
        promTiempoStl /= nExperimentos;

        double dvAbierto =
            sqrt((dvAbiertoL - pow(promTiempoAbierto, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvLinear =
            sqrt((dvLinearL - pow(promTiempoLinear, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvQuad =
            sqrt((dvQuadL - pow(promTiempoQuad, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvDoble =
            sqrt((dvDobleL - pow(promTiempoDoble, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvStl = sqrt((dvStlL - pow(promTiempoStl, 2) * nExperimentos) /
                            (nExperimentos - 1));

        dataExperimento[0][c] = to_string(promTiempoAbierto);
        dataExperimento[1][c] = to_string(promTiempoLinear);
        dataExperimento[2][c] = to_string(promTiempoQuad);
        dataExperimento[3][c] = to_string(promTiempoDoble);
        dataExperimento[4][c] = to_string(promTiempoStl);

        desviaciones[0][c] = to_string(dvAbierto);
        desviaciones[1][c] = to_string(dvLinear);
        desviaciones[2][c] = to_string(dvQuad);
        desviaciones[3][c] = to_string(dvDoble);
        desviaciones[4][c] = to_string(dvStl);

        ++c;
    }

    write_data(features, dataExperimento,
               "../resultados/busquedas1_username.csv");

    write_data(features, desviaciones,
               "../resultados/dv_busquedas1_username.csv");
}

void searchTimeTestTipo2(vector<data_struct>& datosInsercion,
                         vector<data_struct>& datosBusqueda,
                         size_t nExperimentos, vector<size_t> nBusquedas) {

    OpenHashingMap<unsigned long long, data_struct> abiertoUl;
    HashLinear<unsigned long long, data_struct> linearUl;
    QuadMap<unsigned long long, data_struct> quadUl;
    DoubleHash<unsigned long long, data_struct> dobleUl;
    unordered_map<unsigned long long, data_struct> stlUl;

    /* TODO: Hacer función insertData para dejar de repetir codigo de insercion
     */
    /* Insertamos los datos */
    for (size_t i = 0; i < datosInsercion.size() / 2; ++i) {
        abiertoUl.put(datosInsercion[i].user_id, datosInsercion[i]);
        linearUl.put(datosInsercion[i].user_id, datosInsercion[i]);
        quadUl.put(datosInsercion[i].user_id, datosInsercion[i]);
        dobleUl.put(datosInsercion[i].user_id, datosInsercion[i]);
        stlUl.insert({datosInsercion[i].user_id, datosInsercion[i]});
    }

    /*
     * Los datos se guardaran en cuatro filas, cada una con las columnas:
     * tipo_mapa, cuentas_1000, cuentas_5000 ...
     */
    vector<vector<string>> dataExperimento(
        5, vector<string>(nBusquedas.size() + 1, ""));
    dataExperimento[0][0] = "hashing_abierto";
    dataExperimento[1][0] = "hashing_cerrado_lineal";
    dataExperimento[2][0] = "hashing_cerrado_cuadratico";
    dataExperimento[3][0] = "hashing_cerrado_doble";
    dataExperimento[4][0] = "std::unordered_map";
    /* También habra otro vector con las desviaciones estándar. */
    vector<vector<string>> desviaciones(dataExperimento);

    /*
     * Se harán 1000 busquedas de elementos no existentes para las 1000
     * busquedas. En vista de que ingresaremos los valores en orden, los que
     * siempre quedarán sin insertar serán los de índices 17000 hacia adelante.
     * Buscaremos aquellos.
     */

    size_t c = 1;
    for (auto cuenta : nBusquedas) {
        cout << "### Buscando tipo 2, id, cuenta ###" << cuenta << endl;

        double promTiempoAbierto = 0, promTiempoLinear = 0, promTiempoQuad = 0,
               promTiempoDoble = 0, promTiempoStl = 0;

        double dvAbiertoL = 0, dvLinearL = 0, dvQuadL = 0, dvDobleL = 0,
               dvStlL = 0;
        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Tiempo de busqueda con llaves de user_id */
            double tiempoAbierto =
                searchTimer(abiertoUl, datosBusqueda, cuenta, 0);
            double tiempoLinear =
                searchTimer(linearUl, datosBusqueda, cuenta, 0);
            double tiempoQuad = searchTimer(quadUl, datosBusqueda, cuenta, 0);
            double tiempoDoble = searchTimer(dobleUl, datosBusqueda, cuenta, 0);
            double tiempoStl = searchTimer(stlUl, datosBusqueda, cuenta, 0);

            promTiempoAbierto += tiempoAbierto;
            promTiempoLinear += tiempoLinear;
            promTiempoQuad += tiempoQuad;
            promTiempoDoble += tiempoDoble;
            promTiempoStl += tiempoStl;

            dvAbiertoL += pow(tiempoAbierto, 2);
            dvLinearL += pow(tiempoLinear, 2);
            dvQuadL += pow(tiempoQuad, 2);
            dvDobleL += pow(tiempoDoble, 2);
            dvStlL += pow(tiempoStl, 2);
        }

        promTiempoAbierto /= nExperimentos;
        promTiempoLinear /= nExperimentos;
        promTiempoQuad /= nExperimentos;
        promTiempoDoble /= nExperimentos;
        promTiempoStl /= nExperimentos;

        double dvAbierto =
            sqrt((dvAbiertoL - pow(promTiempoAbierto, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvLinear =
            sqrt((dvLinearL - pow(promTiempoLinear, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvQuad =
            sqrt((dvQuadL - pow(promTiempoQuad, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvDoble =
            sqrt((dvDobleL - pow(promTiempoDoble, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvStl = sqrt((dvStlL - pow(promTiempoStl, 2) * nExperimentos) /
                            (nExperimentos - 1));

        dataExperimento[0][c] = to_string(promTiempoAbierto);
        dataExperimento[1][c] = to_string(promTiempoLinear);
        dataExperimento[2][c] = to_string(promTiempoQuad);
        dataExperimento[3][c] = to_string(promTiempoDoble);
        dataExperimento[4][c] = to_string(promTiempoStl);

        desviaciones[0][c] = to_string(dvAbierto);
        desviaciones[1][c] = to_string(dvLinear);
        desviaciones[2][c] = to_string(dvQuad);
        desviaciones[3][c] = to_string(dvDoble);
        desviaciones[4][c] = to_string(dvStl);

        ++c;
    }

    vector<string> features = {"mapa"};
    for (auto cuenta : nBusquedas) {
        features.push_back(to_string(cuenta));
    }

    write_data(features, dataExperimento, "../resultados/busquedas2_id.csv");

    write_data(features, desviaciones, "../resultados/dv_busquedas2_id.csv");

    OpenHashingMap<string, data_struct> abiertoStr;
    HashLinear<string, data_struct> linearStr;
    QuadMap<string, data_struct> quadStr;
    DoubleHash<string, data_struct> dobleStr;
    unordered_map<string, data_struct> stlStr;

    for (size_t i = 0; i < datosInsercion.size() / 2; ++i) {
        abiertoStr.put(datosInsercion[i].username, datosInsercion[i]);
        linearStr.put(datosInsercion[i].username, datosInsercion[i]);
        quadStr.put(datosInsercion[i].username, datosInsercion[i]);
        dobleStr.put(datosInsercion[i].username, datosInsercion[i]);
        stlStr.insert({datosInsercion[i].username, datosInsercion[i]});
    }

    c = 1;
    for (auto cuenta : nBusquedas) {
        cout << "### Buscando tipo 2, usr, cuenta ###" << cuenta << endl;
        double promTiempoAbierto = 0, promTiempoLinear = 0, promTiempoQuad = 0,
               promTiempoDoble = 0, promTiempoStl = 0;

        double dvAbiertoL = 0, dvLinearL = 0, dvQuadL = 0, dvDobleL = 0,
               dvStlL = 0;

        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Tiempo de busqueda con llaves de username */
            double tiempoAbierto =
                searchTimer(abiertoStr, datosBusqueda, cuenta, 0);
            double tiempoLinear =
                searchTimer(linearStr, datosBusqueda, cuenta, 0);
            double tiempoQuad = searchTimer(quadStr, datosBusqueda, cuenta, 0);
            double tiempoDoble =
                searchTimer(dobleStr, datosBusqueda, cuenta, 0);
            double tiempoStl = searchTimer(stlStr, datosBusqueda, cuenta, 0);

            promTiempoAbierto += tiempoAbierto;
            promTiempoLinear += tiempoLinear;
            promTiempoQuad += tiempoQuad;
            promTiempoDoble += tiempoDoble;
            promTiempoStl += tiempoStl;

            dvAbiertoL += pow(tiempoAbierto, 2);
            dvLinearL += pow(tiempoLinear, 2);
            dvQuadL += pow(tiempoQuad, 2);
            dvDobleL += pow(tiempoDoble, 2);
            dvStlL += pow(tiempoStl, 2);
        }

        promTiempoAbierto /= nExperimentos;
        promTiempoLinear /= nExperimentos;
        promTiempoQuad /= nExperimentos;
        promTiempoDoble /= nExperimentos;
        promTiempoStl /= nExperimentos;

        double dvAbierto =
            sqrt((dvAbiertoL - pow(promTiempoAbierto, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvLinear =
            sqrt((dvLinearL - pow(promTiempoLinear, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvQuad =
            sqrt((dvQuadL - pow(promTiempoQuad, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvDoble =
            sqrt((dvDobleL - pow(promTiempoDoble, 2) * nExperimentos) /
                 (nExperimentos - 1));
        double dvStl = sqrt((dvStlL - pow(promTiempoStl, 2) * nExperimentos) /
                            (nExperimentos - 1));

        dataExperimento[0][c] = to_string(promTiempoAbierto);
        dataExperimento[1][c] = to_string(promTiempoLinear);
        dataExperimento[2][c] = to_string(promTiempoQuad);
        dataExperimento[3][c] = to_string(promTiempoDoble);
        dataExperimento[4][c] = to_string(promTiempoStl);

        desviaciones[0][c] = to_string(dvAbierto);
        desviaciones[1][c] = to_string(dvLinear);
        desviaciones[2][c] = to_string(dvQuad);
        desviaciones[3][c] = to_string(dvDoble);
        desviaciones[4][c] = to_string(dvStl);

        ++c;
    }

    write_data(features, dataExperimento,
               "../resultados/busquedas2_username.csv");

    write_data(features, desviaciones,
               "../resultados/dv_busquedas2_username.csv");
}

bool testFuncionamiento(vector<data_struct>& datos) {
    OpenHashingMap<unsigned long long, data_struct> abiertoUl{};
    HashLinear<unsigned long long, data_struct> linearUl{};
    QuadMap<unsigned long long, data_struct> quadUl{};
    DoubleHash<unsigned long long, data_struct> dobleUl{};

    cout << "### Testing de funcionamiento ###\n";
    for (size_t i = 0; i < datos.size(); ++i) {
        abiertoUl.put(datos[i].user_id, datos[i]);
        linearUl.put(datos[i].user_id, datos[i]);
        quadUl.put(datos[i].user_id, datos[i]);
        dobleUl.put(datos[i].user_id, datos[i]);
    }
    cout << "X Inserciones para userid\n";

    for (size_t i = 0; i < datos.size(); ++i) {
        std::optional<data_struct> datoAbierto =
            abiertoUl.get(datos[i].user_id);
        std::optional<data_struct> datoLinear = abiertoUl.get(datos[i].user_id);
        std::optional<data_struct> datoQuad = abiertoUl.get(datos[i].user_id);
        std::optional<data_struct> datoDoble = abiertoUl.get(datos[i].user_id);

        if (!datoAbierto || !(datoAbierto.value() == datos[i])) {
            cout << "En abierto, error para:\n";
            cout << datos[i];
            return false;
        }
        if (!datoLinear || !(datoLinear.value() == datos[i])) {
            cout << "En linear, error para:\n";
            cout << datos[i];
            return false;
        }
        if (!datoQuad || !(datoQuad.value() == datos[i])) {
            cout << "En quad, error para:\n";
            cout << datos[i];
            return false;
        }
        if (!datoDoble || !(datoDoble.value() == datos[i])) {
            cout << "En doble, error para:\n";
            cout << datos[i];
            return false;
        }
    }

    cout << "X Búsquedas para userid\n";

    /* Ahora para username */
    OpenHashingMap<string, data_struct> abiertoStr{};
    HashLinear<string, data_struct> linearStr{};
    QuadMap<string, data_struct> quadStr{};
    DoubleHash<string, data_struct> dobleStr{};

    for (size_t i = 0; i < datos.size(); ++i) {
        abiertoStr.put(datos[i].username, datos[i]);
        linearStr.put(datos[i].username, datos[i]);
        quadStr.put(datos[i].username, datos[i]);
        dobleStr.put(datos[i].username, datos[i]);
    }

    cout << "X Inserciones para username\n";

    for (size_t i = 0; i < datos.size(); ++i) {
        std::optional<data_struct> datoAbierto =
            abiertoUl.get(datos[i].user_id);
        std::optional<data_struct> datoLinear = abiertoUl.get(datos[i].user_id);
        std::optional<data_struct> datoQuad = abiertoUl.get(datos[i].user_id);
        std::optional<data_struct> datoDoble = abiertoUl.get(datos[i].user_id);

        if (!datoAbierto || !(datoAbierto.value() == datos[i])) {
            cout << "En abierto, error para:\n";
            cout << datos[i];
            return false;
        }
        if (!datoLinear || !(datoLinear.value() == datos[i])) {
            cout << "En linear, error para:\n";
            cout << datos[i];
            return false;
        }
        if (!datoQuad || !(datoQuad.value() == datos[i])) {
            cout << "En quad, error para:\n";
            cout << datos[i];
            return false;
        }
        if (!datoDoble || !(datoDoble.value() == datos[i])) {
            cout << "En doble, error para:\n";
            cout << datos[i];
            return false;
        }
    }

    cout << "X Búsquedas para username\n";
    cout << "### Test de funcionamiento listo ###\n";

    return true;
}

void countCapacities(vector<data_struct>& datos) {
    OpenHashingMap<string, data_struct> mapa;

    /* Insertamos */
    for (size_t i = 0; i < datos.size(); ++i) {
        mapa.put(datos[i].username, datos[i]);
    }

    /* Contamos capacities */
    cout << mapa.getCap() << endl;
}

void doTests(vector<data_struct>& datosReales, vector<data_struct>& datosRandom,
             size_t nExperimentos) {
    vector<size_t> cuentas;
    size_t c = 0;

    while (c < datosReales.size()) {
        c += 1000;
        cuentas.push_back(min(c, datosReales.size()));
    }

    if (!testFuncionamiento(datosReales)) {
        cout << "Problemilla\n";
        return;
    }

    OpenHashingMap<string, data_struct> abiertoStr{};
    HashLinear<string, data_struct> linearStr{};
    QuadMap<string, data_struct> quadStr{};
    DoubleHash<string, data_struct> dobleStr{};

    cout << "### Tamaño de Mapas (sin contar reservas): ###" << endl;
    cout << "Abierto: " << sizeof(abiertoStr) << endl;
    cout << "Lineal Cerrado: " << sizeof(linearStr) << endl;
    cout << "Quad Cerrado: " << sizeof(quadStr) << endl;
    cout << "Doble Cerrado: " << sizeof(dobleStr) << endl;

    cout << "### Calculando Tamaño de Hashing Abierto ###\n";
    countCapacities(datosReales);
    cout << "### Corriendo " << nExperimentos << " experimentos\n";
    cout << "### Probando Inserciones ###\n";
    insertionTimeTest(datosReales, nExperimentos, cuentas);
    cout << "### Probando Busquedas ###\n";
    searchTimeTestTipo1(datosReales, nExperimentos, cuentas);
    searchTimeTestTipo2(datosReales, datosRandom, nExperimentos, cuentas);
    cout << "\n\n### DONE ###\n";
}
