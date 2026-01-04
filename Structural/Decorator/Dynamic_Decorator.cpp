// Dynamic Decorator Design Pattern Implementation

#include <iostream>
#include <string>
#include <memory>

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

// Base Decorator
class CoffeeDecorator : public Coffee {
   protected:
       shared_ptr<Coffee> wrapped;

   public:
       CoffeeDecorator(shared_ptr<Coffee> c) : wrapped(move(c)) {}
       virtual ~CoffeeDecorator() = default;
};

// Concrete Decorator 1
class Milk : public CoffeeDecorator {
  public:
      Milk(shared_ptr<Coffee> c) : CoffeeDecorator(move(c)){}

      std::string Get_Description() const override
      {
          return wrapped->Get_Description() + ", Milk";
      }

      double Get_Cost() const
      {
          return wrapped->Get_Cost() + 5.0;
      }
};

// Concrete Decorator 2
class Sugar : public CoffeeDecorator {
  public:
      Sugar(shared_ptr<Coffee> c) : CoffeeDecorator(move(c)){}

      std::string Get_Description() const override
      {
          return wrapped->Get_Description() + ", Sugar";
      }

      double Get_Cost() const
      {
          return wrapped->Get_Cost() + 2.0;
      }
};

// Concrete Decorator 3
class WhippedCream : public CoffeeDecorator {
  public:
      WhippedCream(shared_ptr<Coffee> c) : CoffeeDecorator(move(c)){}

      std::string Get_Description() const override
      {
          return wrapped->Get_Description() + ", WhippedCream";
      }

      double Get_Cost() const
      {
          return wrapped->Get_Cost() + 4.0;
      }
};

// Client
int main()
{
    int baseChoice, choice;
    bool done = false;

    // Create a simple Coffee
    shared_ptr<Coffee> myCoffee;

    cout << "Choose your base coffee:\n";
    cout << "1. Simple Coffee ($5)\n";
    cout << "2. Cuppaccino ($25)\n";

    cin >> baseChoice;

    if (baseChoice == 1)
    {
         myCoffee = make_shared<SimpleCoffee>();
    }
    else if (baseChoice == 2)
    {
        myCoffee = make_shared<Cuppaccino>();
    }
    else
    {
         cout << "Invalid choice, defaulting to Simple Coffee.\n";
         myCoffee = make_shared<SimpleCoffee>();
    }

    // Decorate coffee

    while(!done)
    {
        cout << "\nAdd-ons:\n";
        cout << "1. Milk (+$5)\n";
        cout << "2. Sugar (+$2)\n";
        cout << "3. Whipped Cream (+$4)\n";
        cout << "4. Finish Order\n";

        cin>>choice;

        switch(choice)
        {
          case 1:
            myCoffee = make_shared<Milk>(myCoffee);
            cout << "Milk added!\n";
            break;

          case 2:
            myCoffee = make_shared<Sugar>(myCoffee);
            cout << "Sugar added!\n";
            break;
          case 3:
            myCoffee = make_shared<WhippedCream>(myCoffee);
            cout << "Whipped Cream added!\n";
            break;
          case 4:
            done = true;
            break;
          default:
            cout << "Invalid choice.\n";
        }
    }

    cout<<"Order: "<<myCoffee->Get_Description()<<endl;
    cout<<"Cost: "<<myCoffee->Get_Cost()<<endl;

    return 0;
}
