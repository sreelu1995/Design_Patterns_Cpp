// Simple implementation of Adapter Design Pattern
#include <iostream>
#include <string>

using namespace std;

class XMLData{
  private:
    string Xml_Data;

  public:
    XMLData(string pXMLData)
    {
        Xml_Data = pXMLData;
    }
    
    string get_Xml_Data()
    {
        return Xml_Data;
    }    
};

class DataAnalysisTool{
    private:
      string JSONData;

    public:
      DataAnalysisTool() {}

      DataAnalysisTool(string pJsonData)
      {
          JSONData = pJsonData;
      }
      
      virtual void Analyse_Data()
      {
          cout<<"Analysing JSON data: "<<JSONData<<endl;
      }
};

class Client{
    public:
      Client(){}

      void Process_Data(DataAnalysisTool *tool)
      {
          tool->Analyse_Data();
      }
};

class DataAdapter : public DataAnalysisTool{
    private:
      XMLData* xmlData;

    public:
      DataAdapter(XMLData* pXMLData)
      {
        xmlData = pXMLData;
      }
      
      void Analyse_Data() override
      {
          cout<<"Adapter Analysing JSON data: "<<xmlData->get_Xml_Data()<<endl;
      }
};

int main()
{
  XMLData* xml = new XMLData("This data is in XML Format");
  DataAnalysisTool* tool = new DataAdapter(xml);
  Client* c1 = new Client();
  c1->Process_Data(tool);
  
  return 0;
}