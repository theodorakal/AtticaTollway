#include <iostream>
#include <list>
#include <ctime>
#include "class_attica_tollway.hpp"
#include "class_segment.hpp"
#include "class_entrance.hpp"
#include "class_toll.hpp"
#include "class_vehicle.hpp"

using namespace std;



//ENTRANCE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Entrance::Entrance(Attica_Tollway* o, int entr_no, int rate) : entrance_no(entr_no), num_of_tolls((rand() % 5)+ 10), array_of_tolls(new Toll *[num_of_tolls]), last_toll(-1){
    cout << endl << endl << "entrance no: " << entrance_no << " is being built" << endl;
    
    number_of_e_tolls = rand() % num_of_tolls;
    number_of_collector_tolls = num_of_tolls - number_of_e_tolls;

    cout << "it contains a total of "  << num_of_tolls << " tolls, " << number_of_e_tolls << " of which are e tolls and " << number_of_collector_tolls << " are collector tolls." << endl;

    for(int i = 0; i < num_of_tolls; i++){
        if(i < number_of_e_tolls)
            array_of_tolls[i] = new e_toll(o, 2 * rate, entrance_no);
        else
            array_of_tolls[i] = new collector_toll(o, rate, entrance_no);
    }

}

Entrance::~Entrance(){
    for(int i = 0; i < num_of_tolls; i++){
        delete array_of_tolls[i];
    }
    delete[] array_of_tolls;
}

Vehicle* Entrance::operate(){
    if(last_toll == -1 || last_toll == num_of_tolls - 1){
        last_toll = 0;
        if(array_of_tolls[0]->is_available()){
            return array_of_tolls[0]->pass_tolls();
        }
        else if(!array_of_tolls[0]->is_available()){
            return NULL;
        }
    }

    else{
        last_toll++;
        if(array_of_tolls[last_toll]->is_available()){
            return array_of_tolls[last_toll]->pass_tolls();
        }
        else if(!array_of_tolls[last_toll]->is_available()){
            return NULL;
        }
    }
    return NULL;
}

int Entrance::vehicles_waiting() const{
    int waiting = 0;
    for(int i = 0; i < num_of_tolls; i++){
        waiting += array_of_tolls[i]->vehicles_waiting();
    }
    return waiting;
}

void Entrance::reinitialize(){
    for(int i = 0; i < num_of_tolls; i++){
        array_of_tolls[i]->change_state();
        last_toll = -1;
    }
}


bool Entrance::check_tolls(){
    int x = 0;
    for(int i =0; i < num_of_tolls; i++){
        if(!array_of_tolls[i]->is_available()){   //dhladh an einai unavailable kanoume ++
            x++;
        }
        x += array_of_tolls[i]->is_empty();
    }

    if(x == num_of_tolls){
        return false;
    }
    else{
        return true;
    }
}

void Entrance::refill_tolls(){
    for(int i =0; i < num_of_tolls; i++){
        array_of_tolls[i]->generate_vehicles(entrance_no);
    }
}
// void Entrance::print_entrance() const {
//     cout << "In entrance no : " << entrance_no << endl;
//     for(int i =0; i < num_of_tolls; i++) {
//         cout << "-------  in toll no " << i << "     ------" << endl;
//         array_of_tolls[i]->print_toll();
//     }
// }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
