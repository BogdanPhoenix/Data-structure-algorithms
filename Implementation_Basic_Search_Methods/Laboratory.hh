#pragma once
#include <iostream>
#include <iomanip>
#include "Table_File.hh"

using namespace std;

class Laboratory
{
private:
    /*
        Варіанти меню
    */
    enum Variant{
        Menu_Exit,
        One_exercise,
        Two_exercise
    };
    /*
        Завдання №1
    */
    void ExerciseOne();
    /*
        Завдання №2
    */
    void ExerciseTwo();
    /*
        Пошук
    */
    void Find(int* array, int& size, int& remember_size, int variant);
    /*
        Виведення результатів пошуку
    */
    void Result(int* array, int& size, int& remember_size);
    /*
        Заповнення масиву
    */
    void ArrayAdd(int* array, int &size, int left_limit, int rigth_limit);
    /*
        Виведення масиву
    */
    void ArrayPrint(int *array, int &size);
    /*
        Лінійний пошук
    */
    int SearchLine(int *array, int &size, int key);
    /*
        Бінарний пошук
    */
    int SearchBinar(int *array, int& key, int left_limit, int right_limit);
    /*
        Зсув масиву вліво
    */
    void Displacement_Elements(int* array, int &size, int index_element);
    /*
        Сортування масиву
    */
    void Sort(int* array, int&size);
public:
    /*
        Запуск програми
    */
    void start();
};
