// Static Decorator Design Pattern Implementation

#include <iostream>
#include <string>
#include <type_traits>

using namespace std;

// Base Component (interface)
class Coffee {
  public:
      virtual ~Coffee() = default;
      virtual std::string Get_Description() const = 0;
      virtual double Get_Cost() const = 0;
};

// Concrete Component 1
class SimpleCoffee : public Coffee {
  public:
     std::string Get_Description() const override
     {
         return "Simple Coffee";
     }

     double Get_Cost() const override
     {
         return 5.0;
     }
};

// Concrete Component 2
class Cuppaccino : public Coffee {
  public:
     std::string Get_Description() const override
     {
         return "Cuppaccino";
     }

     double Get_Cost() const override
     {
         return 25.0;
     }
};

// Concept: ensures only Coffee-derived types are allowed
template<typename T>
concept IsCoffee = std::is_base_of<Coffee, T>::value;

// Static Decorator: Milk
template<IsCoffee T>
class Milk : public T {
  public:
      template<typename... Args>
      Milk(Args&&... args) : T(std::forward<Args>(args)...){}

     std::string Get_Description() const override
     {
         return T::Get_Description() + ", Milk";
     }

     double Get_Cost() const override
     {
         return T::Get_Cost() + 5.0;
     }
};

// Static Decorator: Sugar
template<IsCoffee T>
class Sugar: public T {
   public:
     template<typename... Args>
     Sugar(Args&&... args) : T(std::forward<Args>(args)...){}

     std::string Get_Description() const override
     {
         return T::Get_Description() + ", Sugar";
     }

     double Get_Cost() const override
     {
         return T::Get_Cost() + 2.0;
     }
};

// Static Decorator : Whipped Cream
template<IsCoffee T>
class WhippedCream : public T {
   public:
       template<typename... Args>
       WhippedCream(Args&&... args) : T(std::forward<Args>(args)...){}

       std::string Get_Description() const override
       {
          return T::Get_Description() + ", Whipped Cream";
       }

       double Get_Cost() const override
       {
             return T::Get_Cost() + 10.0;
       }
};

int main()
{
    Milk<SimpleCoffee> coffeeWithMilk;
    Sugar<Milk<SimpleCoffee>> coffeeWithMilkAndSugar;
    WhippedCream<Sugar<Milk<Cuppaccino>>> fancyCuppa;

    cout<<"Order Details: "<<coffeeWithMilk.Get_Description()<<endl;
    cout<<"Cost: $"<<coffeeWithMilk.Get_Cost()<<endl;

    cout<<"Order Details: "<<coffeeWithMilkAndSugar.Get_Description()<<endl;
    cout<<"Cost: $"<<coffeeWithMilkAndSugar.Get_Cost()<<endl;

    cout<<"Order Details: "<<fancyCuppa.Get_Description()<<endl;
    cout<<"Cost: $"<<fancyCuppa.Get_Cost()<<endl;

    return 0;
}
