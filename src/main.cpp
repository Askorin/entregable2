#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "../inc/open_hashing_map.h"
/* TODO: Proablemente dejar en un header y compilar por separado */
#include "hashlinear.cpp"
#include "../inc/quad_map.h"

#include <chrono>

using namespace std;
vector<vector<string>> read_csv(string filename) {
    ifstream fin;

    fin.open(filename, ios::in);

    vector<vector<string>> rows;
    string line, temp;
    /* Removemos la primera fila */
    getline(fin, line);
    while (getline(fin, line)) {
        stringstream ss(line);
        vector<string> row = vector<string>(0);
        string column;
        while (getline(ss, column, ',')) {
            row.push_back(column);
        }
        rows.push_back(row);
    }
    return rows;

}

void write_csv(vector<int> mivector, string filename) {
    ofstream fout;
    fout.open(filename, ios::out | ios::trunc);
    fout << "idx,count\n";
    for (size_t i = 0; i < mivector.size(); ++i) {
        fout << i << "," << mivector[i] << "\n";
    }
}



// Función de hasheo para username
size_t h2(string username, size_t m) {

    /* Calcularemos el haschode del string x_0 ... x_d como el polinomio
     * x_d * alpha ^ 0 + x_d-1 * alpha^1 ... x_0 * alpha ^d
     */

    /* Ojo que esto puede hacer overflow */

    /* Utilizamos alpha = 33 como recomendado en el ppt del curso. */
    /* se calcula de manera recursiva como: */
    size_t alpha = 33;
    unsigned long long sum = 0;
    
    for (auto &ch : username) {
        sum = (alpha * sum + (int) ch);
    }


    /* mult mod prime con a, b menores a m (tamaño de la tabla, número primo, quizás). */
    size_t a = 45382, b = 11923;
    
    return (a * sum + b) % m;
}


// Función Hash para el user ID
unsigned long long h1(unsigned long long user_id)
{
    size_t m = 49157, a = 45382, b = 11923;

    return (a * user_id + b) % m;
}



vector<data_struct> convertData(vector<vector<string>> data) {
    vector<data_struct> res = vector<data_struct>();;
    for (auto elemento : data) {
        string university = elemento[0];
        unsigned long long user_id = stoull(elemento[1]);
        string username = elemento[2];
        unsigned int n_tweets = stoul(elemento[3]);
        unsigned int friend_count = stoul(elemento[4]);
        unsigned int follower_count = stoul(elemento[5]);
        string created_at = elemento[6];

        data_struct elementoConvertido = data_struct(university, user_id, username, n_tweets,
                friend_count, follower_count, created_at);
        res.push_back(elementoConvertido);
    }
    return res;
}

void testColisionesUsername() {
    size_t m = 49157;
    vector<vector<string>> data = read_csv("../data/universities_followers_no_dups.csv");
    vector<data_struct> convertedData = convertData(data);


    /* Guardaremos cuenta de las veces que se hasheo a cada indice aquí */
    vector<int> resultados(m, 0);

    for (auto data : convertedData) {
        string username = data.username;
        size_t idx = h2(username, m);
        ++resultados[idx];
    }

    int max = 0;
    int cant_colisiones = 0;

    for (int i = 0; i < resultados.size(); ++i) {
        int count = resultados[i];
        max = count > max ? count : max;
        if (count > 1) {
            cant_colisiones += count - 1;
        }
        
    }

    cout << "cantidad de veces máxima hasheada al mismo índice: " << max << endl;
    cout << "cantidad de colisiones: " << cant_colisiones << endl;

    write_csv(resultados, "../data/results.csv");
}

void testColisionesUserId() {
    size_t m = 49157;
    vector<vector<string>> data = read_csv("../data/universities_followers_no_dups.csv");
    vector<data_struct> convertedData = convertData(data);


    /* Guardaremos cuenta de las veces que se hasheo a cada indice aquí */
    vector<int> resultados(m, 0);

    for (auto data : convertedData) {
        unsigned long long userId = data.user_id;
        size_t idx = h1(userId);
        ++resultados[idx];
    }

    int max = 0;
    int cant_colisiones = 0;

    for (int i = 0; i < resultados.size(); ++i) {
        int count = resultados[i];
        max = count > max ? count : max;
        if (count > 1) {
            cant_colisiones += count - 1;
        }
        
    }

    cout << "cantidad de veces máxima hasheada al mismo índice: " << max << endl;
    cout << "cantidad de colisiones: " << cant_colisiones << endl;

    write_csv(resultados, "../data/results.csv");
}

void testEncadenamiento() {
    vector<vector<string>> data = read_csv("../data/universities_followers_no_dups.csv");
    vector<data_struct> convertedData = convertData(data);
    OpenHashingMap mimapa = OpenHashingMap();

    for (auto entry : convertedData) {
        mimapa.put(entry.username, entry);
    }

    cout << "Elementos ingresados:  " << mimapa.size() << "\n\n";
    cout << "Factor de carga:  " << (float) mimapa.size() / 41957 << "\n\n";

    /* Probaremos algunos usernames interesantes */
    data_struct val = mimapa.get("pachiamira");
    cout << val << "\n\n";
    val = mimapa.get("Pancho3001");
    cout << val << "\n\n";
    val = mimapa.get("rwdiazguaita");
    cout << val << "\n\n";

    val = mimapa.remove("rwdiazguaita");
    cout << val << "\n\n";

    val = mimapa.get("Pancho3001");
    cout << val << "\n\n";
    val = mimapa.get("rwdiazguaita");
    cout << val << "\n\n";

    val = mimapa.remove("rwdiazguaita");
    cout << val << "\n\n";


    cout << "Elementos ingresados:  " << mimapa.size() << "\n\n";
}

void testLineal() {
    vector<vector<string>> data = read_csv("../data/universities_followers_no_dups.csv");
    vector<data_struct> convertedData = convertData(data);
    HashLinear mimapa = HashLinear();

    for (auto entry : convertedData) {
        mimapa.put(entry.user_id, entry);
    }

    cout << "Elementos ingresados:  " << mimapa.size() << "\n\n";
    cout << "Factor de carga:  " << (float) mimapa.size() / 41957 << "\n\n";

    /* Probaremos algunos usernames interesantes */

    /* Imprime pachiamira */
    data_struct val = mimapa.get(32631258);
    cout << val << "\n\n";
    /* Imprime Pancho3001 */
    val = mimapa.get(301185416);
    cout << val << "\n\n";
    /* Imprime rwdiazguaita */
    val = mimapa.get(101859333);
    cout << val << "\n\n";

    /* Imprime rwdiazguaita */
    data_struct rwdiaz = mimapa.remove(101859333);
    cout << rwdiaz << "\n\n";

    /* Imprime Pancho3001 */
    val = mimapa.get(301185416);
    cout << val << "\n\n";
    /* Imprime nulo */
    val = mimapa.get(101859333);
    cout << val << "\n\n";

    /* Imprime nulo */
    val = mimapa.remove(101859333);
    cout << val << "\n\n";

    /* Imprime nulo */
    val = mimapa.get(101859333);
    cout << val << "\n\n";

    /* Imprime nulo */
    mimapa.remove(101859333);
    mimapa.put(rwdiaz.user_id, rwdiaz);
    mimapa.put(rwdiaz.user_id, val);
    val = mimapa.get(rwdiaz.user_id);
    cout << val << "\n\n";


    cout << "Elementos ingresados:  " << mimapa.size() << "\n\n";
}


double insertionTimer(HashMap& mapa, vector<data_struct> datos, bool user_id) {

    auto start = chrono::high_resolution_clock::now();
    for (auto entry : datos) {
        if (user_id) mapa.put(entry.user_id, entry);
        else mapa.put(entry.username, entry);
    }
    auto end = chrono::high_resolution_clock::now();

    // auto delta = chrono::duration_cast<chrono::milliseconds>(end - start);
    /* milisegundos tipo double */
    auto delta = chrono::duration<double, std::milli>(end - start);

    return delta.count();
}

void timeTest() {

    /* Leemos los datos y convertimos a el struct */
    vector<vector<string>> data = read_csv("../data/universities_followers_no_dups.csv");
    vector<data_struct> convertedData = convertData(data);

    /* Mapas de hashing abierto y cerrado */
    OpenHashingMap abierto = OpenHashingMap();
    HashLinear linear = HashLinear();
    QuadMap quad = QuadMap();


    /* Tiempo de inserción con llaves de user_id */
    double tiempoAbierto = insertionTimer(abierto, convertedData, true); 
    double tiempoLinear = insertionTimer(linear, convertedData, true); 
    double tiempoQuad = insertionTimer(quad, convertedData, true); 

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

}


int main() {
        
    // testColisionesUsername();
    // testColisionesUserId();
    // testEncadenamiento(); 
    // testLineal();
    timeTest();

    return 0;
}
