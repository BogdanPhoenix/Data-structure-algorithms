#include "File_System.h"

/*
    Домашній каталог
*/
string File_System::home_directory = "/home/";
/*
    Ініціалізація поточного каталога
*/
List<string> File_System::directory = {home_directory};
/*
    Перехід в казаний каталог
*/
void File_System::set_catalog(string _directory){
    directory.push_end(_directory);
}
/*
    Отримання адресу до поточного каталога
*/
string File_System::get_catalog(){
    string name = "";
    for(int i = 0; i < directory.count(); i++){
        name += directory.print_element(i);
    }
    return name;
}
/*
    Повернення в попередній каталог
*/
void File_System::back_catalog(){
    directory.remove_end();
}
/*
    Перевірка чи пустий каталог
*/
bool File_System::is_catalog_empty(string name){
    string file_name = get_catalog() + name;
    return filesystem::is_empty(file_name);
}
/*
    Перевірка чи вказаний об'єкт є каталогом
*/
bool File_System::check_catalog(string name){
    string check_file_name = get_catalog() + name;
    if(filesystem::is_directory(check_file_name))
        return true;
    return false;
}
/*
    Виведення на екран не скритого вмісту каталога
*/
void File_System::catalog_content(List<string>& content){
    content.remove_all();
    filesystem::path::string_type name;
    for(auto it : filesystem::directory_iterator(get_catalog())){
        name = it.path().filename();
        if(name != ".." && name != "."  && name[0] != '.'){
            if(filesystem::is_directory(it))
                name+= "/";
            content.push_end(name);
        }
    }
}
/*
    Отримання адресу домашнього каталога
*/
string File_System::get_home_catalog(){
    return home_directory;
}
/*
    Перехід з будь-якого каталога в домашній
*/
void File_System::return_home_catalog(){
    directory.remove_all();
    directory.push_beg(home_directory);
}