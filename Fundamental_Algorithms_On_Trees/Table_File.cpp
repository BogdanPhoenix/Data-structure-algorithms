#include "Table_File.h"

/*
    Виведення вмісту каталога
*/
void Table_File::print_list(List<string>& object){
    int i = 0;
    system("clear");
    if(object.is_nullptr())
        File_System::catalog_content(object);
    cout << endl <<"0 - вихід з програми, відміна операції або повернення назад в меню"<<endl;
    cout<<"Поточний каталог: "<< File_System::get_catalog()<<endl;
    cout << setw(5) << "" << "№" << setw(11)<< "" << "Назва" << endl;
    for(int i = 0; i < object.count(); i++)
        cout << setw(9) << "№ " << i + 1 << setw(7)<< "" << object.print_element(i)<<endl;
    cout << endl;
}
/*
    Виведення меню
*/
void Table_File::print_variant_menu(List<string>& object){
    for (auto i = 0; i < object.count(); i++)
        cout << setw(5) << "" << i + 1 << object.print_element(i) << endl;
    cout << setw(5)<<""<<"Ваш варіант: ";
}
/*
    Призупинення виконання програми через виведення технічного повідомлення
*/
void Table_File::check_continue(){
    cout << setw(5)<<""<<"Для продовження натисніть Enter..." << endl;;
    system("read");
}
/*
    Повідомлення користувачу. що під вказаним номером нічого не виявлено
*/
bool Table_File::warning(int index, List<string>& object){
    if(index > object.count() || index < 0){
        cout << endl << setw(5)<<""<<"Під вказаним номером не виявлено об'єкта. Спробуйте іще раз"<< endl;
        Table_File::check_continue();
        return true;
    }
    return false;
}