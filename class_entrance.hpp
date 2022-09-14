#include <iostream>
#include <string>
#include <list>

using namespace std;



class Toll;
class Vehicle;
class Attica_Tollway;

class Entrance{ // kombos eisodos
    private:
        int last_toll;
        int entrance_no;
        int num_of_tolls;         //apo 10 ews 20 diodia i kathe eisodos
        int number_of_e_tolls;         //apo 10 ews 20 diodia i kathe eisodos
        int number_of_collector_tolls;     //kai oti perissepsei einai me eispraktora
        Toll **array_of_tolls;
    public:
        Entrance(Attica_Tollway* o, int entr_no, int rate);
        ~Entrance();
        Vehicle *operate();
        int vehicles_waiting() const; // sunolo olwn twn autokinhtwn pou perimenoun na perasoun apo ola ta diodia ths entrance
        void reinitialize();
        bool check_tolls();
        void refill_tolls();     //kaleitai stin operate gia na kanei refill ta diodia me autokinhta
        //void print_entrance() const;
};