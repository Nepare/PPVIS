#include <iostream>
#include <string>
#include "Header1.h"

using namespace std;

class cNode //класс узла
{
    cNode* left, * right; //указатели на потомков
    string eng, rus; 

public:
    cNode(string eng1, string rus1) //конструктор
    {
        eng = eng1;
        rus = rus1;
        left = right = nullptr;
    }

    string get_eng()
    {
        return eng;
    }
    string get_rus()
    {
        return rus;
    }
    cNode* get_left()
    {
        return left;
    }
    cNode* get_right()
    {
        return right;
    }

    void set_eng(string eng1)
    {
        this->eng = eng1;
    }
    void set_rus(string rus1)
    {
        rus = rus1;
    }
    void set_left(cNode* left1)
    {
        left = left1;
    }
    void set_right(cNode* right1)
    {
        right = right1;
    }
} *root;

class dict //класс самого бинарного дерева
{
private:
    void add_node(cNode *node, string eng1, string rus1)
    {
        if (root == NULL)
        {
            cNode* t = new cNode(eng1, rus1);
            root = t; 
        } //если корневой элемент не создан, то мы выделяем под него память и привязываем к нему указатель корня root
        else 
        {
            cNode* prev, * t;
            bool find = true; //find - это проверка на то, что в дереве ещё нету такого элемента
            t = node; prev = t;

            while (t != nullptr && find) //ищем место под узел: пока рабочий указатель не нулевой (то есть не на последнем уровне), спускаемся на уровень ниже
            {
                prev = t;
                if (eng1 == t->get_eng())
                {
                    find = false;
                }
                if (eng1 < t->get_eng()) { t = t->get_left(); continue; }
                if (eng1 > t->get_eng()) { t = t->get_right(); }
            }
            if (find) //если нет дубликата
            {
                cNode* new_node = new cNode(eng1, rus1);
                t = new_node;
                if (eng1 < prev->get_eng()) prev->set_left(t);
                else prev->set_right(t);
            }
        }
    }
    void find_node(cNode* t, string eng1)
    {
        if (t == nullptr) { cout << endl << "Элемент не найден!" << endl; return; }
        if (eng1 == t->get_eng()) cout << endl << t->get_eng() << ": " << t->get_rus();
        if (eng1 < t->get_eng()) find_node(t->get_left(), eng1);
        if (eng1 > t->get_eng()) find_node(t->get_right(), eng1);
    }
    cNode* delete_node(cNode* node, string eng1)
    {
        bool trying_to_delete_root = false;
        if (node == NULL) return node;
        if (node == root) trying_to_delete_root = true;

        if (eng1 == node->get_eng())
        {
            cNode* tmp;
            if (node->get_right() == NULL)
                tmp = node->get_left();
            else
            {
                cNode* p = node->get_right();
                if (p->get_left() == NULL)
                {
                    p->set_left(node->get_left());
                    tmp = p;
                }
                else
                {
                    cNode* pmin = p->get_left();
                    while (pmin->get_left() != NULL)
                    {
                        p = pmin;
                        pmin = p->get_left();
                    }
                    p->set_left(pmin->get_right());
                    pmin->set_left(node->get_left()); 
                    pmin->set_right(node->get_right());
                    tmp = pmin;
                }
            }
            delete node;
            if (trying_to_delete_root) root = tmp;
            return tmp;
        }
        else if (eng1 < node->get_eng())
            node->set_left(delete_node(node->get_left(), eng1));
        else
            node->set_right(delete_node(node->get_right(), eng1));
        return node;
    }

public:
    void set_translation(string e1, string r1)
    {
        add_node(root, e1, r1);
    }
    void get_translation(string e1)
    {
        find_node(root, e1);
    }
    void remove_translation(string e1)
    {
        delete_node(root, e1);
    }
    void test_root()
    {
        cout << root->get_eng() << " " << root->get_rus();
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    dict *slov = new dict();

    slov->set_translation("hello","привет");
    slov->set_translation("hi", "дарова");
    slov->set_translation("pain", "боль");

    slov->get_translation("hello");
    slov->get_translation("hi");
    slov->remove_translation("hi");
    slov->get_translation("hi");
    //slov->test();

}