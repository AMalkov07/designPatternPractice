#include <iostream>
#include <vector>

using namespace std;

// Observer interface
// this is also called the subscriber interface
class Observer {
public:
    virtual void update() = 0;
};

// Subject interface
// this is also called the publisher interface
class Subject {
public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
};

// Concrete subject
class ConcreteSubject : public Subject {
private:
    vector<Observer*> observers;
    int state;

public:
    void attach(Observer* observer) override {
        observers.push_back(observer);
    }

    void detach(Observer* observer) override {
        for (int i = 0; i < observers.size(); i++) {
            if (observers[i] == observer) {
                observers.erase(observers.begin() + i);
                break;
            }
        }
    }

    void notify() override {
        for (Observer* observer : observers) {
            observer->update();
        }
    }

    int getState() {
        return state;
    }

    void setState(int newState) {
        state = newState;
        notify();
    }
};

// Concrete observer
class ConcreteObserver : public Observer {
private:
    ConcreteSubject* subject;

public:
    ConcreteObserver(ConcreteSubject* subject) {
        this->subject = subject;
        subject->attach(this);
    }

    void update() override {
        int state = subject->getState();
        cout << "Observer received update. New state: " << state << endl;
    }

    ~ConcreteObserver() {
        subject->detach(this);
    }
};

int main() {
    ConcreteSubject* subject = new ConcreteSubject();
    ConcreteObserver* observer1 = new ConcreteObserver(subject);
    ConcreteObserver* observer2 = new ConcreteObserver(subject);

    subject->setState(1);
    subject->setState(2);

    delete observer1;
    delete observer2;
    delete subject;

    return 0;
}
