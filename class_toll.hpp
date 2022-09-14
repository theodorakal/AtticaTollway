#include <iostream>
#include <string>
#include <list>

using namespace std;



class Entrance;
class Toll;
class Vehicle;
class Attica_Tollway;

class Toll{
    protected:
        list <Vehicle*> vehicle_list;
        Attica_Tollway* owner;
        int vehicles_passed;
        bool available;      //ginetai unavailable otan perasoun k oxhmata, dld kleinei
    public:
        Toll(Attica_Tollway* o);
        ~Toll();
        bool is_available();
        bool is_empty();
        Vehicle *pass_tolls();
        virtual bool check_availability() = 0;
        int vehicles_waiting();
        virtual void change_state() = 0;
        void generate_vehicles(int entr);
        //void print_toll();
};

class e_toll : public Toll{
    private:
        int transit_rate;

    public:
        e_toll(Attica_Tollway* o, int rate, int entr);
        ~e_toll();
        bool check_availability();
        void change_state();

};

class collector_toll : public Toll{
    private:
        int transit_rate;

    public:
        collector_toll(Attica_Tollway* o, int rate, int entr);
        ~collector_toll();
        bool check_availability();
        void change_state();
};