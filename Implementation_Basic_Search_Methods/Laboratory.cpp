#include "Laboratory.hh"

/*
    Запуск програми
*/
void Laboratory::start(){
    int variant;
    do{
        system("clear");
        cout << endl <<setw(7)<<""<<"Лабораторна №9"<<endl;
        cout <<setw(7)<<""<<"Реалізація основних методів пошуку.."<<endl << endl;
        cout <<setw(5)<<""<<"0. Вихід"<<endl;
        cout <<setw(5)<<""<<"1. Завдання №1"<<endl;
        cout <<setw(5)<<""<<"2. Завдання №2"<<endl;
        cout <<setw(5)<<""<<"Ваш варіант: ";
        cin >> variant;
        switch(variant){
            case Variant::Menu_Exit: break;
            case Variant::One_exercise: ExerciseOne(); break;
            case Variant::Two_exercise: ExerciseTwo(); break;
        }
    }while(variant != Variant::Menu_Exit);
}
/*
    Завдання №1
*/
void Laboratory::ExerciseOne()
{
    system("clear");
    cout << endl << setw(5)<<""<<"Завдання №1"<<endl;
    cout <<setw(5)<<""<<"1. Створити масив Arr, елементи якого вибираються випадковим чином з інтервалу [10, 90]."<<endl;
    cout <<setw(5)<<""<<"2. Визначити методом лінійного пошуку, чи містить він задане число."<<endl;
    cout <<setw(5)<<""<<"3. Якщо елемент знайдений, то видалити його з масиву"<<endl << endl;
    Table_File::check_continue();

    system("clear");
    int size, remember_size;
    cout << setw(5) << "" << "Введіть розмір масива: ";
    cin >> size;
    remember_size = size;
    int* arr = new int[size];
    ArrayAdd(arr, size, 10, 90);

    do{
        Find(arr, size, remember_size, Variant::One_exercise);
    }while(Table_File::check_exit());
    delete[] arr;
}
/*
    Завдання №2
*/
void Laboratory::ExerciseTwo(){
    system("clear");
    cout << endl << setw(5)<<""<<"Завдання №2"<<endl;
    cout <<setw(5)<<""<<"1. Сформулювати масив Arr, упорядкований за зростанням."<<endl;
    cout <<setw(5)<<""<<"2. Методом бінарного пошуку визначити чи містить він задане число."<<endl;
    cout <<setw(5)<<""<<"3. Якщо елемент знайдений, то видалити його з масиву"<<endl << endl;
    Table_File::check_continue();

    system("clear");
    int size, remember_size;
    cout << setw(5) << "" << "Введіть розмір масива: ";
    cin >> size;
    remember_size = size;
    int* arr = new int[size];
    ArrayAdd(arr, size, -10, 10);
    Sort(arr, size);

    do{
        Find(arr, size, remember_size, Variant::Two_exercise);
    }while(Table_File::check_exit());
    delete[] arr;
}
/*
    Пошук
*/
void Laboratory::Find(int* array, int& size, int& remember_size, int variant){
    int key, index;
    system("clear");
    cout << setw(5)<<""<<"Вміст масиву Arr"<< endl;
    ArrayPrint(array, size);
    cout << setw(5)<<""<<"Введіть число яке хочете знайти: ";
    cin >> key;

    do{
        switch(variant){
            case 1: index = SearchLine(array, size, key); break;
            case 2: index = SearchBinar(array, key, 0, size); break;
        }
        if(index < 0)
           break;
        Displacement_Elements(array, size, index);
    }while(true);
    Result(array, size, remember_size);
}
/*
    Виведення результатів пошуку
*/
void Laboratory::Result(int* array, int& size, int& remember_size){
    if(size == remember_size)
        cout << setw(5)<<""<<"За вашим запитом нічого не виявлено."<< endl << endl;
    else{
            
        cout << endl << setw(5) << "" << "За вашим запитом знайдено " << remember_size - size << " збіги" << endl << endl;
        cout << setw(5) << "" << "Оновлений вміст масиву Arr" << endl;
        ArrayPrint(array, size);
        remember_size -= (remember_size - size);
    }
}
/*
    Заповнення масиву
*/
void Laboratory::ArrayAdd(int* array, int &size, int left_limit, int rigth_limit){
    auto value = rigth_limit - left_limit;
    for(int i = 0; i < size; i++){
        array[i] = rand() % value + left_limit;
    }
}
/*
    Виведення масиву
*/
void Laboratory::ArrayPrint(int *array, int & size){
    cout << endl;
    for(int i = 0; i < size; i++)
        cout << setw(5)<<""<<array[i];
    cout << endl << endl;
}
/*
    Лінійний пошук
*/
int Laboratory::SearchLine(int *array, int &size, int key){
    int i = 0;
    for(; i < size; ++i){
        if(array[i] == key)
            return i;
    }
    return -1;
}
/*
    Бінарний пошук
*/
int Laboratory::SearchBinar(int *array, int& key, int left_limit, int right_limit){
    int index;
    if(left_limit > right_limit){
        return -1;
    }
    else{
        index = (left_limit + right_limit) / 2;
        if(array[index] == key){
            return index;
        }
        else{
            return array[index] < key ? SearchBinar(array, key, index + 1, right_limit) : SearchBinar(array, key, left_limit, index - 1);
        }
    }
}
/*
    Зсув масиву вліво
*/
void Laboratory::Displacement_Elements(int* array, int& size, int index_element){
    for(int i = index_element; i < size - 1; i++){
        array[i] = array[i + 1];
    }
    array = (int*)realloc(array, --size * sizeof(int));
}
/*
    Сортування масиву
*/
void Laboratory::Sort(int* array, int& size){
    int index, buffer;
    for (int j = 1; j < size; j++) {
        index = j - 1;
        buffer = array[j];
        while (index >= 0 && array[index] > buffer) {
            array[index + 1] = array[index];
            --index;
        }
        array[++index] = buffer;
    }
}
