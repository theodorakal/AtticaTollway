#include <iostream>
#include <list>
#include <ctime>
#include "class_attica_tollway.hpp"
#include "class_segment.hpp"
#include "class_entrance.hpp"
#include "class_toll.hpp"
#include "class_vehicle.hpp"

using namespace std;


//TOLL
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Toll::Toll(Attica_Tollway* o) : owner(o), available(true), vehicles_passed(0){

}

Toll::~Toll(){
    list<Vehicle*>::iterator it = vehicle_list.begin();
    while (it != vehicle_list.end()){
        Vehicle* to_delete = *it; 
        it = vehicle_list.erase(it);
        delete to_delete;
    }
}

   
Vehicle *Toll::pass_tolls(){

    if(!vehicle_list.empty()){    //an den einai adeio to vec twn oxhmatwn pisw apo ta diodia vgale to prwto
        if(check_availability()){    //an to diodio einai anoixto
            list<Vehicle*>::iterator it = vehicle_list.begin();
            Vehicle *v = *it;
            vehicle_list.erase(vehicle_list.begin());
            vehicles_passed++;
            return v;
        }
        else if(!check_availability()){
            available = false;
            return NULL;
        }
    }
    else{
        return NULL;
    }
    return NULL;
}  

bool Toll::is_available(){
    return available;
}

int Toll::vehicles_waiting(){
    return vehicle_list.size();
}



bool Toll::is_empty(){
    return vehicle_list.empty();
}

void Toll::generate_vehicles(int entr){
    int random_num_of_vehicles = (rand() % 10) + 1;
    for(int i = 0; i < random_num_of_vehicles; i++){
        Vehicle* v = new Vehicle(owner,-1,entr); // den einai mesa se segment, einai se eisodo
        vehicle_list.push_back(v);
    }
}

// void Toll::print_toll() {
//     list<Vehicle*>::iterator it;
//     cout << "Vehicles in this toll: " << vehicle_list.size() << endl;
//     for (it  = vehicle_list.begin(); it != vehicle_list.end(); it++) {
//         (*it)->print_vehicle(); 
//     }
    
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//eTOLL
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
e_toll::e_toll(Attica_Tollway* o, int rate, int entr) : Toll(o), transit_rate(rate){
    //cout << "an e toll is being built" << endl;
    int random_num_of_vehicles = (rand() % 5) + 10;
    cout << "In entrance " << entr << " random number of vehicles to create are: " << random_num_of_vehicles << endl;
    for(int i = 0; i < random_num_of_vehicles; i++){
        Vehicle* v = new Vehicle(owner,-1,entr);
        vehicle_list.push_back(v);
    }
    //δημιουργει τυχαιο αριθμο οχηματων, τα βαζει στο βεκτορ, αυτα περιμενουν πισω απο το διοδιο να μπουν στην αττικη οδο
}

e_toll::~e_toll() {

}

bool e_toll::check_availability(){
    if(vehicles_passed < transit_rate){
        return true;
    }
    else{
        return false;   //shmainei oti perase o max arithmos vehicles
    }
}

void e_toll::change_state(){
    if(!check_availability()){ // an false -> dhl an kataferan na perasei o max arithos vehicles
        transit_rate++;
    }
    else{
        transit_rate--;
    }
    vehicles_passed = 0;
    available = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//COLLECTOR_TOLL
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
collector_toll::collector_toll(Attica_Tollway* o, int rate, int entr) : Toll(o), transit_rate(rate){
    //cout << "a collector toll is being built" << endl;
    int random_num_of_vehicles = (rand() % 5) + 10;
    cout << "In entrance " << entr << " random number of vehicles to create are: " << random_num_of_vehicles << endl;
    for(int i = 0; i < random_num_of_vehicles; i++){
        Vehicle* v = new Vehicle(owner,-1,entr); // den einai mesa se segment, einai se eisodo
        vehicle_list.push_back(v);
    }
    //δημιουργει τυχαιο αριθμο οχηματων, τα βαζει στο βεκτορ, αυτα περιμενουν πισω απο το διοδιο να μπουν στην αττικη οδο

}

collector_toll::~collector_toll() {

}

bool collector_toll::check_availability(){
    if(vehicles_passed < transit_rate){
        return true;
    }
    else{
        return false;
    }
}

void collector_toll::change_state(){
    if(!check_availability()){ // an false -> dhl an kataferan na perasei o max arithos vehicles
        transit_rate++;
    }
    else{
        transit_rate--;
    }
    vehicles_passed = 0;
    available = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
