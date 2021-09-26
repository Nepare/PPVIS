#pragma once
#include <iostream>
#include <vector>

using namespace std;


class cNode 
{
    cNode* left, * right;       /// pointers to the children
    string eng, nullpoint = "Element not found";
    vector<string> rus_multiple; ///vector of possible russian translations

public:
    cNode(string eng_inp, string rus_inp) {       
        eng = eng_inp;
        rus_multiple.push_back(rus_inp);
        left = right = nullptr;
    } /// constructor

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
    }       /// utility element, we return its address to the find_node() function

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
}; ///just a binary tree node class with getters and setters



class dict      /// binary tree class
{
private:
    cNode* root;
    void add_node(cNode* node, string eng_inp, string rus_inp); ///recursively inserts a new english word with the translations into the tree

    string& find_node(cNode* t, string eng_inp, int index); /// finds and returns one particular translation of an element

    void delete_tr(cNode* t, string eng_inp, int index); ///recursively deletes one of the translations

    cNode* delete_node(cNode* node, string eng_inp); ///recursively deletes one elements and all it contains

    int count_nodes(cNode* node); /// counts the amount of english words in the dictionary

public:
    void set_translation(string eng_inp, string rus_inp); ///adds a new english word and its translations

    void remove_translation(string eng_inp); ///удаляет элемент дерева deletes an element (word) of a dictionary

    int length(); ///returns the amount of words

    int tr_count(string eng_inp); ///return the amount of russian translations of a particular english word 

    void delete_one_translation(string eng_inp, int index); ///deletes one of the translations

    // overloading operators 
    string operator[] (string eng_inp); ///overloaded operator to get translations
    string& operator[] (pair<string, int> transl); ///overloaded operator to CHANGE the translation (there is an english word and the number of the translation that needs to be changed) 
    void operator-= (string eng_inp); ///overloaded operator of deleting the word
    void operator+= (pair<string, string> eng_inp); ///overloaded operator of adding a word and one translation to this word
};
