#ifndef MYFILE_H
#define MYFILE_H

#include <string>
#include <vector>
#include <unordered_map>

#include "fileversion.h"

class MyFile
{
private:
    std::string filename;

    std::vector<int> versions;
    std::vector<FileVersion> file_versions;

    int last_version = 1;
public:
    MyFile();
    MyFile(std::string filename);

    int get_last_version();

    const std::vector<FileVersion>& get_versions();

    std::string get_filename();

    FileVersion get_file_by_version(int v);

    FileVersion get_file_by_date(std::string date);

    FileVersion get_file_by_state(std::string state);

    void create_custom_version(int version, std::string date, std::string state);

    void create_linear_version(std::string date, std::string state);

    int find_prev_version(int v);
};

#endif // MYFILE_H
#pragma once
