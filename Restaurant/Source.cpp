#include<iostream>
#include<Windows.h>
#include<assert.h>
#include<string>
#include<conio.h>
enum Colors
{
	RED=12,WHITE=15,GREEN=10,YELLOW=14,CYAN=11,BLUE=9
};

class Menu
{
	int id;
	std::string name;
	double menu_rating;
	std::string category;
	double price;
	double tax;
public:
	static int myid;
	Menu():name(""),menu_rating(0),category(""),price(0),tax(0){}
	Menu(std::string name,std::string category,double menu_rating,double price,double tax)
	{
		setID();
		setName(name);
		setMenuRating(menu_rating);
		setCategory(category);
		setPrice(price);
		setTax(tax);
	}
	//Setter
	void setID()
	{
		id = ++myid;
	}
	void setID(int id)
	{
		this->id = id;
	}
	void setName(std::string name)
	{
		assert(name != "");
		this->name = name;
	}
	void setMenuRating(double menu_rating)
	{
		assert(menu_rating >= 0||menu_rating<=10);
		this->menu_rating = menu_rating;
	}
	void setCategory(std::string category)
	{
		assert(category != "");
		this->category = category;
	}
	void setPrice(double price)
	{
		assert(price > 0);
		this->price = price;
	}
	void setTax(double tax)
	{
		assert(tax >= 0);
		this->tax = tax;
	}
	//Getter
	int getID()const
	{
		return id;
	}
	std::string getName()const
	{
		return name;
	}
	double getMenuRating()const
	{
		return menu_rating;
	}
	std::string getCategory()const
	{
		return category;
	}
	double getPrice()const
	{
		return price;
	}
	double getTax()const
	{
		return tax;
	}
	//Show
	void Show()const
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		std::cout << "==========================================\n";
		std::cout << "ID: ";
		SetConsoleTextAttribute(hConsole,BLUE);
		std::cout << getID() << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);
		std::cout << "Name: ";
		SetConsoleTextAttribute(hConsole,CYAN );
		std::cout << getName() << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);
		std::cout << "Category: ";
		SetConsoleTextAttribute(hConsole, CYAN);
		std::cout << getCategory() << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);
		std::cout << "Menu Rating: ";
		if (getMenuRating() < 5)
		{
			SetConsoleTextAttribute(hConsole, RED);
		}
		else if (getMenuRating() < 8)
		{
			SetConsoleTextAttribute(hConsole,YELLOW );
		}
		else
		{
			SetConsoleTextAttribute(hConsole,GREEN );

		}
		std::cout << getMenuRating() << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);
		std::cout << "Price: ";
		SetConsoleTextAttribute(hConsole, CYAN );
		std::cout << getPrice() << " $" << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);
		std::cout << "Tax: ";
		SetConsoleTextAttribute(hConsole, CYAN);
		std::cout << getTax() << " %" << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	//operator overload
	Menu& operator++(int)
	{
		if (menu_rating < 10)
		{
			this->menu_rating++;
		}
		else 
		{
			std::cout << "Menu rating can't be more than 10." << std::endl;
		}
		return *this;
	}
	Menu& operator--(int)
	{
		if (menu_rating > 0)
		{
			this->menu_rating--;
		}
		else
		{
			std::cout << "Menu rating can't be less than 0." <<std:: endl;
		}

		return *this;
	}
	friend std::ostream& operator << (std::ostream & out, const Menu & menu);
	friend std::istream& operator>>(std::istream& in,Menu& menu);
};

std::ostream& operator << (std::ostream& out, const Menu& menu)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	out << "==========================================\n";
	out << "ID: ";
	SetConsoleTextAttribute(hConsole, BLUE);
	out << menu.id << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	out << "Name: ";
	SetConsoleTextAttribute(hConsole, CYAN);
	out << menu.name << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	out << "Category: ";
	SetConsoleTextAttribute(hConsole, CYAN);
	out << menu.category << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	out << "Menu Rating: ";
	if (menu.menu_rating < 5)
	{
		SetConsoleTextAttribute(hConsole, RED);
	}
	else if (menu.menu_rating < 8)
	{
		SetConsoleTextAttribute(hConsole, YELLOW);
	}
	else
	{
		SetConsoleTextAttribute(hConsole, GREEN);

	}
	out << menu.menu_rating << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	out << "Price: ";
	SetConsoleTextAttribute(hConsole, CYAN);
	out << menu.price << " $" << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	out << "Tax: ";
	SetConsoleTextAttribute(hConsole, CYAN);
	out << menu.tax << " %" << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	return out;
}
std::istream& operator>>(std::istream& in,Menu& menu)
{
	menu.setID(menu.getID()+1);
	std::string temp;
	std::cout << "Enter Dish Name: ";
	getline(in,temp);
	menu.name = temp;
	std::cout << "Enter Dish Category: ";
	getline(in, temp);
	menu.category=temp;
	std::cout << "Enter Menu Rating: ";
	in >> menu.menu_rating;
	std::cout << "Enter Price: ";
	in >> menu.price;
	std::cout << "Enter Tax: ";
	in >> menu.tax;
	return in;
}

int Menu::myid = 0;

class Restaurant
{
	std::string name;
	std::string address;
	std::string phone_number;
	double rating;
	double avrgcost;
	int max_menu_count;
	Menu** menu;
public:
	static int restaurant_no;
	Restaurant():name(""),address(""),phone_number(""),rating(0),avrgcost(0),max_menu_count(0),menu(nullptr){}
	Restaurant(std::string name,std::string address,std::string phone_number, int max_menu_count,Menu**menu)
	{
		setName(name);
		setAddress(address);
		setPhoneNumber(phone_number);
		setMaxMenuCount(max_menu_count);
		setMenu(menu);
		CalculateRating();
		CalculateAvarageCost();
	}
	//Calculate
	void CalculateRating()
	{
		double temp=0;
		for (size_t i = 0; i < max_menu_count; i++)
		{
			temp += menu[i]->getMenuRating();
		}
		setRating(temp / max_menu_count);
	}
	void CalculateAvarageCost()
	{
		double temp=0;
		for (size_t i = 0; i < max_menu_count; i++)
		{
			temp += menu[i]->getPrice();
		}
		setAverageCost(temp / max_menu_count);
	}
	//Setter
	void setName(std::string name)
	{
		assert(name != "");
		this->name = name;
	}
	void setAddress(std::string address)
	{
		assert(address != "");
		this->address = address;
	}
	void setPhoneNumber(std::string phone_number)
	{
		assert(phone_number != "");
		this->phone_number = phone_number;
	}
	void setRating(double rating)
	{
		this->rating = rating;
	}
	void setAverageCost(double avrgcost)
	{
		this->avrgcost = avrgcost;
	}
	void setMaxMenuCount(int max_menu_count)
	{
		this->max_menu_count = max_menu_count;
	}
	void setMenu(Menu**menu)
	{
		this->menu = new Menu * [this->max_menu_count];
		for (size_t i = 0; i < this->max_menu_count; i++)
		{
			this->menu[i] = new Menu(*menu[i]);
		}
	}
	//Getter
	std::string getName()const
	{
		return name;
	}
	std::string getAddress()const
	{
		return address;
	}
	std::string getPhoneNumber()const
	{
		return phone_number;
	}
	double getRating()const
	{
		return rating;
	}
	double getAverageCost()const
	{
		return avrgcost;
	}
	double getMaxMenuCount()const
	{
		return max_menu_count;
	}
	Menu** getMenu()const
	{
		return menu;
	}
	//
	void addMenu(Menu& menu)
	{
		size_t new_size = getMaxMenuCount() + 1;
		auto new_menu = new Menu * [new_size];
		if (new_size - 1)
		{
			for (size_t i = 0; i < new_size - 1; i++)
			{
				new_menu[i] = new Menu;
				*new_menu[i] = std::move(*this->menu[i]);
			}
		}
		new_menu[new_size - 1] = new Menu(menu);
		this->menu = new_menu;
		setMaxMenuCount(new_size);
		CalculateRating();
		CalculateAvarageCost();
		sortMenu(true);
	}
	void deleteMenu(int id) 
	{
		assert(id > 0);
		size_t new_size = getMaxMenuCount() - 1;

		auto new_menu = new Menu * [new_size];

		if (new_size != 0)
		{
			for (size_t i = 0, j = 0; i <new_size+1; i++)
			{
				if (id != menu[i]->getID())
				{
					new_menu[j] = new Menu;
					*new_menu[j] = std::move(*menu[i]);
					j++;
				}
				else
				{
					delete menu[i];
					menu[i] = nullptr;
				}
			}
		}
		else
		{
			delete menu[0];
			menu[0] = nullptr;
			new_menu = nullptr;
		}

		this->max_menu_count = new_size;
		this->menu = new_menu;
		CalculateRating();
		CalculateAvarageCost();
		sortMenu(true);
	}
	void updateMenu(int id)
	{
		assert(id > 0);
		for (size_t i = 0; i < max_menu_count; i++)
		{
			if (id == menu[i]->getID())
			{
				menu[i]->setID(menu[i]->getID() - 1);
				std::cin >> *menu[i];
				CalculateRating();
				CalculateAvarageCost();
				sortMenu(true);
			}
		}
		CalculateRating();
		CalculateAvarageCost();
		sortMenu(true);
	}
	void increaseMenuRating(int id)
	{
		for (size_t i = 0; i < max_menu_count; i++)
		{
			if (id == menu[i]->getID())
			{
				(*menu[i])++;
				CalculateRating();
				sortMenu(true);
			}
		}
	}
	void decreaseMenuRating(int id)
	{
		for (size_t i = 0; i < max_menu_count; i++)
		{
			if (id == menu[i]->getID())
			{
				(*menu[i])--;
				CalculateRating();
				sortMenu(true);
			}
		}
	}
	void sortMenu(bool reverse = false)
	{
		if (reverse)
		{
			for (size_t i = 0, length = getMaxMenuCount() - 1; i < length; i++)
			{
				bool swapped = false;
				for (size_t j = 0; j < length; j++)
				{
					if (menu[j]->getMenuRating() < menu[j + 1]->getMenuRating())
					{
						auto tmp = new Menu(std::move(*menu[j + 1]));
						*menu[j + 1] = std::move(*menu[j]);
						*menu[j] = std::move(*tmp);

						if (!swapped)
							swapped = true;
					}
				}

				if (!swapped)
					break;
			}
		}
		else
		{
			for (size_t i = 0, length = getMaxMenuCount() - 1; i < length; i++)
			{
				bool swapped = false;
				for (size_t j = 0; j < length; j++)
				{
					if (menu[j]->getMenuRating() > menu[j + 1]->getMenuRating())
					{
						auto tmp = new Menu(std::move(*menu[j + 1]));
						*menu[j + 1] = std::move(*menu[j]);
						*menu[j] = std::move(*tmp);

						if (!swapped)
							swapped = true;
					}
				}

				if (!swapped)
					break;
			}
		}
	}
	~Restaurant()
	{
		for (size_t i = 0; i < max_menu_count; i++)
		{
			delete[]menu[i];
		}
		delete[] menu;
	}
	friend std::ostream& operator << (std::ostream& out, Restaurant& res);
	friend std::istream& operator>>(std::istream& in, Restaurant& res);
};

std::ostream& operator << (std::ostream& out, Restaurant& res)
{
	res.sortMenu(true);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	out << "Restaurnt Name: ";
	SetConsoleTextAttribute(hConsole, CYAN);
	out << res.name << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	out << "Restaurant Address: ";
	SetConsoleTextAttribute(hConsole, CYAN);
	out << res.address << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	out << "Phone Number: ";
	SetConsoleTextAttribute(hConsole, CYAN);
	out << res.phone_number << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	out << "Rating: ";
	if (res.rating < 5)
	{
		SetConsoleTextAttribute(hConsole, RED);
	}
	else if (res.rating < 8)
	{
		SetConsoleTextAttribute(hConsole, YELLOW);
	}
	else
	{
		SetConsoleTextAttribute(hConsole, GREEN);

	}
	out << res.rating << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	out << "Average Cost: ";
	SetConsoleTextAttribute(hConsole, CYAN);
	out << res.avrgcost << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	out << "Max Menu Count: ";
	SetConsoleTextAttribute(hConsole, CYAN);
	out << res.max_menu_count << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	for (size_t i = 0; i < res.max_menu_count; i++)
	{
		out << *res.menu[i] << std::endl;
	}
	return out;
}
std::istream& operator>>(std::istream& in, Restaurant& res)
{
	std::string temp;
	std::cout << "Enter Restaurant Name: ";
	getline(in, temp);
	res.name = temp;
	std::cout << "Enter Restaurant Address: ";
	getline(in, temp);
	res.address = temp;
	std::cout << "Eneter Phone Number: ";
	getline(in, temp);
	res.address = temp;
	std::cout << "Enter Max Menu Count: ";
	in >> res.max_menu_count;
	for (size_t i = 0; i < res.max_menu_count; i++)
	{
		in >> *res.menu[i];
	}
	return in; 
}

int Restaurant::restaurant_no = 0;

int main()
{
	Menu* m  = new Menu("Lule kabab", "Kabab", 8.4, 10, 30);
	Menu* m2 = new Menu("Borsh ","Shorba",1,5,10);
	Menu* m3 = new Menu("Yumurta(Qaynadilmish)", "Qelyan-alti", 7.6, 1.5, 10);
	Menu* m4 = new Menu("Dolma", "Isti yemek", 6.8, 10, 15);
	Menu* m5 = new Menu("Plov", "Isti yemek", 10, 15, 20);
	Menu* m6 = new Menu("Choban", "Salat", 6.4, 2.5, 12);
	int max_menu_count = 5;
	Menu** menu = new Menu * [max_menu_count] {m, m2, m3, m4, m5};
	Restaurant* res = new Restaurant("Zeferan", "Zaxid xelilov 84", "+994 55 555 55 55", max_menu_count, menu);
	std::cout << *res;
	/*res->addMenu(*m6);
	res->updateMenu(2);
	res->deleteMenu(3);
	res->increaseMenuRating(4);
	res->decreaseMenuRating(5);*/
	return 0; 
}
	