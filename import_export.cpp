#include <iostream>
#include<list>
#include<vector>
#include <limits>
#include<stack>
#define RESET   "\033[0m"      // Reset to default text color
#define RED     "\033[31m"     // Red text color
#define GREEN   "\033[32m"     // Green text color
#define YELLOW  "\033[33m"     // Yellow text color
#define BLUE    "\033[34m"     // Blue text color
#define MAGENTA "\033[35m"     // Magenta text color
#define CYAN    "\033[36m"     // Cyan text color
#define WHITE   "\033[37m"     // White text color
#define GRAY    "\033[90m"     // Gray text color
#define LIGHT_RED     "\033[91m"     // Light Red text color
#define LIGHT_GREEN   "\033[92m"     // Light Green text color
#define LIGHT_YELLOW  "\033[93m"     // Light Yellow text color
#define LIGHT_BLUE    "\033[94m"     // Light Blue text color
#define LIGHT_MAGENTA "\033[95m"     // Light Magenta text color
#define LIGHT_CYAN    "\033[96m"     // Light Cyan text color

using namespace std;

class Exception {
public:
    int err;
    string msg;
    Exception()
    {
        err = 0;
        msg = " ";
    }
    Exception(int x, string y)
    {
        err = x;
        msg = y;
    }
    Exception(string x)
    {
        err = 401;
        msg = x;
    }
    void showError()
    {
        cout<<MAGENTA<< "\terr_number:" << err << "\terr message:" << msg << endl;
    }
};

class Item {
public:
    string name;
    string description;
    float price_per_unit;
    Item()
    {
        this->name = "";
        this->description = "";
        this->price_per_unit = 0;
    }
    Item(string s, string d, float a)
    {
        this->name = s;
        this->description = d;
        this->price_per_unit = a;
    }
    virtual void printDetails() = 0;
    virtual ~Item() {} // Add a virtual destructor to the base class for proper cleanup
};

class Resource : public Item {
public:
    Resource() : Item() {}
    Resource(string n, string d, float f) : Item(n, d, f) {}

    void printDetails()
    {
        cout <<MAGENTA<< "Name : " << name << "\n"
             << "Price of Item: " << price_per_unit << "\n"
             << "Description : " << description <<"\n"<< endl;
    }
};

class Goods : public Item {
public:
    Goods() : Item() {}
    Goods(string n, string d, float f) : Item(n, d, f) {}

    void printDetails()
    {
        cout <<MAGENTA<< "Name : " << name << "\n"
             << "Price of Item: " << price_per_unit << "\n"
             << "Description : " << description <<"\n"<< endl;
    }
};

class Spices : public Item {
public:
    Spices() : Item() {}
    Spices(string n, string d, float f) : Item(n, d, f) {}

    void printDetails()
    {
        cout <<MAGENTA<< "Name : " << name << "\n"
             << "Price of Item: " << price_per_unit << "\n"
             << "Description : " << description <<"\n"<< endl;
    }
};

class ItemBuilder {
public:
    ItemBuilder() : item(nullptr)
    {
    }

    ItemBuilder* setName(const string& name)
    {
        itemName = name;
        return this;
    }

    ItemBuilder* setDescription(const string& desc)
    {
        itemDesc = desc;
        return this;
    }

    ItemBuilder* setPrice(float price)
    {
        itemPrice = price;
        return this;
    }

    Item* build()
    {
        if (!item)
            {
            // Assuming we have a finite number of item types
            if (itemType == "Resource")
                item = new Resource(itemName, itemDesc, itemPrice);
            else if (itemType == "Goods")
                item = new Goods(itemName, itemDesc, itemPrice);
            else if (itemType == "Spices")
                item = new Spices(itemName, itemDesc, itemPrice);
            else
                throw Exception("Unknown item type: " + itemType);
        }
        return item;
    }

    ItemBuilder* setItemType(const string& type)
    {
        itemType = type;
        return this;
    }

private:
    string itemName;
    string itemDesc;
    float itemPrice;
    string itemType;
    Item* item;
};

class Warehouse
{
public:
    string wareHouseName;
    string location;
    int capacity;
    vector<Item*> storage;

    Warehouse() {}
    Warehouse(string x, string y, int z)
    {
        wareHouseName = x;
        location = y;
        capacity = z;
    }

    void computeCapacity(int n)
    {
        if (n > capacity) {
            throw Exception(1001, "\tcapacity is full");
        } else {
            capacity = capacity - n;
        }

    }

    void accomadateItems(int n, ItemBuilder* itemBuilders[])
    {
        if (n > capacity) {
            throw Exception(1001, "\tcapacity is full");
        } else {
            for (int i = 0; i < n; i++) {
                Item* newItem = itemBuilders[i]->build();
                storage.push_back(newItem);
            }
        }
    }

    void displayStorage()
    {
        if (storage.empty())
        {
            cout << "\tItems are not checked in\n "
                 << endl;
        }

        for (size_t i = 0; i < storage.size(); ++i)
        {
            storage[i]->printDetails();
        }
        cout<<MAGENTA<<"remaining capacity:"<<capacity<<endl;
    }


    // Destructor to deallocate memory for stored items
    ~Warehouse() {
        for (size_t i = 0; i < storage.size(); ++i)
        {
            delete storage[i];
        }
    }
};


class ModeOfTransport
{
public:
  string means;
  int capacity;
  string vehicleNo;

   ModeOfTransport(){}

   ModeOfTransport(string m,int c,string v)
  {
    means=m;
    capacity=c;
    vehicleNo=v;
  }

    void printMode()
    {
      cout<<MAGENTA<<"Mode of Transport:"<<means<<"\nCapacity of vehicle: "<<capacity<<"\nVehicle Number: "<<vehicleNo<<endl;
    }
};




class Exporter
{
public:
  int quantity;
  string companyName;
  string location;
   float sum;

  Exporter()
 {
    this->quantity=0;
    this->companyName="";
    this->location="";
 }

  Exporter(int q,string name, string loc )
 {
    this->quantity=q;
    this->companyName=name;
    this->location=loc;
 }

float totalPrice(Item* items[],int n )
  {
      float price;
      this->sum=0;
     for(int i=0;i<n;i++)
     {
       price = items[i]->price_per_unit*quantity;

       this->sum=this->sum+price;
     }
     return this->sum;
  }
  void printModeOfExport( ModeOfTransport &mode)
  {
      mode.printMode();
  }
  void printExporter()
  {
      cout<<MAGENTA<<"company name:"<<companyName<<"\n"<<"location:"<<location<<endl;
  }

};



class CurrrencyExchange
{
public:
  float findCurrency(string location)
  {
      //cout<<MAGENTA<<"enter 1:Dubai,2:USA,3:UK,4:Vietnam,canda:5,6:Australia,7:china"<<endl;
       int a;
       if(location=="Dubai")
         a=1;
        else  if(location=="USA")
         a=2;
         else  if(location=="UK")
         a=3;
         else  if(location=="Vietnam")
         a=4;
         else  if(location=="Canada")
         a=5;
         else  if(location=="Australia")
         a=6;
         else  if(location=="China")
          a=7;

     switch(a)
       {
         case 1: return 0.045;
                       break;
         case 2: return  0.012;
                     break;
         case 3:  return 0.011;
                     break;

         case 4: return 288.23;
                         break;
         case 5: return 0.016;
                        break;
         case 6: return 0.018;
                            break;
         case 7: return 0.087;
                       break;
         default : cout<<"no such country"<<endl;
                    exit(0);
       }
  }

  float forexConvert(float x, float y)  //in impoter what we will do is "x = e->totalPrice();" "y=findCurrency()" and send that to this function
  {
      return x*y;
  }
};


class Importer
{
public:
    string location;
    Exporter e;
    string companyName;
    float price;

    Importer()
    {}

    Importer(string loc,string comp, Exporter expo)
    {
      this->companyName=comp;
      this->location=loc;
      e = expo;
    }

    void forex(CurrrencyExchange ce,Exporter expo)
    {
      float d=ce.findCurrency(location);
     // cout<<expo.sum<<endl;
      float d1 = ce.forexConvert( expo.sum,  d);
      this->price=d1;

    cout<<MAGENTA<<"final amount to pay is "<<d1<<endl;
    }

    void printImporter()
    {

        cout<<RED<<"importer details"<<endl;
        cout<<MAGENTA<<"location:"<<location<<"\ncompany name:"<<companyName<<endl;
    }


};

class ShortestDistance
{
public:
    vector<vector<int> > distanceMatrix;
    int numVertices;

    ShortestDistance(const vector<vector<int> >& matrix) : distanceMatrix(matrix)
    {
        numVertices = matrix.size();
    }

    vector<int> dijkstraShortestDistance(int startVertex)
    {
        vector<int> dist(numVertices, numeric_limits<int>::max());
        vector<bool> visited(numVertices, false);

        dist[startVertex] = 0;

        for (int count = 0; count < numVertices - 1; ++count)
            {
            int minDist = numeric_limits<int>::max();
            int minVertex = -1;

            for (int v = 0; v < numVertices; ++v)
                {
                if (!visited[v] && dist[v] < minDist)
                {
                    minDist = dist[v];
                    minVertex = v;
                }
            }

            if (minVertex == -1)
                break;

            visited[minVertex] = true;

            for (int v = 0; v < numVertices; ++v)
                {
                if (!visited[v] && distanceMatrix[minVertex][v] &&
                    dist[minVertex] != numeric_limits<int>::max() &&
                    dist[minVertex] + distanceMatrix[minVertex][v] < dist[v])
                {
                    dist[v] = dist[minVertex] + distanceMatrix[minVertex][v];
                }
            }
        }

        return dist;
    }
};

class Invoice
{
    public:
   string source;
   string destination;
   string city[8]={"Dubai","USA","UK","Vietnam","canada","Australia","china","India"};
    Invoice()
    {
       source="";
       destination="";
    }
    void shortestDistance(Exporter e,Importer im)
    {
        this->source=e.location;
        this->destination=im.location;
        int sourceVertex, destinationVertex;
        for(int i=0;i<8;i++)
        {
            if(city[i]==source)
            {
                sourceVertex=i;
            }
            if(city[i]==destination)
            {
               destinationVertex=i;
            }


        }

     vector<vector<int> > distanceMatrix =
     {
         {0,   7000, 5000,  6000,   9000,   8000,     5000,  4000},
         {7000, 0,    4000,  9000,   2000,   11000,    9000,  13000},
         {5000, 4000, 0,     8000,   5000,   13000,    8000,  10000},
         {6000, 9000, 8000,  0,      12000,  11000,    4000,  7000},
         {9000, 2000, 5000,  12000,  0,      14000,    13000, 11000},
         {8000, 11000, 13000, 11000, 14000, 0,       13000, 9000},
         {5000, 9000, 8000,  4000,   13000,  13000,    0,     9000},
         {4000, 13000, 10000, 7000,   11000,  9000,     9000,  0}
    };

    ShortestDistance sd(distanceMatrix);
    cout<<RED<<"Exporter details:"<<endl;
     e.printExporter();
     //cout<<"importer details:"<<endl;
     im.printImporter();

    vector<int> shortestDistances = sd.dijkstraShortestDistance(sourceVertex);
     cout<<MAGENTA << "Shortest distance from  " << source << " to destination " << destination << ": "
         << shortestDistances[destinationVertex] << "\n";

      cout<<YELLOW<<"Maximum retail price :"<<im.price<<"$"<<endl;
      if(im.price>2000&&im.price<=5000)
      {
          im.price=im.price*0.2+im.price;
      }
      else if (im.price>5000&&im.price<=7000)
      {
          im.price=im.price*0.4+im.price;
      }
       else
      {
          im.price=im.price*0.5+im.price;
      }
       cout<<YELLOW<<"Total price after adding GST:"<<im.price<<"$"<<endl;


  }
};
int main()
{

    ItemBuilder itemBuilder1;
    ItemBuilder itemBuilder2;
    ItemBuilder itemBuilder3;
    ItemBuilder itemBuilder4;
    ItemBuilder itemBuilder5;

    ItemBuilder* itemBuilders[5] = { &itemBuilder1, &itemBuilder2, &itemBuilder3,&itemBuilder4,&itemBuilder5 };

    // Set attributes for each itemBuilder
    itemBuilder1.setItemType("Resource")->setName("Gold")->setDescription("24 carat")->setPrice(50000);
    itemBuilder2.setItemType("Resource")->setName("Clove")->setDescription("Big clove")->setPrice(100);
    itemBuilder3.setItemType("Goods")->setName("Shampoo")->setDescription("Sunsilk")->setPrice(50);
    itemBuilder4.setItemType("Goods")->setName("Icecream")->setDescription("Amul")->setPrice(30);
    itemBuilder5.setItemType("Resource")->setName("Lithium")->setDescription("Lithium ore")->setPrice(30);

Item* items[3]= { new Resource("Gold","24 carat",50000), new Resource("clove","Big clove",100), new Resource("Shampoo","Sunsilk",50)};

    Exporter e1(3,"Ambani groups","India");

    Warehouse w1("Ambani store house","Delhi",50);

    ModeOfTransport m1("Air ways",50,"DB235");


    cout<<LIGHT_BLUE<<"Enter Importer Details such as country,company name,Qunatity of items "<<endl;
    string country;
    string companyname;
    int n;
    cin>>country;
    cin>>companyname;
    cin>>n;
    Importer im(country,companyname,e1);

    CurrrencyExchange c1;

    Invoice in;

   cout<<CYAN<<"\t\t.............Hello! welcome to Indian Import and Export System........."<<endl;
      int a;
    while(1)
    {
      cout<<GREEN<<"\nclick : 1 To get Warehouse details\n\t2:Exporter detils\n\t3:Importer Details \n\t4: Generate Invoice"<<endl;
      cin>>a;

      switch(a)
      {
          case 1:
          {
              cout<<YELLOW<<"Checks whether capacity is enough in store the items.........."<<endl;
              try {
                     w1.computeCapacity(n);
                     w1.accomadateItems(5, itemBuilders);
                }

             catch(Exception &e)
              {
                 e.showError();
              }
              catch(...)
             {
             cout<<"Default Exception"<<endl;
             }
             cout<<"currenty items present in warehouse"<<endl;
             w1.displayStorage();

          } break;

          case 2:
            {
                cout<<YELLOW<<"Displays the name of Exporter and Total amount of items beign exported"<<endl;
                e1.printExporter();
                e1.printModeOfExport(m1);
                float price = e1.totalPrice(items,n);
                cout<<YELLOW<<"The price of the total items being exported:"<<price<<endl;

            }break;

          case 3:
            {
                cout<<YELLOW<<" Calculates the total amount to be paid in importer's location currency"<<endl;


                im.printImporter();
                im.forex(c1,e1);
            }break;

          case 4:
            {
                cout<<YELLOW<<"Generates invoice including exporter details , importer details and Shortest distance to deliver the items"<<endl;
                in.shortestDistance(e1,im);

            }break;

      }

    }

   return 0;
}