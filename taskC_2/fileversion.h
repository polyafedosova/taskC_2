#ifndef FILEVERSION_H
#define FILEVERSION_H

#include <string>

class FileVersion
{
private:
    int version;

    std::string create_date;

    std::string state;
public:
    FileVersion();
    FileVersion(int last_version, std::string date, std::string state);
    int get_version();
    std::string get_date();
    std::string get_state();
};
#endif // FILEVERSION_H
