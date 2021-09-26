#pragma once
#include <iostream>
#include <vector>

using namespace std;


class cNode     // ����� ����
{
    cNode* left, * right;       // ��������� �� ��������
    string eng, nullpoint = "������� �� ������";
    vector<string> rus_multiple; //������ ��������� ��������� ����������� �����

public:
    cNode(string eng_inp, string rus_inp) {       
        eng = eng_inp;
        rus_multiple.push_back(rus_inp);
        left = right = nullptr;
    } /// �����������

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
    }       /// ��������������� �������, ������ ��� ����� �� ���������� � ������� find_node()

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
}; ///����� ���� ��������� ������ � ��������� � ���������



class dict      /// ����� ��������� ������
{
private:
    cNode* root;
    void add_node(cNode* node, string eng_inp, string rus_inp); ///���������� ���������� ����� ���������� ����� � ��� �������� � ������

    string& find_node(cNode* t, string eng_inp, int index); ///���� � ���������� ������� - ���� ���������� �������

    void delete_tr(cNode* t, string eng_inp, int index); ///���������� ������� ���� �� ���������

    cNode* delete_node(cNode* node, string eng_inp); ///���������� ������� ��� ������� (���������� ����� � ��� ��� ��������)

    int count_nodes(cNode* node); ///������� ���������� ���������� ���� � �������

public:
    void set_translation(string eng_inp, string rus_inp); ///��������� ����� ���������� ����� � ��� ��������

    void remove_translation(string eng_inp); ///������� ������� ������

    int length(); ///���������� ���������� ����

    int tr_count(string eng_inp); ///���������� ���������� ������� ��������� ����������� ����������� �����

    void delete_one_translation(string eng_inp, int index); ///������� ���� �� ���������

    // ���������� ����������
    string operator[] (string eng_inp); ///������������� �������� ��� ��������� ��������
    string& operator[] (pair<string, int> transl); ///������������� �������� ��� ��������� �������� (� ���� ���������� ����� � ����� ��������, ������� ����� ��������)
    void operator-= (string eng_inp); ///������������� �������� ��� �������� �����
    void operator+= (pair<string, string> eng_inp); ///������������� �������� ��� ���������� ����� � ������ ��� ��������
};