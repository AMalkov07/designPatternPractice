#include <iostream>
#include <string>

class Shape {
public:
    virtual ~Shape() {}
    virtual Shape* clone() const = 0;
    virtual void draw() const = 0;
};

class Circle : public Shape {
public:
    Circle(int x, int y, int radius)
        : x_(x), y_(y), radius_(radius) {}

    Shape* clone() const override {
        return new Circle(*this);
    }

    void draw() const override {
        std::cout << "Drawing a circle at (" << x_ << ", " << y_ << ") with radius " << radius_ << std::endl;
    }

    int x_, y_, radius_;
};

class Rectangle : public Shape {
public:
    Rectangle(int x, int y, int width, int height)
        : x_(x), y_(y), width_(width), height_(height) {}

    Shape* clone() const override {
        return new Rectangle(*this);
    }

    void draw() const override {
        std::cout << "Drawing a rectangle at (" << x_ << ", " << y_ << ") with width " << width_ << " and height " << height_ << std::endl;
    }

    int x_, y_, width_, height_;
};

class ShapeFactory {
public:
    ShapeFactory()
        : circle_prototype_(new Circle(0, 0, 1)), rectangle_prototype_(new Rectangle(0, 0, 1, 1)) {}

    ~ShapeFactory() {
        delete circle_prototype_;
        delete rectangle_prototype_;
    }

    Shape* createCircle(int x, int y, int radius) {
        Circle* circle = dynamic_cast<Circle*>(circle_prototype_->clone());
        circle->x_ = x;
        circle->y_ = y;
        circle->radius_ = radius;
        return circle;
    }

    Shape* createRectangle(int x, int y, int width, int height) {
        Rectangle* rectangle = dynamic_cast<Rectangle*>(rectangle_prototype_->clone());
        rectangle->x_ = x;
        rectangle->y_ = y;
        rectangle->width_ = width;
        rectangle->height_ = height;
        return rectangle;
    }

private:
    Shape* circle_prototype_;
    Shape* rectangle_prototype_;
};

int main() {
    ShapeFactory factory;

    Shape* circle1 = factory.createCircle(10, 20, 30);
    circle1->draw();

    Shape* circle2 = factory.createCircle(100, 200, 300);
    circle2->draw();

    Shape* rectangle1 = factory.createRectangle(40, 50, 60, 70);
    rectangle1->draw();

    Shape* rectangle2 = factory.createRectangle(400, 500, 600, 700);
    rectangle2->draw();

    delete circle1;
    delete circle2;
    delete rectangle1;
    delete rectangle2;

    return 0;
}