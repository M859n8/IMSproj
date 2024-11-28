#include "simlib.h"
#include <stdio.h>
#include <cstring>


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
Queue RegularQ("|Regular Ride Queue");
Queue SingleRideQ("Single Ride Queue");

Queue RideQ("Ride Queue");


// class Board: public Process {
// public:
//     void Behaviour();
//     void start_boarding();
//     }

// class Ride : public Process {
//     void Behavior();
// }

