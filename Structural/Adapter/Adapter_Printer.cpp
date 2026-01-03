// Adapter Design Pattern detailed implementation

#include <iostream>
#include <string>
#include <memory>

using namespace std;

// Target Interface
class IPrinter{
    public:
      virtual void Print_data(string str) = 0;
      virtual ~IPrinter() = default;
};

// Adaptee
class Legacy_Printer{
    public:
      void Old_Print(string str)
      {
          cout<<"Legacy printing: "<<str<<endl;
      }
};

// Adapter
class Printer_Adapter : public IPrinter{
   private:
      shared_ptr<Legacy_Printer> printer;
   public:
      Printer_Adapter(shared_ptr<Legacy_Printer> lPrinter) : printer(lPrinter){}

      void Print_data(string str)
      {
        cout<<"Using adapter to print data...\n";
        printer->Old_Print(str);
      }      
};

// concrete class
class Modern_Printer : public IPrinter{
    public:
      void Print_data(string str)
      {
          cout<<"Modern Printer: "<<str<<endl;
      }
};

// client
int main()
{
  string data = "Hello";
  shared_ptr<Legacy_Printer> lp = make_shared<Legacy_Printer>();
  shared_ptr<IPrinter> p1 = make_shared<Printer_Adapter>(lp);
  p1->Print_data(data);
  
  shared_ptr<IPrinter> p2 = make_shared<Modern_Printer>();
  p2->Print_data(data);

  return 0;
}