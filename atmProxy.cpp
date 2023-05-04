#include <string>
#include <iostream>

class User{
public:
    User(int b)
        : balance(b) {}
    void grantAccess(){
        access = true;
    }
    bool getAccess(){
        return access;
    }
    int getBalance(){
        return balance;
    }
    void subBalance(int amount){
        balance -= amount;
    }
    void addBalance(int amount){
        balance += amount;
    }

private:
    bool access = false;
    int balance;
};

class Atm{
public:
    virtual void deposit(int amount) = 0;
    virtual void withdraw(int amount) = 0;
};

class Realatm : public Atm{
public:
    Realatm(User *user)
        : m_user(user) {}
    
    void deposit(int amount) override {
        m_user->addBalance(amount);
    }
    void withdraw(int amount) {
        m_user->subBalance(amount);
    }
private:
    User *m_user;
};

class Proxyatm : public Atm {
public:
    Proxyatm(User *user)
        : m_user(user), realatm(new Realatm(user)){}
    void deposit(int amount) override {
        if (m_user->getAccess()){
            realatm->deposit(amount);
        } else {
            std::cout << "access denied!" << std::endl;
        }
    }
    void withdraw(int amount) {
        if (m_user->getAccess()){
            realatm->withdraw(amount);
        } else {
            std::cout << "access denied!" << std::endl;
        }
    }
private:
    Realatm* realatm;
    User *m_user;    
};

int main(){
    User *u1 = new User(1000);
    Atm *a1 = new Proxyatm(u1);
    a1->deposit(500);
    std::cout << "current balance is: " << u1->getBalance() << std::endl;
    a1->withdraw(500);
    std::cout << "current balance is: " << u1->getBalance() << std::endl;
    u1->grantAccess();
    a1->deposit(500);
    std::cout << "current balance is: " << u1->getBalance() << std::endl;
    a1->withdraw(200);
    std::cout << "current balance is: " << u1->getBalance() << std::endl;
    delete u1;
    delete a1;
    return 0;
}