#pragma once
#include <iostream>
#include <iomanip>
#include "Turn.hh"
#include "Stack.hh"
using namespace std;
/*
    Варіанти меню
*/
enum Variant{
    Exit,
    One_exercise,
    Two_exercise
};

class Graphic{
private:
    /*
        Завдання номер один
    */
    void Exercise_One();
    /*
        Завдання номер два
    */
    void Exercise_Two();
    /*
        Виведення вмісту стека та черги
    */
    template<class T>
    void Print(T& structs, int size);
    /*
        Призупинення виконання програми через виведення технічного повідомлення
    */
    void check_continue();
public:
    /*
        Старт програми
    */
    void Start();
};