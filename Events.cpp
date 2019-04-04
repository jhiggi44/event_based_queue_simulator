#include <iostream>
#include <iomanip>
#include "Events.hpp"

// onArrival returns an Event if one needs to be added, otherwise it return null and they are added to the bank line
Event Bank::onArrival(Event e) {
    if (this->line.empty()) {
        // check for tellers that aren't busy
        for(int i = 0; i < this->tellers.size(); i++) {
            if (this->tellers[i].isNull) {
                this->tellers[i] = e.customer;
//                std::cout << "time now " << e.timeOfEvent << "\n";
                int timeOfEvent = e.timeOfEvent + e.customer.secondsToService;
//                std::cout << "time will finish " << timeOfEvent << "\n\n";
                //print isArrival to check
                return Event(timeOfEvent, i);
            }
        }
        // if all tellers are busy
        this->line.push(e.customer);
    } else {
        this->line.push(e.customer);
    }
    // This is a NULL event, which means no new event needs to be added
    return Event();
}

Event Bank::onTellerFinish(Event e) {
    // customer's arrival time - time now = total wait time.
//    std::cout << "teller num " << e.tellerNum << "\n";

//    std::cout << "teller #" << e.tellerNum << " finished at " << e.timeOfEvent
//                << " and the customer arrived at " << tellers[e.tellerNum].arrivalTime << "\n\n";
    int totalWaitTime = e.timeOfEvent - this->tellers[e.tellerNum].arrivalTime;
    this->waitTimes.push_back(totalWaitTime);

    if (!this->line.empty()) {
        Customer c = this->line.front();
        this->line.pop();
        this->tellers[e.tellerNum] = c;
        int timeOfEvent = e.timeOfEvent + c.secondsToService;
        return Event(timeOfEvent, e.tellerNum);
    }
    this->tellers[e.tellerNum] = Customer();
    // This is a NULL event, which means no new event needs to be added
    return Event();
}

void Store::onArrival(Event e, int timePassed) {
    Customer c = e.customer;
    // update line's wait times, but it can't go below zero
    for (int i = 0; i < this->lineTimes.size(); i++) {
        this->lineTimes[i] -= timePassed;
        if (this->lineTimes[i] < 0) {
            this->lineTimes[i] = 0;
        }
    }
//    for (int i = 0; i < this->lineTimes.size(); i++) {
//        std::cout << "line" << i << "'s wait is " << this->lineTimes[i] << "\n";
//    }

    // randomized line
//    int randomIndex = rand() % 6;
//    std::cout << "random index " << randomIndex << "\n";
//    this->lineTimes[randomIndex] += c.secondsToService;
//    this->storeWaitTimes.push_back(this->lineTimes[randomIndex]);

    // find the shortest line
    std::sort(this->lineTimes.begin(), this->lineTimes.end());
    this->lineTimes[0] += c.secondsToService;
    this->waitTimes.push_back(this->lineTimes[0]);
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

// starts at time 0, goes up
bool operator<(const Event& a, const Event& b) {return a.timeOfEvent > b.timeOfEvent;}

