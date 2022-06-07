// ConsoleCarDealer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Detail.h"


int main()
{
    setlocale(LC_ALL, "Russian");
    Catalog *catalog=new Catalog();
    std::set<std::string>* Models;
    Detail *d=new Detail(
             "NOKIAN WR C VAN 195/65 R16C 104/102S",
             10800,
             "Шины",
             "Колесо",
             "NOKIAN"
             
             );
    catalog->addDetail(d);
    
    d = new Detail(d,
        "HANKOOK WINTER I*CEPT IZ 2 W616 205/55 R16 94T",
        9600,
        "Шины",
        "Колесо",
        "HANKOOK"
    );
    catalog->addDetail(d);

 
    d = new Detail(
        "PROMA PREMIER 7X17/5X114.3 D67.1 ET35 NERO",
        10300,
        "Диски",
        "Колеса",
        "PROMA",
        "Китай",
        true
    //     Models
    );
    catalog->addDetail(d);

    
    d = new Detail(d,
        "REPLAY B208 8X18/5X112 D66.6 ET30 S",
        15300,
        "Диски",
        "Колеса",
        "REPLAY",
        "Италия",
        true,

        new std::string[6]{ "ix","SPORTAGE 1.0", "IX55", "SPORTAGE 2.0","Запорожец","" }

    );

    catalog->addDetail(d);

    std::cout << catalog->print();
    std::cout << "Элемент 2 :\n" << catalog->print(-1)<<"\n";

    std::cout <<"\nРезультат поиска :\n"<< catalog->print(catalog->FindForName("1", 10));

    std::cout << "\nРезультат поиска аналога детали 2 :\n" << catalog->print(catalog->FindAnalog(2, 10));

    std::cout << "\nРезультат поиска аналога детали 3 :\n" << catalog->print(catalog->FindAnalog(3,10));
}

