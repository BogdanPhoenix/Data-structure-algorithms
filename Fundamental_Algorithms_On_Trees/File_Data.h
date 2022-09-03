#pragma once
#include <iostream>

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
    File_Edit,
    File_Create,
    File_Delete,
    File_Return_Name
};
/*
    Режими роботи з підтвердженням вибору
*/
enum Confirmation{
    Exit,
    Yes,
    No
};
/*
    Варіанти меню
*/
enum Variant{
    Menu_Exit,
    One_exercise,
    Two_exercise
};