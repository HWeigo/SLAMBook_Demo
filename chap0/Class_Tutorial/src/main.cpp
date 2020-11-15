#include <iostream>

using namespace std;

class Car
{
public:
    string brand;
    string model;
    int year;

    void showCarInfo();
    void setCarOwner(string name)
    {
        owner = name;
    }
    string getCarOwner()
    {
        return owner;
    }
    Car();

private:
    string owner;
    int price;
};

Car::Car(void)
{
    brand = "None";
    model = "None";
    year = -1;
    owner = "None";
}

void Car::showCarInfo()
{
    cout << "Brand: " << brand << endl;
    cout << "Model: " << model << endl;
    cout << "Year: " << year << endl;
}

int main()
{
    Car carObj1;

    carObj1.model = "Honda";
    carObj1.model = "Civic";
    carObj1.year = 2020;

    Car carObj2;

    carObj1.showCarInfo();
    carObj2.showCarInfo();

    carObj1.setCarOwner("WeiHuang");
    cout << "Car1's Owner: " << carObj1.getCarOwner() << endl;
    return EXIT_SUCCESS;    
}
