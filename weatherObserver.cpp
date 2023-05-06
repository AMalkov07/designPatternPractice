#include <vector>
#include <iostream>

class Observer {
public:
    virtual void update() = 0;
    //virtual void subscribe(WeatherChannel* s) = 0;
};

class Subject {
public:
    virtual void subscribe(Observer* subscriber) = 0;
    virtual void unsubscribe(Observer* subsriber) = 0;
    virtual void notify() = 0;
};

class WeatherChannel : public Subject {
    int temp;
    int humidity;
    std::vector<Observer*> subscribers;

public:
    WeatherChannel(int t, int h) 
        : temp(t), humidity(h) {}
    void changeTmp(int newTemp){
        temp = newTemp;
    }
    void changeHumidity(int newHumidity) {
        humidity = newHumidity;
        notify();
    }
    void subscribe(Observer* subscriber) override {
        subscribers.push_back(subscriber);
        notify();
    }
    void unsubscribe(Observer* subscriber) override {
        for (int i=0;i<subscribers.size();i++) {
            if (subscriber = subscribers[i]){
                subscribers.erase(subscribers.begin() + i);
                break;
            }
        }
    }
    void notify() override {
        for (Observer* subscriber : subscribers) {
            subscriber->update();
        }
    }

    int getTemp(){
        return temp;
    }

    int getHumidity(){
        return humidity;
    }
};

class RandomPerson : public Observer {
    WeatherChannel* subject=nullptr;
public:

    RandomPerson(WeatherChannel* s) {
        subject=s;
        subject->subscribe(this);
    }

/*     void subscribe(WeatherChannel* s) override{
        subject = s;
        s->subscribe(this);
    } */

    void update() override{
        std::cout << "thoday's temperature is " << subject->getTemp() << std::endl;
        std::cout << "thoday's humidity is " << subject->getHumidity() << std::endl;
    }
    ~RandomPerson(){
        subject->unsubscribe(this);
    }
};

int main(){
    WeatherChannel* wc = new WeatherChannel(10, 10);
    RandomPerson* p1 = new RandomPerson(wc);
    RandomPerson* p2 = new RandomPerson(wc);
    //p1->subscribe(wc);
    wc->changeTmp(100);
    //p2->subscribe(wc);
    wc->changeTmp(1000);
    wc->changeHumidity(222);
    
    return 0;
}