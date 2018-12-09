#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

struct Node
{
    Node* next;
    Node* prev;
    int value;
};

class CircularList
{
    Node *root = nullptr;
//    Node *tail = nullptr;

public:
    Node* insert(Node *before, int value)
    {
        Node *newNode = new Node{ nullptr, nullptr, value };
        if(root == nullptr) {
            root = newNode;
            newNode->prev = root;
            newNode->next = root;
        }
        else {
            newNode->prev = before->prev;
            newNode->next = before;
            before->prev->next = newNode;
            before->prev = newNode;

            if(before == root) {
                root = newNode;
            }
        }
        return newNode;
    }

    Node* erase(Node *what)
    {
        Node *next;
        if(root == root->next) {
            root = nullptr;
            next = nullptr;
        }
        else {
            what->prev->next = what->next;
            what->next->prev = what->prev;
            next = what->next;
            if(what == root) {
                root = next;
            }
        }
        delete what;
        return next;
    }

    ~CircularList()
    {
        Node *node = root;
        while(node != nullptr) {
            node = erase(node);
        }
    }
};

int main()
{
    int p;
    int n;
    std::vector<long long> scores;

    CircularList _marbles;
    
    scanf("%i players; last marble is worth %i points.", &p, &n);
    scores.resize(p);

    Node *current = _marbles.insert(nullptr, 0);
    Node *behind;

    int marbleNumber = 1;
    int turn = 0;
    while(marbleNumber <= n) {
        if(marbleNumber % 23 == 0) {
            scores[ turn ] += marbleNumber;
            int i = 0;
            behind = current;
            while(i < 7) {
                behind = behind->prev;
                ++i;
            }
            scores[ turn ] += behind->value;
            current = _marbles.erase(behind);
        }
        else {
            current = _marbles.insert(current->next->next, marbleNumber);
        }
        turn = (turn + 1) % p;
        ++marbleNumber;
    }
    std::cout << *max_element(scores.begin(), scores.end()) << std::endl;
    return 0;
}
