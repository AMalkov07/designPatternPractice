#include <string>
#include <iostream>

struct toppings{
    bool none;
    bool peperonni;
    bool ham;
    bool chicken;
    bool olives;
    bool pineapple;
    bool mushrooms;

    void printToppings() {
        std::cout << "your selected toppings are:" << std::endl;
        if (none) {
            std::cout << "none" << std::endl;
            return;
        }
        if (peperonni) {
            std::cout << "peperoni" << std::endl;
        }
        if (ham) {
            std::cout << "ham" << std::endl;
        }
        if (chicken) {
            std::cout << "chicken" << std::endl;
        }
        if (olives) {
            std::cout << "olives" << std::endl;
        }
        if (pineapple) {
            std::cout << "pineapple" << std::endl;
        }
        if (mushrooms) {
            std::cout << "mushrooms" << std::endl;
        }
    }
};

class pizza {
public:
    void addSauce(const std::string& sa) {sauce = sa;}
    void addCheese(const std::string& ch) {cheese = ch;}
    void addCrust(const std::string& cr) {crust = cr;}
    void addPeperoni() {top->peperonni = true;}
    void addHam() {top->ham = true;}
    void addChicken() {top->chicken = true;}
    void addOlives() {top->olives = true;}
    void addPineapple() {top->pineapple = true;}
    void addMushrooms() {top->mushrooms = true;}
    void addNone() {top->none = true;}

    void printPizza() {
        std::cout << "the base of your pizza is a " << crust << " crust with " << cheese << " cheese and " << sauce << " sauce" << std::endl;
        top->printToppings();
    }
private:
    std::string sauce;
    std::string cheese;
    std::string crust;
    toppings* top = new toppings();
};

class pizzaBuilder {
public:
    virtual void addSauce() = 0;
    virtual void addCheese() = 0;
    virtual void addCrust() = 0;
    virtual void addToppings() = 0;
    virtual pizza* getPizza() = 0;
};

class cheesePizzaBuilder : public pizzaBuilder {
public:
    void addSauce() override { m_pizza->addSauce("classic red"); }
    void addCheese() override { m_pizza->addCheese("mozzarella"); }
    void addCrust() override { m_pizza->addCrust("thin"); }
    void addToppings() override { m_pizza->addNone(); }
    pizza* getPizza() override {return m_pizza;}

private:
pizza *m_pizza = new pizza();
};

class meatLoversPizzaBuilder : public pizzaBuilder {
public:
    void addSauce() override { m_pizza->addSauce("bbq"); }
    void addCheese() override { m_pizza->addCheese("mozzarella"); }
    void addCrust() override { m_pizza->addCrust("thick"); }
    void addToppings() override { 
        m_pizza->addPeperoni(); 
        m_pizza->addHam(); 
        m_pizza->addChicken(); 
    }
    pizza* getPizza() override {return m_pizza;}

private:
pizza *m_pizza = new pizza();
};

class pizzaFactory{
public:
    pizza* createPizza(pizzaBuilder* pb){
        pb->addSauce();
        pb->addCrust();
        pb->addCheese();
        pb->addToppings();
        return pb->getPizza();
    }
};

int main() {
    pizzaFactory* pf = new pizzaFactory();
    pizzaBuilder* cheese = new cheesePizzaBuilder();
    pizza* p1 = pf->createPizza(cheese);
    p1->printPizza();

    pizzaBuilder* meatLovers = new meatLoversPizzaBuilder();
    pizza* p2 = pf->createPizza(meatLovers);
    p2->addOlives();
    p2->printPizza();
    return 0;
}