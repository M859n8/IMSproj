#include "simlib.h"
#include <stdio.h>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

const int HIGH_AMOUNT = 70;
const int SUPERHIGH_AMOUNT = 75;
const int MIDDLE_AMOUNT = 50;
const int LOW_AMOUNT = 40;
#define ENTRANCE 3//was 30

// #define Ride1AMOUNT 10//was 30
#define RIDE_CAPACITY 8 //was 20

// Структура для зберігання даних про атракціон
struct Attraction {
    int id;                 // ID атракціону
    int popularity;
    bool isForAdults;       // Чи є обмеження для дорослих
    bool single_rider;
    int capacity;           // Вмісткість
    int people_in_row;
    double rideDuration;    // Тривалість проходження атракціону
};

std::vector<Attraction> attractions = {
///id,popul,age,singl,capc,row,time
    {0, 2,false,false, 20, 4, 5}, // Flying Carpets
    {1, 1,true,true, 20, 4, 7}, // Turtle Coaster  //popular was 1
    {2, 2,true,true, 36, 6, 5}, // Toy Soldier   //single was true
    {3, 3,false,false, 28, 2, 5} // Dog ZigZag
    // {4, 1,false,true, 24, 4, 7}, // Ratatouille
    // {5, 2,true,true, 20, 4, 5}, //  RC  Racer
    // {6, 3,false,false, 20, 2, 5}, // Cars Road Trip
    // {7, 1,true,false, 21, 21, 5}, // Tower Terror
    // {8, 2,false,true, 20, 4, 5}, // Spider Man
    // {9, 2,true, true,24, 2, 5} // Avengers
};


Queue EntranceQ("Entrance Queue");
Facility EntranceL[ENTRANCE]; 
// Facility Ride1[Ride1AMOUNT]; 
Queue SingleRideZero("Single empty  Ride Queue");

Queue RegularRideQ0("Regular 0 Ride Queue");
//Queue SingleRideQ0("Single 1 Ride Queue");

Queue RegularRideQ1("Regular 1 Ride Queue");
Queue SingleRideQ1("Single 1 Ride Queue");

Queue RegularRideQ2("Regular 2 Ride Queue");
Queue SingleRideQ2("Single 2 Ride Queue");

Queue RegularRideQ3("Regular 3 Ride Queue");
Queue SingleRideQ3("Single 3 Ride Queue");


Queue RideQ("Ride Queue");

Stat income("Income from ticket pay");
const double ClOSE_TIME = 10000;

// class Board: public Process {
// public:
//     void Behaviour();
//     void start_boarding();
//     }

// class Ride : public Process {
//     void Behavior();
// }

bool case1 ; //debug only 