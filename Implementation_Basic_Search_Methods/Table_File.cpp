#include "Table_File.hh"

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
/*
    Запит про підтвердження виходу
*/
bool Table_File::check_exit(){
    int result;
    cout << setw(5)<<""<<"Ви хочете продовжити чи вийти?" << endl;
    cout << setw(7)<<""<<"0. Ні"<< endl;
    cout << setw(7)<<""<<"1. Так"<< endl;
    cout << setw(5)<<""<<"Ваш варіант: ";
    cin >> result;
    return result;
}