#include <iostream>
#include <fstream>

struct Node {
    int childrenCount;
    int metadataCount;
    Node** children;
    int* metadata;
};

Node* ReadTree(std::ifstream& file)
{
    Node* node = new Node;
    file >> node->childrenCount;
    file >> node->metadataCount;
    if(node->childrenCount > 0) {
        node->children = new Node*[ node->childrenCount ];
        for(int i = 0; i < node->childrenCount; i++)
            node->children[ i ] = ReadTree(file);
    }
    else
        node->children = nullptr;
    if(node->metadataCount > 0) {
        node->metadata = new int[ node->metadataCount ];
        for(int i = 0; i < node->metadataCount; i++)
            file >> node->metadata[ i ];
    }
    else
        node->metadata = nullptr;
    return node;
}

void RemoveTree(Node *root)
{
    delete[] root->metadata;
    for(int i = 0; i < root->childrenCount; i++)
        RemoveTree(root->children[ i ]);
    delete[] root->children;
    delete root;
}

// Part 1
int GetSum(Node *root)
{
    int sum = 0;
    for(int i = 0; i < root->metadataCount; i++)
        sum += root->metadata[ i ];
    for(int i = 0; i < root->childrenCount; i++)
        sum += GetSum(root->children[ i ]);
    return sum;
}

// Part 2
int GetValue(Node *node)
{
    int sum = 0;
    if(node->childrenCount > 0) {
        for(int i = 0; i < node->metadataCount; i++) {
            int m = node->metadata[ i ];
            if(m > 0 && m < node->childrenCount + 1)
                sum += GetValue(node->children[ m - 1 ]);
        }
    }
    else {
        for(int i = 0; i < node->metadataCount; i++)
            sum += node->metadata[ i ];
    }
    return sum;
}

int main()
{
    std::string s;
    std::getline(std::cin, s, '\n');
    std::ifstream file(s);

    Node *root = ReadTree(file);
    std::cout << GetSum(root) << std::endl;
    std::cout << GetValue(root) << std::endl;

    file.close();
    RemoveTree(root);
    return 0;
}
