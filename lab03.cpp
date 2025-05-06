/*Написать компьютерную программу, содержащую описание классов для иерархии геометрических объектов (точка, линия, квадрат, ромб, прямоугольник, параллелограмм) с реализацией набора методов (изобразить, убрать, передвинуть, повернуть) .
Проверить возможность реализации различных вариантов регламентации доступа к компонентам классов.
Реализовать отождествление базовых объектов "Квадрат" для объектов "Параллелограмм" с использованием виртуального наследования.
Преобразовать класс "Точка" в абстрактный класс.
Проверить возможность позднего связывания для методов геометрических объектов.
Наследовать от поинта класс базовый поинт испоьловать его как свойство классов для хранения координат вершин фигуры
Сделать класс шейп, т.к. у т. не должно быть метода ротате
*/

#include <iostream>
#include <cmath>

class Point {
public:
    virtual double getX() const = 0;
    virtual double getY() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual ~Point() {}
};

class BasicPoint : public Point {
private:
    double x, y;
public:
    BasicPoint(double x, double y) : x(x), y(y) {}

    double getX() const override { return x; }
    double getY() const override { return y; }

    void move(double dx, double dy) override {
        x += dx;
        y += dy;
    }
};

class Shape {
public:
    virtual void draw() const = 0;
    virtual void erase() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void rotate(double angle) = 0;
    virtual ~Shape() {}
};

class Line : public Shape {
private:
    BasicPoint start, end;
public:
    Line(double x1, double y1, double x2, double y2) : start(x1, y1), end(x2, y2) {}

    void draw() const override {
        std::cout << "Drawing line from (" << start.getX() << ", " << start.getY() << ") to (" << end.getX() << ", " << end.getY() << ")" << std::endl;
    }

    void erase() const override {
        std::cout << "Erasing line" << std::endl;
    }

    void move(double dx, double dy) override {
        start.move(dx, dy);
        end.move(dx, dy);
    }

    void rotate(double angle) override {
        double radians = angle * M_PI / 180.0;
        double dx = end.getX() - start.getX();
        double dy = end.getY() - start.getY();
        double newX = dx * cos(radians) - dy * sin(radians);
        double newY = dx * sin(radians) + dy * cos(radians);
        end = BasicPoint(start.getX() + newX, start.getY() + newY);
    }
};

class Square : public Shape {
private:
    BasicPoint topLeft;
    double side;
public:
    Square(double x, double y, double s) : topLeft(x, y), side(s) {}

    void draw() const override {
        std::cout << "Drawing square at (" << topLeft.getX() << ", " << topLeft.getY() << ") with side " << side << std::endl;
    }

    void erase() const override {
        std::cout << "Erasing square" << std::endl;
    }

    void move(double dx, double dy) override {
        topLeft.move(dx, dy);
    }

    void rotate(double angle) override {
        std::cout << "Rotating square by " << angle << " degrees" << std::endl;
    }
};

class Rectangle : public Shape {
private:
    BasicPoint topLeft;
    double width, height;
public:
    Rectangle(double x, double y, double w, double h) : topLeft(x, y), width(w), height(h) {}

    void draw() const override {
        std::cout << "Drawing rectangle at (" << topLeft.getX() << ", " << topLeft.getY() << ") with width " << width << " and height " << height << std::endl;
    }

    void erase() const override {
        std::cout << "Erasing rectangle" << std::endl;
    }

    void move(double dx, double dy) override {
        topLeft.move(dx, dy);
    }

    void rotate(double angle) override {
        std::cout << "Rotating rectangle by " << angle << " degrees" << std::endl;
    }
};

class Parallelogram : public virtual Square {
private:
    double offset;
public:
    Parallelogram(double x, double y, double s, double o) : Square(x, y, s), offset(o) {}

    void draw() const override {
        std::cout << "Drawing parallelogram based on square with side " << getSide() << " and offset " << offset << std::endl;
    }

    void erase() const override {
        std::cout << "Erasing parallelogram" << std::endl;
    }

    void move(double dx, double dy) override {
        Square::move(dx, dy);
    }

    void rotate(double angle) override {
        std::cout << "Rotating parallelogram by " << angle << " degrees" << std::endl;
    }
};

class Rhombus : public Shape {
private:
    BasicPoint center;
    double diagonal1, diagonal2;
public:
    Rhombus(double x, double y, double d1, double d2) : center(x, y), diagonal1(d1), diagonal2(d2) {}

    void draw() const override {
        std::cout << "Drawing rhombus at (" << center.getX() << ", " << center.getY() << ") with diagonals " << diagonal1 << " and " << diagonal2 << std::endl;
    }

    void erase() const override {
        std::cout << "Erasing rhombus" << std::endl;
    }

    void move(double dx, double dy) override {
        center.move(dx, dy);
    }

    void rotate(double angle) override {
        std::cout << "Rotating rhombus by " << angle << " degrees" << std::endl;
    }
};

void demo(Shape* shape) {
    shape->draw();
    shape->move(5, 5);
    shape->rotate(45);
    shape->erase();
}

int main() {
    Square sq(0, 0, 10);
    Line ln(0, 0, 5, 5);

    std::cout << "--- Demo: Square ---" << std::endl;
    demo(&sq);

    std::cout << "\n--- Demo: Line ---" << std::endl;
    demo(&ln);
    return 0;
}
