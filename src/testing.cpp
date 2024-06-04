#include "../inc/testing.h"
#include "../inc/map.h"
#include "../inc/data_parsing.h"
#include "../inc/open_hashing_map.h"
#include "../inc/quad_map.h"
#include "../inc/hash_linear.h"
#include "../inc/double_map.h"
#include <chrono>
#include <algorithm>


using namespace std;


double insertionTimer(HashMap<unsigned long long, data_struct>& mapa, vector<data_struct>& datos, size_t count) {

    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        auto volatile result = mapa.put(datos[i].user_id, datos[i]);
    }
    auto end = chrono::high_resolution_clock::now();

    // auto delta = chrono::duration_cast<chrono::milliseconds>(end - start);
    /* milisegundos tipo double */
    auto delta = chrono::duration<double, milli>(end - start);

    return delta.count();
}

double insertionTimer(HashMap<string, data_struct>& mapa, vector<data_struct>& datos, size_t count) {

    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        auto volatile result = mapa.put(datos[i].username, datos[i]);
    }
    auto end = chrono::high_resolution_clock::now();

    // auto delta = chrono::duration_cast<chrono::milliseconds>(end - start);
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

    // auto delta = chrono::duration_cast<chrono::milliseconds>(end - start);
    /* milisegundos tipo double */
    auto delta = chrono::duration<double, milli>(end - start);

    return delta.count();
}

double insertionTimer(unordered_map<string, data_struct>& mapa, vector<data_struct>& datos, size_t count) {

    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        auto volatile result = mapa.insert({datos[i].username, datos[i]});
    }
    auto end = chrono::high_resolution_clock::now();

    // auto delta = chrono::duration_cast<chrono::milliseconds>(end - start);
    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);

    return delta.count();
}


double searchTimer(HashMap<unsigned long long, data_struct>& mapa, vector<data_struct>& datos,
    size_t count, size_t idxComienzo) {
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = idxComienzo; i < idxComienzo + count; ++i) {
        auto volatile result = mapa.get(datos[i].user_id);
    }

    auto end = chrono::high_resolution_clock::now();
    auto delta = chrono::duration<double, std::milli>(end - start);
    return delta.count();
}

double searchTimer(HashMap<string, data_struct>& mapa, vector<data_struct>& datos,
        size_t count, size_t idxComienzo) {
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = idxComienzo; i < idxComienzo + count; ++i) {
        auto volatile result = mapa.get(datos[i].username);
    }

    auto end = chrono::high_resolution_clock::now();

    // auto delta = chrono::duration_cast<chrono::milliseconds>(end - start);
    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);
    return delta.count();

}

double searchTimer(unordered_map<unsigned long long, data_struct>& mapa, vector<data_struct>& datos,
        size_t count, size_t idxComienzo) {
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = idxComienzo; i < idxComienzo + count; ++i) {
        auto volatile result = mapa.find(datos[i].user_id);
    }

    auto end = chrono::high_resolution_clock::now();

    // auto delta = chrono::duration_cast<chrono::milliseconds>(end - start);
    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);
    return delta.count();
}

double searchTimer(unordered_map<string, data_struct>& mapa, vector<data_struct>& datos,
        size_t count, size_t idxComienzo) {
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = idxComienzo; i < idxComienzo + count; ++i) {
        auto volatile result = mapa.find(datos[i].username);
    }

    auto end = chrono::high_resolution_clock::now();

    // auto delta = chrono::duration_cast<chrono::milliseconds>(end - start);
    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);
    return delta.count();

}

void insertionTimeTest(vector<data_struct>& datos, size_t nExperimentos, vector<size_t> cuentas) {
    OpenHashingMap<unsigned long long, data_struct> abiertoUl;
    HashLinear<unsigned long long, data_struct> linearUl;
    QuadMap<unsigned long long, data_struct> quadUl;
    DoubleHash<unsigned long long, data_struct> dobleUl;
    unordered_map<unsigned long long, data_struct> stlUl;


    /* 
     * Los datos se guardaran en cuatro filas, cada una con las columnas:
     * tipo_mapa, cuentas_1000, cuentas_5000 ... 
     */
    vector<vector<string>> data_experimento = vector<vector<string>>(5, vector<string>(cuentas.size() + 1, ""));
    data_experimento[0][0] = "hashing_abierto";
    data_experimento[1][0] = "hashing_cerrado_lineal";
    data_experimento[2][0] = "hashing_cerrado_cuadratico";
    data_experimento[3][0] = "hashing_cerrado_doble";
    data_experimento[4][0] = "std::unordered_map";
    

    size_t c = 1;
    for (auto cuenta : cuentas) {
        cout << "### Insertando, id, cuenta ###" << cuenta << endl;
        double tiempoAbierto = 0, tiempoLinear = 0, tiempoQuad = 0, tiempoStl = 0, tiempoDoble = 0;
        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Mapas que usaremos para user_id */
            abiertoUl = OpenHashingMap<unsigned long long, data_struct>();
            linearUl = HashLinear<unsigned long long, data_struct>();
            quadUl = QuadMap<unsigned long long, data_struct>();
            dobleUl = DoubleHash<unsigned long long, data_struct>();
            stlUl = unordered_map<unsigned long long, data_struct>();

            /* Tiempo de inserción con llaves de user_id */
            tiempoAbierto += insertionTimer(abiertoUl, datos, cuenta);
            tiempoLinear += insertionTimer(linearUl, datos, cuenta);
            tiempoQuad += insertionTimer(quadUl, datos, cuenta);
            tiempoDoble += insertionTimer(dobleUl, datos, cuenta);
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

    vector<string> features = {"mapa"};
    for (auto cuenta : cuentas) {
        features.push_back(to_string(cuenta));
    }
    
    write_data(features, 
            data_experimento, "../resultados/inserciones_id.csv");

    OpenHashingMap<string, data_struct> abiertoStr;
    HashLinear<string, data_struct> linearStr;
    QuadMap<string, data_struct> quadStr;
    DoubleHash<string, data_struct> dobleStr;
    unordered_map<string, data_struct> stlStr;

    c = 1;
    for (auto cuenta : cuentas) {
        cout << "### Insertando, usr, cuenta ###" << cuenta << endl;
        double tiempoAbierto = 0, tiempoLinear = 0, tiempoQuad = 0, tiempoStl = 0, tiempoDoble = 0;
        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Mapas que usaremos para username */
            abiertoStr = OpenHashingMap<string, data_struct>();
            linearStr = HashLinear<string, data_struct>();
            quadStr = QuadMap<string, data_struct>();
            dobleStr = DoubleHash<string, data_struct>();
            stlStr = unordered_map<string, data_struct>();

            /* Tiempo de inserción con llaves de username */
            tiempoAbierto += insertionTimer(abiertoStr, datos, cuenta); 
            tiempoLinear += insertionTimer(linearStr, datos, cuenta); 
            tiempoQuad += insertionTimer(quadStr, datos, cuenta); 
            tiempoDoble += insertionTimer(dobleStr, datos, cuenta); 
            tiempoStl += insertionTimer(stlStr, datos, cuenta);
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

    write_data(features, 
            data_experimento, "../resultados/inserciones_username.csv");

}


void searchTimeTestTipo1(vector<data_struct>& datos, size_t nExperimentos, vector<size_t> nBusquedas) {
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
    vector<vector<string>> data_experimento(5, vector<string>(nBusquedas.size() + 1));
    data_experimento[0][0] = "hashing_abierto";
    data_experimento[1][0] = "hashing_cerrado_lineal";
    data_experimento[2][0] = "hashing_cerrado_cuadratico";
    data_experimento[3][0] = "hashing_cerrado_doble";
    data_experimento[4][0] = "std::unordered_map";

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


        // features.push_back(to_string(abiertoUl.getLoadFactor()));
        features.push_back(to_string(cuenta));


        double tiempoAbierto = 0, tiempoLinear = 0, tiempoQuad = 0, tiempoStl = 0, tiempoDoble = 0;
        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Tiempo de busqueda con llaves de user_id */
            tiempoAbierto += searchTimer(abiertoUl, datos, cuenta, 0);
            tiempoLinear += searchTimer(linearUl, datos, cuenta, 0);
            tiempoQuad += searchTimer(quadUl, datos, cuenta, 0);
            tiempoDoble += searchTimer(dobleUl, datos, cuenta, 0);
            tiempoStl += searchTimer(stlUl, datos, cuenta, 0);
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

    write_data(features, 
            data_experimento, "../resultados/busquedas1_id.csv");

    OpenHashingMap<string, data_struct> abiertoStr;
    HashLinear<string, data_struct> linearStr;
    QuadMap<string, data_struct> quadStr;
    DoubleHash<string, data_struct> dobleStr;
    unordered_map<string, data_struct> stlStr;

    /* Para username */
    c = 1;
    for (auto cuenta : nBusquedas) {
        cout << "### Buscando tipo 1, usr, cuenta ###" << cuenta << endl;
        /* Creamos un subconjunto aleatorio del dataset de {cuenta} elementos */
        // sample(datos.begin(), datos.end(), back_inserter(subset), cuenta, std::mt19937{random_device{}()});
        //

        /* Mapas que usaremos para username */
        abiertoStr = OpenHashingMap<string, data_struct>();
        linearStr = HashLinear<string, data_struct>();
        quadStr = QuadMap<string, data_struct>();
        dobleStr = DoubleHash<string, data_struct>();
        stlStr = unordered_map<string, data_struct>();

        /* TODO: Hacer función insertData para dejar de repetir codigo de insercion */
        /* Insertamos los datos */
        for (size_t i = 0; i < datos.size(); ++i) {
            abiertoStr.put(datos[i].username, datos[i]);
            linearStr.put(datos[i].username, datos[i]);
            quadStr.put(datos[i].username, datos[i]);
            dobleStr.put(datos[i].username, datos[i]);
            stlStr.insert({datos[i].username, datos[i]});
        }


        double tiempoAbierto = 0, tiempoLinear = 0, tiempoQuad = 0, tiempoStl = 0, tiempoDoble = 0;
        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Tiempo de busqueda con llaves de username */
            tiempoAbierto += searchTimer(abiertoStr, datos, cuenta, 0); 
            tiempoLinear += searchTimer(linearStr, datos, cuenta, 0); 
            tiempoQuad += searchTimer(quadStr, datos, cuenta, 0); 
            tiempoDoble += searchTimer(dobleStr, datos, cuenta, 0);
            tiempoStl += searchTimer(stlStr, datos, cuenta, 0);
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


    write_data(features, 
            data_experimento, "../resultados/busquedas1_username.csv");
}


void searchTimeTestTipo2(vector<data_struct>& datosInsercion, vector<data_struct>& datosBusqueda,
        size_t nExperimentos, vector<size_t> nBusquedas) {

    OpenHashingMap<unsigned long long, data_struct> abiertoUl;
    HashLinear<unsigned long long, data_struct> linearUl;
    QuadMap<unsigned long long, data_struct> quadUl;
    DoubleHash<unsigned long long, data_struct> dobleUl;
    unordered_map<unsigned long long, data_struct> stlUl;


    /* TODO: Hacer función insertData para dejar de repetir codigo de insercion */
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
    vector<vector<string>> data_experimento(5, vector<string>(nBusquedas.size() + 1, ""));
    data_experimento[0][0] = "hashing_abierto";
    data_experimento[1][0] = "hashing_cerrado_lineal";
    data_experimento[2][0] = "hashing_cerrado_cuadratico";
    data_experimento[3][0] = "hashing_cerrado_doble";
    data_experimento[4][0] = "std::unordered_map";

    /*
     * Se harán 1000 busquedas de elementos no existentes para las 1000 busquedas.
     * En vista de que ingresaremos los valores en orden, los que siempre quedarán sin insertar
     * serán los de índices 17000 hacia adelante. Buscaremos aquellos.
     */

    size_t c = 1;
    for (auto cuenta : nBusquedas) {
        cout << "### Buscando tipo 2, id, cuenta ###" << cuenta << endl;
        double tiempoAbierto = 0, tiempoLinear = 0, tiempoQuad = 0, tiempoDoble = 0, tiempoStl = 0;
        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Tiempo de busqueda con llaves de user_id */
            tiempoAbierto += searchTimer(abiertoUl, datosBusqueda, cuenta, 0); 
            tiempoLinear += searchTimer(linearUl, datosBusqueda, cuenta, 0); 
            tiempoQuad += searchTimer(quadUl, datosBusqueda, cuenta, 0); 
            tiempoDoble += searchTimer(dobleUl, datosBusqueda, cuenta, 0); 
            tiempoStl += searchTimer(stlUl, datosBusqueda, cuenta, 0);
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

    vector<string> features = {"mapa"};
    for (auto cuenta : nBusquedas) {
        features.push_back(to_string(cuenta));
    }

    write_data(features, 
            data_experimento, "../resultados/busquedas2_id.csv");



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
        /* Mapas que usaremos para username */

        double tiempoAbierto = 0, tiempoLinear = 0, tiempoQuad = 0, tiempoDoble = 0, tiempoStl = 0;
        for (size_t i = 0; i < nExperimentos; ++i) {
            /* Tiempo de busqueda con llaves de username */
            tiempoAbierto += searchTimer(abiertoStr, datosBusqueda, cuenta, 0); 
            tiempoLinear += searchTimer(linearStr, datosBusqueda, cuenta, 0); 
            tiempoQuad += searchTimer(quadStr, datosBusqueda, cuenta, 0); 
            tiempoDoble += searchTimer(dobleStr, datosBusqueda, cuenta, 0); 
            tiempoStl += searchTimer(stlStr, datosBusqueda, cuenta, 0);
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

    write_data(features, 
            data_experimento, "../resultados/busquedas2_username.csv");
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
        std::optional<data_struct> datoAbierto = abiertoUl.get(datos[i].user_id);
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
        std::optional<data_struct> datoAbierto = abiertoUl.get(datos[i].user_id);
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


void doTests(vector<data_struct>& datosReales, vector<data_struct>& datosRandom, size_t nExperimentos) {
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

 


