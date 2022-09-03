#include "Graphic.hh"

/*
    Завдання номер один
*/
void Graphic::Exercise_One(){
    system("clear");
    cout << endl << setw(5)<<""<<"Завдання №1"<<endl;
    cout <<setw(5)<<""<<"1. Сформулювати чергу з 8 чисел."<<endl;
    cout <<setw(5)<<""<<"2. Потроїти модуль різниці між 2-м і 3-м числом черзі."<<endl;
    cout <<setw(5)<<""<<"3. Результат помістити в чергу."<<endl << endl;
    int element_two, element_tree, difference;
    Turn<int> turn;
    for (int i = 0; i < 8; i++){
        turn.push_end(rand() % 21 - 10);
    }

    Print(turn, turn.count());

    element_two = turn.print_element(1);
    element_tree = turn.print_element(2);
    difference = abs(element_two - element_tree);

    cout << endl << setw(5) << "" << "Елемент №2: " << element_two << endl;
    cout << setw(5) << "" << "Елемент №3: " << element_tree << endl << endl;

    cout << setw(5) << "" << "Модуль різниці елемента №2 та №3: " << difference << endl << endl;
    turn.push_end(difference * 3);

    cout << setw(5) << "" << "Потроєний модуль різниці додано в кінець черги." << endl;
    cout << setw(5) << "" << "Нова черга." << endl << endl;

    Print(turn, turn.count());
}

/*
    Завдання номер два
*/
void Graphic::Exercise_Two(){
    system("clear");
    cout << endl << setw(5)<<""<<"Завдання №2"<<endl;
    cout <<setw(5)<<""<<"1. Створити стек 30 випадкових чисел в діапазоні від 0 до 100. Надрукувати їх."<<endl;
    cout <<setw(5)<<""<<"2. Знайти елемент стека з максимальним значенням і поміняти його з елементом, що має наступне максимальне значення."<<endl << endl;
    Stack<int> stack;
    int max_index_one = 0, max_index_two = 0;
    for(int i = 0; i < 30; i++){
        stack.push_beg(rand()%100);
    }
    cout << setw(5)<<""<<"Вміст стека" << endl << endl;
    Print(stack, stack.count());

    max_index_one = stack.max_element_index(stack.count());
    max_index_two = stack.max_element_index(max_index_one);

    cout << setw(5)<<""<<"Максимальний елемент №1: "<<stack.print_element(max_index_one) << " під індексом: "<<max_index_one<<endl;
    cout << setw(5)<<""<<"Максимальний елемент №2: "<<stack.print_element(max_index_two) << " під індексом: "<<max_index_two<<endl << endl;
    stack.swap(max_index_one, max_index_two);

    cout << setw(5)<<""<<"Оновлений вміст стека" << endl << endl;
    Print(stack, stack.count());
}
/*
    Виведення вмісту стека та черги
*/
template<class T>
void Graphic::Print(T& structs, int size){
    for (int i = 0; i < size; i++){
        cout << setw(5) << "" << structs.print_element(i);
    }
    cout << endl << endl;
}
/*
    Призупинення виконання програми через виведення технічного повідомлення
*/
void Graphic::check_continue(){
    cout << setw(5)<<""<<"Для продовження натисніть Enter..." << endl;;
    system("read");
}
/*
    Старт програми
*/
void Graphic::Start(){
    int variant;
    do{
        system("clear");
        cout << endl <<setw(10)<<""<<"Лабораторна №7"<<endl;
        cout <<setw(10)<<""<<"Робота зі структурованими типами даних."<<endl << endl;
        cout <<setw(5)<<""<<"1. Завдання №1"<<endl;
        cout <<setw(5)<<""<<"2. Завдання №2"<<endl;
        cout <<setw(5)<<""<<"Ваш варіант: ";
        cin >> variant;
        switch(variant){
            case Variant::Exit: break;
            case Variant::One_exercise: Exercise_One(); break;
            case Variant::Two_exercise: Exercise_Two(); break;
        }
        if(variant != Variant::Exit)
            check_continue();
    }while(variant != Variant::Exit);
}