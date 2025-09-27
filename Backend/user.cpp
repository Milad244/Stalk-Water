#include <iostream>
#include <string>
using namespace std;

class User
{
private:
    string name;
    double weight; //kg
    string gender;
    double waterLevel; 
    int drinksPerDay;
public:
    //Constructors
    User();
    User(const string&, const double&, const string&, const double&, const int&);
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

    int drinkMore(User u); //returns how much water need to drink more

};
User::User() : name("N/A"), weight(0), gender("N/A"), waterLevel(0.0), drinksPerDay(0) {}
User::User(const string& n, const double& w, const string& g, const double& wl, const int& d) : name(n), weight(w), gender(g), waterLevel(wl), drinksPerDay(d) {}
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
    return waterLevel;
}
int User::getDrinksPerDay() const
{
    return drinksPerDay;
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
void User::printInfo(ostream& cout) const
{
    cout << endl;
    cout << "\tYour Name is " << name << endl;
    cout << "\tYour Weight is " << weight << "kg" << endl;
    cout << "\tYour Gender is " << gender << endl;
    cout << "\tYour WaterLevel is " << waterLevel << endl;
    cout << "\tYou Drinks" << drinksPerDay << "ml in a day" << endl;
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
int drinkMore(User u)
{
    int print = u.getWeight() * 30;
    cout << "You need to drink more" << print << "ml to be healthier !" << endl;
}
int main() {
    User u1;
    cout << "Enter an User";
    cin >> u1;

    drinkMore(u1);
    
    u1.~User();

    system("Pause");
    return 0;

    
}