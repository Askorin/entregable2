#ifndef TESTING_H
#define TESTING_H
#include "map.h"
#include "data_struct.h"
#include <unordered_map>
#include <vector>


double insertionTimer(HashMap& mapa, std::vector<data_struct> datos);

double insertionTimer(std::unordered_map<unsigned long long, data_struct>& mapa, 
        std::vector<data_struct> datos);

void timeTest(std::vector<data_struct> datos);

void testFuncionamiento(std::vector<data_struct> datos);

#endif
