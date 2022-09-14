attica_tollway: main.cpp
	g++ -c main.cpp
	g++ -c class_attica_tollway.cpp
	g++ -c class_segment.cpp
	g++ -c class_entrance.cpp
	g++ -c class_toll.cpp
	g++ -c class_vehicle.cpp
	g++ -o attica_tollway main.o class_attica_tollway.o class_segment.o class_entrance.o class_toll.o class_vehicle.o
