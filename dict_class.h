#pragma once
#include <iostream>
#include <vector>

using namespace std;


class cNode 
{
    cNode* left, * right;       /// указатели на потомков
    string eng, nullpoint = "Элемент не найден";
    vector<string> rus_multiple; ///вектор возможных переводов английского слова

public:
    cNode(string eng_inp, string rus_inp) {       
        eng = eng_inp;
        rus_multiple.push_back(rus_inp);
        left = right = nullptr;
    } /// конструктор

    string get_eng() {
        return eng;
    }

    vector<string> get_rus_multiple() {
        return rus_multiple;
    }

    vector<string>& get_rus_m_element() {
        return rus_multiple;
    }

    string& nullpointer() {
        return nullpoint;
    }       /// вспомогательный элемент, именно его адрес мы возвращаем в функции find_node()

    cNode* get_left() {
        return left;
    }

    cNode* get_right() {
        return right;
    }

    void set_eng(string eng_inp) {
        this->eng = eng_inp;
    }

    void add_to_rus_multiple(string rus_inp) {
        rus_multiple.push_back(rus_inp);
    }

    void delete_from_rus_multiple(int index) {
        rus_multiple.erase(rus_multiple.begin() + index);
    }

    void set_left(cNode* left1) {
        left = left1;
    }

    void set_right(cNode* right1) {
        right = right1;
    }

    bool operator== (cNode comp);
}; ///класс узла бинарного дерева с геттерами и сеттерами



class dict      /// класс бинарного дерева
{
private:
    cNode* root;
    void add_node(cNode* node, string eng_inp, string rus_inp); ///рекурсивно встраивает новое английское слово и его переводы в дерево

    string& find_node(cNode* t, string eng_inp, int index); ///ищет и возвращает элемент - один конкретный перевод

    void delete_tr(cNode* t, string eng_inp, int index); ///рекурсивно удаляет один из переводов

    cNode* delete_node(cNode* node, string eng_inp); ///рекурсивно удаляет сам элемент (английское слово и все его переводы)

    int count_nodes(cNode* node); ///считает количество английских слов в словаре

public:
    void set_translation(string eng_inp, string rus_inp); ///добавляет новое английское слово и его переводы

    void remove_translation(string eng_inp); ///удаляет элемент дерева

    int length(); ///возвращает количество слов

    int tr_count(string eng_inp); ///возвращает количество русских переводов конкретного английского слова

    void delete_one_translation(string eng_inp, int index); ///удаляет один из переводов

    // Перегрузка операторов
    string operator[] (string eng_inp); ///перегруженный оператор для получения перевода
    string& operator[] (pair<string, int> transl); ///перегруженный оператор для ИЗМЕНЕНИЯ перевода (в паре английское слово и номер перевода, который нужно изменить)
    void operator-= (string eng_inp); ///перегруженный оператор для удаления слова
    void operator+= (pair<string, string> eng_inp); ///перегруженный оператор для добавления слова и одного его перевода
};
