#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "List.h"
using namespace std;

class Table_File
{
public:
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
    /*
        Запит про підтвердження виходу
    */
    static bool check_exit();
};