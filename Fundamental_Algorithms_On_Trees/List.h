#pragma once
#include <iostream>
#include <initializer_list>
using namespace std;

template <class T>
class List {
private:
    /*
        Поле даних та вказівник на наступний елемент
    */
    template <class T_E>
    class Element {
    public:
        Element* pNext;
        T_E data;
        Element(T_E _data = T_E(), Element* _pNext = nullptr) {
            data = _data;
            pNext = _pNext;
        }
    };
    /*
        Вказівники на початок та на кінець списка
    */
    Element<T>* head, *last, *remember_element;
    int size, remember_index;
public:
    /*
        Присвоєння початкових значень головним елементам
    */
    List();
    /*
        Конструктор з довільною кількістю параметрів
    */
    List(initializer_list<T> args);
    /*
        Очищення всього вмісту списка
    */
    ~List();
    /*
        Додання елемента на початок списка
    */
    void push_beg(T _data);
    /*
        Додання елемента в кінець списка
    */
    void push_end(T _data);
    /*
        Додання елемента в список за індексом
    */
    void push_index(T _data, int index);
    /*
        Виведення елемента за індексом
    */
    T & print_element(int index);
    /*
        Перевірка чи пустий список
    */
    bool is_nullptr();
    /*
        Виведення розміру списка
    */
    int count();
    /*
        Видалення першого елемента списка
    */
    void remove_beg();
    /*
        Видалення останнього елемента списка
    */
    void remove_end();
    /*
        Видалення всіх елементів списка
    */
    void remove_all();
    /*
        Видалення одного елемента зі списку за вказаним індексом
    */
    void remove_index(int index);
    /*
        Видалення елементів зі списку в діапазоні вказаних за індексами
    */
    void remove_index(int start, int end);
    /*
        Перестановка сусідніх елементів місцями
    */
    void swap(int index);
};

/*
    Присвоєння початкових значень головним елементам
*/
template<class T>
List<T>::List()
{
    remember_index = size = 0;
    remember_element = head = last = nullptr;
}
/*
    Очищення всього вмісту списка
*/
template<class T>
List<T>::~List(){
    remove_all();
}
/*
    Конструктор з довільною кількістю параметрів
*/
template<class T>
List<T>::List(initializer_list<T> args):List(){
    for(auto& arg : args)
        push_end(arg);
}
/*
    Додання елемента на початок списка
*/
template <class T>
void List<T>::push_beg(T _data){
    head = new Element<T>(_data, head);
    size++;
    if(head->pNext == nullptr){
        last = head;
    }
}
/*
    Додання елемента в кінець списка
*/
template <class T>
void List<T>::push_end(T _data){
    if(head == nullptr){
        push_beg(_data);
    }
    else{
        Element<T>* buffer = new Element<T>(_data);
        last->pNext = buffer;
        last = buffer;
        size++;
    }
}
/*
    Додання елемента в список за індексом
*/
template<class T>
void List<T>::push_index(T _data, int index){
    int index_element = 0;
    Element<T>* push,* buffer = head;
    while(index_element < index - 1){
        buffer = buffer->pNext;
        index_element++;
    }
    push = new Element<T>(_data, buffer->pNext);
    buffer->pNext = push;
    size++;
}
/*
    Виведення елемента за індексом
*/
template<class T>
T & List<T>::print_element(int index){
    Element<T>* buffer;
    try{
        if(index >= size)
            throw -1;
        int index_element;
        if(index > remember_index && remember_element != nullptr){
            buffer = remember_element;
            index_element = remember_index;
        }
        else{
            buffer = head;
            index_element = 0;            
        }
        while(index_element != index){
            index_element++;
            buffer = buffer->pNext;
        }
        remember_element = buffer;
        remember_index = index;
    }
    catch(int){
        cout << "УВАГА: Ви вийшли за межи списку." <<endl; 
        cout << "Програму завершено!!!" <<endl;
        remove_all();
        exit(139);
    }
    return buffer->data;
}

/*
    Перевірка чи пустий список
*/
template<class T>
bool List<T>::is_nullptr(){
    return head == nullptr;
}
/*
     Виведення розміру списка
*/
template<class T>
int List<T>::count() { 
    return size; 
}
/*
    Видалення першого елемента списка
*/
template<class T>
void List<T>::remove_beg(){
    try{
        if(head == nullptr)
            throw -1;
        Element<T>* buffer = head;
        head = buffer->pNext;
        delete buffer;
        size--;
    }
    catch(int){
        cout << "УВАГА: Список є порожнім. Видаляти нема що." <<endl; 
        cout << "Програму завершено!!!" <<endl;
        exit(139);
    }
}
/*
    Видалення останнього елемента списка
*/
template<class T>
void List<T>::remove_end(){
    if(last == head){
        remove_beg();
    }
    else{
        int index_element = 0;
        Element<T>* buffer = head;
        while(buffer->pNext != last){
            buffer=buffer->pNext;
        }
        delete last;
        last = buffer;
        size--;
        }
}
/*
    Видалення всіх елементів списка
*/
template<class T>
void List<T>::remove_all(){
    while(head != nullptr){
        remove_beg();
    }
}
/*
    Видалення одного елемента зі списку за вказаним індексом
*/
template<class T>
void List<T>::remove_index(int index){
    try{
        if(index >= size)
            throw -1;
        if(index == 0){
            remove_beg();
        }
        else if(index == size - 1){
            remove_end();
        }
        else{
            int index_element = 0;
            Element<T>* del_element, *buffer = head;
            while(buffer != nullptr && index_element < index - 1){
                index_element++;
                buffer=buffer->pNext;
            }
            del_element = buffer->pNext;
            buffer->pNext = del_element->pNext;
            delete del_element;
            size--;
        }
    }
    catch(int){
        cout << "УВАГА: Ви вийшли за межи списку." <<endl; 
        cout << "Програму завершено!!!" <<endl;
        remove_all();
        exit(139);
    }
}
/*
    Видалення елементів зі списку в діапазоні вказаних за індексами
*/
template<class T>
void List<T>::remove_index(int start, int end){
    if(start == 0){
        for(int i = 0; i <= end; i++){
            remove_beg();
        }
    }
    else if(end == size - 1){
        for(int i = end; i >= start; i--)
            remove_end();
    }
    else{
        try{
            if(end >= size)
                throw -1;
            for(int i = start; i < end; i++)
                remove_index(start);
        }
        catch(int){
            cout << "УВАГА: Ви вийшли за межи списку." <<endl; 
            cout << "Програму завершено!!!" <<endl;
            remove_all();
            exit(139);
        }
    }
}
/*
    Перестановка сусідніх елементів місцями
*/
template<class T>
void List<T>::swap(int index){
    int index_element = 0;
    Element<T>*buffer = head;
    T data;
    while(index_element < index){
        buffer = buffer->pNext;
        index_element++;
    }
    data = buffer->data;
    remove_index(index);
    push_index(data, index + 1);
}