
#include "model.h"



class Ride : public Process {
    void Behavior() {
        while (true) {
            // printf("3  length %d\n", RideQ.Length());

            if ((SingleRideQ1.Length()+RegularRideQ1.Length()) < RIDE_CAPACITY) {

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
                if (!(SingleRideQ1.empty() && RegularRideQ1.empty())){
                    
                    regular = (int)Uniform(1,capacity+1);
                    single = capacity-regular;
                }

                if (RegularRideQ1.Length() < regular){
                    regular = RegularRideQ1.Length();
                }
                if (SingleRideQ1.Length() < capacity-regular){
                    single = SingleRideQ1.Length();
                }else {
                    ///
                }

                for (int i = row_start; i < row_start+regular; i++){
                riders_in_cabin[i] = RegularRideQ1.GetFirst();
                }
                for (int i = row_start+regular; i < row_start+regular+single; i++){
                riders_in_cabin[i] = SingleRideQ1.GetFirst();
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
    {1, 1,true,true, 20, 4, 7} // Turtle Coaster
    // {2, 2,true,true, 36, 6, 5}, // Toy Soldier
    // {3, 3,false,false, 28, 2, 5}, // Dog ZigZag
    // {4, 1,false,true, 24, 4, 7}, // Ratatouille
    // {5, 2,true,true, 20, 4, 5}, //  RC  Racer
    // {6, 3,false,false, 20, 2, 5}, // Cars Road Trip
    // {7, 1,true,false, 21, 21, 5}, // Tower Terror
    // {8, 2,false,true, 20, 4, 5}, // Spider Man
    // {9, 2,true, true,24, 2, 5} // Avengers
};


class Person : public Process{
    bool singleRider;
    int chosenAttraction;

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

        bool isAdult = Random() > 0.6; // is Child
        chosenAttraction = -1;
        while( Time < ClOSE_TIME - 10*60){
            chosenAttraction = chooseAttraction(isAdult,chosenAttraction);
            switch (chosenAttraction) {
                case 0:
                    // Choose between single ride
                    income(5); // ticket price = 5 $
                    go_to_attraction(SingleRideQ1, RegularRideQ1);
                case 1:
                    // Choose between single rider
                    income(5); // ticket price = 5 $
                    go_to_attraction(SingleRideQ2, RegularRideQ2);
                default:
                    break;
            }
            if(Random() > 0.3){ // go to park
                Wait(Uniform(30 * 60, 60 * 60)); 
            }
        }

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
        bool isTargetOnRoad1 = (targetAttraction >= 0 && targetAttraction <= 6);

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
                    queueSizeR = RegularRideQ1.Length();
                    break;
                case 1:
                    queueSizeR = RegularRideQ2.Length();
                    break;
                // case 2:
                //     // queueSize = Carpet.Length();
                //     break;
                // case 3:
                //     // queueSize = Carpet.Length();
                //     break;
                // case 4:
                //     // queueSize = Carpet.Length();
                //     break;
                // case 5:
                //     // queueSize = Carpet.Length();
                //     break;
                // case 6:
                //     // queueSize = Carpet.Length();
                //     break;
                // case 7:
                //     // queueSize = Carpet.Length();
                //     break;
                // case 8:
                //     // queueSize = Carpet.Length();
                //     break;
                // case 9:
                //     // queueSize = Carpet.Length();
                //     break;
                default:
                    break;
            } 
            // Розрахунок часу чекання
            double WaitTimeR = (static_cast<double>(queueSizeR) / attraction.capacity) * attraction.rideDuration;

            // Розрахунок відстані з урахуванням категорій доріг
            int distance = calculateDistance(currentAttraction, attraction.id);

            double score = calculateAttractionScore(distance, WaitTimeR, attraction.popularity);

            if (score > maxScore) {
                maxScore = score;
                chosenAttraction = attraction.id;
            }
        }

        return chosenAttraction;
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
    // Init(0, ClOSE_TIME);
    (new Generator(people_count))->Activate();
     

    Run();

    EntranceQ.Output();
    RideQ.Output();
    SingleRideQ1.Output();
    RegularRideQ1.Output();
    for(int i= 0; i<ENTRANCE; i++){
        EntranceL[i].Output();
        // EntranceL.Output();

    }
    // for(int i= 0; i<Ride1AMOUNT; i++){
    // Ride1[i].Output();
    // }
}