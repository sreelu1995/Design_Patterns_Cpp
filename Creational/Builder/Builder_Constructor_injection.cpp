#include <iostream>
#include <memory>
#include <string>
using namespace std;

// Product
class Computer {
public:
    string CPU, GPU;
    int RAM;

    void showSpecs() const {
        cout << "CPU: " << CPU << "\nGPU: " << GPU << "\nRAM: " << RAM << " GB\n";
    }
};

// Builder Interface
class IComputerBuilder {
public:
    virtual void buildCPU() = 0;
    virtual void buildGPU() = 0;
    virtual void buildRAM() = 0;
    virtual shared_ptr<Computer> getComputer() = 0;
    virtual ~IComputerBuilder() = default;
};

// Concrete Builder
class GamingPCBuilder : public IComputerBuilder {
private:
    shared_ptr<Computer> pc = make_shared<Computer>();
public:
    void buildCPU() override { pc->CPU = "Intel i9"; }
    void buildGPU() override { pc->GPU = "RTX 4090"; }
    void buildRAM() override { pc->RAM = 32; }
    shared_ptr<Computer> getComputer() override { return pc; }
};

// Director with constructor injection
class Director {
private:
    IComputerBuilder& builder;
public:
    Director(IComputerBuilder& b) : builder(b) {}

    void construct() {
        builder.buildCPU();
        builder.buildGPU();
        builder.buildRAM();
    }
};

// Client
int main() {
    GamingPCBuilder builder;
    Director director(builder);
    director.construct();

    auto pc = builder.getComputer();
    cout << "Gaming PC:\n";
    pc->showSpecs();
}
