//
// Created by Oliver Yu on 2019-04-06.
//

#ifndef ASSIGNMENT16_STORE_H
#define ASSIGNMENT16_STORE_H
#include "Event.h"

class Store {
private:
    std::array<int, 6> lineTimes;
public:
    std::vector<int> waitTimes;
    void onArrival(Event e, int timePassed){
        Customer c = e.customer;
        // update line's wait times, but it can't go below zero
        for (int i = 0; i < this->lineTimes.size(); i++) {
            this->lineTimes[i] -= timePassed;
            if (this->lineTimes[i] < 0) {
                this->lineTimes[i] = 0;
            }
        }

        // find the shortest line
        std::sort(this->lineTimes.begin(), this->lineTimes.end());
        this->lineTimes[0] += c.secondsToService;
        this->waitTimes.push_back(this->lineTimes[0]);
    }
};

#endif //ASSIGNMENT16_STORE_H
