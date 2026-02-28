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

std::unique_ptr<Shape> parse_shape(std::string_view line) {
    std::istringstream iss(std::string(line));
    std::string type;
    iss >> type;

    if (type == "circle") {
        double r;
        if (!(iss >> r))
            return nullptr;
        return std::make_unique<Circle>(r);
    }
    else if (type == "rect") {
        double w, h;
        if (!(iss >> w >> h))
            return nullptr;
        return std::make_unique<Rect>(w, h);
    }

    return nullptr;
}

double total_area(const std::vector<std::unique_ptr<Shape>>& v) {
    double sum = 0.0;

    for (const auto& s : v) {
        if (s)
            sum += s->area();
    }

    return sum;
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    // Пример через фабрик
    shapes.push_back(make_shape(ShapeType::Circle, 5.0));
    shapes.push_back(make_shape(ShapeType::Rect, 3.0, 4.0));

    // Пример через парсер
    shapes.push_back(parse_shape("circle 10"));
    shapes.push_back(parse_shape("rect 2 6"));

    // Вывод
    for (const auto& s : shapes) {
        if (s)
            std::cout << s->name() << " area = " << s->area() << "\n";
    }

    std::cout << "Total area = " << total_area(shapes) << "\n";

    return 0;
}