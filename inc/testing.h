#ifndef TESTING_H
#define TESTING_H
#include "data_struct.h"
#include "map.h"
#include <unordered_map>
#include <vector>

void doTests(std::vector<dataStruct>& datosReales,
             std::vector<dataStruct>& datosRandom, size_t nExperimentos);

double insertionTimer(HashMap<std::string, dataStruct>& mapa,
                      std::vector<dataStruct>& datos, size_t count);

double insertionTimer(HashMap<unsigned long long, dataStruct>& mapa,
                      std::vector<dataStruct>& datos, size_t count);

double insertionTimer(std::unordered_map<unsigned long long, dataStruct>& mapa,
                      std::vector<dataStruct>& datos, size_t count);

double insertionTimer(std::unordered_map<std::string, dataStruct>& mapa,
                      std::vector<dataStruct>& datos, size_t count);

double searchTimer(std::unordered_map<std::string, dataStruct>& mapa,
                   std::vector<dataStruct>& datos, size_t count,
                   size_t idxComienzo);

double searchTimer(std::unordered_map<unsigned long long, dataStruct>& mapa,
                   std::vector<dataStruct>& datos, size_t count,
                   size_t idxComienzo);

double searchTimer(HashMap<std::string, dataStruct>& mapa,
                   std::vector<dataStruct>& datos, size_t count,
                   size_t idxComienzo);

double searchTimer(HashMap<unsigned long long, dataStruct>& mapa,
                   std::vector<dataStruct>& datos, size_t count,
                   size_t idxComienzo);

void insertionTimeTest(std::vector<dataStruct>& datos, size_t nExperimentos,
                       std::vector<size_t> cuentas);

void searchTimeTestTipo1(std::vector<dataStruct>& datos, size_t nExperimentos,
                         std::vector<float> factoresBusquedas);

void searchTimeTestTipo2(std::vector<dataStruct>& datosInsercion,
                         std::vector<dataStruct>& datosBusqueda,
                         size_t nExperimentos, std::vector<float> factoresBusquedas);

bool testFuncionamiento(std::vector<dataStruct>& datos);

void countCapacities(std::vector<dataStruct>& datos);

#endif
