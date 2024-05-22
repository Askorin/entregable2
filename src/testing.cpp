#include "../inc/testing.h"
#include "../inc/map.h"
#include "../inc/data_parsing.h"
#include "../inc/open_hashing_map.h"
#include "../inc/quad_map.h"
#include "../inc/hash_linear.h"
#include <chrono>


using namespace std;

double insertionTimer(HashMap& mapa, vector<data_struct> datos, bool isUserId) {

    chrono::duration<double, milli> delta;
    if (isUserId) {
        auto start = chrono::high_resolution_clock::now();
        for (auto entry : datos) {
            mapa.put(entry.user_id, entry);
        }
        auto end = chrono::high_resolution_clock::now();
        delta = chrono::duration<double, std::milli>(end - start);
    } else {
        auto start = chrono::high_resolution_clock::now();
        for (auto entry : datos) {
            mapa.put(entry.username, entry);
        }
        auto end = chrono::high_resolution_clock::now();
        delta = chrono::duration<double, milli>(end - start);
    }

    // auto delta = chrono::duration_cast<chrono::milliseconds>(end - start);
    /* milisegundos tipo double */

    return delta.count();
}

double insertionTimer(unordered_map<unsigned long long, data_struct>& mapa, vector<data_struct> datos) {

    auto start = chrono::high_resolution_clock::now();
    for (auto entry : datos) {
        mapa.insert({entry.user_id, entry});
    }
    auto end = chrono::high_resolution_clock::now();

    // auto delta = chrono::duration_cast<chrono::milliseconds>(end - start);
    /* milisegundos tipo double */
    auto delta = chrono::duration<double, milli>(end - start);

    return delta.count();
}

double insertionTimer(unordered_map<string, data_struct>& mapa, vector<data_struct> datos) {

    auto start = chrono::high_resolution_clock::now();
    for (auto entry : datos) {
        mapa.insert({entry.username, entry});
    }
    auto end = chrono::high_resolution_clock::now();

    // auto delta = chrono::duration_cast<chrono::milliseconds>(end - start);
    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);

    return delta.count();
}

void timeTest(vector<data_struct> datos) {
    /* Mapas que usaremos para user_id */
    OpenHashingMap abierto = OpenHashingMap();
    HashLinear linear = HashLinear();
    QuadMap quad = QuadMap();
    unordered_map<unsigned long long, data_struct> stl = unordered_map<unsigned long long, data_struct>();;


    /* Tiempo de inserción con llaves de user_id */
    double tiempoAbierto = insertionTimer(abierto, datos, true); 
    double tiempoLinear = insertionTimer(linear, datos, true); 
    double tiempoQuad = insertionTimer(quad, datos, true); 
    double tiempoStl = insertionTimer(stl, datos);

    cout << "############################################" << endl;
    cout << "#                                          #" << endl;
    cout << "#            TIEMPOS CON USERID            #" << endl;
    cout << "#                                          #" << endl;
    cout << "############################################" << endl;
    cout << "---- Tiempo de inserción para hashing abierto ----" << endl;
    cout << tiempoAbierto << " ms\n\n";
    cout << "---- Tiempo de inserción para hashing cerrado, probing lineal ----" << endl;
    cout << tiempoLinear << " ms\n\n";
    cout << "---- Tiempo de inserción para hashing cerrado, probing cuadrático ----" << endl;
    cout << tiempoQuad << " ms\n\n";
    cout << "---- Tiempo de inserción para mapa de la STL ----" << endl;
    cout << tiempoStl << " ms\n\n";

    /* Mapas que usaremos para user_name */
    abierto = OpenHashingMap();
    linear = HashLinear();
    quad = QuadMap();
    stl = unordered_map<unsigned long long, data_struct>();

    /* Tiempo de inserción con llaves de user_id */
    tiempoAbierto = insertionTimer(abierto, datos, false); 
    tiempoLinear = insertionTimer(linear, datos, false); 
    tiempoQuad = insertionTimer(quad, datos, false); 
    tiempoStl = insertionTimer(stl, datos);



    cout << "############################################" << endl;
    cout << "#                                          #" << endl;
    cout << "#           TIEMPOS CON USERNAME           #" << endl;
    cout << "#                                          #" << endl;
    cout << "############################################" << endl;
    cout << "---- Tiempo de inserción para hashing abierto ----" << endl;
    cout << tiempoAbierto << " ms\n\n";
    cout << "---- Tiempo de inserción para hashing cerrado, probing lineal ----" << endl;
    cout << tiempoLinear << " ms\n\n";
    cout << "---- Tiempo de inserción para hashing cerrado, probing cuadrático ----" << endl;
    cout << tiempoQuad << " ms\n\n";
    cout << "---- Tiempo de inserción para mapa de la STL ----" << endl;
    cout << tiempoStl << " ms\n\n";


}

void testFuncionamiento(HashMap& mapa) {
    vector<vector<string>> data = read_csv("../data/universities_followers_no_dups.csv");
    vector<data_struct> convertedData = convertData(data);

    for (auto entry : convertedData) {
        mapa.put(entry.username, entry);
    }

    cout << "Elementos ingresados:  " << mapa.size() << "\n\n";
    cout << "Factor de carga:  " << (float) mapa.size() / 41957 << "\n\n";

    /* Probaremos algunos usernames interesantes */
    data_struct val = mapa.get("pachiamira");
    cout << val << "\n\n";
    val = mapa.get("Pancho3001");
    cout << val << "\n\n";
    val = mapa.get("rwdiazguaita");
    cout << val << "\n\n";

    val = mapa.remove("rwdiazguaita");
    cout << val << "\n\n";

    val = mapa.get("Pancho3001");
    cout << val << "\n\n";
    val = mapa.get("rwdiazguaita");
    cout << val << "\n\n";

    val = mapa.remove("rwdiazguaita");
    cout << val << "\n\n";


    cout << "Elementos ingresados:  " << mapa.size() << "\n\n";
}

