
#include "model.h"



class Ride : public Process {
private:
    Attraction currentAttraction;
    Queue* SingleRideQ;  // Зберігаємо вказівник
    Queue* RegularRideQ; // Зберігаємо вказівник

public:
    // Конструктор за замовчуванням
    Ride() : SingleRideQ(nullptr), RegularRideQ(nullptr) {}

    // Конструктор із параметрами
    Ride(Attraction attraction, Queue& singleQueue, Queue& regularQueue)
        : currentAttraction(attraction), SingleRideQ(&singleQueue), RegularRideQ(&regularQueue) {}

    // Метод для встановлення значень
    void setcurrentAttraction(Attraction attraction, Queue& singleQueue, Queue& regularQueue) {
        currentAttraction = attraction;
        SingleRideQ = &singleQueue;
        RegularRideQ = &regularQueue;
    }

    void Behavior() {
        while (true) {
            // if(case1){
            // printf("case 1 entered ride  length single %d, regular %d\n", SingleRideQ->Length(), RegularRideQ->Length());

            // }else{
            // printf("case 0 entered ride  length single %d, regular %d\n", SingleRideQ->Length(), RegularRideQ->Length());

            // }
            // if (SingleRideQ) {
            //     printf("SingleRideQ length: %d, empty: %d\n", SingleRideQ->Length(), SingleRideQ->empty());
            // } else {
            //     printf("SingleRideQ is null.\n");
            // }
            //change this? delete ? 
            if ((SingleRideQ->Length()+RegularRideQ->Length()) < RIDE_CAPACITY) {

                Passivate(); // Wait until enough people are in the queue

            }
            if(!currentAttraction.single_rider){
                if(SingleRideQ->Length() != 0){
                // printf("without single rider the length must be 0 : %d . ID of the ride %d\n" , SingleRideQ->Length(), currentAttraction.id);
                    
                }
            }
           // printf("5.2 queue length %d\n", RideQ.Length() );
            // Load passengers (up to RIDE_CAPACITY)
            int capacity = 4; //change later
            int regular = 0;
            int single = 0;
            int row_start = 0;
            int row_end = 0;
            
            std::vector<Entity*> riders_in_cabin;   
            
            for (int row_start=0; row_start<RIDE_CAPACITY; ){
                if (!SingleRideQ->empty() || !RegularRideQ->empty()){
                    regular = (int)Uniform(1,capacity+1);
                    single = capacity-regular;
                }

                if (RegularRideQ->Length() < regular){
                    regular = RegularRideQ->Length();
                }
                if (SingleRideQ->Length() < capacity-regular){
                    single = SingleRideQ->Length();

                }else {
                    ///
                    single = capacity-regular;

                    // printf("entered else in ride, single is %d and lendtht %d\n", single, SingleRideQ->Length());
                }

                for (int i = row_start; i < row_start+regular; i++){
                    //  printf("    2.0 reqular length %d ; start %d , end %d\n", regular ,row_start,  row_start+regular);

                    riders_in_cabin.push_back(RegularRideQ->GetFirst());
                row_end++;
                }

                for (int i = row_start+regular; i < row_start+regular+single; i++){
                    // printf("    2 single length %d ; start %d , end %d\n", single ,row_start+regular,  row_start+regular+single);


                    riders_in_cabin.push_back(SingleRideQ->GetFirst());
                row_end++;
                }
                //Wait(10);//time for posadka
                
                row_start+=4;
                
            }
                    // printf("    5 row end %d\n", row_end);
            
// printf("Number of riders: %zu\n", riders_in_cabin.size());

            for (auto& rider : riders_in_cabin) {
                rider->Activate();
            }

                    

            Wait(300); // Ride lasts for 5 minutes

            // Ride completes, all riders are done
             Print("Атракціон завершився, перевезено %d пасажирів на час %.2f\n",row_end, Time);
       riders_in_cabin.clear();







            // If there's still a queue, immediately reactivate
            // if (RideQ.Length() >= RIDE_CAPACITY) {
            //     Activate();
            // }
        }
    }
};


Ride* ptr;
Ride* ptr2;






class Person : public Process{
    bool singleRider;
    int chosenAttraction;
    Attraction current_attraction; 

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
                    case1 = false ;
                    // Choose between single ride
                    income(5); // ticket price = 5 $
                  
                    go_to_attraction(SingleRideZero, RegularRideQ1);
                    // printf("3 SimgleQ : %d, RegularQ : %d\n", SingleRideZero.Length() , RegularRideQ1.Length());

                    if ((SingleRideZero.Length()+RegularRideQ1.Length()) >= RIDE_CAPACITY) {

                        ptr->setcurrentAttraction(current_attraction, SingleRideZero, RegularRideQ1);
                        ptr->Activate(); // Активуємо атракціон, якщо черга наповнена

                    } 
                    Passivate(); // Чекаємо, поки атракціон активує
                    Wait(current_attraction.rideDuration); 

                case 1:
                    case1 = true;
                    // Choose between single rider
                    income(5); // ticket price = 5 $
                    // printf("----------5---------\n");

                    go_to_attraction(SingleRideQ2, RegularRideQ2);
                    // printf("6 SimgleQ : %d, RegularQ : %d\n", SingleRideQ2.Length() , RegularRideQ2.Length());

                    if ((SingleRideQ2.Length()+RegularRideQ2.Length()) >= RIDE_CAPACITY) {
                    // printf("7\n");

                        ptr2->setcurrentAttraction(current_attraction, SingleRideQ2, RegularRideQ2);
                        ptr2->Activate(); // Активуємо атракціон, якщо черга наповнена
                    // printf("----------5---------\n");

                    } 
                    Passivate(); // Чекаємо, поки атракціон активує
                    Wait(current_attraction.rideDuration); 
                case 2:
                    income(5);

                    // go_to_attraction(SingleRideQ3, RegularRideQ3);
                    go_to_attraction(SingleRideZero, RegularRideQ3);


                    // if ((SingleRideQ3.Length()+RegularRideQ3.Length()) >= RIDE_CAPACITY) {
                    if ((SingleRideZero.Length()+RegularRideQ3.Length()) >= RIDE_CAPACITY) {


                        // ptr2->setcurrentAttraction(current_attraction, SingleRideQ3, RegularRideQ3);
                        ptr2->setcurrentAttraction(current_attraction, SingleRideZero, RegularRideQ3);

                        ptr2->Activate(); 
                    } 
                    Passivate(); 
                    Wait(current_attraction.rideDuration); 
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
        if(current_attraction.single_rider){
            
            double singleRider = Random();
            if (singleRider <= 0.5) {
                this->singleRider = true;
                Into(SingleRideQ);
            }else {
                this->singleRider = false;
                Into(RegularRideQ);
            }
        }else{
            this->singleRider = false;

            Into(RegularRideQ);
        }

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
                case 2:
                    queueSizeR = RegularRideQ3.Length();
                    break;
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
        current_attraction = attractions[chosenAttraction];
        return chosenAttraction;
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

    Init(0, 12000);
    ptr = new Ride;
    //ptr->Activate();

    ptr2 = new Ride;
    //ptr2->Activate();

    // Attraction attraction = {1, 2, false, true, 20, 4, 7};
    // Queue singleQueue;
    // Queue regularQueue;

    // // Використання конструктора з параметрами
    // Ride ptr(attraction, singleQueue, regularQueue);
    // ptr.Behavior();

    // // Або через метод
    // Ride ptr2;
    // ptr2.setcurrentAttraction(attraction, singleQueue, regularQueue);
    // ptr2.Behavior();

    // Init(0, ClOSE_TIME);
    (new Generator(people_count))->Activate();
     

    Run();

    EntranceQ.Output();
    // RideQ.Output();
    SingleRideZero.Output();
    RegularRideQ1.Output();

    SingleRideQ2.Output();
    RegularRideQ2.Output();

    SingleRideQ3.Output();
    RegularRideQ3.Output();
    for(int i= 0; i<ENTRANCE; i++){
        EntranceL[i].Output();
        // EntranceL.Output();

    }
    // for(int i= 0; i<Ride1AMOUNT; i++){
    // Ride1[i].Output();
    // }
}