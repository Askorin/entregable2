#include "../inc/data_parsing.h"
#include <ios>
#include <fstream>
#include <sstream>

using namespace std;

vector<vector<string>> read_csv(string filepath) {
    ifstream fin;

    fin.open(filepath, ios::in);

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

void write_csv(vector<int> mivector, string filepath) {
    ofstream fout;
    fout.open(filepath, ios::out | ios::trunc);
    fout << "idx,count\n";
    for (size_t i = 0; i < mivector.size(); ++i) {
        fout << i << "," << mivector[i] << "\n";
    }
}

void write_data(vector<string> columnas, vector<vector<string>> datos, string filepath) {
    ofstream fout;
    fout.open(filepath, ios::out | ios::trunc);
    for (size_t i = 0; i < columnas.size(); ++i) {
        fout << columnas[i];
        if (i != columnas.size() - 1) fout << ",";
    }
    fout << "\n";
    
    for (auto fila : datos) {
        for (size_t i = 0; i < fila.size(); ++i) {
            fout << fila[i];
            if (i != fila.size() - 1) fout << ",";
        }
        fout << "\n";
    }
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
