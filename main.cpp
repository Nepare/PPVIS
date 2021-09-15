#include <iostream>
#include <string>
#include <fstream>
// #include "Header1.h"

using namespace std;


class cNode     // класс узла
{
    cNode *left, *right;       // указатели на потомков
    string eng, rus, nullpoint = "Элемент не найден";

public:
    cNode(string eng_inp, string rus_inp){       // конструктор
        eng = eng_inp;
        rus = rus_inp;
        left = right = nullptr;
    }

    string get_eng(){
        return eng;
    }

    string get_rus(){
        return rus;
    }

    string &get_rus_element(){
        return rus;
    }

    string &nullpointer(){
        return nullpoint;
    }       // вспомогательный элемент, именно его адрес мы возвращаем в функции find_node()

    cNode *get_left(){
        return left;
    }

    cNode *get_right(){
        return right;
    }

    void set_eng(string eng_inp){
        this->eng = eng_inp;
    }

    void set_rus(string rus_inp){
        rus = rus_inp;
    }

    void set_left(cNode *left1){
        left = left1;
    }

    void set_right(cNode *right1){
        right = right1;
    }
} *root;


class dict      // класс бинарного дерева
{
private:
    void add_node(cNode *node, string eng_inp, string rus_inp){
        if (!root){
            cNode *t = new cNode(eng_inp, rus_inp);
            root = t;       // если корневой элемент не создан, то мы выделяем под него
            }               // память и привязываем к нему указатель корня root
        else{
            cNode *prev, *t;
            bool find = true;       // find - это проверка на то, что в дереве ещё нет такого элемента
            t = node; prev = t;

            while (t && find){      // ищем место под узел: пока рабочий указатель не нулевой (то есть не на последнем уровне),
                prev = t;           // спускаемся на уровень ниже
                if (eng_inp == t->get_eng())
                    find = false;
                if (eng_inp < t->get_eng()){
                    t = t->get_left();
                    continue;
                }
                if (eng_inp > t->get_eng())
                    t = t->get_right();
            }
            if (find){       //если нет дубликата
                cNode* new_node = new cNode(eng_inp, rus_inp);
                t = new_node;
                if (eng_inp < prev->get_eng())
                    prev->set_left(t);
                else
                    prev->set_right(t);
            }
        }
    }

    string &find_node(cNode* t, string eng_inp)
    {
        if (!t)
            return root->nullpointer();
        if (eng_inp == t->get_eng())
            return t->get_rus_element();
        if (eng_inp < t->get_eng())
            return find_node(t->get_left(), eng_inp);
        if (eng_inp > t->get_eng())
            return find_node(t->get_right(), eng_inp);
    }

    cNode *delete_node(cNode* node, string eng_inp)     // * - ?
    {
        bool trying_to_delete_root = false;
        if (!node)
            return node;
        if (node == root)
            trying_to_delete_root = true;
        if (eng_inp == node->get_eng()){
            cNode* tmp;
            if (!node->get_right())
                tmp = node->get_left();
            else{
                cNode* p = node->get_right();
                if (!p->get_left()){
                    p->set_left(node->get_left());
                    tmp = p;
                }
                else{
                    cNode* pmin = p->get_left();
                    while (pmin->get_left()){
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

    int count_nodes(cNode *node){
        int count = 0;
        if(node){
            count++;
            if(node->get_left())
                count += count_nodes(node->get_left());
            if(node->get_right())
                count += count_nodes(node->get_right());
        }
        return count;
    }

public:
    void set_translation(string eng_inp, string rus_inp){
        add_node(root, eng_inp, rus_inp);
    }

    void get_translation(string eng_inp){
        if (find_node(root, eng_inp) == "0")
            cout << "Элемент не найден.";
        else {
            string rus_inp = find_node(root, eng_inp);
            cout << eng_inp << ":" << rus_inp << endl;
        }
    }

    void remove_translation(string eng_inp){
        delete_node(root, eng_inp);
    }

    int length(){
        return count_nodes(root);
    }

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

//    void test_root() {
//        cout << root->get_eng() << " " << root->get_rus();
//    }

    // Перегрузка операторов
    string& operator[] (string eng_inp){
        return find_node(root, eng_inp);
    }
    void operator-= (string eng_inp){
        this->remove_translation(eng_inp);
    }
    void operator+= (pair<string,string> eng_inp){
        this->set_translation(eng_inp.first, eng_inp.second);
    }
};


int main(){
    setlocale(LC_ALL, "ru");
    dict *slov = new dict();
    int choice = 1;
    while (choice){
        system("clear");
        cout << "Выберите действие:\n";
        cout << "1.Добавить слово\n";
        cout << "2.Удалить слово\n";
        cout << "3.Поиск перевода английского слова\n";              // ?
        cout << "4.Замена перевода английского слова\n";
        cout << "5.Количество слов в словаре\n";
        cout << "6.Загрузить словарь из файла\n";
        cout << "7.Загрузить словарь в файл (В разработке)\n";
        cout << "0.Выход.\n";
        cout << "Введите действие: ";
        cin >> choice;
        if (!choice) {
            system("clear");
            break;
        }
        int choice_case = 1;
        switch(choice){
            case 1:
                while(choice_case) {
                    system("clear");
                    string eng_word, rus_word;
                    cout << "Введите английское слово: ";
                    cin >> eng_word;
                    cout << "Введите перевод на русском: ";
                    cin >> rus_word;
                    *slov += make_pair(eng_word, rus_word);
                    cout << "Желаете ли вы добавить еще? (1 - да, 0 - нет)";
                    cin >> choice_case;
                }
                break;

            case 2:
                while(choice_case) {
                    system("clear");
                    string del_word;
                    cout << "Введите слово, которое вы желаете удалить: ";
                    cin >> del_word;
                    *slov -= del_word;
                    cout << "Желаете ли вы удалить еще? (1 - да, 0 - нет)";
                    cin >> choice_case;
                }
                break;

            case 3:
                while(choice_case) {
                    system("clear");
                    string tr_word;
                    cout << "Введите слово, которое вы хотите перевести: ";
                    cin >> tr_word;
                    cout << "Перевод: " << (*slov)[tr_word] << endl;
                    cout << "Желаете ли вы перевести еще? (1 - да, 0 - нет)";
                    cin >> choice_case;
                }
                break;

            case 4:
                while(choice_case) {
                    system("clear");
                    string change_word, new_word;
                    cout << "Введите слово, перевод которого нужно изменить: ";
                    cin >> change_word;
                    cout << "Введите перевод: ";
                    cin >> new_word;
                    (*slov)[change_word] = new_word;
                    cout << "Желаете ли вы изменить еще? (1 - да, 0 - нет)";
                    cin >> choice_case;
                }
                break;

            case 5:
                while(choice_case) {
                    system("clear");
                    string del_word;
                    cout << "В словаре: " << (*slov).length() << " слова." << endl;
                    cout << "Введите \"0\" для продолжения: ";
                    cin >> choice_case;
                }
                break;

            case 6:
                while(choice_case) {
                    system("clear");
                    string file_name;
                    cout << "Введите имя файла: ";
                    cin >> file_name;
                    ifstream inp_file;
                    inp_file.open(file_name);
                    if (inp_file.is_open()){
                        string inp_line;
                        while(!inp_file.eof()){
                            getline(inp_file, inp_line);
                            string inp_eng = inp_line.substr(0, inp_line.find('\t'));
                            string inp_rus = inp_line.substr(inp_line.find('\t'), inp_line.length());
                            *slov += make_pair(inp_eng, inp_rus);
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

//            case 7:
//                while(choice_case) {
//                    system("clear");
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


//    (*slov) += make_pair("hello","привет");
//    (*slov) += make_pair("hi", "добро пожаловать");
//    (*slov) += make_pair("bread", "хлеб");

//    cout << (*slov)["hello"] << endl;
//    cout << (*slov)["hi"] << endl;
//    (*slov)["hi"] = "шарнир";
//    cout << (*slov)["hi"] << endl;
//    (*slov) -= "hi";
//    cout << (*slov)["hi"] << endl;
    //slov->test();
    cout << (*slov).length();
}