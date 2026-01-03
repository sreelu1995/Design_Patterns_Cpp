// CHAIN OF RESPONSIBILITY DESIGN PATTERN

#include <iostream>
#include <memory>

using namespace std;

class Handler{
   protected:
       shared_ptr<Handler> next_handler;

   public:
       virtual ~Handler() = default;

       void set_next_handler(shared_ptr<Handler> next_ptr)
       {
          next_handler = next_ptr;
       }

       shared_ptr<Handler> get_next_handler()
       {
           return next_handler;
       }

       virtual void handle_request(std::string request) = 0;
};

class AuthHandler : public Handler
{
   public:
      void handle_request(std::string request)
      {
         if(request == "AUTH")
         {
             cout<<"Processing Authentication request"<<endl;
         }
         else if(get_next_handler())
         {
             cout<<"Passing the request to next handler"<<endl;
             get_next_handler()->handle_request(request);
         }
         else
         {
             cout<<"Unable to process the request "<<request<<endl;
         }
      }
};

class LogHandler : public Handler
{
   public:
      void handle_request(std::string request)
      {
         if(request == "LOG")
         {
             cout<<"Processing login request"<<endl;
         }
         else if(get_next_handler())
         {
             cout<<"Passing the request to next handler"<<endl;
             get_next_handler()->handle_request(request);
         }
         else
         {
             cout<<"Unable to process the request "<<request<<endl;
         }
      }
};

class DataHandler : public Handler
{
   public:
      void handle_request(std::string request)
      {
         if(request == "DATA")
         {
             cout<<"Processing Data request"<<endl;
         }
         else if(get_next_handler())
         {
             cout<<"Passing the request to next handler"<<endl;
             get_next_handler()->handle_request(request);
         }
         else
         {
             cout<<"Unable to process the request "<<request<<endl;
         }
      }
};

int main()
{
  shared_ptr<Handler> auth = make_shared<AuthHandler>();
  shared_ptr<Handler> logg = make_shared<LogHandler>();
  shared_ptr<Handler> data = make_shared<DataHandler>();

  auth->set_next_handler(logg);
  logg->set_next_handler(data);

  auth->handle_request("AUTH");
  auth->handle_request("LOG");
  auth->handle_request("DATA");
  auth->handle_request("TRANSACTION");

  return 0;
}
