#ifndef ASSIGNMENT16_SIMUTILS_H
#define ASSIGNMENT16_SIMUTILS_H

#include "iomanip"
#include "Bank.h"
#include "Store.h"

// starts at time 0, goes up
bool operator<(const Event& a, const Event& b) {return a.timeOfEvent > b.timeOfEvent;}

void printStats(std::vector<int>& waitTimes, const std::string& label) {
    int size = waitTimes.size();
    std::sort(waitTimes.begin(), waitTimes.end());
    int iOfTen = .1 * size;
    int iOfFifty = .5 * size;
    int iOfNinety = .9 * size;
    double tenP = (double) waitTimes.at(iOfTen)/60;
    double fiftyP = (double) waitTimes.at(iOfFifty)/60;
    double ninetyP = (double) waitTimes.at(iOfNinety)/60;
    std::cout << std::fixed<<std::setprecision(2) << label << "\n 10th %tile: "
              << tenP << "\n"<<" 50th %tile: " << fiftyP << "\n" << " 90th %tile: " << ninetyP << "\n" << std::endl;
}

void runSim(std::priority_queue<Event>& events) {
    Bank bank = Bank();
    Store store = Store();
    
    int lastEventTime = 0;
    while (!events.empty()) {
        Event e = events.top();
        if (e.isArrival) {
            // Bank Simulation
            Event tellerEvent = bank.onArrival(e);
            if (!tellerEvent.isNull) {
                events.push(tellerEvent);
            }
            // Store Simulation
            Event e = events.top();
            int timePassed = e.timeOfEvent - lastEventTime;
            store.onArrival(e, timePassed);
            lastEventTime = e.timeOfEvent;
        } else {
            Event tellerEvent = bank.onTellerFinish(e);
            if (!tellerEvent.isNull) {
                events.push(tellerEvent);
            }
        }
        events.pop();
    }
    
    printStats(bank.waitTimes, "Bank wait times (in minutes):");
    printStats(store.waitTimes, "Store wait times (in minutes):");
}

#endif //ASSIGNMENT16_SIMUTILS_H
