// SINGLETON DESIGN PATTERN SAMPLE IMPLEMENTATION USING LOGGER CLASS

#include <iostream>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

class Logger{
    private:
      static mutex mtx;
      static int ctr;
      Logger();
      static Logger* loggerInstance;

    public:
      Logger(const Logger&) = delete;
      Logger& operator=(const Logger&) = delete;
      static Logger* GetLoggerInstance();
      void log(string str);
};

mutex Logger::mtx;
int Logger::ctr = 0;
Logger *Logger::loggerInstance = nullptr;

Logger::Logger()
{
    ctr++;
    cout<<"Constructor for Logger is called. No. of instances is:"<<ctr<<endl;
}

void Logger::log(string str)
{
    cout<<str<<endl;
}

Logger* Logger::GetLoggerInstance()
{
   if(loggerInstance == nullptr)
   {
   mtx.lock();
   {   
    if(loggerInstance == nullptr)
    {
        loggerInstance = new Logger();
    }
   }
   mtx.unlock();
   }
    
    return loggerInstance;
}

void user1_logger()
{
    Logger* log1 = Logger::GetLoggerInstance();
    log1->log("Good morning");
}

void user2_logger()
{
    Logger* log2 = Logger::GetLoggerInstance();
    log2->log("This cat is loud");  
}
 
int main()
{
    thread t1(user1_logger);
    thread t2(user2_logger);
    
    t1.join();
    t2.join();

    return 0;
}