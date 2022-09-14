#include <iostream>
#include <ctime>
#include "class_attica_tollway.hpp"
#include "class_segment.hpp"
#include "class_entrance.hpp"
#include "class_toll.hpp"
#include "class_vehicle.hpp"

using namespace std;



int main(int argc, char *argv[]){
    srand(time(NULL));

    if (argc != 5) {
        cout << "Invalide number of parameters given from command line" << endl;
        cout << "Sorry, ending program" << endl;
        return 0;
    }

    int N = atoi(argv[1]);
    int NSegs = atoi(argv[2]);
    int K = atoi(argv[3]);
    double percent = stod(argv[4]);

    
    Attica_Tollway tollway(NSegs, K, percent);

    tollway.print_segments();
    for (int i = 0; i < N; i++){
        tollway.operate();
    }

    return 0;
}