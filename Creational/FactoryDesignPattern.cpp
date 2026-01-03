// FACTORY DESIGN PATTERN IMPLEMENTATION USING VEHICLE CLASS

#include <iostream>

using namespace std;

class Vehicle{
  public:
    virtual void CreateVehicle() = 0;
};

class Bike : public Vehicle{
  public:
    void CreateVehicle()
    {
        cout<<"Bike is created"<<endl;
    }
};

class Car : public Vehicle{
  public:
    void CreateVehicle()
    {
        cout<<"Car is created"<<endl;
    }
};

class VehicleFactory{
  public:
    static Vehicle* GetVehicle(string vehicleType);
};

Vehicle* VehicleFactory::GetVehicle(string vehicleType)
{
        Vehicle* vehicle = nullptr;

        if(vehicleType == "Car")
        {
            
            vehicle = new Car();
        }
        else if(vehicleType == "Bike")
        {
            vehicle = new Bike();
        }
    return vehicle;
}

int main()
{
  Vehicle* vehicle = VehicleFactory::GetVehicle("Car");
  
  if(vehicle == nullptr)
    cout<<"Vehicle unsupported type. Cannot instantiate\n";
  else
     vehicle->CreateVehicle();    

  return 0;
}