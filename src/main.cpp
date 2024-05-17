#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
vector<vector<string>> read_csv(string filename) {
    ifstream fin;

    fin.open(filename, ios::in);

    vector<vector<string>> rows;
    string line, temp;
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


vector<int> eratosthenes(size_t m) {
    vector<int> res = vector<int>();;
    vector<bool> primos(m, true);
    for (size_t p = 2; p * p < m; p++) {
        if (primos[p]) {
            for (size_t i = p * p; i < m; i += p) {
                primos[i] = false;
            }
        }
    }

    for (size_t p = 2; p < m; p++) {
        if (primos[p]) {
            res.push_back(p);
        }
    }
    return res;
}




int main() {
    size_t m = 49157;
    vector<vector<string>> data = read_csv("../data/universities_followers_no_dups.csv");


    /* Guardaremos cuenta de las veces que se hasheo a cada indice aquí */
    vector<int> resultados(m, 0);
    for (size_t i = 1; i < data.size(); ++i) {
        string username = data[i][2];
        size_t idx = h2(username, m);
        ++resultados[idx];
    }

    int max = 0;
    int cant_colisiones = 0;
    for (int count : resultados) {
        max = count > max ? count : max;
        if (count > 1) {
            cant_colisiones += count - 1;
        }
    }
    cout << "cantidad de veces máxima hasheada al mismo índice: " << max << endl;
    cout << "cantidad de colisiones: " << cant_colisiones << endl;

    write_csv(resultados, "../data/results.csv");
    
    
    return 0;
}
