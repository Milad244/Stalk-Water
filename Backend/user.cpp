#include <iostream>
#include <string>
using namespace std;

struct WaterLog
{
    string date;
    double amount;
};

class User
{
private:
    string name;
    double weight; //kg
    string gender;
    double waterLevel; 
    int drinksPerDay;
    WaterLog logs[100];
    int logCount;

public:
    //Constructors
    User();
    User(const string&, const double&, const string&, const double&, const int&);
    User (const string&, const double&, const string&);
    //Destructor
    ~User();
    //Getters
    string getName() const;
    double getWeight() const;
    string getGender() const;
    double getWaterLevel() const;
    int getDrinksPerDay() const;
    //Setters
    void setName(const string&);
    void setWeight(const double&);
    void setGender(const string&);
    void setWaterLevel(const double&);
    void setDrinksPerDay(const int&);
    //Additional member functions
    void readInfo(istream&);
    void printInfo(ostream&) const;
    //Friend functions
    friend istream& operator>>(istream&, User&);
    friend ostream& operator<<(ostream&, const User&);
    void addDrink(const string& date, double ml);
    int drinkMore()const; //returns how much water need to drink more


};

User::User() : name("N/A"), weight(0), gender("N/A"), waterLevel(0.0), drinksPerDay(0) {}
User::User(const string& n, const double& w, const string& g, const double& wl, const int& d) : name(n), weight(w), gender(g), waterLevel(wl), drinksPerDay(d) {}
User::User (const string& n, const double& w, const string& g):  name(n), weight(w), gender(g){};
User::~User() {}

//Getters
string User::getName() const
{
    return name;
}
double User::getWeight() const
{
    return weight;
}
string User::getGender() const
{
    return gender;
}
double User::getWaterLevel() const
{
    double total = 0;
    for (int i = 0; i < logCount; i++) {
        total += logs[i].amount;
    }
    return total;
}
int User::getDrinksPerDay() const
{
    return logCount;
}

//Setters
void User::setName(const string& n)
{
    name = n;
}
void User::setWeight(const double& w)
{
    weight = w;
}
void User::setGender(const string& g)
{
    gender = g;
}
void User::setWaterLevel(const double& wl)
{
    waterLevel = wl;
}
void User::setDrinksPerDay(const int &d)
{
    drinksPerDay = d;
}
void User::readInfo(istream& cin)
{
    cout << endl;
    cout << "\tEnter your name: ";
    cin >> name;
    cout << "\tEnter your weight: ";
    cin >> weight;
    cout << "\tEnter your gender: ";
    cin >> gender;
}
void User::printInfo(ostream& cout) const {
    cout << "{"
         << "\"name\":\"" << name << "\","
         << "\"weight\":" << weight << ","
         << "\"gender\":\"" << gender << "\","
         << "\"waterNeeded\":" << drinkMore()
         << "}";
}
istream& operator>>(istream &cin, User& u)
{
    u.readInfo(cin);
    return cin;
}
ostream& operator<<(ostream& cout, const User& u)
{
    u.printInfo(cout);
    return cout;
}

void User::addDrink(const string &date, double ml)
{
    if (logCount < 100) { // check capacity
        logs[logCount].date = date;
        logs[logCount].amount = ml;
        logCount++;
    } else {
        cout << "Log is full! Cannot add more than 100 entries." << endl;
    }
}

int User::drinkMore()const
{
    return static_cast<int>(getWeight() * 30); // returns ml
}

int main(int argc, char* argv[]) {
    string name = argc > 1 ? argv[1] : "Jane Doe";
    double weight = argc > 2 ? stod(argv[2]) : 0;
    string gender = argc > 3 ? argv[3] : "N/A";
    double waterLevel = argc > 4 ? stod(argv[4]) : 0.0;
    int drinksPerDay = argc > 5 ? stoi(argv[5]) : 0;
    //User user(name, weight, gender, waterLevel, drinksPerDay); // existing user
    User user (name, weight, gender); // new user

    // output JSON to node.js
    user.printInfo(cout);

    return 0;
    
}