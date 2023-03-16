#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include <vector>
#include <unordered_map>
#include "myfile.h"

using Config = std::unordered_map<std::string, FileVersion>;

class Application
{
private:
    std::string application_name;

    std::vector<MyFile> files;
public:
    Application();
    Application(std::string app_name);

    std::string get_app_name();

    const std::vector<MyFile>& get_files();

    MyFile& get_file_by_name(std::string filename);

    bool is_file_in_app(std::string filename);

    void add_file(MyFile new_file);

    Config get_config_by_version(int v);

    int find_prev_version_files(int v);

    std::vector<FileVersion> get_config_by_date(std::string date);

    std::vector<FileVersion> get_config_by_state(std::string state);
};

#endif // APPLICATION_H
