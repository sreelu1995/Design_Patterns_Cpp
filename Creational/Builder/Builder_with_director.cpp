// BUILDER DESIGN PATTERN IMPLEMENTATION WITH JUST MULTIPLE BUILDERS AND INTERFACE, DIRECTOR, BUILDER CLASSES

#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Car
{
  private:
   string engine;
   int seats;
   bool hasGPS;

  public:
  // alternate solution is to make builder class a friend
    void SetEngine(string e)
    {
        engine = e;
    }

    void SetSeats(int s)
    {
        seats = s;
    }

    void SetGPS(bool g)
    {
        hasGPS = g;
    }

    void Show_Specs()
    {
        cout<<"Engine: "<<engine<<endl;
        cout<<"Number of Seats: "<<seats<<endl;
        cout<<"Has GPS or NOT (yes/no): "<<(hasGPS ? "yes": "no")<<endl;
    }    
};

class ICarBuilder{
  public:
    virtual void BuildEngine() = 0;
    virtual void BuildSeats() = 0; 
    virtual void BuildGPS() = 0;
    
    virtual std::unique_ptr<Car> getCar() = 0;
    
    virtual ~ICarBuilder() = default;
};

class F1CarBuilder : public ICarBuilder{
  private:
    std::unique_ptr<Car> car = make_unique<Car>();
  public:
      void BuildEngine() override
      {
          car->SetEngine("V8 Turbo");
      }
      
      void BuildSeats() override
      {
          car->SetSeats(1);
      }
      
      void BuildGPS() override
      {
          car->SetGPS(false);
      }

  std::unique_ptr<Car> getCar() override
  {
      return move(car);
  }
};

class SUVCarBuilder : public ICarBuilder{
    private:
      std::unique_ptr<Car> car = make_unique<Car>();
    public:
      void BuildEngine() override
      {
          car->SetEngine("V6 DIESEL");
      }
      
      void BuildSeats() override
      {
          car->SetSeats(8);
      }
      
      void BuildGPS() override
      {
          car->SetGPS(true);
      }

      std::unique_ptr<Car> getCar() override
      {
          return move(car);
      }
};

class CarDirector{
  public:
    void construct(ICarBuilder &myBuilder)
    {
        myBuilder.BuildEngine();
        myBuilder.BuildSeats();
        myBuilder.BuildGPS();
    }
};

int main()
{
  CarDirector director;

  F1CarBuilder spb;
  director.construct(spb);
  unique_ptr<Car> Redbull = spb.getCar();
  Redbull->Show_Specs();
  
  cout<<endl;

  SUVCarBuilder suv1;
  director.construct(suv1);
  unique_ptr<Car> Defender = suv1.getCar();
  Defender->Show_Specs();

  return 0;
}