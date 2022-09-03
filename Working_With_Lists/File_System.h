#pragma once
#include <iostream>
#include <filesystem>
#include "List.h"

using namespace std;

class File_System{
private:
    /*
        Домашній каталог
    */
    static string home_directory;
    /*
        Ініціалізація поточного каталога
    */
    static List<string> directory;
public:
    /*
        Перехід в казаний каталог
    */
    static void set_catalog(string _directory);
    /*
        Отримання адресу до поточного каталога
    */
    static string get_catalog();
    /*
        Повернення в попередній каталог
    */
    static void back_catalog();
    /*
        Перевірка чи пустий каталог
    */
    static bool is_catalog_empty(string name);
    /*
        Перевірка чи вказаний об'єкт є каталогом
    */
    static bool check_catalog(string name);
    /*
        Виведення на екран не скритого вмісту каталога
    */
    static void catalog_content(List<string>& content);
    /*
        Отримання адресу домашнього каталога
    */
    static string get_home_catalog();
    /*
        Перехід з будь-якого каталога в домашній
    */
    static void return_home_catalog();
};