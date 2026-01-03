// Observer Design Pattern

#include <iostream>
#include <string>
#include <list>
#include <memory>

using namespace std;

class ISubscriber{
    public:
      virtual void notify(const string& msg) = 0;
      virtual ~ISubscriber() = default;
};

class User : public ISubscriber{
    private:
      string name;
    public:
      User(const string& u_name) : name(u_name){}
      
      void notify(const string& msg) override
      {
          std::cout << name << " received: " << msg<<endl;
      }
};

class Channel{
    private:
      list<shared_ptr<ISubscriber>> Users;
      
    public:
      void Subscribe(shared_ptr<ISubscriber> user)
      {
          Users.push_back(user);
      }
      
      void Unsubscribe(shared_ptr<ISubscriber> user)
      {
         Users.remove(user);
      }
      
      void Publish(const string& msg)
      {
          for(auto user: Users)
          {
              user->notify(msg);
          }
      }
};

int main()
{
    
  shared_ptr<Channel> c1= make_shared<Channel>();
  
  shared_ptr<User> user1 = make_shared<User>("Kylie");
  shared_ptr<User> user2 = make_shared<User>("Halie");
  shared_ptr<User> user3 = make_shared<User>("Mareo");
  
  c1->Subscribe(user1);
  c1->Subscribe(user2);
  c1->Subscribe(user3);
  
  c1->Publish("Sale at amazon up tonight\n");
  
  c1->Unsubscribe(user1);
  
  c1->Publish("Flipkart sale is cancelled\n");

  return 0;
}