
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
            //change this? delete ? 
            if ((SingleRideQ->Length()+RegularRideQ->Length()) < RIDE_CAPACITY) {
            // if ((SingleRideQ->Length()+RegularRideQ->Length()) < RIDE_CAPACITY) { додати що більше однієї людини

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
                if(currentAttraction.id == 3){

                    printf("before  get first %d \n", SingleRideQ->Length());
                }

                    riders_in_cabin.push_back(SingleRideQ->GetFirst());
                if(currentAttraction.id == 3){

                    printf("after get first %d \n", SingleRideQ->Length());
                }

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

            if(currentAttraction.id == 3){
            printf("single rider length : %d . ID of the ride %d\n" , SingleRideQ->Length(), currentAttraction.id);

            }
                    

            Wait(currentAttraction.rideDuration); // Ride lasts for 5 minutes

            // Ride completes, all riders are done
            //  Print("Атракціон завершився, перевезено %d пасажирів на час %.2f\n",row_end, Time);
       riders_in_cabin.clear();







            // If there's still a queue, immediately reactivate
            // if (RideQ.Length() >= RIDE_CAPACITY) {
            //     Activate();
            // }
        }
    }
};


Ride* ptr0;
Ride* ptr1;
Ride* ptr2;
Ride* ptr3;






class Person : public Process{
    bool singleRider;
    int currentAttraction;
    Attraction current_attraction;
    int waitTimeRegular; 

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
        currentAttraction = -1; 
        while( Time < ClOSE_TIME - 10*60){ 
            currentAttraction = chooseAttraction(isAdult); 
            switch (currentAttraction) { 
                case 0:
                    case1 = false ;
                    // Choose between single ride
                    income(5); // ticket price = 5 $
                  
                    go_to_attraction(SingleRideZero, RegularRideQ0);
                    // printf("3 SimgleQ : %d, RegularQ : %d\n", SingleRideZero.Length() , RegularRideQ0.Length());

                    // if ((SingleRideZero.Length()+RegularRideQ0.Length()) >= RIDE_CAPACITY) {

                        ptr0->setcurrentAttraction(current_attraction, SingleRideZero, RegularRideQ0);
                        ptr0->Activate(); // Активуємо атракціон, якщо черга наповнена

                    // } 
                    Passivate(); // Чекаємо, поки атракціон активує
                    Wait(current_attraction.rideDuration); 
                    // break;

                case 1:
                    income(5); 

                    go_to_attraction(SingleRideQ1, RegularRideQ1);

                    // if ((SingleRideQ1.Length()+RegularRideQ1.Length()) >= RIDE_CAPACITY) {

                        ptr1->setcurrentAttraction(current_attraction, SingleRideQ1, RegularRideQ1);
                        ptr1->Activate(); 

                    // } 
                    Passivate(); 
                    Wait(current_attraction.rideDuration); 
                    // break;
                case 2:
                    income(5);

                    go_to_attraction(SingleRideQ2, RegularRideQ2);

                    // if ((SingleRideQ2.Length()+RegularRideQ2.Length()) >= RIDE_CAPACITY) {
                        ptr2->setcurrentAttraction(current_attraction, SingleRideQ2, RegularRideQ2);
                        ptr2->Activate(); 
                    // } 
                    Passivate(); 
                    Wait(current_attraction.rideDuration); 
                    // break;
                case 3:
                    income(5); 
                    // printf("chosen attraction id %d\n", this->current_attraction.id );
                    go_to_attraction(SingleRideQ3, RegularRideQ3);
                    printf("    single rider length : %d . ID of the ride %d\n" , SingleRideQ3.Length(), current_attraction.id);

                    // if ((SingleRideZero.Length()+RegularRideQ3.Length()) >= RIDE_CAPACITY) {

                        ptr3->setcurrentAttraction(current_attraction, SingleRideQ3, RegularRideQ3);
                        ptr3->Activate(); 

                    // } 
                    Passivate(); 
                    Wait(current_attraction.rideDuration); 
                    // break;
                default:
                    break;
            }
            if(Random() > 0.3){ // go to park
                Wait(Uniform(30 * 60, 60 * 60)); 
            }
        }

    }
    
    void go_to_attraction(Queue &SingleRideQ, Queue &RegularRideQ){
        if(current_attraction.single_rider){
            
            double singleRider = Random();
            if (singleRider <= 0.5) {
                this->singleRider = true;
                Into(SingleRideQ);
            }else {
                this->singleRider = false;
                Into(RegularRideQ);
            }
            // printf("single rider length : %d . ID of the ride %d\n" , SingleRideQ->Length(), currentAttraction.id);

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

    int calculateDistance(int targetAttraction) { 
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
    int chooseAttraction(bool isAdult) { 
        int chosenAttraction = -1; // ID обраного атракціону 
        double maxScore = -1; 

        for (const auto& attraction : attractions) { 
            // Фільтрація атракціонів за обмеженнями 
            if (!isAdult && attraction.isForAdults) continue; // Пропустити, якщо це дитина і атракціон тільки для дорослих 
            int queueSizeR; 
            switch (attraction.id) { 
                case 0: 
                    queueSizeR = RegularRideQ0.Length(); 
                    break; 
                case 1: 
                    queueSizeR = RegularRideQ1.Length(); 
                    break; 
                case 2: 
                    queueSizeR = RegularRideQ2.Length(); 
                    break; 
                case 3: 
                    queueSizeR = RegularRideQ3.Length(); 
                    break; 
                // case 4: 
                //     queueSizeR = RegularRideQ5.Length(); 
                //     break; 
                // case 5: 
                //     queueSizeR = RegularRideQ6.Length(); 
                //     break; 
                // case 6: 
                //     queueSizeR = RegularRideQ7.Length(); 
                //     break; 
                // case 7: 
                //     queueSizeR = RegularRideQ8.Length(); 
                //     break; 
                // case 8: 
                //     queueSizeR = RegularRideQ9.Length(); 
                //     break; 
                // case 9: 
                //     queueSizeR = RegularRideQ10.Length(); 
                //     break; 
                default: 
                    break; 
            }  
            // Розрахунок часу чекання 
            int WaitTimeR = static_cast<int>(queueSizeR / attraction.capacity) * attraction.rideDuration; 
            // Розрахунок відстані з урахуванням категорій доріг 
            int distance = calculateDistance(attraction.id); 

            double score = calculateAttractionScore(distance, WaitTimeR, attraction.popularity); 

            if (score > maxScore) { 
                maxScore = score; 
                chosenAttraction = attraction.id; 
                waitTimeRegular = WaitTimeR; 
            } 
        } 

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
    ptr0 = new Ride;
    //ptr->Activate();

    ptr1 = new Ride;
    ptr2 = new Ride;
    //ptr->Activate();

    ptr3 = new Ride;
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
    RegularRideQ0.Output();

    SingleRideQ1.Output();
    RegularRideQ1.Output();

    SingleRideQ2.Output();
    RegularRideQ2.Output();

    RegularRideQ3.Output();
    SingleRideQ3.Output();


    for(int i= 0; i<ENTRANCE; i++){
        EntranceL[i].Output();
        // EntranceL.Output();

    }
    // for(int i= 0; i<Ride1AMOUNT; i++){
    // Ride1[i].Output();
    // }
}