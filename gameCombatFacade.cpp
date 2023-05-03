#include <iostream>

class Character{
public:
    Character(int health, int attack, int ar) 
        : hp(health), atk(attack), armor(ar) {}

    void updateHP (int newHealth) {
        hp = newHealth;
    }
    int getHealth(){
        return hp;
    }
    int getAtk(){
        return atk;
    }
    int getArmor(){
        return armor;
    }
    void death(){
        alive = false;
    }
private:
    int hp;
    int atk;
    int armor;
    bool alive = true;
};

class damageCalculation{
public:
    int damageAmount(int atk, int armor) {
        return atk - armor;
    }
    void changeHealth(Character* c, int healthReduction) {
       c->updateHP(c->getHealth() - healthReduction);
       std::cout << "the new health is " << c->getHealth() << std::endl;
       if (c->getHealth() <= 0) {
        c->death();
       }
    }
};

//thie class is facade
class combat {
public:
    void attack(Character* c1, Character* c2){
        int tmp = dc->damageAmount(c1->getAtk(), c2->getArmor());
        dc->changeHealth(c2, tmp);
    }
damageCalculation* dc = new damageCalculation();
};

int main(){
    combat* comb = new combat();
    Character* c1 = new Character(100, 50, 10);
    Character* c2 = new Character(100, 50, 10);
    comb->attack(c1, c2);
    comb->attack(c1, c2);
    comb->attack(c2, c1);
    comb->attack(c1, c2);
    comb->attack(c2, c1);
    return 0;
}