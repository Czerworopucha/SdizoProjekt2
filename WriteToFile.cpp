#include <fstream>
#include <algorithm>
#include "WriteToFile.h"

void WriteToFile::saveMapToFile(std::string filename, std::map<double, double> timesInMilliseconds){
    std::ofstream file(filename, std::ios::trunc);

    for (auto const& [key, val] : timesInMilliseconds)
    {
        auto value = std::to_string(val);
        std::replace( value.begin(), value.end(), '.', ',');

        auto keyValue = std::to_string(key);
        std::replace( keyValue.begin(), keyValue.end(), '.', ',');

        file << keyValue << ';' << value << std::endl;
    }
    file.close();
}