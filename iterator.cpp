#include <iostream>
#include <vector>

// Define the Iterator interface
class Iterator {
public:
    virtual int getNext() = 0;
    virtual bool hasNext() = 0;
};

// Define a Concrete Iterator class that iterates over a vector
class VectorIterator : public Iterator {
private:
    std::vector<int> data;
    int index;

public:
    VectorIterator(std::vector<int> v) : data(v), index(0) {}

    int getNext() {
        int value = data[index];
        index++;
        return value;
    }

    bool hasNext() {
        return index < data.size();
    }
};

// Define a class that uses the Iterator to iterate over a collection
class Collection {
private:
    Iterator* iterator;

public:
    Collection(Iterator* it) : iterator(it) {}

    void iterate() {
        while (iterator->hasNext()) {
            std::cout << iterator->getNext() << std::endl;
        }
    }
};

int main() {
    // Create a vector of integers to iterate over
    std::vector<int> data = {1, 2, 3, 4, 5};

    // Create a Concrete Iterator object to iterate over the vector
    VectorIterator* it = new VectorIterator(data);

    // Create a Collection object that uses the Iterator to iterate over the vector
    Collection* collection = new Collection(it);

    // Iterate over the vector using the Collection object
    collection->iterate();

    // Clean up memory
    delete it;
    delete collection;

    return 0;
}
