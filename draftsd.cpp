#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <fstream>

#define MAX_LEVEL 6

const float P = 0.5;

using namespace std;

ifstream fin("abce.in");
ofstream fout("abce.out");

struct Node
{
    int key;
    Node** forward;
    Node(int level, int& key)
    {
        forward = new Node * [level + 1];
        memset(forward, 0, sizeof(Node*) * (level + 1));
        this->key = key;
    }
    ~Node()
    {
        delete[] forward;
    }
};

struct SkipList
{
    Node* header;
    int value;
    int level;
    SkipList()
    {
        header = new Node(MAX_LEVEL, value);
        level = 0;
    }
    ~SkipList()
    {
        delete header;
    }
    void afisare();
    bool verificare_element(int&);
    void insert_element(int&);
    void delete_element(int&);
    int maxim(int&);
    int minim(int&);
    void afisare_range(int&, int&);
};

int main()
{

    SkipList lista;
    int choice, n, x, y, q;
    fin >> q;
    for (int i = 0; i < q; i++)
    {
        fin >> n;
        if (n == 1)
        {
            fin >> n;
            lista.insert_element(n);
        }

        else if (n == 2)
        {
            fin >> n;
            lista.delete_element(n);
        }

        else if (n == 3)
        {
            fin >> n;
            if (lista.verificare_element(n))
                fout << "1";
            else
                fout << "0" << endl;
        }

        else if (n == 4)
        {
            fin >> x;
            n = lista.maxim(x);
            if (n != -1)
                fout << n << endl;
            else
                fout << "Nu exista" << endl;
        }

        else if (n == 5)
        {
            fin >> x;
            n = lista.minim(x);
            if (n != -1)
                fout << n << endl;
            else
                fout << "Nu  exista." << endl;
        }

        else if (n == 6)
        {
            fin >> x;
            fin >> y;
            lista.afisare_range(x, y);
        
        }
    }
    
    return 0;
}

float frand()
{
    return (float)rand() / RAND_MAX;
}

int random_level()
{
    static bool first = true;
    if (first)
    {
        srand((unsigned)time(NULL));
        first = false;
    }
    int lvl = (int)(log(frand()) / log(1. - P));
    return lvl < MAX_LEVEL ? lvl : MAX_LEVEL;
}

void SkipList::insert_element(int& value)
{
    Node* x = header;
    Node* nou[MAX_LEVEL + 1];
    memset(nou, 0, sizeof(Node*) * (MAX_LEVEL + 1));
    for (int i = level; i >= 0; i--)
    {
        while (x->forward[i] != NULL && x->forward[i]->key < value)
        {
            x = x->forward[i];
        }
        nou[i] = x;
    }
    x = x->forward[0];
    if (x == NULL || x->key != value)
    {
        int lvl = random_level();
        if (lvl > level)
        {
            for (int i = level + 1; i <= lvl; i++)
            {
                nou[i] = header;
            }
            level = lvl;
        }
        x = new Node(lvl, value);
        for (int i = 0; i <= lvl; i++)
        {
            x->forward[i] = nou[i]->forward[i];
            nou[i]->forward[i] = x;
        }
    }
}

void SkipList::delete_element(int& value)
{
    Node* x = header;
    Node* nou[MAX_LEVEL + 1];
    memset(nou, 0, sizeof(Node*) * (MAX_LEVEL + 1));
    for (int i = level; i >= 0; i--)
    {
        while (x->forward[i] != NULL && x->forward[i]->key < value)
        {
            x = x->forward[i];
        }
        nou[i] = x;
    }
    x = x->forward[0];
    if (x->key == value)
    {
        for (int i = 0; i <= level; i++)
        {
            if (nou[i]->forward[i] != x)
                break;
            nou[i]->forward[i] = x->forward[i];
        }
        delete x;
        while (level > 0 && header->forward[level] == NULL)
        {
            level--;
        }
    }
}

bool SkipList::verificare_element(int& s_value)
{
    Node* x = header;
    for (int i = level; i >= 0; i--)
    {
        while (x->forward[i] != NULL && x->forward[i]->key < s_value)
        {
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    return x != NULL && x->key == s_value;
}

void SkipList::afisare()
{
    const Node* x = header->forward[0];
    while (x != NULL)
    {
        fout << x->key;
        x = x->forward[0];
        if (x != NULL)
            fout << " - ";
    }
    fout << endl;
}

int SkipList::maxim(int& value)
{
    Node* x = header;
    for (int i = level; i >= 0; i--)
    {
        while (x->forward[i] != NULL && x->forward[i]->key <= value)
        {
            x = x->forward[i];
        }
    }
    if (x != header)
        return x->key;
    else
        return -1;
}

int SkipList::minim(int& value)
{
    Node* x = header;
    for (int i = level; i >= 0; i--)
    {
        while (x->forward[i] != NULL && x->forward[i]->key < value)
        {
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    if (x != NULL)
        return x->key;
    else
        return -1;
}

void SkipList::afisare_range(int& x, int& y)
{
    Node* p = header;
    for (int i = level; i >= 0; i--)
    {
        while (p->forward[i] != NULL && p->forward[i]->key < x)
        {
            p = p->forward[i];
        }
    }
    p = p->forward[0];
    while (p != NULL && p->key <= y)
    {
        fout << p->key;
        p = p->forward[0];
        if (p != NULL && p->key <= y)
            fout << " ";
    }
    fout << endl;
}