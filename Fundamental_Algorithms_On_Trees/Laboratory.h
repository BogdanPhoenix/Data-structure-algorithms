#pragma once
#include <iostream>
#include <iomanip>
#include "Tree.h"
#include "Graphic-Menu.h"
#include "List.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Laboratory{
private:
    Tree<string> tree;
    string file_name;
    Graphic_Menu menu;

    /*
        Завдання №1
    */
    void exercise_one();
    /*
        Завдання №2
    */
    void exercise_two();
    /*
        Вибрати файл
    */
    void set_file();
    /*
        Перевірка файлу
    */
    bool check_file();
    /*
        Зчитування даних з файла
    */
    void read_data();
    /*
        Графічне виведення інформації
    */
    void print();
public:
    /*
        Запуск програми
    */
    void start();
};