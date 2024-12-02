#include "simlib.h"
#include <stdio.h>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <map>
#include <iostream>

#define ENTRANCE 30//was 30
#define DAY_TICKET_PRICE 135


float timeInQueue = 0;
int AttractionsCount = 0; //test only

// Структура для зберігання даних про атракціон
struct Attraction {
    int id;                 // ID атракціону
    int popularity;
    bool isForAdults;       // Чи є обмеження для дорослих
    bool single_rider;
    int capacity;           // Вмісткість
    int people_in_row;
    double rideDuration;    // Тривалість проходження атракціону
    int price;
};

std::vector<Attraction> attractions = {
///id,popul,age,singl,capc,rowC,time,price
    {0, 2,false,false, 20, 4, 300, 5}, // Flying Carpets 1  //nopremieracc
    {1, 1,true,true, 20, 4, 300, 21}, // Turtle Coaster 2
    {2, 2,true,true, 36, 6, 300, 5}, // Toy Soldier 3  //nopremieracc
    {3, 3,false,false, 28, 2, 300, 5}, // Dog ZigZag 4 //nopremieracc
    {4, 1,false,true, 24, 4, 7*60, 14}, // Ratatouille 5
    {5, 2,true,true, 20, 4, 5*60, 5}, //  RC  Racer 6 //nopremieracc
    {6, 3,false,false, 20, 2, 5*60, 5}, // Cars Road Trip 7
    {7, 1,true,false, 21, 21, 5*60, 14}, // Tower Terror 8
    {8, 2,false,true, 20, 4, 5*60, 16}, // Spider Man 9
    {9, 2,true, true,24, 2, 5*60, 12} // Avengers 10
};


std::map<std::string, int> seasonSettings = {
    {"spring", 7000},
    {"summer", 7500}, 
    {"autumn", 5000}, 
    {"winter", 4500}   
};



Queue EntranceQ("Entrance Queue");
Facility EntranceL[ENTRANCE]; 
Queue SingleRideZero("Single empty  Ride Queue");

Queue RegularRideQ0("Regular 0 Ride Queue");

Queue RegularRideQ1("Regular 1 Ride Queue");
Queue SingleRideQ1("Single 1 Ride Queue");

Queue RegularRideQ2("Regular 2 Ride Queue");
Queue SingleRideQ2("Single 2 Ride Queue");

Queue RegularRideQ3("Regular 3 Ride Queue");

Queue RegularRideQ4("Regular 4 Ride Queue");
Queue SingleRideQ4("Single 4 Ride Queue");

Queue RegularRideQ5("Regular 5 Ride Queue");
Queue SingleRideQ5("Single 5 Ride Queue");

Queue RegularRideQ6("Regular 6 Ride Queue");

Queue RegularRideQ7("Regular 7 Ride Queue");

Queue RegularRideQ8("Regular 8 Ride Queue");
Queue SingleRideQ8("Single 8 Ride Queue");

Queue RegularRideQ9("Regular 9 Ride Queue");
Queue SingleRideQ9("Single 9 Ride Queue");





Stat income0("Income from ticket pay attraction 0");
Stat income1("Income from ticket pay attraction 1");
Stat income2("Income from ticket pay attraction 2");
Stat income3("Income from ticket pay attraction 3");
Stat income4("Income from ticket pay attraction 4");
Stat income5("Income from ticket pay attraction 5");
Stat income6("Income from ticket pay attraction 6");
Stat income7("Income from ticket pay attraction 7");
Stat income8("Income from ticket pay attraction 8");
Stat income9("Income from ticket pay attraction 9");



const double ClOSE_TIME = 43000; //~12h

// class Board: public Process {
// public:
//     void Behaviour();
//     void start_boarding();
//     }

// class Ride : public Process {
//     void Behavior();
// }

