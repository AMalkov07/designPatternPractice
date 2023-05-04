#include <iostream>
#include <string>

// Interface for the real subject
class Subject {
public:
    virtual void request() = 0;
};

// Real subject that performs the actual task
class RealSubject : public Subject {
public:
    void request() override {
        std::cout << "RealSubject: Handling request.\n";
    }
};

// Proxy that acts as a middleman between the client and the real subject
// a Proxy can either act as security and limit a clients access to the real subject, or alternatively it can work as a rapper class that adds more functionality to the real subject, in this ex. its the latter
class Proxy : public Subject {
public:
    Proxy(Subject* real_subject) 
        : real_subject_(real_subject) {}

    void request() override {
        if (checkAccess()) {
            real_subject_->request();
            logAccess();
        }
    }

private:
    Subject* real_subject_;
    std::string client_name_ = "John Doe";

    bool checkAccess() const {
        std::cout << "Proxy: Checking access prior to firing a real request.\n";
        return client_name_ == "John Doe";
    }

    void logAccess() const {
        std::cout << "Proxy: Logging the time of the request.\n";
    }
};

// Client code that interacts with the proxy
int main() {
    RealSubject* real_subject = new RealSubject();
    Proxy* proxy = new Proxy(real_subject);

    proxy->request();

    delete proxy;
    delete real_subject;

    return 0;
}
