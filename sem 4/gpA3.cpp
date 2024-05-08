#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

const int MAX_LEVEL = 5;

struct Node {
    int value;
    Node* forward[MAX_LEVEL + 1];
};

class SkipList {
private:
    Node* head;
    int level;
    float p;

public:
    SkipList() {
        head = new Node();
        level = 0;
        p = 0.5;
    }

    int randomLevel() {
        int lvl = 0;
        while (((float)rand() / RAND_MAX) < p && lvl < MAX_LEVEL)
            lvl++;
        return lvl;
    }

    void insert(int value) {
        Node* update[MAX_LEVEL + 1];
        Node* current = head;

        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < value)
                current = current->forward[i];
            update[i] = current;
        }

        current = current->forward[0];

        if (current == nullptr || current->value != value) {
            int newLevel = randomLevel();

            if (newLevel > level) {
                for (int i = level + 1; i <= newLevel; i++)
                    update[i] = head;
                level = newLevel;
            }

            Node* newNode = new Node();
            newNode->value = value;

            for (int i = 0; i <= newLevel; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
        }
    }

    int closestElement(int value) {
        Node* current = head;

        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value <= value)
                current = current->forward[i];
        }

        return current->value;
    }
};

int main() {
    srand(time(NULL));

    SkipList skipList;

    int numElements;
    cout << "Enter the number of elements: ";
    cin >> numElements;

    cout << "Enter the elements: ";
    for (int i = 0; i < numElements; i++) {
        int value;
        cin >> value;
        skipList.insert(value);
    }

    int valueToFind;
    cout << "Enter the value to find the closest element: ";
    cin >> valueToFind;

    int closest = skipList.closestElement(valueToFind);
    cout << "Closest element to " << valueToFind << " is: " << closest << endl;

    return 0;
}
