#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Strategy Interface
class PaymentStrategy {
    public:
      virtual void pay(int amount) = 0;
      virtual ~PaymentStrategy() = default;    
};

// Concrete Strategy UPI Payment
class UPIPayment : public PaymentStrategy {
    private:
      string upi_id;
    
    public:
      UPIPayment(string id) : upi_id(std::move(id)) {}

      void pay(int amount) override
      {
        cout<<"Paid "<<amount<<" Using UPI ID (" << upi_id << " )\n";
      }      
};

// Concrete Strategy Card Payment
class CardPayment : public PaymentStrategy {
    private:
      string card_no;
    
    public:
      CardPayment(string card) : card_no(std::move(card)) {}

      void pay(int amount) override
      {
        cout<<"Paid "<<amount<<" Using Card (" << card_no << " )\n";
      }       
};

// Concrete Strategy Cash Payment
class CashPayment : public PaymentStrategy {
    public:
      void pay(int amount) override
      {
        cout<<"Paid "<<amount<<" Using Cash\n";
      } 
};

// context (class using strategy)
class ShoppingCart {
    private:
      unique_ptr<PaymentStrategy> strategy;
      int total = 0;
      
    public:
      void addItem(int price)
      {
          total += price;
      }
      
      void SetPaymentStrategy(unique_ptr<PaymentStrategy> s)
      {
          strategy = std::move(s);
      }
      
      void checkout()
      {
          if(!strategy)
          {
              cout<<"Please select a payment method!\n";
              return;
          }
          strategy->pay(total);
          total = 0;
      }
};

int main()
{
  ShoppingCart cart;
  cart.addItem(100);
  cart.addItem(200);
  
  cart.SetPaymentStrategy(make_unique<CardPayment>("1122998877446655"));
  cart.checkout();
  
  cart.addItem(500);
  cart.SetPaymentStrategy(make_unique<CashPayment>());
  cart.checkout();

  cart.addItem(650);
  cart.addItem(800);
  cart.addItem(550);
  
  cart.SetPaymentStrategy(make_unique<UPIPayment>("abc@okabcbank"));
  cart.checkout();

  return 0;
}