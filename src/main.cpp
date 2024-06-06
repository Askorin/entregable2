#include "../inc/data_parsing.h"
#include "../inc/testing.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {

    size_t nExperimentos;
    if (argc == 2) {
        nExperimentos = stoi(argv[1]);
    } else {
        nExperimentos = 10;
    }

    /* Leemos los datos y convertimos en vector de data_struct */
    vector<vector<string>> datosReales =
        read_csv("../data/universities_followers_no_dups.csv");
    vector<vector<string>> datosRandom =
        read_csv("../data/universities_followers_no_dups_random.csv");

    vector<dataStruct> datosRealesConverted = convertData(datosReales);
    vector<dataStruct> datosRandomConverted = convertData(datosRandom);
    cout << "### Dataset real con " << datosRealesConverted.size()
         << " elementos ###\n";
    cout << "### Dataset random con " << datosRandomConverted.size()
         << " elementos ###\n";

    doTests(datosRealesConverted, datosRandomConverted, nExperimentos);

    return 0;
}
