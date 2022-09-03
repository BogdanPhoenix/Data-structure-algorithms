#pragma once
#include <iostream>
#include <initializer_list>
using namespace std;

template<class T>
class Turn
{
private:
    /*
        Поле даних та вказівник на наступний елемент
    */
    template <class T_E>
    class Element
    {
    public:
        Element *pNext;
        T_E data;
        Element(T_E _data = T_E(), Element *_pNext = nullptr)
        {
            data = _data;
            pNext = _pNext;
        }
    };
    /*
        Вказівники на початок, на кінець черги та вказівник на попередній елемент до якого зверталися
    */
    Element<T> *head, *last, *remember_element;
    /*
        Розмір черги та індек попереднього елемента який використовувався перед цим
    */
    int size, remember_index;
    /*
        Додання елемента на початок черги
    */
    void push_beg(T _data);
    /*
        Пошук елемента черги за номером та передача його для подальшої обробки
    */
    Element<T>* find(int index);
public:
    /*
        Присвоєння початкових значень головним елементам
    */
    Turn();
    /*
        Конструктор з довільною кількістю параметрів
    */
    Turn(initializer_list<T> args);
    /*
        Очищення всього вмісту черги
    */
    ~Turn();
    /*
        Додання елемента в кінець черги
    */
    void push_end(T _data);
    /*
        Виведення елемента за індексом
    */
    T &print_element(int index);
    /*
        Перевірка чи пуста черга
    */
    bool is_nullptr();
    /*
        Виведення розміру черги
    */
    int count();
    /*
        Видалення першого елемента черги
    */
    void remove_beg();
    /*
        Видалення всіх елементів черги
    */
    void remove_all();
};
/*
    Присвоєння початкових значень головним елементам
*/
template <class T>
Turn<T>::Turn()
{
    remember_index = size = 0;
    remember_element = head = last = nullptr;
}
/*
    Конструктор з довільною кількістю параметрів
*/
template <class T>
Turn<T>::Turn(initializer_list<T> args):Turn()
{
    for (auto &arg : args)
        push_end(arg);
}
template <class T>
Turn<T>::~Turn()
{
    remove_all();
}
/*
    Додання елемента на початок черги
*/
template <class T>
void Turn<T>::push_beg(T _data)
{
    head = new Element<T>(_data, head);
    size++;
    if (head->pNext == nullptr)
    {
        last = head;
    }
}
/*
    Додання елемента в кінець черги
*/
template <class T>
void Turn<T>::push_end(T _data)
{
    if (head == nullptr)
    {
        push_beg(_data);
    }
    else
    {
        Element<T> *buffer = new Element<T>(_data);
        last->pNext = buffer;
        last = buffer;
        size++;
    }
}
/*
    Виведення елемента за індексом
*/
template <class T>
T &Turn<T>::print_element(int index)
{
    Element<T> *buffer;
    try
    {
        if (index >= size)
            throw -1;
        buffer = find(index);
    }
    catch (int)
    {
        cout << "УВАГА: Ви вийшли за межи списку." << endl;
        cout << "Програму завершено!!!" << endl;
        remove_all();
        exit(139);
    }
    return buffer->data;
}
/*
    Перевірка чи пуста черга
*/
template <class T>
bool Turn<T>::is_nullptr()
{
    return head == nullptr;
}
/*
     Виведення розміру черги
*/
template <class T>
int Turn<T>::count()
{
    return size;
}
/*
    Видалення першого елемента черги
*/
template <class T>
void Turn<T>::remove_beg()
{
    try
    {
        if (head == nullptr)
            throw -1;
        Element<T> *buffer = head;
        head = buffer->pNext;
        delete buffer;
        size--;
    }
    catch (int)
    {
        cout << "УВАГА: Список є порожнім. Видаляти нема що." << endl;
        cout << "Програму завершено!!!" << endl;
        exit(139);
    }
}
/*
    Видалення всіх елементів черги
*/
template <class T>
void Turn<T>::remove_all()
{
    while (head != nullptr)
    {
        remove_beg();
    }
}
/*
    Пошук елемента черги за номером та передача його для подальшої обробки
*/
template<class T>
Turn<T>::Element<T>* Turn<T>::find(int index){
    Element<T>* buffer = head;
    int index_element;
        if (index > remember_index && remember_element != nullptr)
        {
            buffer = remember_element;
            index_element = remember_index;
        }
        else
        {
            buffer = head;
            index_element = 0;
        }
        while (index_element != index)
        {
            index_element++;
            buffer = buffer->pNext;
        }
        remember_element = buffer;
        remember_index = index;
    return buffer;
}