#include <iostream>
#include <unordered_set>
#include <iterator>

using namespace std;

template<typename T>
class Set {
private:
    unordered_set<T> elements;

public:
    // Add a new element to the set
    void Add(const T& element) {
        elements.insert(element);
    }

    // Remove an element from the set
    void Remove(const T& element) {
        elements.erase(element);
    }

    // Check if the set contains a specific element
    bool Contains(const T& element) const {
        return elements.count(element) > 0;
    }

    // Get the size of the set
    int Size() const {
        return elements.size();
    }

    // Get an iterator to loop over the set
    typename unordered_set<T>::const_iterator Iterator() const {
        return elements.begin();
    }

    // Compute the intersection of this set with another set
    Set<T> Intersection(const Set<T>& other) const {
        Set<T> result;
        for (const T& element : elements) {
            if (other.Contains(element)) {
                result.Add(element);
            }
        }
        return result;
    }

    // Compute the union of this set with another set
    Set<T> Union(const Set<T>& other) const {
        Set<T> result = *this;
        for (const T& element : other.elements) {
            result.Add(element);
        }
        return result;
    }

    // Compute the difference between this set and another set
    Set<T> Difference(const Set<T>& other) const {
        Set<T> result = *this;
        for (const T& element : other.elements) {
            result.Remove(element);
        }
        return result;
    }

    // Check if this set is a subset of another set
    bool IsSubsetOf(const Set<T>& other) const {
        for (const T& element : elements) {
            if (!other.Contains(element)) {
                return false;
            }
        }
        return true;
    }
};

// Function to get user input
template<typename T>
T GetUserInput(const string& prompt) {
    T value;
    cout << prompt;
    cin >> value;
    return value;
}

// Main function to demonstrate the Set class
int main() {
    Set<int> set1;
    Set<int> set2;

    // Populate set1
    int numElements1 = GetUserInput<int>("Enter the number of elements for Set 1: ");
    for (int i = 0; i < numElements1; ++i) {
        int element = GetUserInput<int>("Enter an element for Set 1: ");
        set1.Add(element);
    }

    // Populate set2
    int numElements2 = GetUserInput<int>("Enter the number of elements for Set 2: ");
    for (int i = 0; i < numElements2; ++i) {
        int element = GetUserInput<int>("Enter an element for Set 2: ");
        set2.Add(element);
    }

    // Perform set operations
    cout << "Set 1 size: " << set1.Size() << endl;
    cout << "Set 2 size: " << set2.Size() << endl;

    Set<int> intersection = set1.Intersection(set2);
    cout << "Intersection of Set 1 and Set 2: ";
    for (auto it = intersection.Iterator(); it != intersection.Iterator(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    Set<int> unionSet = set1.Union(set2);
    cout << "Union of Set 1 and Set 2: ";
    for (auto it = unionSet.Iterator(); it != unionSet.Iterator(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    Set<int> difference = set1.Difference(set2);
    cout << "Difference (Set 1 - Set 2): ";
    for (auto it = difference.Iterator(); it != difference.Iterator(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    if (set2.IsSubsetOf(set1)) {
        cout << "Set 2 is a subset of Set 1" << endl;
    } else {
        cout << "Set 2 is not a subset of Set 1" << endl;
    }

    return 0;
}
