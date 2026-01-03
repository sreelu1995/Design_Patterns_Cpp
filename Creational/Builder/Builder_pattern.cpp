// BUILDER DESIGN PATTERN IMPLEMENTATION WITH JUST MULTIPLE BUILDERS WITHOUT DIRECTOR

#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Car
{
  private:
   string modelName;
   string engine;
   int seats;
   bool hasGPS;

  public:
    Car(string mname, string eType, int seat, bool gps): modelName(mname), engine(eType), seats(seat), hasGPS(gps) {}

  // alternate solution of using set methods is to make builder class a friend
    void SetModelName(string e)
    {
        modelName = e;
    }

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
        cout<<"Model Name: "<<modelName<<endl;
        cout<<"Engine: "<<engine<<endl;
        cout<<"Number of Seats: "<<seats<<endl;
        cout<<"Has GPS or NOT (yes/no): "<<(hasGPS ? "yes": "no")<<endl;
    }    
};

class ICarBuilder{
  public:    
    virtual std::unique_ptr<Car> getCar() = 0;
    
    virtual ~ICarBuilder() = default;
};

class F1CarBuilder : public ICarBuilder{
  private:
    std::unique_ptr<Car> car;
  public:
    F1CarBuilder(string name)
    {
        car = make_unique<Car>(name, "V8 Turbo", 1, false);
    }

  std::unique_ptr<Car> getCar() override
  {
      return move(car);
  }
};

class SUVCarBuilder : public ICarBuilder{
    private:
      std::unique_ptr<Car> car;
    public:
      SUVCarBuilder(string name)
      {
          car = make_unique<Car>(name, "V6 DIESEL", 8, true);
      }

      std::unique_ptr<Car> getCar() override
      {
          return move(car);
      }
};

int main()
{
  F1CarBuilder spb("RedBull");
  unique_ptr<Car> Redbull = spb.getCar();
  Redbull->Show_Specs();
  
  cout<<endl;

  SUVCarBuilder suv1("Defender");
  unique_ptr<Car> Defender = suv1.getCar();
  Defender->Show_Specs();
  
  cout<<endl;
  
  SUVCarBuilder suv2("Hyundai Venue");
  unique_ptr<Car> Venue = suv2.getCar();
  Venue->Show_Specs();

  return 0;
}