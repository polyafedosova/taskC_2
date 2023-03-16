#include "fileversion.h"

FileVersion::FileVersion()
{

}

FileVersion::FileVersion(int last_version,
    std::string date,
    std::string state) : version(last_version), create_date(date), state(state) {}

std::string FileVersion::get_date()
{
    return create_date;
}

int FileVersion::get_version()
{
    return version;
}

std::string FileVersion::get_state()
{
    return state;
}
