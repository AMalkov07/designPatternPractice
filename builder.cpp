#include <iostream>
#include <string>

class Car {
public:
    void setBrand(const std::string& brand) { m_brand = brand; }
    void setModel(const std::string& model) { m_model = model; }
    void setYear(int year) { m_year = year; }
    void setColor(const std::string& color) { m_color = color; }
    void setHorsepower(int horsepower) { m_horsepower = horsepower; }
    void addHeatedSeats() {
        heatedSeats = true;
        heatedSeatsOutput = "does";
    }
    void removeHeatedSeats() {
        heatedSeats = false;
        heatedSeatsOutput = "does Not";
    }

    void printInfo() const {
        std::cout << "Brand: " << m_brand << std::endl
                  << "Model: " << m_model << std::endl
                  << "Year: " << m_year << std::endl
                  << "Color: " << m_color << std::endl
                  << "Horsepower: " << m_horsepower << std::endl
                  << "This car " << heatedSeatsOutput << " have heated seats" << std::endl;
    }

private:
    std::string m_brand;
    std::string m_model;
    int m_year;
    std::string m_color;
    int m_horsepower;
    bool heatedSeats = false;
    std::string heatedSeatsOutput = "does Not";

/*     std::string printHeatedSeats(){
        if (heatedSeats) {
            return "does";
        }    
        return "does NOT";
    } */
};

//this is the interface that defines the functions that should be defined in every type of car
class CarBuilder {
public:
    virtual void buildBrand() = 0;
    virtual void buildModel() = 0;
    virtual void buildYear() = 0;
    virtual void buildColor() = 0;
    virtual void buildHorsepower() = 0;
    virtual Car* getCar() = 0;
};

class SportsCarBuilder : public CarBuilder {
public:
    SportsCarBuilder(){
        m_car->addHeatedSeats();
    }
    void buildBrand() override { m_car->setBrand("Ferrari"); }
    void buildModel() override { m_car->setModel("488 GTB"); }
    void buildYear() override { m_car->setYear(2021); }
    void buildColor() override { m_car->setColor("Red"); }
    void buildHorsepower() override { m_car->setHorsepower(661); }
    Car* getCar() override { return m_car; }

private:
    Car* m_car = new Car();
};

class SUVBuilder : public CarBuilder {
public:
    void buildBrand() override { m_car->setBrand("Toyota"); }
    void buildModel() override { m_car->setModel("RAV4"); }
    void buildYear() override { m_car->setYear(2022); }
    void buildColor() override { m_car->setColor("Blue"); }
    void buildHorsepower() override { m_car->setHorsepower(203); }
    Car* getCar() override { return m_car; }

private:
    Car* m_car = new Car();
};

// this class acts as the director, meaning that it defines the order in which the functions in our subclasses should be called
class CarFactory {
public:
    Car* createCar(CarBuilder* builder) {
        builder->buildBrand();
        builder->buildModel();
        builder->buildYear();
        builder->buildColor();
        builder->buildHorsepower();
        return builder->getCar();
    }
};

int main() {
    CarFactory carFactory;
    CarBuilder* sportsCarBuilder = new SportsCarBuilder();
    Car* sportsCar = carFactory.createCar(sportsCarBuilder);
    sportsCar->printInfo();
    sportsCar->removeHeatedSeats();
    sportsCar->printInfo();
    delete sportsCarBuilder;
    delete sportsCar;

    CarBuilder* suvBuilder = new SUVBuilder();
    Car* suv = carFactory.createCar(suvBuilder);
    suv->printInfo();
    delete suvBuilder;
    delete suv;

    return 0;
}
