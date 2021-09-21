#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
#include "Header1.h"

using namespace std;

class cNode     // класс узла
{
    cNode* left, * right;       // указатели на потомков
    string eng, nullpoint = "Элемент не найден";
    vector<string> rus_multiple;

public:
    cNode(string eng_inp, string rus_inp) {       // конструктор
        eng = eng_inp;
        rus_multiple.push_back(rus_inp);
        left = right = nullptr;
    }

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
    }       // вспомогательный элемент, именно его адрес мы возвращаем в функции find_node()

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
} *root;



class dict      // класс бинарного дерева
{
private:
    void add_node(cNode* node, string eng_inp, string rus_inp) {
        if (!root) {
            cNode* t = new cNode(eng_inp, rus_inp);
            root = t;       // если корневой элемент не создан, то мы выделяем под него
        }               // память и привязываем к нему указатель корня root
        else {
            cNode* prev, * t;
            bool find = true;       // find - это проверка на то, что в дереве ещё нет такого элемента
            t = node; prev = t;

            while (t && find) {      // ищем место под узел: пока рабочий указатель не нулевой (то есть не на последнем уровне),
                prev = t;           // спускаемся на уровень ниже
                if (eng_inp == t->get_eng())
                {
                    for (int i = 0; i < t->get_rus_multiple().size(); i++) 
                    {
                        if (rus_inp == t->get_rus_multiple()[i])
                        {
                            find = false;
                        }
                    }
                    if (find)
                    {
                        t->add_to_rus_multiple(rus_inp);
                    }
                }
                if (eng_inp < t->get_eng()) {
                    t = t->get_left();
                    continue;
                }
                if (eng_inp > t->get_eng())
                    t = t->get_right();
            }
            if (find) {       //если нет дубликата
                cNode* new_node = new cNode(eng_inp, rus_inp);
                t = new_node;
                if (eng_inp < prev->get_eng())
                    prev->set_left(t);
                else
                    prev->set_right(t);
            }
        }
    }

    string& find_node(cNode* t, string eng_inp, int index)
    {
        if (!t)
            return root->nullpointer(); //если элемента не существует, возвращаем nullpointer
        if (eng_inp == t->get_eng())
        {
            if (t->get_rus_multiple().size() <= index) return root->nullpointer(); //если мы выходим за пределы вектора, тоже возвращаем nullpointer
            return t->get_rus_m_element()[index];
        }
            
        if (eng_inp < t->get_eng())
            return find_node(t->get_left(), eng_inp, index);
        if (eng_inp > t->get_eng())
            return find_node(t->get_right(), eng_inp, index);
    }

    void delete_tr(cNode* t, string eng_inp, int index)
    {
        if (!t)
            return;
        if (eng_inp == t->get_eng())
        {
            if (t->get_rus_multiple().size() < index) return;
            t->delete_from_rus_multiple(index - 1);
        }

        if (eng_inp < t->get_eng())
            delete_tr(t->get_left(), eng_inp, index);
        if (eng_inp > t->get_eng())
            delete_tr(t->get_right(), eng_inp, index);
    }

    cNode* delete_node(cNode* node, string eng_inp)     // * - ?
    {
        bool trying_to_delete_root = false;
        if (!node)
            return node;
        if (node == root)
            trying_to_delete_root = true;
        if (eng_inp == node->get_eng()) {
            cNode* tmp;
            if (!node->get_right())
                tmp = node->get_left();
            else {
                cNode* p = node->get_right();
                if (!p->get_left()) {
                    p->set_left(node->get_left());
                    tmp = p;
                }
                else {
                    cNode* pmin = p->get_left();
                    while (pmin->get_left()) {
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
            if (trying_to_delete_root)
                root = tmp;
            return tmp;
        }
        else if (eng_inp < node->get_eng())
            node->set_left(delete_node(node->get_left(), eng_inp));
        else
            node->set_right(delete_node(node->get_right(), eng_inp));
        return node;
    }

    int count_nodes(cNode* node) {
        int count = 0;
        if (node) {
            count++;
            if (node->get_left())
                count += count_nodes(node->get_left());
            if (node->get_right())
                count += count_nodes(node->get_right());
        }
        return count;
    }

public:
    void set_translation(string eng_inp, string rus_inp) {
        add_node(root, eng_inp, rus_inp);
    }

    void get_translation(string eng_inp) {
        if (find_node(root, eng_inp, 0) == "0")
            cout << "Элемент не найден.";
        else {
            string rus_inp = find_node(root, eng_inp, 0);
            cout << eng_inp << ":" << rus_inp << endl;
        }
    }

    void remove_translation(string eng_inp) {
        delete_node(root, eng_inp);
    } //удаляет сам узел слова со всеми элементами

    int length() {
        return count_nodes(root);
    }

    int tr_count(string eng_inp) {
        int i = 0;
        while (true)
        {
            if (find_node(root, eng_inp, i) == "Элемент не найден") {
                break;
            }
            i++;
        }
        return i;
    }

    void delete_one_translation(string eng_inp, int index) {
        delete_tr(root, eng_inp, index);
    } //удаляет ОДИН перевод

    //    void get_words(cNode *node, string words, int len){
    //        int point = 0;
    //        if(node) {
    //            words[point] = node.get_eng();
    //            if(node->get_left())
    //                int a;
    //            if(node->get_right())
    //                int b;
    //        }
    //    }

        // Перегрузка операторов
    string operator[] (string eng_inp) {
        string output = "";
        for (int i = 0; i < tr_count(eng_inp); i++)
        {
            output += find_node(root, eng_inp, i) + " ";
        }
        return output;
    }
    string& operator[] (pair<string, int> transl) {
        return find_node(root, transl.first, transl.second);
    }
    void operator-= (string eng_inp) {
        this->remove_translation(eng_inp);
    }
    void operator+= (pair<string, string> eng_inp) {
        this->set_translation(eng_inp.first, eng_inp.second);
    }
};


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    dict* slov = new dict();
    int choice = 1;
    while (choice) {
        system("cls");
        cout << "Выберите действие:\n"; 
        cout << "1. Добавить слово (или перевод к существующему слову)\n"; 
        cout << "2. Удалить слово\n";
        cout << "3. Удалить перевод из слова\n";
        cout << "4. Поиск перевода английского слова\n";            
        cout << "5. Замена перевода английского слова\n"; 
        cout << "6. Количество слов в словаре\n";
        cout << "7. Загрузить словарь из файла\n";
//        cout << "8. Загрузить словарь в файл (В разработке)\n";
        cout << "0. Выход.\n";
        cout << "Введите действие: ";
        cin >> choice;
        if (!choice) {
            system("cls");
            break;
        }
        int choice_case = 1;
        switch (choice) {
        case 1:
            while (choice_case) {
                system("cls");
                string eng_word, rus_word;
                cout << "Введите английское слово: ";
                cin >> eng_word;

                int translation_count = 1;
                cout << "Сколько переводов для этого слова вы хотите: ";
                cin >> translation_count;
                for (int i = 0; i < translation_count; i++)
                {
                    cout << "Введите " << i+1 << "-й перевод на русском: ";
                    cin >> rus_word;
                    *slov += make_pair(eng_word, rus_word);
                }
                cout << "Желаете ли вы добавить еще? (1 - да, 0 - нет) ";
                cin >> choice_case;
            }
            break;

        case 2:
            while (choice_case) {
                system("cls");
                string del_word;
                cout << "Введите слово, которое вы желаете удалить: ";
                cin >> del_word;
                *slov -= del_word;
                cout << "Желаете ли вы удалить еще? (1 - да, 0 - нет) ";
                cin >> choice_case;
            }
            break;

        case 3:
            while (choice_case) {
                system("cls");
                string del_tr;
                cout << "Введите слово, перевод которого вы желаете удалить: ";
                cin >> del_tr;
                cout << "Переводы: \n";
                for (int i = 0; i < slov->tr_count(del_tr); i++)
                {
                    cout << i + 1 << ". " << (*slov)[make_pair(del_tr, i)] << endl;
                }
                cout << "Перевод под каким номером вы хотите удалить: ";
                int tr_numb;
                cin >> tr_numb;

                slov->delete_one_translation(del_tr, tr_numb);

                cout << "Желаете ли вы удалить перевод еще? (1 - да, 0 - нет) ";
                cin >> choice_case;
            }
            break;

        case 4:
            while (choice_case) {
                system("cls");
                string tr_word;
                cout << "Введите слово, которое вы хотите перевести: ";
                cin >> tr_word;
                cout << "Перевод: " << (*slov)[tr_word] << endl;
                cout << "Желаете ли вы перевести еще? (1 - да, 0 - нет) ";
                cin >> choice_case;
            }
            break;

        case 5:
            while (choice_case) {
                system("cls");
                string change_word, new_word;
                cout << "Введите слово, перевод которого нужно изменить: ";
                cin >> change_word;

                if (slov->tr_count(change_word) == 1)
                {
                    cout << "Текущий перевод: " << (*slov)[change_word] << "\nВведите новый перевод: ";
                    cin >> new_word;
                    (*slov)[make_pair(change_word, 0)] = new_word;
                }
                else {
                    cout << "Переводы: \n";
                    for (int i = 0; i < slov->tr_count(change_word); i++)
                    {
                        cout << i + 1 << ". " << (*slov)[make_pair(change_word, i)] << endl;
                    }
                    cout << "Перевод под каким номером вы хотите изменить: ";
                    int tr_numb;
                    cin >> tr_numb;
                    cout << "Введите новый перевод: ";
                    cin >> new_word;
                    (*slov)[make_pair(change_word, tr_numb - 1)] = new_word;

                }
                cout << "Желаете ли вы изменить еще? (1 - да, 0 - нет) ";
                cin >> choice_case;
            }
            break;

        case 6:
            while (choice_case) {
                system("cls");
                string del_word;
                cout << "В словаре: " << (*slov).length() << " слова." << endl;
                cout << "Введите \"0\" для продолжения: ";
                cin >> choice_case;
            }
            break;

        case 7:
            while (choice_case) {
                system("cls");
                string file_name = "dictionary.txt";
                //cout << "Введите имя файла: ";
                //cin >> file_name;
                ifstream inp_file;
                inp_file.open(file_name);
                if (inp_file.is_open()) {
                    string inp_line;
                    while (!inp_file.eof()) {
                        getline(inp_file, inp_line);
                        string inp_eng = inp_line.substr(0, inp_line.find('\t'));
                        string inp_rus = inp_line.substr(inp_line.find('\t') + 1);
                        int space_index = 0;
                        string rus_tr;
                        for (int i = 0; i < inp_rus.length(); i++) //разбиваем вторую часть строки на разные переводы
                        {
                            if (inp_rus[i] == ' ')
                            {
                                rus_tr = inp_rus.substr(space_index, i - space_index);
                                *slov += make_pair(inp_eng, rus_tr);
                                space_index = i+1;
                            }
                        }
                        rus_tr = inp_rus.substr(space_index, inp_rus.length());
                        *slov += make_pair(inp_eng, rus_tr);
                    }
                    inp_file.close();
                    cout << "Словарь из файла успешно загружен!" << endl;
                }
                else
                    cout << "Файл не открыт!" << endl;
                cout << "Введите \"0\" для продолжения: ";
                cin >> choice_case;
            }
            break;

            //            case 8:
            //                while(choice_case) {
            //                    system("cls");
            //                    string file_name;
            //                    cout << "Введите имя файла: ";
            //                    cin >> file_name;
            //                    ofstream otp_file;
            //                    otp_file.open(file_name);
            //                    if (otp_file.is_open()) {
            //                        string otp_line;
            //
            //
            //                        otp_file.close();
            //                        cout << "Словарь успешно загружен в файл!" << endl;
            //                    }
            //                    else
            //                        cout << "Файл не открыт!" << endl;
            //                    cout << "Введите \"0\" для продолжения: ";
            //                    cin >> choice_case;
            //                }
            //                break;
        }
    }

}