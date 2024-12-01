
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
            Passivate(); // Wait until enough people are in the queue

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
                }

                for (int i = 0; i < regular; i++){

                    riders_in_cabin.push_back(RegularRideQ->GetFirst());
                }

                for (int i = 0; i < single; i++){
                    riders_in_cabin.push_back(SingleRideQ->GetFirst());
                }
                
            }
            Wait(currentAttraction.rideDuration); // Ride lasts for 5 minutes
            for (auto& rider : riders_in_cabin) {
                rider->Activate();
            }
           
            riders_in_cabin.clear();

        }
    }
    void closingSoon(Attraction attraction, Queue& singleQueue, Queue& regularQueue){
        // Поки черги не порожні, запускаємо атракціон
            std::vector<Entity*> riders_in_cabin;   
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
    // int AttractionsCount;

    void Behavior() {
        double arrival = Normal(1.5 * 3600.0, 0.5 * 3600.0);
        if (arrival <= 0) {
            arrival = 1; // Мінімальне значення для уникнення помилки
        }
        Wait(arrival);


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
        //AttractionsCount = 0; //TEST ONLY MAYBE DO NOT NEED THIS 
        currentAttraction = -1;
        while( Time < ClOSE_TIME-10*60){
            chooseAttraction(isAdult);
            if(currentAttraction == -1){
                goto themePark;
            }
            if(distanceToNext != 0){
                double speed = Normal(210.0, 90.0);
                if (speed <= 0) {
                    speed = 1; // Мінімальне значення для уникнення помилки
                }

              
            }
            float queueTime; //test only
            float queueTime1; 
            float queueTime2; 
            float queueTime3; 
            float queueTime4; 
            float queueTime5; 
            float queueTime6; 
            float queueTime7; 
            float queueTime8; 
            float queueTime9; 


            switch (current_attraction.id) {
                case 0:
                    income0(current_attraction.price); 
                  
                    go_to_attraction(SingleRideZero, RegularRideQ0);
                    queueTime = Time;
                    if ((SingleRideZero.Length()+RegularRideQ0.Length()) >= current_attraction.capacity) {

                        ptr0->setcurrentAttraction(current_attraction, SingleRideZero, RegularRideQ0);
                        ptr0->Activate(); // Активуємо атракціон, якщо черга наповнена
                    } 
                    
                    Passivate(); // Чекаємо, поки атракціон активує
                    queueTime = Time - (queueTime - current_attraction.rideDuration);
                    timeInQueue += queueTime;
                    AttractionsCount++;

                    break;

                case 1:

                    income1(current_attraction.price); 

                    go_to_attraction(SingleRideQ1, RegularRideQ1);
                    queueTime1 = Time;

                    if ((SingleRideQ1.Length()+RegularRideQ1.Length()) >= current_attraction.capacity) {
                        ptr1->setcurrentAttraction(current_attraction, SingleRideQ1, RegularRideQ1);
                        ptr1->Activate(); 
                    }  
                    
                    Passivate();
                    queueTime1 = Time - (queueTime1 - current_attraction.rideDuration);
                    timeInQueue += queueTime1;
                    AttractionsCount++;

                    break;
                case 2:
                    income2(current_attraction.price);

                    go_to_attraction(SingleRideQ2, RegularRideQ2);
                    queueTime2 = Time;

                    if ((SingleRideQ2.Length()+RegularRideQ2.Length()) >=current_attraction.capacity) {
                        ptr2->setcurrentAttraction(current_attraction, SingleRideQ2, RegularRideQ2);
                        ptr2->Activate(); 
                    }  
                    
                    Passivate(); 
                    queueTime2 = Time - (queueTime2 - current_attraction.rideDuration);
                    timeInQueue += queueTime2;
                    AttractionsCount++;

                    break;
                case 3:
                    income3(current_attraction.price); 
                    go_to_attraction(SingleRideZero, RegularRideQ3);
                    queueTime3 = Time;

                    if ((SingleRideZero.Length()+RegularRideQ3.Length()) >= current_attraction.capacity) {
                        ptr3->setcurrentAttraction(current_attraction, SingleRideZero, RegularRideQ3);
                        ptr3->Activate(); 
                    }  
                    
                    Passivate(); 
                    queueTime3 = Time - (queueTime3 - current_attraction.rideDuration);
                    timeInQueue += queueTime3;
                    AttractionsCount++;

                    break;
                case 4:
                    income4(current_attraction.price);
                    go_to_attraction(SingleRideQ4, RegularRideQ4);
                    queueTime4 = Time;

                    if ((SingleRideQ4.Length()+RegularRideQ4.Length()) >=current_attraction.capacity) {
                        ptr4->setcurrentAttraction(current_attraction, SingleRideQ4, RegularRideQ4);
                        ptr4->Activate(); 
                    }
                    
                    Passivate(); 
                    queueTime4 = Time - (queueTime4 - current_attraction.rideDuration);
                    timeInQueue += queueTime4;
                    AttractionsCount++;

                    break;
                case 5:
                    income5(current_attraction.price);
                    go_to_attraction(SingleRideQ5, RegularRideQ5);
                    queueTime5 = Time;

                    if ((SingleRideQ5.Length()+RegularRideQ5.Length()) >=current_attraction.capacity) {
                        ptr5->setcurrentAttraction(current_attraction, SingleRideQ5, RegularRideQ5);
                        ptr5->Activate(); 
                    }
                 
                    Passivate(); 
                    queueTime5 = Time - (queueTime5 - current_attraction.rideDuration);
                    timeInQueue += queueTime5;
                    AttractionsCount++;

                    break;
                case 6:
                    income6(current_attraction.price);
                    go_to_attraction(SingleRideZero, RegularRideQ6);
                    queueTime6 = Time;

                    if ((SingleRideZero.Length()+RegularRideQ6.Length()) >=current_attraction.capacity) {
                        ptr6->setcurrentAttraction(current_attraction, SingleRideZero, RegularRideQ6);
                        ptr6->Activate(); 
                    } 
                 
                    Passivate(); 
                    queueTime6 = Time - (queueTime6 - current_attraction.rideDuration);
                    timeInQueue += queueTime6;
                    AttractionsCount++;

                    break;
                case 7:
                    income7(current_attraction.price);
                    go_to_attraction(SingleRideZero, RegularRideQ7);
                    queueTime7 = Time;

                    if ((SingleRideZero.Length()+RegularRideQ7.Length()) >=current_attraction.capacity) {
                        ptr7->setcurrentAttraction(current_attraction, SingleRideZero, RegularRideQ7);
                        ptr7->Activate(); 
                    } 
             
                    Passivate(); 
                    queueTime7 = Time - (queueTime7 - current_attraction.rideDuration);
                    timeInQueue += queueTime7;
                    AttractionsCount++;

                    break;
                case 8:
                    income8(current_attraction.price);
                    go_to_attraction(SingleRideQ8, RegularRideQ8);
                    queueTime8 = Time;

                    if ((SingleRideQ8.Length()+RegularRideQ8.Length()) >=current_attraction.capacity) {
                        ptr8->setcurrentAttraction(current_attraction, SingleRideQ8, RegularRideQ8);
                        ptr8->Activate(); 
                    }
               
                    Passivate(); 
                    queueTime8 = Time - (queueTime8 - current_attraction.rideDuration);
                    timeInQueue += queueTime8;
                    AttractionsCount++;

                    break;
                case 9:
                    income9(current_attraction.price);
                    go_to_attraction(SingleRideQ9, RegularRideQ9);
                    queueTime9 = Time;

                    if ((SingleRideQ9.Length()+RegularRideQ9.Length()) >=current_attraction.capacity) {
                        ptr9->setcurrentAttraction(current_attraction, SingleRideQ9, RegularRideQ9);
                        ptr9->Activate(); 
                    } 
              
                    Passivate(); 
                    queueTime9 = Time - (queueTime9 - current_attraction.rideDuration);
                    timeInQueue += queueTime9;
                    AttractionsCount++;

                    break;
                
                default:
                    break;
            }
            visitedAttractions[current_attraction.id] = true;
            if(Random() < 0.3){ // go to park
                themePark:
                
                Wait(Uniform(20 * 60, 40 * 60)); 
            }

        }
        // AttractionsAmount(AttractionsCount);

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

        }else{
            this->singleRider = false;

            Into(RegularRideQ);
        }

    }
   
    double calculateAttractionScore(int distance, int waitTime, int popularity, bool visited) {
        const double weightPopularity = 2.5; //1/4
        const double weightDistance = 0.8; //1/12
        const double weightWaitTime = 0.17; //2/12 but dividet by 10 because waiting time is usualy > 10
        const double weightVisited = 5.0; //1/2
        int visitedInt = 0;
        if(visited){
            visitedInt = 1;
        }

        double score = weightPopularity * popularity + 
                            weightDistance * distance  + 
                            weightWaitTime * (waitTime/60 ) +
                            weightVisited * visitedInt;
        
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
        double minScore = std::numeric_limits<double>::max();; 

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
            // printf("printf: %d\n");
            if(WaitTimeR > 60*60){
                // printf("skip attraction");
                continue;
            }
            // Розрахунок відстані з урахуванням категорій доріг 
            int distance = calculateDistance(attraction.id); 

            double score = calculateAttractionScore(distance, WaitTimeR, attraction.popularity, visitedAttractions[attraction.id]);

            if (score < minScore) {
                minScore = score;
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
            (new Person)->Activate(); 

        } 
    }
    int People_count;
};

class Closing : public Event {
public:

    void Behavior() {
        

        ptr0->closingSoon(attractions[0], SingleRideZero, RegularRideQ0);
        ptr1->closingSoon(attractions[1], SingleRideQ1, RegularRideQ1);
        ptr2->closingSoon(attractions[2], SingleRideQ2, RegularRideQ2);
        ptr3->closingSoon(attractions[3], SingleRideZero, RegularRideQ3);
        ptr4->closingSoon(attractions[4], SingleRideQ4, RegularRideQ4);
        ptr5->closingSoon(attractions[5], SingleRideQ5, RegularRideQ5);
        ptr6->closingSoon(attractions[6], SingleRideZero, RegularRideQ6);
        ptr7->closingSoon(attractions[7], SingleRideZero, RegularRideQ7);
        ptr8->closingSoon(attractions[8], SingleRideQ8, RegularRideQ8);
        ptr9->closingSoon(attractions[9], SingleRideQ9, RegularRideQ9);
        AttractionsAmount(AttractionsCount);


    }
};

void updatePrices(int priceChange) {
    for (auto& attraction : attractions) {
        attraction.price += priceChange;
    }
}

int main(int argc , char **argv)
{
    int people_count;
    int basicPrice = DAY_TICKET_PRICE; //price is taken from disneyland official website
     if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <season> [+/- priceChange]\n";
        std::cerr << "Season must be one of: spring, summer, autumn, winter.\n";
        return 1;
    }

    std::string season = argv[1];
    if (seasonSettings.find(season) == seasonSettings.end()) {
        std::cerr << "Error: Invalid season. Choose from spring, summer, autumn, winter.\n";
        return 1;
    }
    people_count = seasonSettings[season];

    int priceChange = 0;
    // Обробка аргументу зміни ціни
    if (argc == 3) {
        std::string priceChangeArg = argv[2];
        if (priceChangeArg[0] == '+' || priceChangeArg[0] == '-') {
            try {
                priceChange = std::stoi(priceChangeArg);
            } catch (const std::invalid_argument&) {
                std::cerr << "Error: Invalid price change value. Must be in the format +N or -N.\n";
                return 1;
            }
        } else {
            std::cerr << "Error: Invalid price change format. Must start with '+' or '-'.\n";
            return 1;
        }
    }

    if (priceChange != 0) {
        updatePrices(priceChange);
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

    Closing* closeTimeProc = new Closing();
    closeTimeProc->Activate(Time + (ClOSE_TIME - 10*60));

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

    income0.Output();
    income1.Output();
    income2.Output();
    income3.Output();
    income4.Output();
    income5.Output();
    income6.Output();
    income7.Output();
    income8.Output();
    income9.Output();
    printf("+----------------------------------------------------------+\n");
    printf("    Basic income from people that day: %d\n", people_count*basicPrice );
    printf("    Income from all rides with a set price : %0.2f\n", income0.Sum()+income1.Sum()+income2.Sum()+
    income3.Sum()+income4.Sum()+income5.Sum()+income6.Sum()+income7.Sum()+income8.Sum()+income9.Sum());
    printf("+----------------------------------------------------------+\n");

    AttractionsAmount.Output();

    
    printf("time in queue %0.2f, time per person %0.2f\n", timeInQueue, timeInQueue/people_count);
    printf("amount of attractions %d,  per person  %d\n", AttractionsCount, AttractionsCount/people_count);
    

    // for(int i= 0; i<Ride1AMOUNT; i++){
    // Ride1[i].Output();
    // }
}