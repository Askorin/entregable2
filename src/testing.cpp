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

double insertionTimer(HashMap<unsigned long long, dataStruct>& mapa,
                      vector<dataStruct>& datos, size_t count) {

    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        auto volatile result = mapa.put(datos[i].userId, datos[i]);
    }
    auto end = chrono::high_resolution_clock::now();

    /* milisegundos tipo double */
    auto delta = chrono::duration<double, milli>(end - start);

    return delta.count();
}

double insertionTimer(HashMap<string, dataStruct>& mapa,
                      vector<dataStruct>& datos, size_t count) {

    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        auto volatile result = mapa.put(datos[i].userName, datos[i]);
    }
    auto end = chrono::high_resolution_clock::now();

    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);

    return delta.count();
}

double insertionTimer(unordered_map<unsigned long long, dataStruct>& mapa,
                      vector<dataStruct>& datos, size_t count) {

    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        auto volatile result = mapa.insert({datos[i].userId, datos[i]});
    }
    auto end = chrono::high_resolution_clock::now();

    /* milisegundos tipo double */
    auto delta = chrono::duration<double, milli>(end - start);

    return delta.count();
}

double insertionTimer(unordered_map<string, dataStruct>& mapa,
                      vector<dataStruct>& datos, size_t count) {

    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        auto volatile result = mapa.insert({datos[i].userName, datos[i]});
    }
    auto end = chrono::high_resolution_clock::now();

    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);

    return delta.count();
}

double searchTimer(HashMap<unsigned long long, dataStruct>& mapa,
                   vector<dataStruct>& datos, size_t count,
                   size_t idxComienzo) {
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = idxComienzo; i < idxComienzo + count; ++i) {
        auto volatile result = mapa.get(datos[i].userId);
    }

    auto end = chrono::high_resolution_clock::now();

    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);
    return delta.count();
}

double searchTimer(HashMap<string, dataStruct>& mapa,
                   vector<dataStruct>& datos, size_t count,
                   size_t idxComienzo) {
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = idxComienzo; i < idxComienzo + count; ++i) {
        auto volatile result = mapa.get(datos[i].userName);
    }

    auto end = chrono::high_resolution_clock::now();

    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);
    return delta.count();
}

double searchTimer(unordered_map<unsigned long long, dataStruct>& mapa,
                   vector<dataStruct>& datos, size_t count,
                   size_t idxComienzo) {
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = idxComienzo; i < idxComienzo + count; ++i) {
        auto volatile result = mapa.find(datos[i].userId);
    }

    auto end = chrono::high_resolution_clock::now();

    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);
    return delta.count();
}

double searchTimer(unordered_map<string, dataStruct>& mapa,
                   vector<dataStruct>& datos, size_t count,
                   size_t idxComienzo) {
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = idxComienzo; i < idxComienzo + count; ++i) {
        auto volatile result = mapa.find(datos[i].userName);
    }

    auto end = chrono::high_resolution_clock::now();

    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);
    return delta.count();
}

void insertionTimeTest(vector<dataStruct>& datos, size_t nExperimentos,
                       vector<size_t> cuentas) {
    OpenHashingMap<unsigned long long, dataStruct> abiertoUl;
    HashLinear<unsigned long long, dataStruct> linearUl;
    QuadMap<unsigned long long, dataStruct> quadUl;
    DoubleHash<unsigned long long, dataStruct> dobleUl;
    unordered_map<unsigned long long, dataStruct> stlUl;

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
            abiertoUl = OpenHashingMap<unsigned long long, dataStruct>();
            linearUl = HashLinear<unsigned long long, dataStruct>();
            quadUl = QuadMap<unsigned long long, dataStruct>();
            dobleUl = DoubleHash<unsigned long long, dataStruct>();
            stlUl = unordered_map<unsigned long long, dataStruct>();

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

    OpenHashingMap<string, dataStruct> abiertoStr;
    HashLinear<string, dataStruct> linearStr;
    QuadMap<string, dataStruct> quadStr;
    DoubleHash<string, dataStruct> dobleStr;
    unordered_map<string, dataStruct> stlStr;

    c = 1;
    for (auto cuenta : cuentas) {
        cout << "### Insertando, usr, cuenta ###" << cuenta << endl;
        double promTiempoAbierto = 0, promTiempoLinear = 0, promTiempoQuad = 0,
               promTiempoDoble = 0, promTiempoStl = 0;

        double dvAbiertoL = 0, dvLinearL = 0, dvQuadL = 0, dvDobleL = 0,
               dvStlL = 0;
        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Mapas que usaremos para username */
            abiertoStr = OpenHashingMap<string, dataStruct>();
            linearStr = HashLinear<string, dataStruct>();
            quadStr = QuadMap<string, dataStruct>();
            dobleStr = DoubleHash<string, dataStruct>();
            stlStr = unordered_map<string, dataStruct>();

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

void searchTimeTestTipo1(vector<dataStruct>& datos, size_t nExperimentos,
                         vector<size_t> nBusquedas) {
    OpenHashingMap<unsigned long long, dataStruct> abiertoUl;
    HashLinear<unsigned long long, dataStruct> linearUl;
    QuadMap<unsigned long long, dataStruct> quadUl;
    DoubleHash<unsigned long long, dataStruct> dobleUl;
    unordered_map<unsigned long long, dataStruct> stlUl;

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
        abiertoUl = OpenHashingMap<unsigned long long, dataStruct>();
        linearUl = HashLinear<unsigned long long, dataStruct>();
        quadUl = QuadMap<unsigned long long, dataStruct>();
        dobleUl = DoubleHash<unsigned long long, dataStruct>();
        stlUl = unordered_map<unsigned long long, dataStruct>();

        /* Insertamos los datos */
        for (size_t i = 0; i < datos.size(); ++i) {
            abiertoUl.put(datos[i].userId, datos[i]);
            linearUl.put(datos[i].userId, datos[i]);
            quadUl.put(datos[i].userId, datos[i]);
            dobleUl.put(datos[i].userId, datos[i]);
            stlUl.insert({datos[i].userId, datos[i]});
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

    OpenHashingMap<string, dataStruct> abiertoStr;
    HashLinear<string, dataStruct> linearStr;
    QuadMap<string, dataStruct> quadStr;
    DoubleHash<string, dataStruct> dobleStr;
    unordered_map<string, dataStruct> stlStr;
    /* Insertamos los datos */
    for (size_t i = 0; i < datos.size(); ++i) {
        abiertoStr.put(datos[i].userName, datos[i]);
        linearStr.put(datos[i].userName, datos[i]);
        quadStr.put(datos[i].userName, datos[i]);
        dobleStr.put(datos[i].userName, datos[i]);
        stlStr.insert({datos[i].userName, datos[i]});
    }

    /* Para username */
    c = 1;
    for (auto cuenta : nBusquedas) {
        cout << "### Buscando tipo 1, usr, cuenta ###" << cuenta << endl;
        /* Mapas que usaremos para username */
        abiertoStr = OpenHashingMap<string, dataStruct>();
        linearStr = HashLinear<string, dataStruct>();
        quadStr = QuadMap<string, dataStruct>();
        dobleStr = DoubleHash<string, dataStruct>();
        stlStr = unordered_map<string, dataStruct>();

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

void searchTimeTestTipo2(vector<dataStruct>& datosInsercion,
                         vector<dataStruct>& datosBusqueda,
                         size_t nExperimentos, vector<size_t> nBusquedas) {

    OpenHashingMap<unsigned long long, dataStruct> abiertoUl;
    HashLinear<unsigned long long, dataStruct> linearUl;
    QuadMap<unsigned long long, dataStruct> quadUl;
    DoubleHash<unsigned long long, dataStruct> dobleUl;
    unordered_map<unsigned long long, dataStruct> stlUl;

    /* TODO: Hacer función insertData para dejar de repetir codigo de insercion
     */
    /* Insertamos los datos */
    for (size_t i = 0; i < datosInsercion.size() / 2; ++i) {
        abiertoUl.put(datosInsercion[i].userId, datosInsercion[i]);
        linearUl.put(datosInsercion[i].userId, datosInsercion[i]);
        quadUl.put(datosInsercion[i].userId, datosInsercion[i]);
        dobleUl.put(datosInsercion[i].userId, datosInsercion[i]);
        stlUl.insert({datosInsercion[i].userId, datosInsercion[i]});
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

    OpenHashingMap<string, dataStruct> abiertoStr;
    HashLinear<string, dataStruct> linearStr;
    QuadMap<string, dataStruct> quadStr;
    DoubleHash<string, dataStruct> dobleStr;
    unordered_map<string, dataStruct> stlStr;

    for (size_t i = 0; i < datosInsercion.size() / 2; ++i) {
        abiertoStr.put(datosInsercion[i].userName, datosInsercion[i]);
        linearStr.put(datosInsercion[i].userName, datosInsercion[i]);
        quadStr.put(datosInsercion[i].userName, datosInsercion[i]);
        dobleStr.put(datosInsercion[i].userName, datosInsercion[i]);
        stlStr.insert({datosInsercion[i].userName, datosInsercion[i]});
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

bool testFuncionamiento(vector<dataStruct>& datos) {
    OpenHashingMap<unsigned long long, dataStruct> abiertoUl{};
    HashLinear<unsigned long long, dataStruct> linearUl{};
    QuadMap<unsigned long long, dataStruct> quadUl{};
    DoubleHash<unsigned long long, dataStruct> dobleUl{};

    cout << "### Testing de funcionamiento ###\n";
    for (size_t i = 0; i < datos.size(); ++i) {
        abiertoUl.put(datos[i].userId, datos[i]);
        linearUl.put(datos[i].userId, datos[i]);
        quadUl.put(datos[i].userId, datos[i]);
        dobleUl.put(datos[i].userId, datos[i]);
    }
    cout << "X Inserciones para userid\n";

    for (size_t i = 0; i < datos.size(); ++i) {
        std::optional<dataStruct> datoAbierto =
            abiertoUl.get(datos[i].userId);
        std::optional<dataStruct> datoLinear = abiertoUl.get(datos[i].userId);
        std::optional<dataStruct> datoQuad = abiertoUl.get(datos[i].userId);
        std::optional<dataStruct> datoDoble = abiertoUl.get(datos[i].userId);

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
    OpenHashingMap<string, dataStruct> abiertoStr{};
    HashLinear<string, dataStruct> linearStr{};
    QuadMap<string, dataStruct> quadStr{};
    DoubleHash<string, dataStruct> dobleStr{};

    for (size_t i = 0; i < datos.size(); ++i) {
        abiertoStr.put(datos[i].userName, datos[i]);
        linearStr.put(datos[i].userName, datos[i]);
        quadStr.put(datos[i].userName, datos[i]);
        dobleStr.put(datos[i].userName, datos[i]);
    }

    cout << "X Inserciones para username\n";

    for (size_t i = 0; i < datos.size(); ++i) {
        std::optional<dataStruct> datoAbierto =
            abiertoUl.get(datos[i].userId);
        std::optional<dataStruct> datoLinear = abiertoUl.get(datos[i].userId);
        std::optional<dataStruct> datoQuad = abiertoUl.get(datos[i].userId);
        std::optional<dataStruct> datoDoble = abiertoUl.get(datos[i].userId);

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

void countCapacities(vector<dataStruct>& datos) {
    OpenHashingMap<string, dataStruct> mapa;

    /* Insertamos */
    for (size_t i = 0; i < datos.size(); ++i) {
        mapa.put(datos[i].userName, datos[i]);
    }

    /* Contamos capacities */
    cout << mapa.getCap() << endl;
}

void doTests(vector<dataStruct>& datosReales, vector<dataStruct>& datosRandom,
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

    OpenHashingMap<string, dataStruct> abiertoStr{};
    HashLinear<string, dataStruct> linearStr{};
    QuadMap<string, dataStruct> quadStr{};
    DoubleHash<string, dataStruct> dobleStr{};

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
