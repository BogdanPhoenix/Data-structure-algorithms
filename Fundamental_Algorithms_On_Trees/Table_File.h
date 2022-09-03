#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "List.h"
#include "File_Data.h"
#include "File_System.h"
using namespace std;

class Table_File
{
public:
    /*
        Виведення вмісту каталога
    */
    static void print_list(List<string>& object);
    /*
        Виведення меню
    */
    static void print_variant_menu(List<string>& object);
    /*
        Призупинення виконання програми через виведення технічного повідомлення
    */
    static void check_continue();
    /*
        Повідомлення користувачу. що під вказаним номером нічого не виявлено
    */
    static bool warning(int index, List<string>& object);
};