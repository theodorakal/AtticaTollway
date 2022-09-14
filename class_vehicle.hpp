#include <iostream>
#include <string>
#include <list>

using namespace std;



class Entrance;
class Toll;
class Vehicle;
class Attica_Tollway;

class Vehicle{
    private:
        bool ready;
        int segment;
        int destination;
        int entrance;

    public:
        Vehicle(Attica_Tollway* o, int seg, int entr);
        void set_ready();
        void set_not_ready();
        bool is_ready();
        int get_destination() const;
        void change_state_of_vehicle(int seg); 
        //void print_vehicle();
};