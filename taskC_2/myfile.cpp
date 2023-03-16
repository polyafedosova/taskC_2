#include "myfile.h"

MyFile::MyFile()
{

}

MyFile::MyFile(std::string filename) : filename(filename) {}

int MyFile::get_last_version()
{
    return last_version;
}

std::string MyFile::get_filename()
{
    return filename;
}

const std::vector<FileVersion>& MyFile::get_versions()
{
    return file_versions;
}

FileVersion MyFile::get_file_by_version(int v)
{
    for (int i = 0; i < versions.size(); i++)
    {
        if (versions[i] == v)
            return file_versions[i];
    }

    throw "Такой версии файла не существует";
}

FileVersion MyFile::get_file_by_date(std::string date)
{
    for (auto file : file_versions)
    {
        if (file.get_date() == date)
            return file;
    }

    throw "Такой версии файла не существует";
}

FileVersion MyFile::get_file_by_state(std::string state)
{
    for (auto file : file_versions)
    {
        if (file.get_state() == state)
            return file;
    }

    throw "Такой версии файла не существует";
}

void MyFile::create_linear_version(std::string date, std::string state)
{
    FileVersion tmp(last_version, date, state);
    file_versions.push_back(std::move(tmp));
    versions.push_back(last_version);
    last_version++;
}

void MyFile::create_custom_version(int version, std::string date, std::string state)
{
    file_versions.push_back(std::move(FileVersion{ version, date, state }));
    versions.push_back(version);
    last_version = version + 1;
}

int MyFile::find_prev_version(int v)
{
    for (int i = versions.size() - 1; i >= 0; --i)
    {
        if (versions[i] == v)
        {
            return versions[i];
        }
    }

    return -1;
}