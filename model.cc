
#include "model.h"



class Ride : public Process {
private:
    Attraction currentAttraction;
    Queue* SingleRideQ;  // Зберігаємо вказівник
    Queue* RegularRideQ; // Зберігаємо вказівник
    bool closing_soon;

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
        // start: 
        while (Time < ClOSE_TIME ) {
            // if(Time > ClOSE_TIME-20*60){
            //     // printf("qoto time.");
            //     // printf(" на час %.2f\n", Time);

            //     goto send;
            // }
            //change this? delete ? 
            // if ((SingleRideQ->Length()+RegularRideQ->Length()) < currentAttraction.capacity) {
            // if ((SingleRideQ->Length()+RegularRideQ->Length()) < RIDE_CAPACITY) { додати що більше однієї людини

                Passivate(); // Wait until enough people are in the queue
            // }
            // if(!currentAttraction.single_rider){
            //     if(SingleRideQ->Length() != 0){
            //     // printf("without single rider the length must be 0 : %d . ID of the ride %d\n" , SingleRideQ->Length(), currentAttraction.id);
                    
            //     }
            // }
           // printf("5.2 queue length %d\n", RideQ.Length() );
            // Load passengers (up to RIDE_CAPACITY)
            // int capacity = currentAttraction.people_in_row; //change later
            
            
            // send:

            int row_end = 0; //test only
            std::vector<Entity*> riders_in_cabin;   
            
            for (int i=0; i<currentAttraction.capacity; i++ ){
                int regular = 0;
                int single = 0;
                if (!SingleRideQ->empty() || !RegularRideQ->empty()){
                    regular = (int)Uniform(1, currentAttraction.people_in_row+1);
                    single =  currentAttraction.people_in_row-regular;
                }

                if (RegularRideQ->Length() < regular){
                    regular = RegularRideQ->Length();
                }
                if (SingleRideQ->Length() <  currentAttraction.people_in_row-regular){
                    single = SingleRideQ->Length();

                }else {
                    single =  currentAttraction.people_in_row-regular;

                    // printf("entered else in ride, single is %d and lendtht %d\n", single, SingleRideQ->Length());
                }

                for (int i = 0; i < regular; i++){

                    riders_in_cabin.push_back(RegularRideQ->GetFirst());
                    row_end++; //test only
                }

                for (int i = 0; i < single; i++){
                    riders_in_cabin.push_back(SingleRideQ->GetFirst());
                    row_end++;  //test only
                }
                //Wait(10);//time for posadka
                
            }
            // printf("    5 row end %d\n", row_end);
            
            // printf("Number of riders: %zu\n", riders_in_cabin.size());

            // for (auto& rider : riders_in_cabin) {
            //     rider->Activate();
            // }

            Wait(currentAttraction.rideDuration); // Ride lasts for 5 minutes
            // printf("    1\n");
              for (auto& rider : riders_in_cabin) {
            // printf("    2\n");

                rider->Activate();
            }
            // printf("    3\n");

            // Ride completes, all riders are done
            //  Print("Атракціон завершився, перевезено %d пасажирів на час %.2f\n",row_end, Time);
            // if(Time > ClOSE_TIME-20*60 && currentAttraction.capacity != 20){
            //     printf("Атракціон завершився, перевезено %d пасажирів на час %.2f, id of ride %d, cap is %d\n",row_end, Time, currentAttraction.id, currentAttraction.capacity);

            // }
            riders_in_cabin.clear();

            // printf("    4\n");
            // Passivate();
            // goto start;

            // If there's still a queue, immediately reactivate
            // if (RideQ.Length() >= RIDE_CAPACITY) {
            //     Activate();
            // }
        }
    }
    void closingSoon(Attraction attraction, Queue& singleQueue, Queue& regularQueue){
        // Поки черги не порожні, запускаємо атракціон
            std::vector<Entity*> riders_in_cabin;   
// printf("closing soon \n");
        while (!singleQueue.Empty() || !regularQueue.Empty()) {
            int numPeople = 0;
            // Тепер саджаємо людей з регулярної черги
            while (!regularQueue.Empty() && numPeople < attraction.capacity) {
                riders_in_cabin.push_back(regularQueue.GetFirst()); // вивести людину з регулярної черги
                numPeople++;
            }
            // Спочатку саджаємо людей з одиночної черги
            while (!singleQueue.Empty() && numPeople < attraction.capacity) {
                riders_in_cabin.push_back(singleQueue.GetFirst()); // вивести людину з одиночної черги
                numPeople++;
            }
            Wait(currentAttraction.rideDuration); // Ride lasts for 5 minutes

            for (auto& rider : riders_in_cabin) {
// printf("closing soon 2\n");

                rider->Activate();
            }
            riders_in_cabin.clear();
        }
    }
    
};


Ride* ptr0;
Ride* ptr1;
Ride* ptr2;
Ride* ptr3;
Ride* ptr4;
Ride* ptr5;
Ride* ptr6;
Ride* ptr7;
Ride* ptr8;
Ride* ptr9;





class Person : public Process{
    bool singleRider;
    int currentAttraction;
    bool closing_soon;
    Attraction current_attraction;
    int distanceToNext; // distance to the next attraction
    std::vector<bool> visitedAttractions;

    void Behavior() {
        // Wait(Normal(3600,  14400));  // Car waiting to arrive between cca 7:45 and 12:00
        Wait(Uniform(1800, 14400));

        if (visitedAttractions.empty()) {
            // Ініціалізуємо вектор лише один раз
            visitedAttractions = std::vector<bool>(10, false);
        }
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
        

        bool isAdult = Random() < 0.787; 
        currentAttraction = -1;
        while( Time < ClOSE_TIME){
            if(Time > ClOSE_TIME-20*60){
                closing_soon = true;
                goto closing0;
            }
            // currentAttraction = chooseAttraction(isAdult);
            chooseAttraction(isAdult);
            if(currentAttraction == -1){
                goto themePark;
            }
            // printf("Distance : %d\n", distanceToNext);
            if(distanceToNext != 0){
                Wait(distanceToNext*5*60);
            }
            // currentAttraction = current_attraction.id;
            switch (current_attraction.id) {
                case 0:
                    // Choose between single ride
                    income(current_attraction.price); // ticket price = 5 $
                  
                    go_to_attraction(SingleRideZero, RegularRideQ0);
                    // printf("3 SimgleQ : %d, RegularQ : %d\n", SingleRideZero.Length() , RegularRideQ0.Length());
// printf("1\n");
                    if ((SingleRideZero.Length()+RegularRideQ0.Length()) >= current_attraction.capacity) {
// printf("2\n");

                        ptr0->setcurrentAttraction(current_attraction, SingleRideZero, RegularRideQ0);
// printf("3\n");
                        

                        ptr0->Activate(); // Активуємо атракціон, якщо черга наповнена
// printf("4\n");
                    // } else if((Time>ClOSE_TIME-20*60) && (Time<ClOSE_TIME)){
                    } else if(closing_soon){
                        closing0:
                        //  printf("eraising remainings 0\n");
                        // ptr0->Activate(); 
                        ptr0->closingSoon(current_attraction, SingleRideZero, RegularRideQ0);
                        
                        goto closing1;

                        
                    }
                    Passivate(); // Чекаємо, поки атракціон активує
                    // Wait(current_attraction.rideDuration); 
                    break;

                case 1:
                    income(current_attraction.price); 
                    go_to_attraction(SingleRideQ1, RegularRideQ1);
                    if ((SingleRideQ1.Length()+RegularRideQ1.Length()) >= current_attraction.capacity) {
                        ptr1->setcurrentAttraction(current_attraction, SingleRideQ1, RegularRideQ1);
                        ptr1->Activate(); 
                    }  else if(closing_soon){
                        closing1:
                        ptr1->closingSoon(current_attraction, SingleRideQ1, RegularRideQ1);
                        goto closing2;
                    }
                    Passivate(); 
                    break;
                case 2:
                    income(current_attraction.price);
                    go_to_attraction(SingleRideQ2, RegularRideQ2);
                    if ((SingleRideQ2.Length()+RegularRideQ2.Length()) >=current_attraction.capacity) {
                        ptr2->setcurrentAttraction(current_attraction, SingleRideQ2, RegularRideQ2);
                        ptr2->Activate(); 
                    }  else if(closing_soon){
                        closing2:
                        ptr2->closingSoon(current_attraction, SingleRideQ2, RegularRideQ2);
                        goto closing3;
                    }
                    Passivate(); 
                    break;
                case 3:
                    income(current_attraction.price); 
                    go_to_attraction(SingleRideZero, RegularRideQ3);
                    if ((SingleRideZero.Length()+RegularRideQ3.Length()) >= current_attraction.capacity) {
                        ptr3->setcurrentAttraction(current_attraction, SingleRideZero, RegularRideQ3);
                        ptr3->Activate(); 
                    }  else if(closing_soon){
                        closing3:
                        ptr3->closingSoon(current_attraction, SingleRideZero, RegularRideQ3);
                        goto closing4;
                    }
                    Passivate(); 
                    // Wait(current_attraction.rideDuration); 
                    break;
                case 4:
                    income(current_attraction.price);
                    go_to_attraction(SingleRideQ4, RegularRideQ4);
                    if ((SingleRideQ4.Length()+RegularRideQ4.Length()) >=current_attraction.capacity) {
                        ptr4->setcurrentAttraction(current_attraction, SingleRideQ4, RegularRideQ4);
                        ptr4->Activate(); 
                    }  else if(closing_soon){
                        closing4:

                        ptr4->closingSoon(current_attraction, SingleRideQ4, RegularRideQ4);
                        goto closing5;
                    }
                    Passivate(); 
                    break;
                case 5:
                    income(current_attraction.price);
                    go_to_attraction(SingleRideQ5, RegularRideQ5);
                    if ((SingleRideQ5.Length()+RegularRideQ5.Length()) >=current_attraction.capacity) {
                        ptr5->setcurrentAttraction(current_attraction, SingleRideQ5, RegularRideQ5);
                        ptr5->Activate(); 
                    }  else if(closing_soon){
                        closing5:

                        ptr5->closingSoon(current_attraction, SingleRideQ5, RegularRideQ5);
                        goto closing6;
                    }
                    Passivate(); 
                    break;
                case 6:
                    income(current_attraction.price);
                    go_to_attraction(SingleRideZero, RegularRideQ6);
                    if ((SingleRideZero.Length()+RegularRideQ6.Length()) >=current_attraction.capacity) {
                        ptr6->setcurrentAttraction(current_attraction, SingleRideZero, RegularRideQ6);
                        ptr6->Activate(); 
                    }  else if(closing_soon){
                        closing6:

                        ptr6->closingSoon(current_attraction, SingleRideZero, RegularRideQ6);
                        goto closing7;
                    }
                    Passivate(); 
                    break;
                case 7:
                    income(current_attraction.price);
                    go_to_attraction(SingleRideZero, RegularRideQ7);
                    if ((SingleRideZero.Length()+RegularRideQ7.Length()) >=current_attraction.capacity) {
                        ptr7->setcurrentAttraction(current_attraction, SingleRideZero, RegularRideQ7);
                        ptr7->Activate(); 
                    }  else if(closing_soon){
                        closing7:

                        ptr7->closingSoon(current_attraction, SingleRideZero, RegularRideQ7);
                        goto closing8;
                    }
                    Passivate(); 
                    break;
                case 8:
                    income(current_attraction.price);
                    go_to_attraction(SingleRideQ8, RegularRideQ8);
                    if ((SingleRideQ8.Length()+RegularRideQ8.Length()) >=current_attraction.capacity) {
                        ptr8->setcurrentAttraction(current_attraction, SingleRideQ8, RegularRideQ8);
                        ptr8->Activate(); 
                    }  else if(closing_soon){
                        closing8:

                        ptr8->closingSoon(current_attraction, SingleRideQ8, RegularRideQ8);
                        goto closing9;
                    }
                    Passivate(); 
                    break;
                case 9:
                    income(current_attraction.price);
                    go_to_attraction(SingleRideQ9, RegularRideQ9);
                    if ((SingleRideQ9.Length()+RegularRideQ9.Length()) >=current_attraction.capacity) {
                        ptr9->setcurrentAttraction(current_attraction, SingleRideQ9, RegularRideQ9);
                        ptr9->Activate(); 
                    }  else if(closing_soon){
                        closing9:
                        ptr2->closingSoon(current_attraction, SingleRideQ9, RegularRideQ9);
                    }
                    Passivate(); 
                    break;
                
                default:
                    break;
            }
            visitedAttractions[current_attraction.id] = true;
            if(Random() < 0.3){ // go to park
                themePark:
                
                // printf("go to park\n");
                Wait(Uniform(20 * 60, 40 * 60)); 
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
   
    double calculateAttractionScore(int distance, int waitTime, int popularity, bool visited) {
        const double weightPopularity = 3.0;
        const double weightDistance = 0.5;
        const double weightWaitTime = 2.0;
        const double weightVisited = 5.0; //maybe less

        double score = weightPopularity / (popularity )+ 
                            weightDistance / (distance + 1) + 
                            weightWaitTime / (waitTime/60 + 1) ;
        if (!visited) {
            score += weightVisited;
        }

        return score;
    }

    int calculateDistance(int targetAttraction) { 
        if(currentAttraction == -1){ 
            return (targetAttraction+1); 
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

    void chooseAttraction(bool isAdult) { 
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
                case 4: 
                    queueSizeR = RegularRideQ4.Length(); 
                    break; 
                case 5: 
                    queueSizeR = RegularRideQ5.Length(); 
                    break; 
                case 6: 
                    queueSizeR = RegularRideQ6.Length(); 
                    break; 
                case 7: 
                    queueSizeR = RegularRideQ7.Length(); 
                    break; 
                case 8: 
                    queueSizeR = RegularRideQ8.Length(); 
                    break; 
                case 9: 
                    queueSizeR = RegularRideQ9.Length(); 
                    break; 
                default: 
                    break; 
            }  
            // Розрахунок часу чекання 
            int WaitTimeR = static_cast<int>(queueSizeR / attraction.capacity) * attraction.rideDuration; 
            if(WaitTimeR > 60*60){
                printf("skip attraction");
                continue;
            }
            // Розрахунок відстані з урахуванням категорій доріг 
            int distance = calculateDistance(attraction.id); 

            double score = calculateAttractionScore(distance, WaitTimeR, attraction.popularity, visitedAttractions[attraction.id]);

            if (score > maxScore) {
                maxScore = score;
                chosenAttraction = attraction.id;
                distanceToNext = distance;
            }
        }
        if(chosenAttraction == -1){
            currentAttraction == -1;
        }else{
            current_attraction = attractions[chosenAttraction];

            currentAttraction = chosenAttraction;
        }
        // return chosenAttraction;
    }
};




class Generator : public Event {
public:
    Generator(int people_count) : Event() {
            People_count = people_count;
    };
    void Behavior() { 
        for(int i = 0 ; i <People_count; i++) {
            // Wait(Uniform(1800, 14400));
            // (new Person)->Activate(Time+Uniform(1800, 14400)); 
            (new Person)->Activate(); 

        } 
    }
    int People_count;
};




int main(int argc , char **argv)
{
    int people_count;
    if (argc < 2) {
        // printf("Error: Missing argument for season (summer or winter)\n");
        return 1;
    }

    if (strcmp(argv[1], "summer") == 0) {
        people_count = HIGH_AMOUNT;
    } else if (strcmp(argv[1], "winter") == 0) {
        people_count = LOW_AMOUNT;
    } else {
        // printf("Error: Invalid season argument\n");
        return 1;
    }

    Init(0,ClOSE_TIME);
    ptr0 = new Ride;
    ptr1 = new Ride;
    ptr2 = new Ride;
    ptr3 = new Ride;
    ptr4 = new Ride;
    ptr5 = new Ride;
    ptr6 = new Ride;
    ptr7 = new Ride;
    ptr8 = new Ride;
    ptr9 = new Ride;

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

    SingleRideZero.Output();
    RegularRideQ0.Output();

    SingleRideQ1.Output();
    RegularRideQ1.Output();

    SingleRideQ2.Output();
    RegularRideQ2.Output();

    RegularRideQ3.Output();

    SingleRideQ4.Output();
    RegularRideQ4.Output();

    SingleRideQ5.Output();
    RegularRideQ5.Output();

    RegularRideQ6.Output();

    RegularRideQ7.Output();

    SingleRideQ8.Output();
    RegularRideQ8.Output();

    SingleRideQ9.Output();
    RegularRideQ9.Output();



    // for(int i= 0; i<ENTRANCE;){
    //     EntranceL[i].Output();
    //     // EntranceL.Output();
    //     i+=3;

    // }
    income.Output();
    // for(int i= 0; i<Ride1AMOUNT; i++){
    // Ride1[i].Output();
    // }
}