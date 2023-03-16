#include <iostream>
#include <string>
#include "application.h"

using namespace std;

void create_file(Application& app)
{
    std::cout << "Введите название вашего файла: ";
    std::string filename;
    std::cin >> filename;

    MyFile file(filename);
    app.add_file(file);
}

void add_new_version(Application& app)
{
    std::cout << "Введите название вашего файла, для которого будет создана версия: ";
    std::string filename;
    std::cin >> filename;
    if (!app.is_file_in_app(filename))
    {
        std::cerr << "Такого файла нет в проекте" << std::endl;
        return;
    }

    std::cout << "Введите номер версии (если хотите последовательно нумеровать версии, введите -1: ";
    int version = 0;
    std::cin >> version;

    std::cout << "Введите дату создания версии в виде ГГГГ-ММ-ДД: ";
    std::string date;
    std::cin >> date;

    std::cout << "Введите состояние версии: ";
    std::string state;
    std::cin >> state;

    if (version == -1)
        app.get_file_by_name(filename).create_linear_version(date, state);
    else
        app.get_file_by_name(filename).create_custom_version(version, date, state);

    std::cout << "Версия добавлена." << std::endl;
}


void print_info(Application& app)
{
    std::cout << "Приложение: " << app.get_app_name() << std::endl;
    std::cout << "Файлы: " << std::endl;
    std::cout << "\n";
    for (auto file : app.get_files())
    {
        std::cout << "Файл: " << file.get_filename() << std::endl;
        for (auto file_version : file.get_versions())
        {
            std::cout << " Версия: " << file_version.get_version() << ", дата создания: " << file_version.get_date() << ", состояние: " << file_version.get_state();
            std::cout << std::endl;
        }
    }
}

void print_config_by_version(Application& app)
{
    std::cout << "Введите номер версии, конфигурацию которой надо получить: ";
    int version = 0;
    std::cin >> version;
    if (version < 0)
    {
        std::cerr << "Некорректное значение для версии" << std::endl;
        return;
    }

    try
    {
        Config configuration = app.get_config_by_version(version);
        std::cout << "Конфигурация версии " << version << ":" << std::endl;
        for (auto conf_line : configuration)
        {
            std::cout << "Файл: " << conf_line.first << " -> Версия: " << conf_line.second.get_version() <<
                ", Дата создания: " << conf_line.second.get_date() << ", Состояние: " << conf_line.second.get_state() << std::endl;
        }
    }
    catch (const char* msg)
    {
        std::cerr << msg << std::endl;
        std::cout << "Ищем ближайшую корректную версию" << std::endl;
        int prev_version = app.find_prev_version_files(version);
        if (prev_version == -1)
        {
            std::cerr << "Ваши файлы не имеют соответствия по версиям" << std::endl;
            return;
        }

        std::cout << "Ближайшая корректная версия: " << prev_version << std::endl;
    }
}

void print_menu()
{
    std::cout << "Выберите действие:" << std::endl;
    std::cout << "1. Добавить файл" << std::endl;
    std::cout << "2. Добавить версию для файла" << std::endl;
    std::cout << "3. Просмотреть информацию о приложении" << std::endl;
    std::cout << "4. Получить конфигурацию для определенного номера версии" << std::endl;
    std::cout << "5. Выход" << std::endl;
}

void load_debug_data(Application& app)
{
    MyFile f1{ "f1" };
    MyFile f2{ "f2" };

    f1.create_custom_version(1, "3456456", "f1");
    f1.create_custom_version(2, "3456456", "f1");
    f1.create_custom_version(3, "3456456", "f1");
    f1.create_custom_version(4, "3456456", "f1");
    f1.create_custom_version(6, "3456456", "f1");

    f2.create_custom_version(1, "7867865", "f2");
    f2.create_custom_version(3, "7867865", "f2");
    f2.create_custom_version(5, "7867865", "f2");

    app.add_file(f1);
    app.add_file(f2);
}

int main()
{
    system("chcp 1251");
    std::cout << "Местная система контроля версий" << std::endl;
    std::cout << "Введите название для приложения: ";
    std::string app_name;
    std::cin >> app_name;

    Application app(app_name);
    bool end = false;
    int doing;
    while (!end)
    {
        std::cout << "\n";
        print_menu();
        std::cout << "\n";
        std::cout << "Введите номер: ";
        std::cin >> doing;
        switch (doing)
        {
        case 1:
            create_file(app);
            break;
        case 2:
            add_new_version(app);
            break;
        case 3:
            print_info(app);
            break;
        case 4:
            print_config_by_version(app);
            break;
        case 5:
            end = true;
            break;
        default:
            std::cerr << "Выбран некорректный номер действия!" << std::endl;
        }
    }
    return 0;
}
