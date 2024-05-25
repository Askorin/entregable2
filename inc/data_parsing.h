#ifndef DATA_PARSING_H
#define DATA_PARSING_H
#include <string>
#include <vector>
#include "data_struct.h"

std::vector<std::vector<std::string>> read_csv(std::string filepath);

void write_csv(std::vector<int> mivector, std::string filepath);

void write_data(std::vector<std::string> columnas, std::vector<std::vector<std::string>> datos, 
        std::string filepath);

std::vector<data_struct> convertData(std::vector<std::vector<std::string>> data);
    
#endif
