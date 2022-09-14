#include <iostream>
#include <string>
#include <list>


using namespace std;



class Entrance;
class Toll;
class Vehicle;
class Attica_Tollway;

class Segment{
    private:
        Entrance *entrance;
        int segment_no;
        int vehicle_capacity; // xwrhtikothta oxhmatwn, to kathe tmima tha xwraei apo 200 mexri 400 oxhmata
        list <Vehicle*> vehicle_list;
        
        Segment *previous;
        Segment *next;
        double percent;
        
    public:
        Segment(Attica_Tollway* o, int cap, int seg_no, int rate, double perc);
        ~Segment();
        bool enter();
        void exit();
        bool pass(int num_of_segments);
        void set_previous(Segment *ptr);
        void set_next(Segment *ptr);
        int get_no_of_vehicles() const;
        void operate(int num_of_segments);
        void set_ready();
        //void print_vehicles();
        //void print_entrance() const;
};