#include <iostream>

class Test{
public:
    int a;
    int b;
    Test(int a, int b) :
        a(a), b(b)
    {}
};

int main() {
    Test t(69, 420);
    std::cout <<t.a<<std::endl;
    std::cout <<t.b<<std::endl;
    return 0;
}