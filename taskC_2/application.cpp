#include "application.h"
#include <algorithm>
#include <iostream>

Application::Application()
{

}

Application::Application(std::string app_name) :application_name(app_name) {}

std::string Application::get_app_name()
{
    return application_name;
}

const std::vector<MyFile>& Application::get_files()
{
    return files;
}


MyFile& Application::get_file_by_name(std::string filename)
{
    return *(std::find_if(files.begin(), files.end(),
        [&](MyFile f) {return f.get_filename() == filename; }));
}

bool Application::is_file_in_app(std::string filename)
{
    return std::find_if(files.begin(), files.end(),
        [&](MyFile f) {return f.get_filename() == filename; }) != std::end(files);
}

void Application::add_file(MyFile new_file)
{
    files.push_back(new_file);
}

Config Application::get_config_by_version(int v)
{
    Config result;
    for (auto file : files)
    {
        result[file.get_filename()] = file.get_file_by_version(v);
    }
    return result;
}

int Application::find_prev_version_files(int v)
{
    for (int i = v; i >= 0; --i)
    {
        bool nextFlag = true;
        for (auto file : files)
        {
            if (file.find_prev_version(i) == -1)
            {
                nextFlag = false;
                break;
            }
        }
        if (nextFlag)
            return i;
    }

    return -1;
}


std::vector<FileVersion> Application::get_config_by_date(std::string date)
{
    std::vector<FileVersion> result{};
    for (auto file : files)
    {
        result.push_back(file.get_file_by_date(date));
    }

    return result;
}

std::vector<FileVersion> Application::get_config_by_state(std::string state)
{
    std::vector<FileVersion> tmp;
    return tmp;
}
