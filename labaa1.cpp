#include <iostream>
#include <string>
#include "Header1.h"

using namespace std;

class cNode //класс узла
{
    cNode* left, * right; //указатели на потомков
    string eng, rus, nullpoint = "Элемент не найден"; 

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
    string& get_rus_element()
    {
        return rus;
    }
    string& nullpointer()
    {
        return nullpoint;
    } //вспомогательный элемент, именно его адрес мы возвращаем в функции find_node()
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
    string& find_node(cNode* t, string eng1)
    {
        if (t == nullptr) { return root->nullpointer(); }
        if (eng1 == t->get_eng()) return t->get_rus_element();
        if (eng1 < t->get_eng()) return find_node(t->get_left(), eng1);
        if (eng1 > t->get_eng()) return find_node(t->get_right(), eng1);
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
        if (find_node(root, e1) == "0") cout << "Элемент не найден";
        else 
        {
            string r1 = find_node(root, e1);
            cout << e1 << ":" << r1 << endl;
        }
    }
    void remove_translation(string e1)
    {
        delete_node(root, e1);
    }
    void test_root()
    {
        cout << root->get_eng() << " " << root->get_rus();
    }

    string& operator[] (string e1)  { return find_node(root, e1); }
    void operator-= (string e1) { this->remove_translation(e1); }
    void operator+= (pair<string,string> e1) { this->set_translation(e1.first,e1.second); }
};


int main()
{
    setlocale(LC_ALL, "ru");
    dict *slov = new dict();

    (*slov) += make_pair("hello","привет");
    (*slov) += make_pair("hi", "добро пожаловать");
    (*slov) += make_pair("bread", "хлеб");

    cout << (*slov)["hello"] << endl;
    cout << (*slov)["hi"] << endl;
    (*slov)["hi"] = "шарнир";
    cout << (*slov)["hi"] << endl;
    (*slov) -= "hi";
    cout << (*slov)["hi"] << endl;
    //slov->test();

}