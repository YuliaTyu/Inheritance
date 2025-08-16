#include<iostream>
using namespace std;

class Animal
{
public:
	virtual void Sound() = 0;//чисто-виртуальный метод = 0
};
class Cat: public Animal{};

class Lion : public Cat
{
public:
	void Sound()override
	{
		cout << "PPPPPPP" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Animal animal; ошибки 4326 и 2259 - нельзя создать экземпляр 
	Lion lion;
}