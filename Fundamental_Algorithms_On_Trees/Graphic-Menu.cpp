#include "Graphic-Menu.h"

/*
    Старт програми
*/
void Graphic_Menu::start(){
    int variant;
    List<string> menu ({
        ". Робота з файлами.",
        ". Робота з каталогами." 
    });
    do{
        Table_File::print_list(content);
        Table_File::print_variant_menu(menu);
        cin >> variant;
        switch(variant){
            case System_Regime::System_Exit: break;
            case System_Regime::Select_File: file(); break;
            case System_Regime::Select_Catalog: catalog(); break;
            default: cout << endl << setw(5)<<""<<"Такого варіанту немає. Спробуйте іще раз." << endl; Table_File::check_continue();
        }
    }while(variant != 0 && file_name.empty());
    system("clear");
}
/*
    Запит на підтвердження видалення вмісту каталога
*/
bool Graphic_Menu::confirmation(string type, string name){
    int variant;
    do{
        system("clear");
        cout << endl << setw(5)<<""<<"Ви дійсно хочете видалити "<< type << " " << name << "?"<<endl;
        cout << endl <<setw(5)<<""<< "Варіанти відповіді"<< endl;
        cout <<setw(5)<<""<<"1. Так."<<endl;
        cout <<setw(5)<<""<<"2. Ні."<<endl;
        cout <<setw(5)<<""<< "Ваш варіант: ";
        cin >> variant;
        switch (variant)
        {
            case Confirmation::Yes: return true;
            case Confirmation::Exit:
            case Confirmation::No: return false;
            default: cout << endl << setw(5)<<""<<"Такого варіанту немає. Спробуйте іще раз." << endl; Table_File::check_continue();
        }
    }while(variant < 0 && variant > 2 || variant != 0);
}

////////////Каталог////////////

/*
    Меню взаємодії з каталогами та їх вмістом
*/
void Graphic_Menu::catalog(){
    int variant;
    List<string> menu ({
        ". Наступний каталог.",
        ". Повернутися до попереднього каталогу.",
        ". Повернутися до домашнього каталогу.",
        ". Створити каталог.",
        ". Видалити каталог."
    });
    do{
        Table_File::print_list(content);
        Table_File::print_variant_menu(menu);
        cin >> variant;
        switch(variant){
            case Catalog_Work_Variant::Catalog_Exit: break;
            case Catalog_Work_Variant::Catalog_Next: catalog_next(); break;
            case Catalog_Work_Variant::Catalog_Return_Previous: catalog_previous(); break;
            case Catalog_Work_Variant::Catalog_Return_Home: catalog_home(); break;
            case Catalog_Work_Variant::Catalog_New: catalog_new(); break;
            case Catalog_Work_Variant::Catalog_Delete: catalog_delete(); break;
            default: cout << endl << setw(5)<<""<<"Такого варіанту немає. Спробуйте іще раз." << endl; Table_File::check_continue();
        }
        catalog_name.clear();
    }while(variant != 0);
}
/*
    Вибір необхідного каталога за вказаним номером
*/
void Graphic_Menu::catalog_select(){
    int index;
    do{
        Table_File::print_list(content);
        cout << setw(5)<<""<<"Введіть номер каталога, який хочете використати: ";
        cin >> index;
        if(index == 0){ break; }
        if(Table_File::warning(index, content)){ continue; }
        catalog_name = content.print_element(index - 1);
        if(!File_System::check_catalog(catalog_name)){
            cout << endl<<setw(5)<<""<<"Вибраний вами пунк не є каталогом" << endl;
            Table_File::check_continue();
            catalog_name.clear();
        }
    }while(catalog_name.empty());
}
/*
    Перехід до наступного каталога за вказаним номером
*/
void Graphic_Menu::catalog_next(){
    do{
        catalog_name.clear();
        catalog_select();
        if(!catalog_name.empty())
            File_System::set_catalog(catalog_name);
        content.remove_all();
    }while(!catalog_name.empty());
}
/*
    Повернення на рівень вище. 
    Повернення в попередній каталог
*/
void Graphic_Menu::catalog_previous(){
    if(File_System::get_catalog() != File_System::get_home_catalog()){
        content.remove_all();
        File_System::back_catalog();
    }
    else{
        cout << endl<<setw(5)<<""<<"Ви знаходитеся в домашньому каталозі. Повертатися більше немає куди."<< endl;
        Table_File::check_continue();
    }

}
/*
    Повернення в домашній каталог
*/
void Graphic_Menu::catalog_home(){
    File_System::return_home_catalog();
    content.remove_all();
}
/*
    Створення нового каталогу в даному каталозі
*/
void Graphic_Menu::catalog_new(){
    do{
        Table_File::print_list(content);
        cout << setw(5)<<""<<"Введіть назву каталогу: ";
        cin.ignore();
        getline(cin, catalog_name);
        if(catalog_name.empty()){
            cout << endl<<setw(5)<<""<<"Дане поле є порожнім. Спробуйте іще раз."<< endl;
            Table_File::check_continue();
        }
    }while(catalog_name.empty());
    string command = "mkdir -p " + File_System::get_catalog() + catalog_name;
    system(command.c_str());
    content.remove_all();
}
/*
    Видалення вказаного каталога
*/
void Graphic_Menu::catalog_delete(){
    catalog_select();
    string command;
    if(!File_System::is_catalog_empty(catalog_name)){
        cout << setw(5)<<""<<"Каталог "<< catalog_name << " не є порожнім"<< endl;
    }
    if(confirmation("каталог", catalog_name)){
        command = "rm -r " + File_System::get_catalog() + catalog_name;
        system(command.c_str());
        content.remove_all();
    }
}

////////////Файл////////////

/*
    Меню взаємодії з файлами в каталозі
*/
void Graphic_Menu::file(){
    int variant;
    List<string> menu ({
        ". Редагувати файл через системний блокнот.",
        ". Створити файл через системний блокнот.",
        ". Видалити файл.",
        ". Вибрати файл." 
    });
    do{
        file_name.clear();
        Table_File::print_list(content);
        Table_File::print_variant_menu(menu);
        cin >> variant;
        switch(variant){
            case File_Work_Vatiant::File_Exit: break;
            case File_Work_Vatiant::File_Edit: file_edit_data(); break;
            case File_Work_Vatiant::File_Create: file_created_data(); break;
            case File_Work_Vatiant::File_Delete: file_delete(); break;
            case File_Work_Vatiant::File_Return_Name: 
                file_select();  
                if(!file_name.empty())
                    variant = File_Work_Vatiant::File_Exit;
                break;
            default: cout << endl << setw(5)<<""<<"Такого варіанту немає. Спробуйте іще раз." << endl; Table_File::check_continue();
        }
    }while(variant != File_Work_Vatiant::File_Exit);
}
/*
    Вибір необхідного файла за вказаним номером
*/
void Graphic_Menu::file_select(){
    int index;
     do{
        Table_File::print_list(content);
        cout << setw(5)<<""<<"Введіть номер файла, який хочете використати: ";
        cin >> index;
        if(index == 0){ break; }
        if(Table_File::warning(index, content)){ continue; }
        file_name = content.print_element(index - 1);
        if(File_System::check_catalog(file_name)){
            cout << endl<<setw(5)<<""<<"Вибраний вами пунк не є файлом" << endl;
            Table_File::check_continue();
            file_name.clear();
        }
    }while(file_name.empty());
}
/*
    Редагування вмісту файлу за допомогою системних програм
*/
void Graphic_Menu::file_edit_data(){
    file_select();
    string command = "nano " + File_System::get_catalog() + file_name;
    system(command.c_str());
}
/*
    Створення нового файлу в даному каталозі за допомогою системних програм
*/
void Graphic_Menu::file_created_data(){
    do{
        Table_File::print_list(content);
        cout << setw(5)<<""<<"Введіть назву файлу та розширення до нього: ";
        cin.ignore();
        getline(cin, file_name);
        if(file_name.empty()){
            cout << endl<<setw(5)<<""<<"Дане поле є порожнім. Спробуйте іще раз."<< endl;
            Table_File::check_continue();
        }
    }while(file_name.empty());
    string command = "nano " + File_System::get_catalog() + file_name;
    system(command.c_str());
    content.remove_all();
}
/*
    Видалення файла
*/
void Graphic_Menu::file_delete(){
    file_select();
    string command = "rm " + File_System::get_catalog() + file_name;
    system(command.c_str());
    content.remove_all();
}
/*
    Повертає назву файла
*/
string Graphic_Menu::get_file_name(){
    return File_System::get_catalog() + file_name;
}