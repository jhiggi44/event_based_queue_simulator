#include <iostream>
#include <queue>
#include <array>
#include "simUtils.h"


int main(int argc, const char* argv[]) {
    if (argc < 3) {
        std::cout << "Not enough args...\n";
        exit(1);
    }
    
    const int hours_of_operation = 12;
    const int total_minutes = hours_of_operation * 60;
    const int total_seconds = total_minutes * 60;
    const int totalCustomers = std::atof(argv[1]) * total_minutes;
    const int maxServiceTimeInSeconds = std::atof(argv[2]) * 60;
    const long seed = std::atol(argv[3]);

    std::srand(seed);
    std::priority_queue<Event> events;
//    std::cout << "total customers is " << totalCustomers << "\n";
//    std::cout << "max service time in seconds is " << maxServiceTimeInSeconds << "\n";

    // generate customers and events
    for (int i = 0; i < totalCustomers; i++) {
        int arrivalTime = rand() % total_seconds;
        int secondsToService = rand() % maxServiceTimeInSeconds;
        Customer c = Customer(secondsToService, arrivalTime);
        events.emplace(Arrival(arrivalTime, c));
    }

    runSim(events);

    return 0;
}
