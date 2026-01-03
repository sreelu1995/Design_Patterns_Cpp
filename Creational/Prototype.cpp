// Prototype Design Pattern Implementation

#include <iostream>
#include <memory>
#include <unordered_map>
#include<string>

using namespace std;

// Base prototype
class Shape{
  protected:
      int x, y;
      std::string color;

  public:
      Shape() : x(0), y(0), color("black") {}
      Shape(const Shape& source)
      {
          x = source.x;
          y = source.y;
          color = source.color;
      }

      virtual ~Shape() = default;

      virtual unique_ptr<Shape> clone() const = 0;

      virtual void print() const
      {
        cout << "Shape at (" << x << ", " << y << ") color: " << color << endl;
      }

      void Set_Parameters(int a, int b, const std::string& clr)
      {
          x = a;
          y = b;
          color = clr;
      }
};

class Rectangle : public Shape{
  private:
      int width, height;

  public:
    Rectangle(int a = 0, int b = 0) : width(a), height(b) {}
    Rectangle(const Rectangle& source) : Shape(source)
    {
        width = source.width;
        height = source.height;
    }

    ~Rectangle() override = default;

    virtual unique_ptr<Shape> clone() const override
    {
        return make_unique<Rectangle>(*this);
    }

    void print() const override
    {
        cout << "Rectangle at (" << x << ", " << y << ") color: " << color << " Width: "<<width<<" Height: "<<height<<endl;
    }
};

class Circle : public Shape{
  private:
      float radius;

  public:
    Circle(float r=0) : radius(r) {}
    Circle(const Circle& source) : Shape(source)
    {
        radius = source.radius;
    }

    ~Circle() override = default;

    virtual unique_ptr<Shape> clone() const override
    {
        return make_unique<Circle>(*this);
    }

    void print() const override
    {
        cout << "Circle at (" << x << ", " << y << ") color: " << color << " Radius: "<<radius<<endl;
    }
};

class ShapeRegistry {
  private:
    unordered_map<string, unique_ptr<Shape>> prototypes;

  public:
    void Add_Prototype(const string& key, unique_ptr<Shape> prototype)
    {
        prototypes[key] = move(prototype);
    }

    unique_ptr<Shape> Create_Shape(const string& key)
    {
        auto it = prototypes.find(key);

        if(it != prototypes.end())
            return it->second->clone();

        return nullptr;
    }
};

int main()
{
  ShapeRegistry Client;

  auto CirclePrototype = make_unique<Circle>(20);
  // CirclePrototype->Set_Parameters(10, 20, "Red");

  Client.Add_Prototype("Circle", move(CirclePrototype));

  auto RectanglePrototype = make_unique<Rectangle>(16,18);
  RectanglePrototype->Set_Parameters(100, 100, "Yellow");

  Client.Add_Prototype("Rectangle", move(RectanglePrototype));

  auto circle1 = Client.Create_Shape("Circle");
  auto circle2 = Client.Create_Shape("Circle");

  auto rectangle1 = Client.Create_Shape("Rectangle");
  auto rectangle2 = Client.Create_Shape("Rectangle");

  circle1->Set_Parameters(10, 20, "Red");

  circle2->Set_Parameters(104, 205, "Yellow");

  circle1->print();
  circle2->print();
  rectangle1->print();
  rectangle2->print();

  return 0;
}
