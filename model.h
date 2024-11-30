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

Queue RegularRideQ3("|Regular 3 Ride Queue");
Queue SingleRideQ3("Single 3 Ride Queue");

Queue RegularRideQ4("|Regular 4 Ride Queue");
Queue SingleRideQ4("Single 4 Ride Queue");

Queue RegularRideQ5("|Regular 5 Ride Queue");
Queue SingleRideQ5("Single 5 Ride Queue");

Queue RegularRideQ6("|Regular 6 Ride Queue");
Queue SingleRideQ6("Single 6 Ride Queue");

Queue RegularRideQ7("|Regular 7 Ride Queue");
Queue SingleRideQ7("Single 7 Ride Queue");

Queue RegularRideQ8("|Regular 8 Ride Queue");
Queue SingleRideQ8("Single 8 Ride Queue");

Queue RegularRideQ9("|Regular 9 Ride Queue");
Queue SingleRideQ9("Single 9 Ride Queue");

Queue RegularRideQ10("|Regular 10 Ride Queue");
Queue SingleRideQ10("Single 10 Ride Queue");

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

