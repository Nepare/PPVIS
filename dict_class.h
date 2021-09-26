#pragma once
#include <iostream>
#include <vector>

using namespace std;


class cNode 
{
    cNode* left, * right;       /// ÑÐºÐ°Ð·Ð°ÑÐµÐ»Ð¸ Ð½Ð° Ð¿Ð¾ÑÐ¾Ð¼ÐºÐ¾Ð²
    string eng, nullpoint = "Ð­Ð»ÐµÐ¼ÐµÐ½Ñ Ð½Ðµ Ð½Ð°Ð¹Ð´ÐµÐ½";
    vector<string> rus_multiple; ///Ð²ÐµÐºÑÐ¾Ñ Ð²Ð¾Ð·Ð¼Ð¾Ð¶Ð½ÑÑ Ð¿ÐµÑÐµÐ²Ð¾Ð´Ð¾Ð² Ð°Ð½Ð³Ð»Ð¸Ð¹ÑÐºÐ¾Ð³Ð¾ ÑÐ»Ð¾Ð²Ð°

public:
    cNode(string eng_inp, string rus_inp) {       
        eng = eng_inp;
        rus_multiple.push_back(rus_inp);
        left = right = nullptr;
    } /// ÐºÐ¾Ð½ÑÑÑÑÐºÑÐ¾Ñ

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
    }       /// Ð²ÑÐ¿Ð¾Ð¼Ð¾Ð³Ð°ÑÐµÐ»ÑÐ½ÑÐ¹ ÑÐ»ÐµÐ¼ÐµÐ½Ñ, Ð¸Ð¼ÐµÐ½Ð½Ð¾ ÐµÐ³Ð¾ Ð°Ð´ÑÐµÑ Ð¼Ñ Ð²Ð¾Ð·Ð²ÑÐ°ÑÐ°ÐµÐ¼ Ð² ÑÑÐ½ÐºÑÐ¸Ð¸ find_node()

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
}; ///ÐºÐ»Ð°ÑÑ ÑÐ·Ð»Ð° Ð±Ð¸Ð½Ð°ÑÐ½Ð¾Ð³Ð¾ Ð´ÐµÑÐµÐ²Ð° Ñ Ð³ÐµÑÑÐµÑÐ°Ð¼Ð¸ Ð¸ ÑÐµÑÑÐµÑÐ°Ð¼Ð¸



class dict      /// ÐºÐ»Ð°ÑÑ Ð±Ð¸Ð½Ð°ÑÐ½Ð¾Ð³Ð¾ Ð´ÐµÑÐµÐ²Ð°
{
private:
    cNode* root;
    void add_node(cNode* node, string eng_inp, string rus_inp); ///ÑÐµÐºÑÑÑÐ¸Ð²Ð½Ð¾ Ð²ÑÑÑÐ°Ð¸Ð²Ð°ÐµÑ Ð½Ð¾Ð²Ð¾Ðµ Ð°Ð½Ð³Ð»Ð¸Ð¹ÑÐºÐ¾Ðµ ÑÐ»Ð¾Ð²Ð¾ Ð¸ ÐµÐ³Ð¾ Ð¿ÐµÑÐµÐ²Ð¾Ð´Ñ Ð² Ð´ÐµÑÐµÐ²Ð¾

    string& find_node(cNode* t, string eng_inp, int index); ///Ð¸ÑÐµÑ Ð¸ Ð²Ð¾Ð·Ð²ÑÐ°ÑÐ°ÐµÑ ÑÐ»ÐµÐ¼ÐµÐ½Ñ - Ð¾Ð´Ð¸Ð½ ÐºÐ¾Ð½ÐºÑÐµÑÐ½ÑÐ¹ Ð¿ÐµÑÐµÐ²Ð¾Ð´

    void delete_tr(cNode* t, string eng_inp, int index); ///ÑÐµÐºÑÑÑÐ¸Ð²Ð½Ð¾ ÑÐ´Ð°Ð»ÑÐµÑ Ð¾Ð´Ð¸Ð½ Ð¸Ð· Ð¿ÐµÑÐµÐ²Ð¾Ð´Ð¾Ð²

    cNode* delete_node(cNode* node, string eng_inp); ///ÑÐµÐºÑÑÑÐ¸Ð²Ð½Ð¾ ÑÐ´Ð°Ð»ÑÐµÑ ÑÐ°Ð¼ ÑÐ»ÐµÐ¼ÐµÐ½Ñ (Ð°Ð½Ð³Ð»Ð¸Ð¹ÑÐºÐ¾Ðµ ÑÐ»Ð¾Ð²Ð¾ Ð¸ Ð²ÑÐµ ÐµÐ³Ð¾ Ð¿ÐµÑÐµÐ²Ð¾Ð´Ñ)

    int count_nodes(cNode* node); ///ÑÑÐ¸ÑÐ°ÐµÑ ÐºÐ¾Ð»Ð¸ÑÐµÑÑÐ²Ð¾ Ð°Ð½Ð³Ð»Ð¸Ð¹ÑÐºÐ¸Ñ ÑÐ»Ð¾Ð² Ð² ÑÐ»Ð¾Ð²Ð°ÑÐµ

public:
    void set_translation(string eng_inp, string rus_inp); ///Ð´Ð¾Ð±Ð°Ð²Ð»ÑÐµÑ Ð½Ð¾Ð²Ð¾Ðµ Ð°Ð½Ð³Ð»Ð¸Ð¹ÑÐºÐ¾Ðµ ÑÐ»Ð¾Ð²Ð¾ Ð¸ ÐµÐ³Ð¾ Ð¿ÐµÑÐµÐ²Ð¾Ð´Ñ

    void remove_translation(string eng_inp); ///ÑÐ´Ð°Ð»ÑÐµÑ ÑÐ»ÐµÐ¼ÐµÐ½Ñ Ð´ÐµÑÐµÐ²Ð°

    int length(); ///Ð²Ð¾Ð·Ð²ÑÐ°ÑÐ°ÐµÑ ÐºÐ¾Ð»Ð¸ÑÐµÑÑÐ²Ð¾ ÑÐ»Ð¾Ð²

    int tr_count(string eng_inp); ///Ð²Ð¾Ð·Ð²ÑÐ°ÑÐ°ÐµÑ ÐºÐ¾Ð»Ð¸ÑÐµÑÑÐ²Ð¾ ÑÑÑÑÐºÐ¸Ñ Ð¿ÐµÑÐµÐ²Ð¾Ð´Ð¾Ð² ÐºÐ¾Ð½ÐºÑÐµÑÐ½Ð¾Ð³Ð¾ Ð°Ð½Ð³Ð»Ð¸Ð¹ÑÐºÐ¾Ð³Ð¾ ÑÐ»Ð¾Ð²Ð°

    void delete_one_translation(string eng_inp, int index); ///ÑÐ´Ð°Ð»ÑÐµÑ Ð¾Ð´Ð¸Ð½ Ð¸Ð· Ð¿ÐµÑÐµÐ²Ð¾Ð´Ð¾Ð²

    // ÐÐµÑÐµÐ³ÑÑÐ·ÐºÐ° Ð¾Ð¿ÐµÑÐ°ÑÐ¾ÑÐ¾Ð²
    string operator[] (string eng_inp); ///Ð¿ÐµÑÐµÐ³ÑÑÐ¶ÐµÐ½Ð½ÑÐ¹ Ð¾Ð¿ÐµÑÐ°ÑÐ¾Ñ Ð´Ð»Ñ Ð¿Ð¾Ð»ÑÑÐµÐ½Ð¸Ñ Ð¿ÐµÑÐµÐ²Ð¾Ð´Ð°
    string& operator[] (pair<string, int> transl); ///Ð¿ÐµÑÐµÐ³ÑÑÐ¶ÐµÐ½Ð½ÑÐ¹ Ð¾Ð¿ÐµÑÐ°ÑÐ¾Ñ Ð´Ð»Ñ ÐÐÐÐÐÐÐÐÐ¯ Ð¿ÐµÑÐµÐ²Ð¾Ð´Ð° (Ð² Ð¿Ð°ÑÐµ Ð°Ð½Ð³Ð»Ð¸Ð¹ÑÐºÐ¾Ðµ ÑÐ»Ð¾Ð²Ð¾ Ð¸ Ð½Ð¾Ð¼ÐµÑ Ð¿ÐµÑÐµÐ²Ð¾Ð´Ð°, ÐºÐ¾ÑÐ¾ÑÑÐ¹ Ð½ÑÐ¶Ð½Ð¾ Ð¸Ð·Ð¼ÐµÐ½Ð¸ÑÑ)
    void operator-= (string eng_inp); ///Ð¿ÐµÑÐµÐ³ÑÑÐ¶ÐµÐ½Ð½ÑÐ¹ Ð¾Ð¿ÐµÑÐ°ÑÐ¾Ñ Ð´Ð»Ñ ÑÐ´Ð°Ð»ÐµÐ½Ð¸Ñ ÑÐ»Ð¾Ð²Ð°
    void operator+= (pair<string, string> eng_inp); ///Ð¿ÐµÑÐµÐ³ÑÑÐ¶ÐµÐ½Ð½ÑÐ¹ Ð¾Ð¿ÐµÑÐ°ÑÐ¾Ñ Ð´Ð»Ñ Ð´Ð¾Ð±Ð°Ð²Ð»ÐµÐ½Ð¸Ñ ÑÐ»Ð¾Ð²Ð° Ð¸ Ð¾Ð´Ð½Ð¾Ð³Ð¾ ÐµÐ³Ð¾ Ð¿ÐµÑÐµÐ²Ð¾Ð´Ð°
};
