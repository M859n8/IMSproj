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

Queue EntranceQ;
Facility EntranceL[ENTRANCE]; 
// Facility EntranceL; 

Queue CarpetR;
Queue CarpetS;
Facility Carpet; 

Queue TowerR;
Queue TowerS;
Facility Tower;
Stat income("Income from ticket pay");
const double ClOSE_TIME = 10000;


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
    {0, 2,false,false, 20, 4, 5}, // Flying Carpets
    {1, 1,true,true, 20, 4, 7}, // Turtle Coaster
    {2, 2,true,true, 36, 6, 5}, // Toy Soldier
    {3, 3,false,false, 28, 2, 5}, // Dog ZigZag
    {4, 1,false,true, 24, 4, 7}, // Ratatouille
    {5, 2,true,true, 20, 4, 5}, //  RC  Racer
    {6, 3,false,false, 20, 2, 5}, // Cars Road Trip
    {7, 1,true,false, 21, 21, 5}, // Tower Terror
    {8, 2,false,true, 20, 4, 5}, // Spider Man
    {9, 2,true, true,24, 2, 5} // Avengers
};
double calculateAttractionScore(int distance, double waitTime, int popularity) {
    const double weightPopularity = 3.0;
    const double weightDistance = 1.0;
    const double weightWaitTime = 2.0;

    return weightPopularity / popularity + 
           weightDistance / (distance + 1) + 
           weightWaitTime / (waitTime + 1) ;
}

int calculateDistance(int currentAttraction, int targetAttraction) {
    if(currentAttraction == -1){
        return targetAttraction +1;
    }
    // Категорії доріг
    bool isCurrentOnRoad1 = (currentAttraction >= 0 && currentAttraction <= 6);
    bool isTargetOnRoad1 = (targetAttraction. >= 0 && targetAttraction. <= 6);

    bool isCurrentOnRoad2 = (currentAttraction >= 7 && currentAttraction <= 9);
    bool isTargetOnRoad2 = (targetAttraction >= 7 && targetAttraction <= 9);

    if (isCurrentOnRoad1 && isTargetOnRoad2) {
        // Рахуємо відстань через вхід
        return currentAttraction +1 + (targetAttraction + 1 - 7); 
    } else if (isCurrentOnRoad2 && isTargetOnRoad1) {
        // Рахуємо відстань через вхід
        return (currentAttraction - 7 + 1) + targetAttraction + 1; 
    } else {
        return std::abs(currentAttraction - targetAttraction);
    }
}
int chooseAttraction(bool isAdult,int currentAttraction) {
    int chosenAttraction = -1; // ID обраного атракціону
    double maxScore = -1;

    for (const auto& attraction : attractions) {
        // Фільтрація атракціонів за обмеженнями
        if (!isAdult && attraction.isForAdults) continue; // Пропустити, якщо це дитина і атракціон тільки для дорослих
        int queueSizeR;
        switch (attraction.id) {
            case 0:
                queueSizeR = CarpetR.Length();
                break;
            case 1:
                queueSizeR = TowerR.Length();
                break;
            case 2:
                // queueSize = Carpet.Length();
                break;
            case 3:
                // queueSize = Carpet.Length();
                break;
            case 4:
                // queueSize = Carpet.Length();
                break;
            case 5:
                // queueSize = Carpet.Length();
                break;
            case 6:
                // queueSize = Carpet.Length();
                break;
            case 7:
                // queueSize = Carpet.Length();
                break;
            case 8:
                // queueSize = Carpet.Length();
                break;
            case 9:
                // queueSize = Carpet.Length();
                break;
            default:
                break;
        } 
        // Розрахунок часу чекання
        double WaitTimeR = (static_cast<double>(queueSizeR) / attraction.capacity) * attraction.rideDuration;

        // Розрахунок відстані з урахуванням категорій доріг
        int distance = calculateDistance(currentAttraction, attraction.id);

        double score = calculateAttractionScore(distance, WaitTimeR, WaitTimeS, attraction.popularity);

        if (score > maxScore) {
            maxScore = score;
            chosenAttraction = attraction.id;
        }
    }

    return chosenAttraction;
}

class Person : public Process{

    void Behavior() {
        int free_entr = -1;
        back:
        printf("1\n");

        for (int a=0; a<ENTRANCE; a++){
            if (!EntranceL[a].Busy()) { 
                free_entr=a; 
                break; 
            }
        }
        printf("2\n");

        if (free_entr == -1) {
            Into(EntranceQ);
            Passivate();
            goto back;
        printf("3\n");
        }
        printf("4\n");

        Seize(EntranceL[free_entr]);
        printf("5\n");

        Wait(Exponential(30)); // Час на проходження
        printf("6\n");

        Release(EntranceL[free_entr]);
        printf("7\n");

        if (EntranceQ.Length()>0) {
        printf("8\n");

			(EntranceQ.GetFirst())->Activate();
		}
        bool isAdult = Random() > 0.6; // is Child
        int chosenAttraction = -1;
        while( Time < ClOSE_TIME - 10*60){
            chosenAttraction = chooseAttraction(isAdult,chosenAttraction);
            switch (attraction.id) {
                case 0:
                    // Choose between single ride
                    income(5); // ticket price = 5 $
                    Into(EntranceQ);
                    Passivate();
                    // Ride attr
                case 1:
                    // Choose between single rider
                    Into(EntranceQ);
                    Passivate();
                    // Ride attr
                default:
                    break;
            }
            if(Random() > 0.3){ // go to park
                Wait(Uniform(30 * 60, 60 * 60)); 
            }
        }

    }
    
};

class Generator : public Event {
public:
    Generator(int people_count) : Event() {
            People_count = people_count;
    };
    void Behavior() { 
        for(int i = 0 ; i <People_count; i++) { 
            (new Person)->Activate(); 
        } 
    }
    int People_count;
};




int main(int argc , char **argv)
{
    int people_count;
    if (argc < 2) {
        printf("Error: Missing argument for season (summer or winter)\n");
        return 1;
    }

    if (strcmp(argv[1], "summer") == 0) {
        people_count = HIGH_AMOUNT;
    } else if (strcmp(argv[1], "winter") == 0) {
        people_count = LOW_AMOUNT;
    } else {
        printf("Error: Invalid season argument\n");
        return 1;
    }
    // Init(0, 10000);
    Init(0, ClOSE_TIME);
    (new Generator(people_count))->Activate();
    Run();
    for(int i= 0; i<ENTRANCE; i++){
        EntranceL[i].Output();
        // EntranceL.Output();

    }
    
}