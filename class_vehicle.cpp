#include <iostream>
#include <list>
#include <ctime>
#include "class_attica_tollway.hpp"
#include "class_segment.hpp"
#include "class_entrance.hpp"
#include "class_toll.hpp"
#include "class_vehicle.hpp"

using namespace std;



//VEHICLE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vehicle::Vehicle(Attica_Tollway* o, int seg, int entr) : ready(false) , segment(seg), entrance(entr){
    // prepei na exoume to plh8os twn segments ths attica tollway
    int upper_bound = o->segments() - 1; // to -1 giati mporei ta segments na einai 10, alla ari8mountai apo 0 ews 9
    int lower_bound;
    if(segment == -1){
        lower_bound = entrance;
    }
    else {
        lower_bound = segment;
    }
    //destination node metaksy komvou eisodou kai teleytaioy komvou -> estw oti exoume oti ta tmhmata 8a einai apo 200 ews 400
    destination = (rand() % (upper_bound - lower_bound + 1)) + lower_bound; // dhl apo seg - mexri 400 , apla epeidh einai pros8esh, estw to megisto apo rand 8a einai 400-seg , ara to sunoloko megisto 400-seg+seg=400
}

int Vehicle::get_destination() const{ return destination; }

void Vehicle::set_ready(){
    ready = true;
}

void Vehicle::set_not_ready(){
    ready = false;
}

bool Vehicle::is_ready(){
    return ready;
}

// kaleitai stis enter kai pass tou segment gia na allaksei ta antikeimena segment kai entrance tou autokinhtou
// pernaw san orisma to segment sto opoio 8a brisketai pleon
// gia auto sthn pass, afou pernaei sto epomeno , pernaw to segment_no tou epomenou
void Vehicle::change_state_of_vehicle(int seg){
    segment = seg;
    entrance = -1;
}

//prosorinh sunarthsh gia na dw an ginontai swsta oi allages tws state twn autokinhtwn
// void Vehicle::print_vehicle(){
//     cout << "einai mesa sthn entrance no: " << entrance << " kai sto segment no: " << segment << " me destination: " << destination << endl;
// }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////