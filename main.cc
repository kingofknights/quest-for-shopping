#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

template<typename KeyType, typename ValueType>
std::pair<KeyType, ValueType> get_max( const std::map<KeyType, ValueType>& x )
{
	using pairtype = std::pair<KeyType, ValueType>;
	return *std::max_element(x.begin(), x.end(), [] (const pairtype & p1, const pairtype & p2)
	{
		return p1.second > p2.second;
	});
}


struct iteminfo
{
	int shopnumber;
	float pricelist;
	std::string nameofitem;
};

class Shopping
{
public:
	Shopping() {};
	~Shopping() {};
private:
	std::string itemname;
	int shopnum;
	float price;
	signed int numOfItemtoShop;
	std::vector<std::string> ItemWannaShop;
	std::vector<iteminfo> vectrofstruct;

public:
	void ReadCSVfileSepratedByComma(std::string);
	void ReadCSVfileSepratedByTab(std::string);
	void GoShopping();
	void SearchShopWithItem(std::string);
	void DisplayShopName();
	void GetCheapPrice();
};

void
Shopping::ReadCSVfileSepratedByTab(std::string filename)
{
	std::ifstream file;
	file.open(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "File cant be open" << std::endl;
	}
	else
	{
		while (file.good())
		{
			file >> shopnum >> price >> itemname;
			std::cout << shopnum << '\t' << price << '\t' << itemname << std::endl;
		}
	}
	file.close();
	return;
}

void
Shopping::ReadCSVfileSepratedByComma(std::string filename)
{
	std::string shopnum, price, itemname;
	std::ifstream file;
	file.open(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "File cant be open" << std::endl;
	}
	else
	{
		while (file.good())
		{
			getline(file, shopnum, ',');
			getline(file, price, ',');
			getline(file, itemname);
			std::cout << shopnum.c_str() << '\t' << price.c_str() << '\t' << itemname << std::endl;

		}
	}
	file.close();
	return;
}

void
Shopping::GoShopping()
{
	std::cout << "Number of Item to shop :";
	std::cin >> numOfItemtoShop;
	while (numOfItemtoShop != 0)
	{
		std::cout << "Enter Item name:";
		std::cin >> itemname;
		ItemWannaShop.push_back(itemname);
		numOfItemtoShop--;
	}
	return;
}
int x = 0;
void
Shopping::SearchShopWithItem(std::string filename)
{

	for (std::vector<std::string>::iterator it = ItemWannaShop.begin(); it != ItemWannaShop.end(); ++it)
	{
		std::ifstream file;
		file.open(filename.c_str());
		if (!file.is_open())
		{
			std::cerr << "File cant be open" << std::endl;
		}
		else
		{
			while (file.good())
			{
				file >> shopnum >> price >> itemname;
				if (*it == itemname)
				{
					vectrofstruct.push_back(iteminfo());
					vectrofstruct[x].shopnumber = shopnum;
					vectrofstruct[x].pricelist = price;
					vectrofstruct[x].nameofitem = itemname;

					x++;
				}
			}
		}
		file.close();

	}
	return;
}

void
Shopping::DisplayShopName()
{
	for (int i = 0; i < x; ++i)
	{
		std::cout << vectrofstruct[i].shopnumber << '\t'
		          << vectrofstruct[i].pricelist << '\t'
		          << vectrofstruct[i].nameofitem << std::endl;

	}
	GetCheapPrice();
	return;
}


void
Shopping::GetCheapPrice()
{	float temp = -1; int temp2;
	for (int i = 0; i < x; ++i)
	{
		for (int j = i; j < x; ++j)
		{
			if (vectrofstruct[i].nameofitem != vectrofstruct[j].nameofitem &&
			        vectrofstruct[i].shopnumber == vectrofstruct[j].shopnumber)
			{
				temp = vectrofstruct[i].pricelist + vectrofstruct[j].pricelist;
				temp2 = vectrofstruct[i].shopnumber;

			}
		}
	}
	if (temp > 0)
	{
		std::cout << temp2 << '\t' << temp << std::endl;
	}
	else
		std::cout << "none" << std::endl;
	return;
}



int main(int argc, char *argv[])
{
	std::string filename = argv[1];
	// std::cin >> filename;
	Shopping s;
	s.ReadCSVfileSepratedByTab(filename);
	s.GoShopping();
	s.SearchShopWithItem(filename);
	// s.DisplayShopName();
	s.GetCheapPrice();
	return 0;
}



