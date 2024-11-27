#include "simlib.h"
#include <stdio.h>
#include <cstring>

const int HIGH_AMOUNT = 70;
const int SUPERHIGH_AMOUNT = 75;
const int MIDDLE_AMOUNT = 50;
const int LOW_AMOUNT = 40;
#define ENTRANCE 3//was 30

Queue EntranceQ;
Facility EntranceL[ENTRANCE]; 
// Facility EntranceL; 


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
    Init(0, 10000);
    (new Generator(people_count))->Activate();
    Run();
    for(int i= 0; i<ENTRANCE; i++){
        EntranceL[i].Output();
        // EntranceL.Output();

    }
    
}