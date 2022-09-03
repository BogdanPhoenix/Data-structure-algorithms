#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include "Graphic-Menu.h"

using namespace std;
struct Book_Info{
    int number_ticket, numder_days, price;
    string fist_name_abonent, author, book_name;
    time_t data, year_publication;
};
class Laboratory{
    private:
    Graphic_Menu menu;
public:
    void Exercise_One();
    void Exercise_Two();
};