#include <iostream>  
#include <string>     
using namespace std;  

//================ USER CLASS =================//
// User class banai jo sign up, login aur user count handle karegi
class User {
private:
    string name,email,password;  
public:
    static int userCount;        // Total users count track karne ke liye

    User(string n="",string e="",string p="")  // Constructor, default values empty
    { 
        name=n; 
        email=e;
        password=p; 
        userCount++; // User create hone par count increment
    }

    void signUp()  // Sign up function
    {    
        cout<<"---- Sign Up ---\n";  
        cout<<"Name: ";  
        cin>>name;  
        cout<<"Email: "; 
        cin>>email; 
        cout<<"Password: "; 
        cin>>password; 
        cout<<"Account Created Successfully!\n"; 
    }

    bool login()  // Login function
    {     
        cout<<"---- Login -----\n";
        string e,p;  // Temporary variables for input
        cout<<"Email: "; 
        cin>>e; 
        cout<<"Password: ";
        cin>>p; 
        if(e!=email||p!=password)  // Credentials check
        {
            cout<<"Login Failed!\n";  
            return false;  
        }
        cout<<"Login Successful: "<<name<<endl; 
        return true;
    }
    string getName()  // Name return function
    { 
        return name; 
    }
    static void showUserCount()  // Total users show
    { 
        cout<<"Total Users: "<<userCount<<endl; 
    }
    // Virtual function for overriding  Polymorphism (Run-time)
    virtual void role() { 
	    cout<<"Generic User\n";
	 } 
};
int User::userCount=0; // Static variable initialize

//================ CUSTOMER CLASS =================//
// Customer class, User se inherit karti hai
class Customer:public User{
    string address; 
public:
    void setAddress()  
    {  
        cout<<"Enter Address: "; 
        cin>>address; 
    }

    string getAddress()  
    { 
        return address; 
    }
    void role()  override// Overriding User ka virtual function Polymorphism (Run-time)
	{ 
        cout<<"Role: Customer\n"; 
    }
};

//================ RIDER CLASS =================//
// Rider class, User se inherit kare, delivery track kare
class Rider:public User{
    string location;   // Current location
    int timeLeft;      // Delivery time
    string riderName;  // Rider ka naam
public:
    Rider(string n="Ali")  // Constructor default name
    {  
        location="Restaurant"; 
        timeLeft=40; 
        riderName=n; 
    }

    void moveCloser(string loc, int reduce)
	 {
        location = loc;          // Location update
        timeLeft -= reduce;      // Time reduce
        if(timeLeft < 0)
		    timeLeft = 0; // Negative time avoid
        cout << "\nRider: " << riderName << endl; // Rider ka naam display
        cout << "Current Location: " << location << endl; // Location display
        cout << "Time Left: " << timeLeft << " minutes" << endl; // Remaining time display
    }

    void role() override // Overriding User ka virtual function Polymorphism (Run-time)
    { 
        cout<<"Rider is Available"; 
    }
};

//================ MENU ITEM CLASS =================//
// MenuItem class, har item ka naam aur price store
class MenuItem{
    string name; // Item name
    int price;   // Item price
public:
    MenuItem(string n="",int p=0)  // Constructor
    { 
        name=n; 
        price=p; 
    }

    string getName()  // Item name return
    { 
        return name; 
    }

    int getPrice()  // Price return
    { 
        return price; 
    }

    void showItem()  // Item print
    { 
        cout<<name<<" - Rs."<<price<<endl; 
    }
};

//================ LOCATION CLASS =================//
// Location class, location ka naam store aur show
class Location{
    string name; // Location name
public:
    Location(string n="")  
	{// Constructor
        name=n; 
    }
    string getName() 
	{ // Name return
        return name; 
    }
    void showLocation() 
	 {   // Name print 
        cout<<name<<endl; 
    }
};

//================ RESTAURANT CLASS =================//
// Restaurant class, naam aur 5 menu items store
class Restaurant{
public:
    string name; // Restaurant name
    MenuItem items[5]; // MenuItem ek alag class hai (jisme item ka naam aur price hotY hai)

    Restaurant(string n="")
	 {  // Constructor 
        name=n; 
    }
    void setMenu(MenuItem menu[5]) 
	 {  // Menu set function 
        for(int i=0;i<5;i++) 
		    items[i]=menu[i]; // Menu assign
    }

    void showMenu()  
	{  // Menu print function 
        cout<<"\nMenu of "<<name<<endl; 
        for(int i=0;i<5;i++)
            cout<<i+1<<". "<<items[i].getName()<<" - Rs."<<items[i].getPrice()<<endl; // Each item print
    }
};

//================ CART CLASS =================//
// Cart class, items aur total track karne ke liye
class Cart{
	public:
    string names[10],addr[10]; 
    int qty[10],price[10],count; // Quantity, price aur (count ab tak kitne items add ho chuke)
    string customerAddress; 
public:
    Cart() 
	 { // Constructor initialize
        count=0; 
    }

    void add(string n,int q,int p,string a) 
	 { // Item add function
        names[count]=n; // count batata hai ki array me agla empty position kaunsa hai.
        qty[count]=q;
        price[count]=p;
        addr[count]=a;
        customerAddress=a;
        count++;
        cout<<q<<" x "<<n<<" added to cart.\n"; 
    }

    void show() {  // Cart show
        int total=0;
        cout<<"\n----- CART -----\n"; 
        for(int i=0;i<count;i++){
            cout<<"Item: "<<names[i]<<"\n"; 
            cout<<"Quantity: "<<qty[i]<<"\n"; 
            cout<<"Price: Rs."<<price[i]<<" each\n"; 
            total+=qty[i]*price[i]; // Total calculate
        }
        cout<<"Total Bill: Rs."<<total<<"\n"; // Total print
        cout<<"Address: "<<customerAddress<<"\n"; // Address print
        cout<<"----------------\n";
    }

    int getTotal()  
	{ // Total amount return 
        int total=0;
        for(int i=0;i<count;i++)
		    total+=qty[i]*price[i];
        return total;
    }
};

//================ PAYMENT CLASS =================//
// Payment class, payment method choose
class Payment{
public:
    void makePayment(int amount) 
	  {// Payment function
        int choice;
        cout << "\nChoose Payment Method:" << endl;
        cout << "1. Cash on Delivery" << endl;
        cout << "2. Card" << endl;
        cout << "Choice: ";
        cin >> choice;  

        try {
            if(choice == 1)
			 {
                cout << "Cash on Delivery Selected\n";
            } else if(choice == 2) 
			{
                cout << "Card Payment Selected\n";
            } else {
                throw "Invalid choice!";  
            }
        }
        catch(const char* msg) 
		{
            cout << msg << endl;  // Error message print
        }

    }
};

//================ FEEDBACK CLASS =================//
// Feedback class, rating aur comments input
class Feedback{
public:
    void giveFeedback() 
	{
        int rating; 
        string comment;
        cout<<"\nPlease provide feedback for your order:\n";
        cout<<"Rating (1-5): "; 
        cin>>rating; 
        cin.ignore();
        cout<<"Comments: "; 
        getline(cin,comment); 
        cout<<"Thank you for your feedback!\nRating: "<<rating<<"/5 | Comment: "<<comment<<endl; 
    }
};

//================ MAIN FUNCTION =================//
int main() 
{
    cout<<"===== ONLINE FOOD DELIVERY SIMULATOR =====\n\n"; 

    Customer c; // Customer object
    c.signUp(); // Sign up
    c.setAddress(); // Address input
    if(!c.login()) return 0; // Login check
    c.role(); // Role show

    Rider r; // Rider object
    r.role(); // Rider role

    //Location class array object
    Location locations[5]={ 
        Location("Clifton"),
        Location("Gulshan"),
        Location("Defence"),
        Location("North Nazimabad"),
        Location("PECHS")
    };

    int locChoice;
    cout<<"\nSelect Your Location:\n";
    for(int i=0;i<5;i++)
        cout<<i+1<<". "<<locations[i].getName()<<endl;
    cin>>locChoice;

    cout<<"\nRestaurants in "<<locations[locChoice-1].getName()<<":\n";
    
    //Resturant class ka array object
    Restaurant rest[5]={ 
        Restaurant("KFC"),
        Restaurant("Pizza Max"),
        Restaurant("Student Biryani"),
        Restaurant("Chinese Wok"),
        Restaurant("BBQ Tonight")
    };
   //Menuitem class k array object
    MenuItem kfcMenu[5]={ 
        MenuItem("Zinger Burger",550),
        MenuItem("Twister",450),
        MenuItem("Fries",300),
        MenuItem("Coleslaw",150),
        MenuItem("Soft Drink",100)
    };
    rest[0].setMenu(kfcMenu);

    MenuItem pizzaMenu[5]={ 
        MenuItem("Pepperoni",700),
        MenuItem("Margherita",650),
        MenuItem("Garlic Bread",200),
        MenuItem("Chicken Wings",400),
        MenuItem("Soft Drink",150)
    };
    rest[1].setMenu(pizzaMenu);

    MenuItem biryaniMenu[5]={ 
        MenuItem("Chicken Biryani",500),
        MenuItem("Beef Biryani",550),
        MenuItem("Mutton Biryani",600),
        MenuItem("Raita",100),
        MenuItem("Salad",150)
    };
    rest[2].setMenu(biryaniMenu);

    MenuItem chineseMenu[5]={ 
        MenuItem("Kung Pao Chicken",600),
        MenuItem("Sweet & Sour Pork",650),
        MenuItem("Fried Rice",350),
        MenuItem("Spring Roll",200),
        MenuItem("Soup",150)
    };
    rest[3].setMenu(chineseMenu);

    MenuItem bbqMenu[5]={ 
        MenuItem("BBQ Chicken",800),
        MenuItem("BBQ Ribs",900),
        MenuItem("Grilled Fish",700),
        MenuItem("Fries",300),
        MenuItem("Soft Drink",150)
    };
    rest[4].setMenu(bbqMenu);

    // Restaurants list print
    for(int i=0;i<5;i++)
        cout<<i+1<<". "<<rest[i].name<<endl;

    int restChoice; 
    cin>>restChoice; 
    cin.ignore(); // User select restaurant

    rest[restChoice-1].showMenu(); // Menu show

    Cart cart; // Cart object
    char more='y';
    while(more=='y')  // Loop for multiple items
    {
        int it,q;
        cout<<"Select item: ";
        cin>>it;
        cout<<"Quantity: ";
        cin>>q;
        cin.ignore();

        cart.add(                                     
            rest[restChoice-1].items[it-1].getName(), //rest = saare restaurants ka array 
            q,                                       // Selected restaurant ka selected item ka name
            rest[restChoice-1].items[it-1].getPrice(), // Item ka price
            c.getAddress()                           // Customer ka address
        ); 

        cout<<"Add more items? (y/n): "; 
        cin>>more;
        cin.ignore(); 
        // input buffer clear kar rahe hain
    }

    cart.show(); // Cart show

    Payment pay; // Payment object
    pay.makePayment(cart.getTotal()); // Payment process

    string route[4]={"Restaurant","Main Road","Sector 5","Customer Home"}; // Delivery route
    int reduceTime[4] = {5,10,15,10};
    for(int i=0;i<4;i++)                               
        r.moveCloser(route[i], reduceTime[i]);              

    cout<<"\nOrder Delivered Successfully!\n"; // Delivery complete

    Feedback f;
    f.giveFeedback(); // Feedback input

    User::showUserCount(); // Total users show

    cout<<"\nThanks for using the Online Food Delivery Simulator!\n"; // End message
}

