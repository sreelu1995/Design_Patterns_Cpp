// Simple Observer Design Pattern

#include <iostream>
#include <string>
#include <list>

using namespace std;

class ISubscriber{
    public:
      virtual void notify(string msg) = 0;
};

class User : public ISubscriber{
    private:
      int user_id;
    public:
      User(int id)
      {
          user_id = id;
      }
      
      void notify(string msg) override
      {
          cout<<"This message is printed by user "<<user_id<<" : "<<msg<<endl;
      }      
};

class Group
{
    private:
      list<ISubscriber*> users;
    public:
      void Subscribe(ISubscriber* user)
      {
          users.push_back(user);
      }
      
      void Unsubscribe(ISubscriber* user)
      {
          users.remove(user);
      }
      
      void Notify(string msg)
      {
          for(auto user : users)
          {
              user->notify(msg);
          }
      }
};

int main()
{
  Group* group = new Group();
  
  User* user1 = new User(1);
  User* user2 = new User(2);
  User* user3 = new User(3);
  
  group->Subscribe(user1);
  group->Subscribe(user2);
  group->Subscribe(user3);
  
  group->Notify("Test message 1");
  
  group->Unsubscribe(user1);
  
  group->Notify("Test message 2");

  return 0;
}