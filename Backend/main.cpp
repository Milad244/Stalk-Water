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
    User(const string&, const double&, const string&);
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

    int drinkMore(User u); //returns how much water need to drink more

};

User::User() : name("N/A"), weight(0), gender("N/A") {}
User::User(const string& n, const double& w, const string& g) : name(n), weight(w), gender(g) {}
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
int drinkMore(User u)
{
    int print = u.getWeight() * 30;
    cout << "You need to drink more" << print << "ml" << endl;
}

int main() {

    
}

