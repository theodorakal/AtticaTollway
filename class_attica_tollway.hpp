#include <iostream>
#include <string>
#include <list>

using namespace std;



class Entrance;
class Toll;
class Vehicle;
class Attica_Tollway;
class Segment;


class Attica_Tollway {
    private:
        int num_of_segments;
        Segment **array_of_segments;     //pinakas me deiktes se segments

    public:
        Attica_Tollway(int NSegs, int rate, double percent);
        ~Attica_Tollway();
        void operate();
        int segments() const;
        //void print_segments() const;
};