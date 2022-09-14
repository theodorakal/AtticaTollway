#include <iostream>
#include <list>
#include <ctime>
#include "class_attica_tollway.hpp"
#include "class_segment.hpp"
#include "class_entrance.hpp"
#include "class_toll.hpp"
#include "class_vehicle.hpp"

using namespace std;

class Segment;
class Entrance;
class Toll;
class Vehicle;



//ATTICA_TOLLWAY
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Attica_Tollway::Attica_Tollway(int NSegs, int rate, double per) : num_of_segments(NSegs), array_of_segments(new Segment *[NSegs]){
    cout << "Highway in operation" << endl;

    for(int i = 0; i < num_of_segments; i++){ //ftiaxnw ta segments kai ta topothetw ston pinaka
        int random = (rand() % 200) + 200;       //xwritikotita metaksy 200 kai 400 oxhmatwn - capacity tou ka8e segment
        Segment *seg = new Segment(this, random, i, rate, per);
        array_of_segments[i] = seg;
    }

    for(int i = 0; i < num_of_segments - 1; i++){       //thetw tous deiktes sto next. to for loop mexri num-1 giati to teleytaio segment den exei epomeno opote to afinw null to next ptr tou teleutaiou segment
        array_of_segments[i]->set_next(array_of_segments[i + 1]);
    }
    for(int i = 1; i < num_of_segments; i++){       //thetw tous deiktes sto previous. to for loop apo 1 giati to prwto segment den exei proigoumeno opote to afinw null to prev ptr tou prwtou segment
        array_of_segments[i]->set_previous(array_of_segments[i - 1]);
    }
}

Attica_Tollway::~Attica_Tollway(){
    cout << "destroying the tollway" << endl;
    for(int i = 0; i < num_of_segments; i++){
        delete array_of_segments[i];
    }
    delete[] array_of_segments;
}

void Attica_Tollway::operate(){
    cout << "in tollway operate..." << endl;
    for(int i = num_of_segments - 1; i >= 0; i--){
        array_of_segments[i]->operate(segments());
        cout << "Number of vehicles in segment " << i << " is " << array_of_segments[i]->get_no_of_vehicles() << endl;
    }

}

int Attica_Tollway::segments() const {
    return num_of_segments;
}

// void Attica_Tollway::print_segments() const{

//     for(int i = 0; i < num_of_segments; i++){
//         cout << "In segment no: " << i << endl << endl;
//         array_of_segments[i]->print_entrance();
//         array_of_segments[i]->print_vehicles();
//     }
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





