// SIMPLE BUILDER DESIGN PATTERN IMPLEMENTATION WITH JUST 1 BUILDER

#include <iostream>
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
    void setEngine(string e)
    {
        engine = e;
    }

    void setSeats(int s)
    {
        seats = s;
    }

    void setGPS(bool g)
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

class CarBuilder{
    private:
      Car car;
    public:
      CarBuilder& Set_Engine(string e)
      {
          car.setEngine(e);
          return *this;
      }
      
      CarBuilder& Set_Seats(int e)
      {
          car.setSeats(e);
          return *this;
      }
      
      CarBuilder& Set_GPS(bool e)
      {
          car.setGPS(e);
          return *this;
      }
      
      Car Build()
      {
          return car;
      }
};
int main()
{
  CarBuilder B;

  Car C = B.Set_Engine("V6")
              .Set_Seats(6)
              .Set_GPS(true)
              .Build();
              
  C.Show_Specs();

  return 0;
}