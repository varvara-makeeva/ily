#include <memory>
#include <vector>
#include <string>
#include <string_view>
#include <cmath>

enum class ShapeType { Circle, Rect };

class Shape {
public:
    virtual ~Shape() = default;

    virtual double area() const = 0;
    virtual ShapeType type() const noexcept = 0;
    virtual std::string name() const = 0;
};

class Circle final : public Shape {
public:
    explicit Circle(double r) : r_(r) {}

    double area() const override {
        return M_PI * r_ * r_;
    }

    ShapeType type() const noexcept override {
        return ShapeType::Circle;
    }

    std::string name() const override {
        return "Circle";
    }

private:
    double r_;
};

class Rect final : public Shape {
public:
    Rect(double w, double h) : w_(w), h_(h) {}

    double area() const override {
        return w_ * h_;
    }

    ShapeType type() const noexcept override {
        return ShapeType::Rect;
    }

    std::string name() const override {
        return "Rect";
    }

private:
    double w_, h_;
};

std::unique_ptr<Shape> make_shape(ShapeType t, double a, double b) {
    switch (t) {
        case ShapeType::Circle:
            return std::make_unique<Circle>(a);
        case ShapeType::Rect:
            return std::make_unique<Rect>(a, b);
        default:
            return nullptr;
    }
}