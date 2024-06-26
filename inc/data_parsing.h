#ifndef DATA_PARSING_H
#define DATA_PARSING_H
#include "data_struct.h"
#include <string>
#include <vector>

std::vector<std::vector<std::string>> read_csv(std::string filepath);

void write_csv(std::vector<int> datos, std::string filepath);

void write_data(std::vector<std::string> columnas,
                std::vector<std::vector<std::string>> datos,
                std::string filepath);

std::vector<dataStruct>
convertData(std::vector<std::vector<std::string>> datos);

#endif
