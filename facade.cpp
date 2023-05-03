#include <iostream>

// Subsystem classes
class SubsystemA {
public:
    void operationA() {
        std::cout << "SubsystemA operation\n";
    }
};

class SubsystemB {
public:
    void operationB() {
        std::cout << "SubsystemB operation\n";
    }
};

// Facade class
class Facade {
private:
    SubsystemA subsystemA;
    SubsystemB subsystemB;
public:
    void operation() {
        subsystemA.operationA();
        subsystemB.operationB();
    }
};

// Client code
int main() {
    Facade facade;
    facade.operation();
    return 0;
}