#include "../inc/data_parsing.h"
#include <fstream>
#include <ios>
#include <sstream>

using namespace std;

vector<vector<string>> read_csv(string filepath) {
    ifstream fIn;

    fIn.open(filepath, ios::in);

    vector<vector<string>> rows;
    string line, temp;
    /* Removemos la primera fila */
    getline(fIn, line);
    while (getline(fIn, line)) {
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

void write_csv(vector<int> datos, string filepath) {
    ofstream fOut;
    fOut.open(filepath, ios::out | ios::trunc);
    fOut << "idx,count\n";
    for (size_t i = 0; i < datos.size(); ++i) {
        fOut << i << "," << datos[i] << "\n";
    }
}

void write_data(vector<string> columnas, vector<vector<string>> datos,
                string filepath) {
    ofstream fOut;
    fOut.open(filepath, ios::out | ios::trunc);
    for (size_t i = 0; i < columnas.size(); ++i) {
        fOut << columnas[i];
        if (i != columnas.size() - 1)
            fOut << ",";
    }
    fOut << "\n";

    for (auto fila : datos) {
        for (size_t i = 0; i < fila.size(); ++i) {
            fOut << fila[i];
            if (i != fila.size() - 1)
                fOut << ",";
        }
        fOut << "\n";
    }
}

vector<dataStruct> convertData(vector<vector<string>> datos) {
    vector<dataStruct> res = vector<dataStruct>();
    ;
    for (auto elemento : datos) {
        string university = elemento[0];
        unsigned long long user_id = stoull(elemento[1]);
        string userName = elemento[2];
        unsigned int nTweets = stoul(elemento[3]);
        unsigned int friendCount = stoul(elemento[4]);
        unsigned int followerCount = stoul(elemento[5]);
        string createdAt = elemento[6];

        dataStruct elementoConvertido =
            dataStruct(university, user_id, userName, nTweets, friendCount,
                        followerCount, createdAt);
        res.push_back(elementoConvertido);
    }
    return res;
}
