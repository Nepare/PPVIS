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
    } ///comparison operator

    void dict::add_node(cNode* node, string eng_inp, string rus_inp) {
        if (!root) {
            cNode* t = new cNode(eng_inp, rus_inp);
            root = t;       /// if the root elements doesn't exist, we allocate memory to it and connect it to the 'root' pointer
        }               
        else {
            cNode* prev, * t;
            bool find = true;       /// find is a check if there is no dublicate english name of this element in the tree
            t = node; prev = t;

            while (t && find) {      /// looking for the place for this node: when the 't' pointer isn't nullpointer (it's not on the bottom level), we go down a level
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
            if (find) {       ///if there is no dublicate
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
            return root->nullpointer(); ///if this element doesn't exist, we return nullpointer
        if (eng_inp == t->get_eng())
        {
            if (t->get_rus_multiple().size() <= index) return root->nullpointer(); ///if we go out of range of the vector, return nullpointer
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
    } ///deletes the node and all the elements within

    int dict::length() {
        return count_nodes(root);
    }

    int dict::tr_count(string eng_inp) {
        int i = 0;
        while (true)
        {
            if (find_node(root, eng_inp, i) == "Element not found") {
                break;
            }
            i++;
        }
        return i;
    }

    void dict::delete_one_translation(string eng_inp, int index) {
        delete_tr(root, eng_inp, index);
    } ///deletes ONE translation

        /// overloading operators
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