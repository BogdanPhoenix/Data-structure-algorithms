#pragma once
#include "Graphic-Menu.h"

using namespace std;

int main(){
    srand(time(NULL));
    List<int> test;
    for(int i = 0; i < 6; i++)
        test.push_end(rand() % 21 - 10);
    for(int i = 0; i < test.count(); i++)
        cout << setw(5) << test.print_element(i);
    cout << endl << endl;

    int index_max;
    for(int i = 0; i < test.count() - 1; i++){
        for(int j = 0; j < test.count() - 1 - i; j++){
            int buffer = test.print_element(j);
            if(buffer > test.print_element(j + 1)){
                test.swap(j);
                j--;
            }
        }
    }
    for(int i = 0; i < test.count(); i++)
        cout << setw(5) << test.print_element(i);
    cout << endl << endl;
    return 0;
} 