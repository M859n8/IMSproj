#include "model.h"


class Ride : public Process {
    void Behavior() {
        while (true) {
            // printf("3  length %d\n", RideQ.Length());

            if ((SingleRideQ.Length()+RegularQ.Length()) < RIDE_CAPACITY) {

                Passivate(); // Wait until enough people are in the queue

            }
            printf("5.2 queue length %d\n", RideQ.Length() );
            // Load passengers (up to RIDE_CAPACITY)
            int capacity = 4; //change later
            int regular = 0;
            int single = 0;
            int row_start = 0;
            Entity *riders_in_cabin[RIDE_CAPACITY];
            for (int row_start=0; row_start<RIDE_CAPACITY; ){
                if (!(SingleRideQ.empty() && RegularQ.empty())){
                    
                    regular = (int)Uniform(1,capacity+1);
                    single = capacity-regular;
                }

                if (RegularQ.Length() < regular){
                    regular = RegularQ.Length();
                }
                if (SingleRideQ.Length() < capacity-regular){
                    single = SingleRideQ.Length();
                }else {
                    ///
                }

                for (int i = row_start; i < row_start+regular; i++){
                riders_in_cabin[i] = RegularQ.GetFirst();
                }
                for (int i = row_start+regular; i < row_start+regular+single; i++){
                riders_in_cabin[i] = SingleRideQ.GetFirst();
                }
                //Wait(10);//time for posadka
                
                row_start+=4;
            }

            for (int i = 0; i < regular+single; i++){
                riders_in_cabin[i]->Activate();
            }

            Wait(120); // Ride lasts for 2 minutes

            // Ride completes, all riders are done
            //  Print("Атракціон завершився, перевезено %d пасажирів на час %.2f\n", RIDE_CAPACITY, Time);
       

            // If there's still a queue, immediately reactivate
            // if (RideQ.Length() >= RIDE_CAPACITY) {
            //     Activate();
            // }
        }
    }
};


Ride* ptr;



class Person : public Process{
    bool singleRider;

    void Behavior() {
        int free_entr = -1;
        back:

        for (int a=0; a<ENTRANCE; a++){
            if (!EntranceL[a].Busy()) { 
                free_entr=a; 
                break; 
            }
        }

        if (free_entr == -1) {
            Into(EntranceQ);
            Passivate();
            goto back;
        }

        Seize(EntranceL[free_entr]);

        Wait(Exponential(60)); // Час на проходження

        Release(EntranceL[free_entr]);

        if (EntranceQ.Length()>0) {

			(EntranceQ.GetFirst())->Activate();
		}
        
        ////////////////////    //////////////////////
  
        go_to_attraction(SingleRideQ, RegularQ);

    }
    
    void go_to_attraction(Queue &SingleRideQ, Queue &RegularRideQ){
        // if (this->rideissingle = true)
        double singleRider = Random();
        if (singleRider <= 0.5) {
            this->singleRider = true;
            Into(SingleRideQ);
        }else {
            this->singleRider = false;
            Into(RegularRideQ);
        }

        if ((SingleRideQ.Length()+RegularRideQ.Length()) >= RIDE_CAPACITY) {
            ptr->Activate(); // Активуємо атракціон, якщо черга наповнена
        } 
        // else {
            Passivate(); // Чекаємо, поки атракціон активує
            Wait(120); // Ride lasts for 2 minutes this->ride->time

        // }

    }
   
    
};

// void Board::start_boarding() {
//     int capacity = 4; //change later
//     int regular = 0;
//     int single = 0;
//     int row_start = 0;
//     Entity *riders_in_cabin[Ride1AMOUNT];
//     for (int row_start=0; row_start<Ride1AMOUNT; ){
//         if (!(SingleRideQ.empty() && RegularQ.empty())){
            
//             regular = (int)Uniform(1,capacity+1);
//             single = capacity-regular;
//         }

//         if (RegularQ.Length() < regular){
//             regular = RegularQ.Length();
//         } 
//         if (SingleRideQ.Length() < capacity-regular){
//             single = SingleRideQ.Length();
//         }

//         for (int i = row_start; i < row_start+regular; i++){
//         riders_in_cabin[i] = RegularQ.GetFirst();
//         }
//         Wait(10);
//         for (int i = row_start+regular; i < row_start+regular+single; i++){
//         riders_in_cabin[i]->Activate();
//         }
//         row_start+=4;
//     }

// }


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

    Init(0, 20000);
    ptr = new Ride;
    ptr->Activate();

    (new Generator(people_count))->Activate();
     

    Run();

    EntranceQ.Output();
    RideQ.Output();
    SingleRideQ.Output();
    RegularQ.Output();
    for(int i= 0; i<ENTRANCE; i++){
        EntranceL[i].Output();
        // EntranceL.Output();

    }
    // for(int i= 0; i<Ride1AMOUNT; i++){
    // Ride1[i].Output();
    // }
}