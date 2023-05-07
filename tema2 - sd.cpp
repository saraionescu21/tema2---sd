#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node(int v) {
        val = v;
        left = nullptr;
        right = nullptr;
    }
};

class ABCS {
public:
    Node* radacina;

    ABCS() {
        radacina = nullptr;
    }

    void insert(int val) {
        Node* newNode = new Node(val);

        if (radacina == nullptr) {
            radacina = newNode;
            return;
        }

        Node* elem = radacina;
        while (true) {
            if (val < elem->val) {
                if (elem->left == nullptr) {
                    elem->left = newNode;
                    return;
                }
                elem = elem->left;
            }
            else {
                if (elem->right == nullptr) {
                    elem->right = newNode;
                    return;
                }
                elem = elem->right;
            }
        }
    }

    void remove(int val) {
        radacina = removeHelper(radacina, val);
    }

    bool search(int val) {
        return searchHelper(radacina, val);
    }

private:
 
    Node* removeHelper(Node* elem, int val) {
        if (elem == nullptr) {
            return elem;
        }

        if (val < elem->val) {
            elem->left = removeHelper(elem->left, val);
        }
        else if (val > elem->val) {
            elem->right = removeHelper(elem->right, val);
        }
        else {
            if (elem->left == nullptr) {
                Node* temp = elem->right;
                delete elem;
                return temp;
            }
            else if (elem->right == nullptr) {
                Node* temp = elem->left;
                delete elem;
                return temp;
            }
            Node* temp = valoare_minima(elem->right);
            elem->val = temp->val;
            elem->right = removeHelper(elem->right, temp->val);
        }
        return elem;
    }

    Node* valoare_minima(Node* node) {
        Node* elem = node;
        while (elem && elem->left != nullptr) {
            elem = elem->left;
        }
        return elem;
    }

    bool searchHelper(Node* current, int val) {
        if (current == nullptr) {
            return false;
        }
        if (current->val == val) {
            return true;
        }
        if (val < current->val) {
            return searchHelper(current->left, val);
        }
        else {
            return searchHelper(current->right, val);
        }
    }
};

int main() 
{
    ABCS tree;

    int q, x, n;
    fin >> q;

    for (int i = 0; i < q; i++)
    {
        fin >> n;
        if (n == 1)
        {
            fin >> x;
            tree.insert(x);
        }

        else if (n == 2)
        {
            fin >> x;
            tree.remove(x);
        }
        else if (n == 3)
		{
			fin >> x;
			fout << tree.search(x) << endl;
		}
    }

    return 0;
}
