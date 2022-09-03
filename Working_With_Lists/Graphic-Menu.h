#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include "File_System.h"

using namespace std;

/*
    Режими роботи з головним меню
*/
enum System_Regime{
    System_Exit,
    Select_File,
    Select_Catalog
};
/*
    Режими роботи з каталогами
*/
enum Catalog_Work_Variant{
    Catalog_Exit,
    Catalog_Next,
    Catalog_Return_Previous,
    Catalog_Return_Home,
    Catalog_New,
    Catalog_Delete
};
/*
    Режими роботи з файлами
*/
enum File_Work_Vatiant{
    File_Exit,
    File_Open,
    File_Edit,
    File_Create,
    File_Delete,
};
/*
    Режими роботи з підтвердженням вибору
*/
enum Confirmation{
    Exit,
    Yes,
    No
};

class Graphic_Menu{
private:
    string file_name, catalog_name;
    List<string> content;

    /*
        Призупинення виконання програми через виведення технічного повідомлення
    */
    void check_continue();
    /*
        Виведення меню
    */
    void print_Variant_Menu(List<string>& menu);
    /*
        Виведення вмісту каталога
    */
    void print_list();
    /*
        Повідомлення користувачу. що під вказаним номером нічого не виявлено
    */
    bool warning(int index);
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
        Виведення на екран вмісту файла
    */
    void file_read_data();
    /*
        Створення нового файлу в даному каталозі за допомогою системних програм
    */
    void file_edit_data();
    /*
        Редагування вмісту файлу за допомогою системних програм
    */
    void file_cread_data();
    /*
        Видалення файла
    */
    void file_delete();
    /*
        Повертає назву файла
    */
    string get_file_name();
public:
    /*
        Старт програми
    */
    void start();
};