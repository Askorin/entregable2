#ifndef DATA_PARSING_H
#define DATA_PARSING_H
#include <string>
#include <vector>
#include "data_struct.h"

std::vector<std::vector<std::string>> read_csv(std::string filename);

void write_csv(std::vector<int> mivector, std::string filename);

std::vector<data_struct> convertData(std::vector<std::vector<std::string>> data);
    
#endif
