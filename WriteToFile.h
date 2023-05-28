#ifndef SDIZOPROJEKT2_WRITETOFILE_H
#define SDIZOPROJEKT2_WRITETOFILE_H


#include <map>
#include <string>

class WriteToFile{
public:
    static void saveMapToFile(std::string filename, std::map<double, double> timesInMilliseconds);
};

#endif //SDIZOPROJEKT2_WRITETOFILE_H
