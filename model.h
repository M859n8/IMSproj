#include "simlib.h"
#include <stdio.h>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

const int HIGH_AMOUNT = 5000; //was 7000
const int SUPERHIGH_AMOUNT = 75;
const int MIDDLE_AMOUNT = 50;
const int LOW_AMOUNT = 40;
#define ENTRANCE 30//was 30

// #define Ride1AMOUNT 10//was 30
// #define RIDE_CAPACITY 20 //was 20

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
///id,popul,age,singl,capc,row,time
    {0, 2,false,false, 20, 4, 3000, 5}, // Flying Carpets 1
    {1, 1,true,true, 20, 4, 3000, 7}, // Turtle Coaster 2
    {2, 2,true,true, 36, 6, 3000, 5}, // Toy Soldier 3
    {3, 3,false,false, 28, 2, 3000, 5} // Dog ZigZag 4
    // {4, 1,false,true, 24, 4, 7, 5}, // Ratatouille 5
    // {5, 2,true,true, 20, 4, 5, 5}, //  RC  Racer 6
    // {6, 3,false,false, 20, 2, 5, 5}, // Cars Road Trip 7
    // {7, 1,true,false, 21, 21, 5, 5}, // Tower Terror 8
    // {8, 2,false,true, 20, 4, 5, 5}, // Spider Man 9
    // {9, 2,true, true,24, 2, 5, 5} // Avengers 10
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
// Queue SingleRideQ3("Single 3 Ride Queue");

// Queue RegularRideQ4("|Regular 4 Ride Queue");
// Queue SingleRideQ4("Single 4 Ride Queue");

// Queue RegularRideQ5("|Regular 5 Ride Queue");
// Queue SingleRideQ5("Single 5 Ride Queue");

// Queue RegularRideQ6("|Regular 6 Ride Queue");
// Queue SingleRideQ6("Single 6 Ride Queue");

// Queue RegularRideQ7("|Regular 7 Ride Queue");
// Queue SingleRideQ7("Single 7 Ride Queue");

// Queue RegularRideQ8("|Regular 8 Ride Queue");
// Queue SingleRideQ8("Single 8 Ride Queue");

// Queue RegularRideQ9("|Regular 9 Ride Queue");
// Queue SingleRideQ9("Single 9 Ride Queue");

// Queue RegularRideQ10("|Regular 10 Ride Queue");
// Queue SingleRideQ10("Single 10 Ride Queue");


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