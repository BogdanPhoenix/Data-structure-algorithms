#pragma once
#include <iostream>
#include <initializer_list>
using namespace std;

template <class T>
class Stack
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
        Вказівники на початок стека та вказівник на елемент, який використовувався перед цим
    */
    Element<T> *head, *remember_element;
    int size, remember_index;
    /*
        Пошук елемента стека за номером та передача його для подальшої обробки
    */
    Element<T>* find(int index);
public:
    /*
        Присвоєння початкових значень головним елементам
    */
    Stack();
    /*
        Конструктор з довільною кількістю параметрів
    */
    Stack(initializer_list<T> args);
    /*
        Очищення всього вмісту стека
    */
    ~Stack();
    /*
        Додання елемента на початок стека
    */
    void push_beg(T _data);
    /*
        Виведення елемента за індексом
    */
    T &print_element(int index);
    /*
        Перевірка чи пустий стек
    */
    bool is_nullptr();
    /*
        Виведення розміру стека
    */
    int count();
    /*
        Видалення першого елемента стека
    */
    void remove_beg();
    /*
        Видалення всіх елементів стека
    */
    void remove_all();
    /*
        Обмін двох елементів між собою за індексами
    */
    void swap(int index_1, int index_2);
    /*
        Пошук максимального елемента та ігнорування елемента за вказаним індексом
    */
    int max_element_index(int ignore_index);
};
/*
    Присвоєння початкових значень головним елементам
*/
template <class T>
Stack<T>::Stack()
{
    remember_index = size = 0;
    remember_element = head = nullptr;
}
/*
    Конструктор з довільною кількістю параметрів
*/
template <class T>
Stack<T>::Stack(initializer_list<T> args) : Stack()
{
    for (auto &arg : args)
        push_beg(arg);
}
/*
    Очищення всього вмісту черги
*/
template <class T>
Stack<T>::~Stack()
{
    remove_all();
}
/*
    Додання елемента на початок стека
*/
template <class T>
void Stack<T>::push_beg(T _data)
{
    head = new Element<T>(_data, head);
    size++;
}
/*
    Виведення елемента за індексом
*/
template <class T>
T &Stack<T>::print_element(int index)
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
    Перевірка чи пустий стек
*/
template <class T>
bool Stack<T>::is_nullptr()
{
    return head == nullptr;
}
/*
    Виведення розміру стека
*/
template <class T>
int Stack<T>::count()
{
    return size;
}
/*
    Видалення першого елемента стека
*/
template <class T>
void Stack<T>::remove_beg()
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
    Видалення всіх елементів стека
*/
template <class T>
void Stack<T>::remove_all()
{
    while (head != nullptr)
    {
        remove_beg();
    }
}
/*
    Обмін двох елементів між собою за індексами
*/
template<class T>
void Stack<T>::swap(int index_one, int index_two){
    /*
    Element<T> *buffer_1, *buffer_2, *element_1, *element_2;
    element_1 = find(--index_two);
    element_2 = find(--index_one);

    buffer_1 = new Element<T>(element_1->pNext->data, element_2->pNext->pNext);
    buffer_2 = new Element<T>(element_2->pNext->data, element_1->pNext->pNext);
    element_1->pNext = buffer_2;
    element_2->pNext = buffer_1;
    */
    
    Element<T> *prev1 = nullptr, *node1 = nullptr, *prev2 = nullptr, *node2 = nullptr, *temp;
    if(index_one != 0 && index_two != 0){
        prev1 = find(--index_one);
        node1 = prev1->pNext;
        prev2 = find(--index_two);
        node2 = prev2->pNext;

        prev1->pNext = node2;
        prev2->pNext = node1;

        temp = node1->pNext;
        node1->pNext = node2->pNext;
        node2->pNext = temp;
    }
    else{
        int max_pos;
        max_pos = index_one != 0 ? index_one : index_two;

        prev2 = find(--max_pos);
        node2 = prev2->pNext;
        node1 = head;

        prev2->pNext = head;

        temp = node1->pNext;
        node1->pNext = node2->pNext;
        node2->pNext = temp;
        head = node2;
    }
}
/*
    Пошук елемента стека за номером та передача його для подальшої обробки
*/
template<class T>
Stack<T>::Element<T>* Stack<T>::find(int index){
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
/*
    Пошук максимального елемента та ігнорування елемента за вказаним індексом
*/
template<class T>
int Stack<T>::max_element_index(int ignore_index){
    Element<T>*buffer = head, *max = head;
    int index = 0, max_index = 0;
    while (buffer != nullptr)
    {
        if(buffer->data > max->data && index != ignore_index){
            max = buffer;
            max_index = index;
        }
        buffer = buffer->pNext;
        index++;
    }
    return max_index;
}