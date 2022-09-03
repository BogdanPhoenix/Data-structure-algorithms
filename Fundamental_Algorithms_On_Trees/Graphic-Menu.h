#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include "File_System.h"
#include "File_Data.h"
#include "Table_File.h"

using namespace std;

class Graphic_Menu{
private:
    string file_name, catalog_name;
    List<string> content;

    /*
        Запит на підтвердження видалення вмісту каталога
    */
    bool confirmation(string type, string name);

////////////Каталог////////////

    /*
        Меню взаємодії з каталогами та їх вмістом
    */
    void catalog();
    /*
        Вибір необхідного каталога за вказаним номером
    */
    void catalog_select();
    /*
        Перехід до наступного каталога за вказаним номером
    */
    void catalog_next();
    /*
        Повернення на рівень вище. 
        Повернення в попередній каталог
    */
    void catalog_previous();
    /*
        Повернення в домашній каталог
    */
    void catalog_home();
    /*
        Створення нового каталогу в даному каталозі
    */
    void catalog_new();
    /*
        Видалення вказаного каталога
    */
    void catalog_delete();

////////////Файл////////////

    /*
        Меню взаємодії з файлами в каталозі
    */
    void file();
    /*
        Вибір необхідного файла за вказаним номером
    */
    void file_select();
    /*
        Редагування вмісту файлу за допомогою системних програм
    */
    void file_edit_data();
    /*
        Створення нового файлу в даному каталозі за допомогою системних програм
    */
    void file_created_data();
    /*
        Видалення файла
    */
    void file_delete();
public:
    /*
        Старт програми
    */
    void start();
    /*
        Повертає назву файла
    */
    string get_file_name();
};