#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "List.h"

using namespace std;

template <class T>
class Tree {
private:
    /*
        Поле даних та вказівник на наступний елемент
    */
    template <class T_E>
    class Element {
    public:
        Element* lNext, *rNext;
        T_E data;
        Element(T_E _data = T_E(), Element* _lNext = nullptr, Element* _rNext = nullptr) {
            data = _data;
            lNext = _lNext;
            rNext = _rNext;
        }
    };
    /*
        Вказівники на початок дерева
    */
    Element<T>* head;
    int size;
    int number_level;
    T left;
    vector<vector<Element<T>*>> rows_level;

    struct cell_display {
        string valstr;
        bool present;
        cell_display() : present(false) {}
        cell_display(string valstr) : valstr(valstr), present(true) {}
    };
    using display_rows = vector< vector< cell_display > >;
    
    /*
        Очищує все дерево від даних, доступний лише в межах класу
    */
    void delete_Tree(Element<T> *&element);
    /*
        Додає елемент в дерево, видимий лише в межах класу
    */
    void add(T _data, Element<T> *&buffer);
    /*
        Виводить кількість рівнів дерева
    */
    int get_level();
    /*
        Визначає максимальний рівень дерева
    */
    int max_level(Element<T> *&buffer);
    /*
        Отримує значення дерева
    */
    display_rows get_row_display();
    /*
        Зчитування кожного рівня дерева та запис даних у масиси
    */
    void level_tree(vector<vector<Element<T>*>> &rows);
    /*
        Форматування даних в текстовий формат, для подальшого графічного відображення
    */
    vector<string> row_formatter(const display_rows& rows_disp);
    /*
        Обрізає зайві відступи зліва від дерева
    */
    static void trim_rows_left(vector<string>& rows);
    /*
        Пошук листків
    */
    void find_leaves(List<int>& buffer);
public:
    /*
        Присвоєння початкових значень головним елементам
    */
    Tree();
    /*
        Очищення всього вмісту дерева
    */
    ~Tree();
    /*
        Метод для отримання від користувача даних
    */
    void push_element(T _data);
    /*
        Видалення вмісту дерева
    */
    void remove_all();
    /*
        Виведення дерева
    */ 
    vector<string> print();
    /*
        Повертає силку на корінь дерева
    */
    bool is_empry();
    /*
        Найлівіший елемент дерева
    */
    T get_left_element();
    /*
        Виведення рівнів дерева на яких є листки
    */
    List<int> is_leaves();
};
/*
    Присвоєння початкових значень головним елементам
*/
template<class T>
Tree<T>::Tree()
{
    size = 0;
    head = nullptr;
    left = T();
}
/*
    Очищення всього вмісту дерева
*/
template<class T>
Tree<T>::~Tree(){
    if(head)
        delete_Tree(head);
}
/*
    Метод для отримання від користувача даних
*/
template<class T>
void Tree<T>::push_element(T _data){
    add(_data, head);
}
/*
    Додає елемент в дерево, видимий лише в межах класу
*/
template<class T>
void Tree<T>::add(T _data, Element<T> *&buffer){
    if(!buffer){
        buffer = new Element(_data);
        size++;
    }
    else{
        if(_data < buffer->data){
            add(_data, buffer->lNext);
        }
        else{
            add(_data, buffer->rNext);
        }
    }
}
/*
    Видалення вмісту дерева
*/
template<class T>
void Tree<T>::remove_all(){
    if(head)
        delete_Tree(head);
}
/*
    Очищує все дерево від даних, доступний лише в межах класу
*/
template<class T>
void Tree<T>::delete_Tree(Element<T> *&element){
    if(element){
        delete_Tree(element->lNext);
        delete_Tree(element->rNext);
        delete element;
        element = nullptr;
        size--;
    }
}
/*
    Повертає силку на корінь дерева
*/
template<class T>
bool Tree<T>::is_empry(){
    return head == nullptr;
}
/*
    Виводить кількість рівнів дерева
*/
template<class T>
int Tree<T>::get_level(){
    return head ? max_level(head) : 0;
}
/*
    Визначає максимальний рівень дерева
*/
template<class T>
int Tree<T>::max_level(Element<T> *&buffer){
    int left_depth = buffer->lNext ? max_level(buffer->lNext) : 0;
    int right_depth = buffer->rNext ? max_level(buffer->rNext) : 0;
    return (left_depth > right_depth ? left_depth : right_depth) + 1;
}
/*
    Отримує значення дерева
*/
template<class T>
typename Tree<T>::display_rows Tree<T>::get_row_display(){
    /*
        get_row_display будує вектор векторів структур cell_display
        кожен вектор структур cell_display представляє один рядок, починаючи з кореня
        почати з обходу дерева для побудови вектора векторів покажчиків вузла 
    */
    vector<vector<Element<T>*>> rows;
    if(!head){
        return display_rows();
    }
    level_tree(rows);
    rows_level = rows;    

    // Усі можливі слоти в дереві отримують структуру cell_display, тому, якщо фактичного вузла в розташуванні структури немає, її логічне поле "present" встановлюється на false.
    // Структура також містить рядкове представлення значення свого вузла, створене за допомогою об'єкта stringstream. 
    display_rows rows_disp;
    /*
        Дозволяє поєднати потоки вводу та виводу з рядком в пам'яті.
        При введені в поток додається в кінець рядка, а що виводиться - вилучається з початка
    */
    stringstream flow_string;
    for(const auto &row : rows){
        rows_disp.emplace_back();
        for(Element<T>* element : row){
            if(element){
                flow_string << element->data;
                rows_disp.back().push_back(cell_display(flow_string.str()));
                flow_string = stringstream();
            }
            else{
                rows_disp.back().push_back(cell_display());
            }
        }
    }
    return rows_disp;
}
/*
    Зчитування кожного рівня дерева та запис даних у масиси
*/
template<class T>
void Tree<T>::level_tree(vector<vector<Element<T>*>> &rows){
    vector<Element<T>*> traversal_stack;
    Element<T>* buffer = head;
    int max_lv = max_level(head);
    rows.resize(max_lv);
    int level = 0;
    while(true){
        //Обмеження, щоб програма не опустилася  нижче максимального рівня
        if(level == max_lv - 1){
            rows[level].push_back(buffer);
            --level;
            continue;
        }
        // Перехід до лівого нащадка, якщо візит до вузла є першим
        if(traversal_stack.size() == level){
            rows[level++].push_back(buffer);
            traversal_stack.push_back(buffer);
            //Якщо вказівник не пустий, перейти на ліву гілку
            if(buffer)
                buffer = buffer->lNext;
            continue;
        }
        // перехід до правого нащадка
        if(rows[level + 1].size() % 2 != 0){
            buffer = traversal_stack.back();
            //Якщо вказівник не пустий перейти на праву гілку
            if(buffer)
                buffer = buffer->rNext;
            ++level;
            continue;
        }
        // Вихід з циклу
        if(level == 0)
            break;
        traversal_stack.pop_back();
        buffer = traversal_stack.back();
        --level;
    };
}
/*
    Форматування даних в текстовий формат, для подальшого графічного відображення
*/
template<class T>
vector<string> Tree<T>::row_formatter(const display_rows& rows_disps){
    /*
        row_formatter приймає вектор рядків структур cell_display, згенерованих get_row_display, і форматує його в тестове представлення як вектор рядків 
    */
    using size_string = string::size_type;
    //Пошук максимальної довжини рядка
    size_string cell_width = 0;
    for(auto& rows_disp : rows_disps){
        for(auto& display : rows_disp){
            if(display.present && display.valstr.length() > cell_width) {
                cell_width = display.valstr.length();
            }
        }
    }
    //Якщо кількість елементів є парною
    if(cell_width % 2 == 0)
        ++cell_width;
    //Дозволяє з'єднати листки, коли всі вони мають розмір одного символу
    if(cell_width < 3)
        cell_width = 3;
    
    //Змінна для збереження кінцувого результату
    vector<string> formatted_rows;
    size_string row_count = rows_disps.size();
    size_string row_elem_count = 1 << (row_count - 1);
    //Кількість пробілів на початку нижнього рядка
    size_string left_pad = 0;

    //Опрацювання даних та отримання необхідної довжини для майбутнього графічного виведення дерева
    for(size_string reverse_indexes = 0; reverse_indexes < row_count; ++reverse_indexes){
        auto& cd_row = rows_disps[row_count - reverse_indexes - 1];
        //Кількість рядків шлешів. Також використовується для інших зміщень тексту
        size_string space = (size_string(1) << reverse_indexes) * (cell_width + 1) / 2 - 1;
        //Збір рядка в одне ціле
        string row;
        for(size_string row_count = 0; row_count < row_elem_count; ++row_count){
            //Додати бльше відступів, якщо це не лівий крайній елемент
            row += string(row_count ? left_pad * 2 + 1 : left_pad, ' ');
            // Виконання над вузлом, якщо він існує
            if(cd_row[row_count].present){
                //Позиція існуючого вузла
                string valstr = cd_row[row_count].valstr;
                //Визначення необхідної кількості пробілів перед та після нащадка
                size_string long_padding = cell_width - valstr.length();
                size_string short_padding = long_padding / 2;
                long_padding -= short_padding;
                row += string(row_count % 2 ? short_padding : long_padding, ' ');
                row += valstr;
                row += string(row_count % 2 ? long_padding : short_padding, ' ');
            }
            else {
                row += string(cell_width, ' ');
            }
        }
        //Додання готового рядка
        formatted_rows.push_back(row);
        //Якщо корінь додано, то цикл завершено
        if(row_elem_count == 1)
            break;
        //Змінні які містять ліву та праву похилі прямі, що ведуть від предка до нащадків
        size_string left_space = space + 1;
        size_string right_space = space - 1;
        for(size_string sr = 0; sr < space; ++sr){
            string row;
            for(size_string c = 0; c < row_elem_count; ++c){
                if(c % 2 == 0) {
                    row += string(c ? left_space*2 + 1 : left_space, ' ');
                    row += cd_row[c].present ? '/' : ' ';
                    row += string(right_space + 1, ' ');
                } 
                else {
                    row += string(right_space, ' ');
                    row += cd_row[c].present ? '\\' : ' ';
                }
            }
            formatted_rows.push_back(row);
            ++left_space;
            --right_space;
        }
        left_pad += space + 1;
        row_elem_count /= 2;
    }
    //Обертає вектор, щоб корінь опинився зверху
    reverse(formatted_rows.begin(), formatted_rows.end());
    return formatted_rows;
}
/*
    Обрізає зайві відступи зліва від дерева
*/
template<class T>
void Tree<T>::trim_rows_left(vector<string>& rows){
    if(!rows.size())
        return;
    auto min_space = rows.front().length();
    for(const auto& row : rows){
        auto i = row.find_first_not_of(' ');
        if(i == string::npos)
            i = row.length();
        if(i == 0)
            break;
        if(i < min_space)
            min_space = i;
    }
    for(auto& row : rows){
        row.erase(0, min_space);
    }
}
/*
    Виведення дерева
*/ 
template<class T>
vector<string> Tree<T>::print(){
    if(get_level() == 0){
        cout << endl << setw(5) << "" << "Дерево порожнє" <<endl << endl;
        return vector<string>();
    }
    auto formatted_rows = row_formatter(get_row_display());
    trim_rows_left(formatted_rows);
    return formatted_rows;
}
/*
    Найлівіший елемент дерева
*/
template<class T>
T Tree<T>::get_left_element(){
    left = T();
    for(int index = 0; index < rows_level.size(); ++index){
        for(Element<T>* element : rows_level[index]){
            if(!element)
                continue;
            if(!element->lNext && !element->rNext && left == T()){
                left = element->data;
                break;
            }
        }
        if(left != T())
            break;
    }
    return left;
}
 /*
    Виведення рівнів дерева на яких є листки
*/
template<class T>
List<int> Tree<T>::is_leaves(){
    List<int> buffer;
    find_leaves(buffer);
    for(int index = 0; index < buffer.count(); ++index){
        auto element = buffer.print_element(index);
        for(int i = index + 1; i < buffer.count(); i++){
            if(element == buffer.print_element(i)){
                buffer.remove_index(i--);
            }
        }
        
    }
    return buffer;
}
/*
    Пошук листків
*/
template<class T>
void Tree<T>::find_leaves(List<int>& buffer){
    for(int index = 0; index < rows_level.size(); ++index){
        for(Element<T>* element : rows_level[index]){
            if(!element)
                continue;
            if(!element->lNext && !element->rNext){
                buffer.push_end(index + 1);
            }
        }
    }
}