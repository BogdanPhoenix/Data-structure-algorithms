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
        print_list();
        print_Variant_Menu(menu);
        cin >> variant;
        switch(variant){
            case System_Regime::System_Exit: break;
            case System_Regime::Select_File: file(); break;
            case System_Regime::Select_Catalog: catalog(); break;
            default: cout << endl << setw(5)<<""<<"Такого варіанту немає. Спробуйте іще раз." << endl; check_continue();
        }
    }while(variant != 0);
}
/*
    Призупинення виконання програми через виведення технічного повідомлення
*/
void Graphic_Menu::check_continue(){
    string next;
    cin.ignore();
    cout << setw(5)<<""<<"Для продовження натисніть Enter...";
    getline(cin, next);
    cout << endl;
}
/*
    Виведення меню
*/
void Graphic_Menu::print_Variant_Menu(List<string>& menu){
    for (auto i = 0; i < menu.count(); i++)
        cout << setw(5) << "" << i + 1 << menu.print_element(i) << endl;
    cout << setw(5)<<""<<"Ваш варіант: ";
}
/*
    Виведення вмісту каталога
*/
void Graphic_Menu::print_list(){
    int i = 0;
    system("clear");
    if(content.is_nullptr())
        File_System::catalog_content(content);
    cout << endl <<"0 - вихід з програми, відміна операції або повернення назад в меню"<<endl;
    cout<<"Поточний каталог: "<< File_System::get_catalog()<<endl;
    cout << setw(5) << "" << "№" << setw(11)<< "" << "Назва" << endl;
    for(int i = 0; i < content.count(); i++)
        cout << setw(9) << "№ " << i + 1 << setw(7)<< "" << content.print_element(i)<<endl;
    cout << endl;
}
/*
    Повідомлення користувачу. що під вказаним номером нічого не виявлено
*/
bool Graphic_Menu::warning(int index){
    if(index > content.count() || index < 0){
        cout << endl << setw(5)<<""<<"Під вказаним номером не виявлено об'єкта. Спробуйте іще раз"<< endl;
        check_continue();
        return true;
    }
    return false;
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
        default: cout << endl << setw(5)<<""<<"Такого варіанту немає. Спробуйте іще раз." << endl; check_continue();
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
        print_list();
        print_Variant_Menu(menu);
        cin >> variant;
        switch(variant){
            case Catalog_Work_Variant::Catalog_Exit: break;
            case Catalog_Work_Variant::Catalog_Next: catalog_next(); break;
            case Catalog_Work_Variant::Catalog_Return_Previous: catalog_previous(); break;
            case Catalog_Work_Variant::Catalog_Return_Home: catalog_home(); break;
            case Catalog_Work_Variant::Catalog_New: catalog_new(); break;
            case Catalog_Work_Variant::Catalog_Delete: catalog_delete(); break;
            default: cout << endl << setw(5)<<""<<"Такого варіанту немає. Спробуйте іще раз." << endl; check_continue();
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
        print_list();
        cout << setw(5)<<""<<"Введіть номер каталога, який хочете використати: ";
        cin >> index;
        if(index == 0){ break; }
        if(warning(index)){ continue; }
        catalog_name = content.print_element(index - 1);
        if(!File_System::check_catalog(catalog_name)){
            cout << endl<<setw(5)<<""<<"Вибраний вами пунк не є каталогом" << endl;
            check_continue();
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
        File_System::back_catalog();
        content.remove_all();
    }
    else{
        cout << endl<<setw(5)<<""<<"Ви знаходитеся в домашньому каталозі. Повертатися більше немає куди."<< endl;
        check_continue();
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
        print_list();
        cout << setw(5)<<""<<"Введіть назву каталогу: ";
        cin.ignore();
        getline(cin, catalog_name);
        if(catalog_name.empty()){
            cout << endl<<setw(5)<<""<<"Дане поле є порожнім. Спробуйте іще раз."<< endl;
            check_continue();
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
        ". Зчитати файл.",
        ". Редагувати файл через системний блокнот.",
        ". Створити файл через системний блокнот.",
        ". Видалити файл.",
        ". Вибрати файл." 
    });
    do{
        print_list();
        print_Variant_Menu(menu);
        cin >> variant;
        switch(variant){
            case File_Work_Vatiant::File_Exit: break;
            case File_Work_Vatiant::File_Open: file_read_data(); break;
            case File_Work_Vatiant::File_Edit: file_edit_data(); break;
            case File_Work_Vatiant::File_Create: file_cread_data(); break;
            case File_Work_Vatiant::File_Delete: file_delete(); break;
            default: cout << endl << setw(5)<<""<<"Такого варіанту немає. Спробуйте іще раз." << endl; check_continue();
        }
        file_name.clear();
    }while(variant != 0);
}
/*
    Вибір необхідного файла за вказаним номером
*/
void Graphic_Menu::file_select(){
    int index;
     do{
        print_list();
        cout << setw(5)<<""<<"Введіть номер файла, який хочете використати: ";
        cin >> index;
        if(index == 0){ break; }
        if(warning(index)){ continue; }
        file_name = content.print_element(index - 1);
        if(File_System::check_catalog(file_name)){
            cout << endl<<setw(5)<<""<<"Вибраний вами пунк не є файлом" << endl;
            check_continue();
        }
    }while(file_name.empty());
}
/*
    Виведення на екран вмісту файла
*/
void Graphic_Menu::file_read_data(){
    file_select();
    system("clear");
    ifstream ifile(File_System::get_catalog() + file_name);
    if(!ifile){
        cout << endl << setw(5) << "" << "Файл не відкрився" << endl;
    }
    else{
        string element;
        List<string> file_contents;
        while(ifile >> element){
            file_contents.push_end(element);
        }
        cout << endl <<"Поточний каталог: "<< File_System::get_catalog()<<endl;
        cout << setw(5) << "" << "Вміст файлу: " << file_name<< endl;
        for(int i = 0; i < file_contents.count(); i++){
            cout << setw(5)<< "" << file_contents.print_element(i);
        }
        cout << endl << endl;
        check_continue();
    }
    ifile.close();
}

/*
    Створення нового файлу в даному каталозі за допомогою системних програм
*/
void Graphic_Menu::file_edit_data(){
    file_select();
    string command = "nano " + File_System::get_catalog() + file_name;
    system(command.c_str());
}
/*
    Редагування вмісту файлу за допомогою системних програм
*/
void Graphic_Menu::file_cread_data(){
    do{
        print_list();
        cout << setw(5)<<""<<"Введіть назву файлу та розширення до нього: ";
        cin.ignore();
        getline(cin, file_name);
        if(file_name.empty()){
            cout << endl<<setw(5)<<""<<"Дане поле є порожнім. Спробуйте іще раз."<< endl;
            check_continue();
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