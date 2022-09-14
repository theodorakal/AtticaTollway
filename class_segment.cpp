#include <iostream>
#include <list>
#include <ctime>
#include "class_attica_tollway.hpp"
#include "class_segment.hpp"
#include "class_entrance.hpp"
#include "class_toll.hpp"
#include "class_vehicle.hpp"

using namespace std;


//SEGMENT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Segment::Segment(Attica_Tollway* o, int random, int seg_no, int rate, double perc) 
    : vehicle_capacity(random), segment_no(seg_no), entrance(new Entrance(o, seg_no, rate)), percent(perc), previous(NULL), next(NULL){
    
    int random_number_of_vehicles = rand() % vehicle_capacity;
    for(int i = 0; i < random_number_of_vehicles; i++){
        Vehicle* v = new Vehicle(o, segment_no, -1); // den einai se eisodo , einai se segment
        vehicle_list.push_back(v);
    }

    set_ready();   //vazei se etoimotita to 40% twn oximatwn gia ton epomeno kuklo operate

}

Segment::~Segment(){
    //cout << "destroying a road segment" << endl;
    list<Vehicle*>::iterator it = vehicle_list.begin();
    while (it != vehicle_list.end()){
        Vehicle* to_delete = *it; 
        it = vehicle_list.erase(it);
        delete to_delete;
    }
    
    delete entrance;
}

void Segment::operate(int num_of_segments){
    cout << "operations in segment no: " << segment_no << endl;
    exit();
    bool flag1=0;
    if (previous != NULL){
        flag1 = previous->pass(num_of_segments);
    }

    if (flag1) {
        cout << "Delays between segments " << previous->segment_no << " and " << segment_no << "." << endl;
    }

    bool flag2 = enter();

    if(flag2){
        cout << "Delays in entrance " << segment_no << "." << endl;
    }

    if(!flag1 && !flag2){
        cout << "Keep safety distances in the segment after node " << segment_no << "." << endl;
    }

    entrance->reinitialize();
    entrance->refill_tolls();
    set_ready();         //vazei se etoimotita pali to 40% twn oximatwn gia ton epomeno kuklo operate
}

int Segment::get_no_of_vehicles() const{
    return vehicle_list.size(); 
}

void Segment::exit(){
    list<Vehicle*>::iterator it = vehicle_list.begin();
    
    while (it != vehicle_list.end()){       //diatrexw ti lista 
        if ((*it)->is_ready() && (*it)->get_destination() == segment_no){
            Vehicle* to_delete = *it;      //dinw ton deikth pros diagrafh gia na mhn xa8ei h dieu8unsh touh autokinhtou
            it = vehicle_list.erase(it);
            delete to_delete;        //otan kanw to erase, apla apodesmeuw th mnhmh meta tou autokinhtou pou bghke oristika apo ton autokinhtodromo-lista
        }
        else {
            it++;
        }
    }
}

bool Segment::pass(int num_of_segments){
    list<Vehicle*>::iterator it = vehicle_list.begin();
    bool didnt_pass = 0;                    //flag pou mas deixnei an estw kai 1 autokinhto pou einai se etoimothta na perasei den ta katafernei
    while (it != vehicle_list.end()){
        //αν ειναι ετοιμο και ο κομβος προορισμου ειναι μεταξυ segment_no + 1 και nsegs τοτε να προχωρησει στο επομενο τμημα
        if ((*it)->is_ready() && (*it)->get_destination() > segment_no && (*it)->get_destination() < num_of_segments){
            if (this->next->vehicle_list.size() < this->next->vehicle_capacity){
                Vehicle* to_enter_next_seg = *it;
                it = vehicle_list.erase(it);            //bgalto apo tin lista tou trexontos tmimatos kai prosthese to stin epomeni
                this->next->vehicle_list.push_back(to_enter_next_seg);
                to_enter_next_seg->set_not_ready();     //εφοσον μπηκε στο επομενο τμημα , δεν ειναι πλεον σε ετοιμοτητα
                to_enter_next_seg->change_state_of_vehicle(this->next->segment_no);
            }
            else{
                didnt_pass = 1;
                it++;
            }
        }
        else{
            it++;
        }
    }

    return didnt_pass;
}

bool Segment::enter(){
    bool delays = 0;
    int counter = 0;
    int veh_waiting_beginning = entrance->vehicles_waiting();

    int i = 0;
    while(vehicle_capacity - vehicle_list.size() > 0){       //enosw xwraei akoma to segment oxhmata...

        if(!entrance->check_tolls()){       //εαν ολα τα διοδια ειναι αδεια η μη διαθεσιμα, σταματα να ψαχνεις για οχηματα
            break;
        }

        Vehicle *v = entrance->operate(); // pairnei autokinhta apo thn entrance kai ta bazei sto segment
        if(v != NULL){
            vehicle_list.push_back(v);
            counter++;
            v->change_state_of_vehicle(segment_no);
            i++;
        }

    }

    if (counter < veh_waiting_beginning){
        delays = 1;
    }

    return delays;

}


void Segment::set_next(Segment *ptr){
    this->next = ptr;
}

void Segment::set_previous(Segment *ptr){
    this->previous = ptr;
}

void Segment::set_ready(){

    list<Vehicle*>::iterator it1;
    list<Vehicle*>::iterator it2 = vehicle_list.begin();
    advance(it2, vehicle_list.size() * percent);

    for(it1 = vehicle_list.begin();  it1 != it2; it1++){
        (*it1)->set_ready();
    }
}

// void Segment::print_vehicles(){
//     int i = 0;
//     cout << endl << endl;
//     cout << "Segment " << segment_no << " with capacity " << vehicle_capacity << endl;
//     for(list<Vehicle*>::iterator it = vehicle_list.begin(); it != vehicle_list.end(); it++){
//         cout << "---------------------" << endl;
//         cout << "Gia to oxhma " << i << endl;
//         cout << "i etoimotita tou oxhmatos " << i << " einai: " <<  (*it)->is_ready() << endl;
//         cout << "to destination node tou oximatos einai to: " << (*it)->get_destination() << endl;
//         (*it)->print_vehicle();
//         i++;
//     }
// }

// void Segment::print_entrance() const{
//     entrance->print_entrance();
// }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
