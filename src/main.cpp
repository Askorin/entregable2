#include <iostream>
#include <string>
#include <vector>
#include "../inc/data_parsing.h"
#include "../inc/testing.h"
#include "../inc/open_hashing_map.h"
/* TODO: Proablemente dejar en un header y compilar por separado */
#include "../inc/hash_linear.h"

using namespace std;

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

    for (size_t i = 0; i < resultados.size(); ++i) {
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

    for (size_t i = 0; i < resultados.size(); ++i) {
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




int main() {
        
    /* Leemos los datos y convertimos en vector de data_struct */
    vector<vector<string>> data = read_csv("../data/universities_followers_no_dups.csv");
    vector<data_struct> convertedData = convertData(data);

    /* Los tests */
    // testColisionesUsername();
    // testColisionesUserId();
    // testEncadenamiento(); 
    // testLineal();
    timeTest(convertedData);

    return 0;
}
