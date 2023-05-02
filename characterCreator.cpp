#include <iostream>
#include <string>

class character{
public:
    std::string weapon;
    virtual ~character() {};
    virtual character* clone() const = 0;
    virtual void printCharacterStats() const = 0;
};

class Mage : public character {
public:
    Mage(std::string w, int m, int ap) :
        manaStat(m), abilityPowerStat(ap) {weapon = w;}

    character* clone() const override {
        return new Mage(*this);
    }

    void printCharacterStats() const override {
        std::cout << "this is a new character of the Mage class. It is using the " << weapon <<" wepon type and it has " << manaStat << " mana and " << abilityPowerStat << " ap" << std::endl;
    }

    //std::string weapon;
    int manaStat;
    int abilityPowerStat;
};

class Warrior : public character {
public:
    Warrior(std::string w, int s, int ad) :
        strength(s), attackDamageStat(ad) {weapon = w;}

    character* clone() const override {
        return new Warrior(*this);
    }

    void printCharacterStats() const override {
        std::cout << "this is a new character of the Warrior class. It is using the " << weapon <<" weapon type and it has " << strength << " strength and " << attackDamageStat << " ad" << std::endl;
    }

    int strength;
    int attackDamageStat;
};

class characterFactory{
    character* magePrototype;    
    character* warriorPrototype;    
public:
    characterFactory() :
        magePrototype(new Mage("unknown", 10, 10)), warriorPrototype(new Warrior("uknown", 10, 10)) {}

    ~characterFactory() {
        delete magePrototype;
        delete warriorPrototype;
    }

    character* createMage(std::string w, int mana, int ap) {
        Mage* newMage = dynamic_cast<Mage*>(magePrototype->clone());
        newMage->weapon = w;
        newMage->manaStat = mana;
        newMage->abilityPowerStat = ap;
        return newMage;
    }

    character* createWarrior(std::string w, int s, int ad) {
        Warrior* newWarrior = dynamic_cast<Warrior*>(warriorPrototype->clone());
        newWarrior->weapon = w;
        newWarrior->attackDamageStat = ad;
        newWarrior->strength = s;
        return newWarrior;
    }
};

int main(){
    characterFactory cf;
    Mage* Rudeus = dynamic_cast<Mage*>(cf.createMage("staff", 100, 80));
    character* Sylphie = cf.createMage("wand", 50, 60);
    character* Eris = cf.createWarrior("sword", 50, 80);
    character* Ghislaine = cf.createWarrior("sword", 60, 70);


    Rudeus->printCharacterStats();
    Sylphie->printCharacterStats();
    Eris->printCharacterStats();
    Ghislaine->printCharacterStats();

    delete Rudeus;
    delete Sylphie;
    delete Eris;
    delete Ghislaine;

    return 0;
}