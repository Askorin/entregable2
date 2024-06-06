#ifndef TESTING_H
#define TESTING_H
#include "data_struct.h"
#include "map.h"
#include <unordered_map>
#include <vector>

void doTests(std::vector<data_struct>& datosReales,
             std::vector<data_struct>& datosRandom, size_t nExperimentos);

double insertionTimer(HashMap<std::string, data_struct>& mapa,
                      std::vector<data_struct>& datos, size_t count);

double insertionTimer(HashMap<unsigned long long, data_struct>& mapa,
                      std::vector<data_struct>& datos, size_t count);

double insertionTimer(std::unordered_map<unsigned long long, data_struct>& mapa,
                      std::vector<data_struct>& datos, size_t count);

double insertionTimer(std::unordered_map<std::string, data_struct>& mapa,
                      std::vector<data_struct>& datos, size_t count);

double searchTimer(std::unordered_map<std::string, data_struct>& mapa,
                   std::vector<data_struct>& datos, size_t count,
                   size_t idxComienzo);

double searchTimer(std::unordered_map<unsigned long long, data_struct>& mapa,
                   std::vector<data_struct>& datos, size_t count,
                   size_t idxComienzo);

double searchTimer(HashMap<std::string, data_struct>& mapa,
                   std::vector<data_struct>& datos, size_t count,
                   size_t idxComienzo);

double searchTimer(HashMap<unsigned long long, data_struct>& mapa,
                   std::vector<data_struct>& datos, size_t count,
                   size_t idxComienzo);

void insertionTimeTest(std::vector<data_struct>& datos, size_t nExperimentos,
                       std::vector<size_t> cuentas);

void searchTimeTestTipo1(std::vector<data_struct>& datos, size_t nExperimentos,
                         std::vector<size_t> cuentas);

void searchTimeTestTipo2(std::vector<data_struct>& datosInsercion,
                         std::vector<data_struct>& datosBusqueda,
                         size_t nExperimentos, std::vector<size_t> cuentas);

bool testFuncionamiento(std::vector<data_struct>& datos);

void countCapacities(std::vector<data_struct>& datos);

#endif
