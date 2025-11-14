#include <iostream>
#include <vector>
#include <cmath>


class Shape {
 public:
  virtual ~Shape() = default;
  virtual double perimeter() const = 0;
  virtual double area() const = 0;
};


class Triangle : public Shape {
 private:
  double a, b, c;
  //  стороны

 public:
  Triangle(double side1, double side2, double side3) {
    a = side1;
    b = side2;
    c = side3;
  }

  double perimeter() const override final {
    return a + b + c;
  }

  double area() const override final {
    double s = (a + b + c) / 2.0;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
  }
};

class Square final : public Shape {
 private:
  double side;

 public:
  Square(double s) {
    side = s;
  }

  double perimeter() const override {
    return 4.0 * side;
  }

  double area() const override {
    return side * side;
  }
};

class Circle final : public Shape {
 private:
  double radius;

public:
  Circle(double r) {
    radius = r;
  }

  double perimeter() const override {
    return 2.0 * M_PI * radius;
  }

  double area() const override {
    return M_PI * radius * radius;
  }
};

int main() {
  std::vector<Shape*> shapes;

  shapes.push_back(new Triangle(3.0, 4.0, 5.0));
  shapes.push_back(new Square(4.0));
  shapes.push_back(new Circle(5.0));

  for (const auto* shape : shapes) {
    std::cout << shape->perimeter() << ' ' << shape->area() << '\n';
  }

  for (auto* shape : shapes) {
    delete shape;
  }

  return 0;
}