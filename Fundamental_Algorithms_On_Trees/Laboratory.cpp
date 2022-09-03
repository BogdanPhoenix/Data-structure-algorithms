#include "Laboratory.h"

/*
    Запуск програми
*/
void Laboratory::start(){
    int variant;
    do{
        system("clear");
        cout << endl <<setw(10)<<""<<"Лабораторна №8"<<endl;
        cout <<setw(10)<<""<<"Фундаментальні алгоритми на деревах."<<endl << endl;
        cout <<setw(5)<<""<<"1. Завдання №1"<<endl;
        cout <<setw(5)<<""<<"2. Завдання №2"<<endl;
        cout <<setw(5)<<""<<"Ваш варіант: ";
        cin >> variant;
        switch(variant){
            case Variant::Menu_Exit: break;
            case Variant::One_exercise: exercise_one(); break;
            case Variant::Two_exercise: exercise_two(); break;
        }
        if(variant != Variant::Menu_Exit)
            Table_File::check_continue();
    }while(variant != Variant::Menu_Exit);
}
/*
    Завдання №1
*/
void Laboratory::exercise_one(){
    system("clear");
    tree.remove_all();
    cout << endl << setw(5)<<""<<"Завдання №1"<<endl;
    cout <<setw(5)<<""<<"1. Створити структуру \"бінарне дерево\" з елементів файлу з символів."<<endl;
    cout <<setw(5)<<""<<"2. Знайти значення самого лівого листка непустого дерева."<<endl << endl;
    Table_File::check_continue();
    set_file();
    if(check_file()){
        if(tree.is_empry()){
            read_data();
        }
        print();
        cout << endl << setw(5) << "" << "Найлівішим елементом даного дерева є елемент: " << tree.get_left_element() << endl << endl;
    }
}
/*
    Завдання №2
*/
void Laboratory::exercise_two(){
    system("clear");
    tree.remove_all();
    cout << endl << setw(5)<<""<<"Завдання №2"<<endl;
    cout <<setw(5)<<""<<"1. Вивести номери рівнів на яких є листя."<<endl << endl;
    Table_File::check_continue();
    set_file();
    if(check_file()){
        if(tree.is_empry()){
            read_data();
        }
        print();
        List<int> level = tree.is_leaves();
        cout << endl << setw(5) <<""<<"Рівні на яких присутнє листя: ";
        for(int index = 0; index < level.count(); ++index){
            cout << level.print_element(index) << ", ";
        }
        cout << endl << endl;
    }
}
/*
    Вибрати файл
*/
void Laboratory::set_file(){
    menu.start();
    file_name = menu.get_file_name();
}
/*
    Перевірка файлу
*/
bool Laboratory::check_file(){
    fstream file(file_name, ios::in);
    if(!file){
        cout << setw(5)<<""<<"Файл не відкрився. Програму завершено."<<endl;
        file.close();
        return false;
    }
    if(File_System::іs_empty(file)){
        cout << setw(5) << "" << "Даний файл порожній." << endl;
        cout << setw(5) << "" << "Заповніть його будь ласка."<< endl;
        return false;
    }
    file.close();
    return true;
}
/*
    Зчитування даних з файла
*/
void Laboratory::read_data(){
    json json_value, test;
    ifstream file(file_name);
    file >> json_value;
    file.close();
    for(auto it : json_value["array"]){
        tree.push_element(it);
    }
}
/*
    Графічне виведення інформації
*/
void Laboratory::print(){
    system("clear");
    auto formatted_rows = tree.print();
    if(formatted_rows.size() != 0){
        for(const auto& row : formatted_rows){
            cout << ' ' << row << '\n';
        }
    }
}