#include "simlib.h"

Facility Linka("Obsluzna linka");
Stat dobaObsluhy("Doba obsluhy na lince");
Histogram dobaVSystemu("Celkova doba v systemu", 0, 40, 20);

int bezCekani = 0;

class Transakce : public Process {
    void Behavior() {
	double tvstup = Time;
	double obsluha;
	
	if (!Linka.Busy()) bezCekani++;
	
	Seize(Linka);
	obsluha = Exponential(10); Wait(obsluha); dobaObsluhy(obsluha);
	Release(Linka);
	dobaVSystemu(Time - tvstup);
    }
};

class Generator : public Event {
    void Behavior() {
	(new Transakce)->Activate();
	Activate(Time + Exponential(11));
    }
};

int main()
{
    Init(0, 100000);
    (new Generator)->Activate();
    Run();
    
    dobaObsluhy.Output();
    Linka.Output();
    dobaVSystemu.Output();
    
    Print("Bez cekani: %d\n", bezCekani);
}