#include "dict_class.h"

using namespace std;

    bool cNode::operator==(cNode comp) {
        if (this->eng == comp.eng) {
            int amount = this->rus_multiple.size();
            if (amount == comp.rus_multiple.size()) {
                for (int i = 0; i < amount; i++) {
                    if (this->rus_multiple[i] != comp.rus_multiple[i]) return false;
                }
            }
            else return false;
        }
        else return false;
        return true;
    } ///Ð¾Ð¿ÐµÑÐ°ÑÐ¾Ñ ÑÑÐ°Ð²Ð½ÐµÐ½Ð¸Ñ

    void dict::add_node(cNode* node, string eng_inp, string rus_inp) {
        if (!root) {
            cNode* t = new cNode(eng_inp, rus_inp);
            root = t;       /// ÐµÑÐ»Ð¸ ÐºÐ¾ÑÐ½ÐµÐ²Ð¾Ð¹ ÑÐ»ÐµÐ¼ÐµÐ½Ñ Ð½Ðµ ÑÐ¾Ð·Ð´Ð°Ð½, ÑÐ¾ Ð¼Ñ Ð²ÑÐ´ÐµÐ»ÑÐµÐ¼ Ð¿Ð¾Ð´ Ð½ÐµÐ³Ð¾ Ð¿Ð°Ð¼ÑÑÑ Ð¸ Ð¿ÑÐ¸Ð²ÑÐ·ÑÐ²Ð°ÐµÐ¼ Ðº Ð½ÐµÐ¼Ñ ÑÐºÐ°Ð·Ð°ÑÐµÐ»Ñ ÐºÐ¾ÑÐ½Ñ root
        }               
        else {
            cNode* prev, * t;
            bool find = true;       /// find - ÑÑÐ¾ Ð¿ÑÐ¾Ð²ÐµÑÐºÐ° Ð½Ð° ÑÐ¾, ÑÑÐ¾ Ð² Ð´ÐµÑÐµÐ²Ðµ ÐµÑÑ Ð½ÐµÑ ÑÐ°ÐºÐ¾Ð³Ð¾ ÑÐ»ÐµÐ¼ÐµÐ½ÑÐ°
            t = node; prev = t;

            while (t && find) {      /// Ð¸ÑÐµÐ¼ Ð¼ÐµÑÑÐ¾ Ð¿Ð¾Ð´ ÑÐ·ÐµÐ»: Ð¿Ð¾ÐºÐ° ÑÐ°Ð±Ð¾ÑÐ¸Ð¹ ÑÐºÐ°Ð·Ð°ÑÐµÐ»Ñ Ð½Ðµ Ð½ÑÐ»ÐµÐ²Ð¾Ð¹ (ÑÐ¾ ÐµÑÑÑ Ð½Ðµ Ð½Ð° Ð¿Ð¾ÑÐ»ÐµÐ´Ð½ÐµÐ¼ ÑÑÐ¾Ð²Ð½Ðµ), ÑÐ¿ÑÑÐºÐ°ÐµÐ¼ÑÑ Ð½Ð° ÑÑÐ¾Ð²ÐµÐ½Ñ Ð½Ð¸Ð¶Ðµ
                prev = t;           
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
            if (find) {       ///ÐµÑÐ»Ð¸ Ð½ÐµÑ Ð´ÑÐ±Ð»Ð¸ÐºÐ°ÑÐ°
                cNode* new_node = new cNode(eng_inp, rus_inp);
                t = new_node;
                if (eng_inp < prev->get_eng())
                    prev->set_left(t);
                else
                    prev->set_right(t);
            }
        }
    }

    string& dict::find_node(cNode* t, string eng_inp, int index)
    {
        if (!t)
            return root->nullpointer(); ///ÐµÑÐ»Ð¸ ÑÐ»ÐµÐ¼ÐµÐ½ÑÐ° Ð½Ðµ ÑÑÑÐµÑÑÐ²ÑÐµÑ, Ð²Ð¾Ð·Ð²ÑÐ°ÑÐ°ÐµÐ¼ nullpointer
        if (eng_inp == t->get_eng())
        {
            if (t->get_rus_multiple().size() <= index) return root->nullpointer(); ///ÐµÑÐ»Ð¸ Ð¼Ñ Ð²ÑÑÐ¾Ð´Ð¸Ð¼ Ð·Ð° Ð¿ÑÐµÐ´ÐµÐ»Ñ Ð²ÐµÐºÑÐ¾ÑÐ°, ÑÐ¾Ð¶Ðµ Ð²Ð¾Ð·Ð²ÑÐ°ÑÐ°ÐµÐ¼ nullpointer
            return t->get_rus_m_element()[index];
        }

        if (eng_inp < t->get_eng())
            return find_node(t->get_left(), eng_inp, index);
        if (eng_inp > t->get_eng())
            return find_node(t->get_right(), eng_inp, index);
    }

    void dict::delete_tr(cNode* t, string eng_inp, int index)
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

    cNode* dict::delete_node(cNode* node, string eng_inp)   
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

    int dict::count_nodes(cNode* node) {
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

    void dict::set_translation(string eng_inp, string rus_inp) {
        add_node(root, eng_inp, rus_inp);
    }

    void dict::remove_translation(string eng_inp) {
        delete_node(root, eng_inp);
    } ///ÑÐ´Ð°Ð»ÑÐµÑ ÑÐ°Ð¼ ÑÐ·ÐµÐ» ÑÐ»Ð¾Ð²Ð° ÑÐ¾ Ð²ÑÐµÐ¼Ð¸ ÑÐ»ÐµÐ¼ÐµÐ½ÑÐ°Ð¼Ð¸


    int dict::length() {
        return count_nodes(root);
    }

    int dict::tr_count(string eng_inp) {
        int i = 0;
        while (true)
        {
            if (find_node(root, eng_inp, i) == "Ð­Ð»ÐµÐ¼ÐµÐ½Ñ Ð½Ðµ Ð½Ð°Ð¹Ð´ÐµÐ½") {

                break;
            }
            i++;
        }
        return i;
    }

    void dict::delete_one_translation(string eng_inp, int index) {
        delete_tr(root, eng_inp, index);
    } ///ÑÐ´Ð°Ð»ÑÐµÑ ÐÐÐÐ Ð¿ÐµÑÐµÐ²Ð¾Ð´

        /// ÐÐµÑÐµÐ³ÑÑÐ·ÐºÐ° Ð¾Ð¿ÐµÑÐ°ÑÐ¾ÑÐ¾Ð²

    string dict::operator[] (string eng_inp) {
        string output = "";
        for (int i = 0; i < tr_count(eng_inp); i++)
        {
            output += find_node(root, eng_inp, i) + " ";
        }
        return output;
    }
    string& dict::operator[] (pair<string, int> transl) {
        return find_node(root, transl.first, transl.second);
    }
    void dict::operator-= (string eng_inp) {
        this->remove_translation(eng_inp);
    }
    void dict::operator+= (pair<string, string> eng_inp) {
        this->set_translation(eng_inp.first, eng_inp.second);
}
