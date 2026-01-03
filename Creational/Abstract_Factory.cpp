// ABSTRACT FACTORY DESIGN PATTERN IMPLEMENTATION

#include <iostream>
#include <memory>

using namespace std;

class IButton{
  public:
      virtual void press() = 0;
      virtual ~IButton() = default;
};

class MacButton : public IButton{
  public:
    void press() override
    {
        cout<<"Mac button is pressed"<<endl;
    }
};

class WinButton : public IButton{
  public:
    void press() override
    {
        cout<<"Windows button is pressed"<<endl;
    }
};

class ITextBox{
  public:
      virtual void ShowText() = 0;
      virtual ~ITextBox() = default;
};

class MacTextBox : public ITextBox{
  public:
    void ShowText() override
    {
        cout<<"Showing Mac Text Box"<<endl;
    }
};

class WinTextBox : public ITextBox{
  public:
    void ShowText() override
    {
        cout<<"Showing Windows Text Box"<<endl;
    }
};

class IFactory{
  public:
      virtual unique_ptr<IButton> CreateButton() = 0;
      virtual unique_ptr<ITextBox> CreateTextBox() = 0;
      virtual ~IFactory() = default;
};

class MacFactory : public IFactory{
  public:
     unique_ptr<IButton> CreateButton() override{
       return make_unique<MacButton>();
     }

     unique_ptr<ITextBox> CreateTextBox() override{
       return make_unique<MacTextBox>();
     }
};

class WinFactory : public IFactory{
  public:
     unique_ptr<IButton> CreateButton() override{
       return make_unique<WinButton>();
     }

     unique_ptr<ITextBox> CreateTextBox() override{
       return make_unique<WinTextBox>();
     }
};

class GUIAbstractFactory{
  public:
      static unique_ptr<IFactory> CreateFactory(const std::string& osType);
};

unique_ptr<IFactory> GUIAbstractFactory::CreateFactory(const std::string& osType)
{
    if(osType == "Win")
        return make_unique<WinFactory>();
    else if(osType == "Mac")
        return make_unique<MacFactory>();
    else
        return make_unique<MacFactory>();  // default assumed to be Mac OS
}

int main()
{
    std::string osType;

    cout<<"Enter your preferred OS Type:";
    cin>>osType;

    unique_ptr<IFactory> fact = GUIAbstractFactory::CreateFactory(osType);

    unique_ptr<IButton> button = fact->CreateButton();
    unique_ptr<ITextBox> textbox = fact->CreateTextBox();

    button->press();
    textbox->ShowText();

    return 0;
}
