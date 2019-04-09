//
// Created by Oliver Yu on 2019-04-06.
//

#ifndef ASSIGNMENT16_BANK_H
#define ASSIGNMENT16_BANK_H
#include "Event.h"

class Bank {
private:
    std::array<Customer, 6> tellers;
    std::queue<Customer> line;
public:
    std::vector<int> waitTimes;

    Event onArrival(Event e){
        if (this->line.empty()) {
            // check for tellers that aren't busy
            for(int i = 0; i < this->tellers.size(); i++) {
                if (this->tellers[i].isNull) {
                    this->tellers[i] = e.customer;
                    //                std::cout << "time now " << e.timeOfEvent << "\n";
                    int timeOfEvent = e.timeOfEvent + e.customer.secondsToService;
                    //                std::cout << "time will finish " << timeOfEvent << "\n\n";
                    //print isArrival to check
                    return Departure(timeOfEvent, i);
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

    Event onTellerFinish(Event e) {
        int totalWaitTime = e.timeOfEvent - this->tellers[e.tellerNum].arrivalTime;
        this->waitTimes.push_back(totalWaitTime);

        if (!this->line.empty()) {
            Customer c = this->line.front();
            this->line.pop();
            this->tellers[e.tellerNum] = c;
            int timeOfEvent = e.timeOfEvent + c.secondsToService;
            return Departure(timeOfEvent, e.tellerNum);
        }
        this->tellers[e.tellerNum] = Customer();
        // This is a NULL event, which means no new event needs to be added
        return Event();
    }
};
#endif //ASSIGNMENT16_BANK_H
