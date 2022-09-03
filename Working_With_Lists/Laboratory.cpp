#include "Laboratory.h"

void Laboratory::Exercise_One(){
    int time = 5;
    while(time > 0){
        system("clear");
        cout << setw(5)<<""<<"Вибір файлу через " << time-- << "с."<<endl; 
        this_thread::sleep_for(chrono::milliseconds(1000));
    } 
    menu.start();
}

void Laboratory::Exercise_Two(){

}