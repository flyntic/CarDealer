#pragma once
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <set>
#include <map>

class Detail
{
private:
	static int CountId;
	int idDetail;
	std::string name;
	std::string type;
	std::string category;

	int price;
	std::string manufactured;
	std::string country;
	bool original;
	std::set < std::string > *setSuitModelsAuto;
	std::string comment;

	int nextAnalog;
	int prevAnalog;
public:

	Detail  (std::string Name, 
		             int Price,
		     std::string Type,
		     std::string Category,
		     std::string Manufactured = "noname", 
		     std::string Country = "no defined", 
		            bool Original = false,
             std::string *SetSuitModelsAuto = nullptr  
             ) :
	  //setSuitModelsAuto{ SetSuitModelsAuto },
		       original{ Original },
	       manufactured{ Manufactured },
		        country{ Country },
		           type{ Type },
		       category{ Category },
		          price{ Price },
		           name{ Name }
	{
		setSuitModelsAuto = new std::set<std::string>;
		if (SetSuitModelsAuto != NULL)
		{
			for(int i=0; ;i++)
			{
				if (SetSuitModelsAuto[i] == "") break;
				setSuitModelsAuto->insert(SetSuitModelsAuto[i]);
			}
		}
		idDetail = ++CountId;
		nextAnalog = -1;
		prevAnalog = -1;

	}

	Detail(  Detail *D, 
		std::string Name,
		        int Price,
		std::string Type,
		std::string Category,
		std::string Manufactured = "noname",
		std::string Country = "no defined",
	           bool Original = false,
		std::string* SetSuitModelsAuto = nullptr
	) :Detail(Name,Price,Type,Category,Manufactured,Country,Original,SetSuitModelsAuto)
	{
		prevAnalog = D->idDetail;
		nextAnalog = D->nextAnalog;
		D->nextAnalog = idDetail;
	
	}

	std::string getName() { return name; }
	std::string getType() { return type; }
	int getPrice() { return price; }
	int getId() { return idDetail; }
	int getNextAnalog() { return nextAnalog; }
	int getPrevAnalog() { return prevAnalog; }

	std::string getModelsAuto()
	{
		if (setSuitModelsAuto != 0)
		{
			std::string out;
			for (auto m = setSuitModelsAuto->begin(); m != setSuitModelsAuto->end();)
			{
				out += *m;
				out += (++m != setSuitModelsAuto->end()) ? ", " : "";
			}
			return out;
		}
		else return "-";
	}

	std::string Print(bool idprint=true,bool typeprint=true,bool categoryprint=false,bool manprint=true, bool origprint=true, bool autoprint=false,bool priceprint=true,std::string format="\n\t\t")
	{

		return  (idprint?std::to_string(idDetail)+ format.c_str()[1]:"")  + (typeprint?type + " " :"") + (categoryprint ? category + " ": "")  + name + format+
			          (manprint? "Производитель " + manufactured + " (" + country + ") ":"") + (original == true ? "оригинал " : "неоригинал ")+
			(autoprint?format + "Модели авто: " + getModelsAuto() :"") + (priceprint?format+ "Цена " + std::to_string(price):"")+format.c_str()[0];
	}

	bool CheckName(std::string str)
	{
		//if (idDetail==2)
		//return true;
		return false;
	}

	bool operator ==( int id)
	{
		return idDetail == id;
	}
	bool operator !=(int id)
	{
		return !(operator==(id));
	}
	friend bool operator==(int id, Detail d)
	{
		return d.operator==(id);
	}
	friend bool operator!=(int id, Detail d)
	{
		return d.operator!=(id);
	}
};

class Catalog
{
private:
	std::set < std::string> SetType;
	std::set < std::string> SetCategory;
	std::map <std::string, std::set<std::string> >  ListTypeInCategory;


	std::vector < Detail*>* Details;

public:

	Catalog()
	{
		Details = new std::vector<Detail*>;
	}

	void Save(std::string jsonfile = NULL)
	{

	}
	//void Add(De) {}

	//void Remove() {}

	int* FindForName(std::string testname,int length_data)//std::vector<Detail*> *findDetails) 
		{
			//bool find = false;
	int* findDetails = new int[length_data+1];
	findDetails[0] = -1;
	int i = 0;
			for(auto d:*Details)
				if (d->CheckName(testname))
				{ 
					findDetails[i++] = d->getId();//->push_back(d);
					if (i > length_data)break;
				}
			findDetails[i] = -1;
			return findDetails;
		}
	    
	int* FindAnalog(int id, int length_data)//std::vector<Detail*> *findDetails) 
	{
		
		int* findDetails = new int[length_data + 1];
		findDetails[0] = -1;
		int i = 0;
		Detail* D=Details->at(id-1);
		while (D->getPrevAnalog() > 0)
		{
			findDetails[i++] = D->getPrevAnalog();
			if (i > length_data)break;
			D = Details->at(D->getPrevAnalog()-1);
		}
	    D = Details->at(id - 1);
		while (D->getNextAnalog() > 0)
		{
			findDetails[i++] = D->getNextAnalog();
			if (i > length_data)break;
			D = Details->at(D->getNextAnalog()-1);
		}
		findDetails[i] = -1;
		return findDetails;
	}

		std::string print()
		{
			std::string str="";
			for(auto d:*Details)
				str += "Деталь : " + (*d).Print();//"  "

			return str;
		}

		std::string print(int idDetail)
		{
			if (idDetail == -1)
				return "Нет такой детали";

			std::string str ;
			for (auto d : *Details)
				if (idDetail==*d) str +=  (*d).Print();
			
			return str;
		}

		void getCategory(std::string* CategorySet, int& length, std::string strfindname = "")
		{

		}

		//void getCategory(std::string* CategorySet, int& length, std::string strfindname = "")
		//{
		//
		//}

		void getType(std::string* CategorySet, int& length, std::string categoryname, std::string strfindname = "")
		{

		}

		bool addCategory(std::string name)
		{
			return true;

		}

		bool addType(std::string name)
		{
			return true;

		}

		bool addListTypeInCategory(std::string nameCategory, std::string  nameType)
		{
			return true;
		}

		bool addDetail(Detail *d)
		{
		
			Details->push_back(d);
			return true;
		}
	
		std::string print(int *idD)
		{
			if (*idD == -1)
				return "Нет таких деталей ";

			std::string str = "";
			for (auto d : *Details)
				for (int *i=idD;*i>0;i++)
					if (*d == *i) { str += "Деталь : " + (*d).Print(); break; }

			return str;
		}

		
};

