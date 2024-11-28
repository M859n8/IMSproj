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
#define RIDE_CAPACITY 20


Queue EntranceQ("Entrance Queue");
Facility EntranceL[ENTRANCE]; 
// Facility Ride1[Ride1AMOUNT]; 
Queue RegularRideQ1("|Regular 1 Ride Queue");
Queue SingleRideQ1("Single 1 Ride Queue");

Queue RegularRideQ2("|Regular 2 Ride Queue");
Queue SingleRideQ2("Single 2 Ride Queue");

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

