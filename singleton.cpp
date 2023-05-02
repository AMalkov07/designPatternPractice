#include <iostream>

class Singleton {
private:
    //instance is a static member variable meaning that its value is shared among all instances of this class
    static Singleton* instance;
    Singleton() {}

public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }

    void showMessage() {
        std::cout << "Hello World!" << std::endl;
    }
};

Singleton* Singleton::instance = nullptr;

int main() {
    Singleton* singleton = Singleton::getInstance();
    singleton->showMessage();
    return 0;
}