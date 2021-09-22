#include <fstream>
#include <Windows.h>
#include <string>
#include "dict_class.h"


using namespace std;


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
                /*cout << "Введите имя файла: ";
                cin >> file_name;*/
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
        }
    }

}