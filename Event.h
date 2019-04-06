//
// Created by Oliver Yu on 2019-04-06.
//

#ifndef ASSIGNMENT16_EVENT_H
#define ASSIGNMENT16_EVENT_H
#include <string>
#include <queue>
#include <array>

struct Customer {
    bool isNull;
    int secondsToService, arrivalTime;
    // totalSecondsWaiting starts out at secondsToService, and will change if they have to wait any longer (in line)
    Customer(int secondsToService, int arrivalTime) {
        this->secondsToService = secondsToService;
        this->arrivalTime = arrivalTime;
        this->isNull = false;
    }
    // default constructor, signifies the lack of a customer essentially
    Customer() {
        this->isNull = true;
        this->arrivalTime = -1;
        this->secondsToService = -1;
    }
};

class Event{
public:
    // Two types of events: Arrival & Departure
    // isArrival events happen to both store and bank, others only happen to bank.
    bool isArrival, isNull;
    //timeOfEvent applies to both
    int timeOfEvent, tellerNum;
    Customer customer;

    Event() : timeOfEvent(-1), isNull(true){}

    Event(bool isArrival, bool isNull, int timeOfEvent) : isArrival(isArrival), isNull(isNull), timeOfEvent(timeOfEvent) {}

    void setCustomer(Customer customer) {
        this -> customer = customer;
    }

    void setTellerNum(int tellerNum) {
        this -> tellerNum = tellerNum;
    }
};

class Arrival : public Event {
public:
    // events that take a Customer are interpreted as customers arriving
    Arrival(int timeOfEvent, Customer customer) : Event(true, false, timeOfEvent) {
        setCustomer(customer);
    }

};


//TODO: change every isArrival = false to Departure
class Departure : public Event {
public:
    // events that takes a tellerNum are interpreted as tellers finishing
    Departure(int timeOfEvent, int tellerNum) : Event(false, false, timeOfEvent) {
        setTellerNum(tellerNum);
    }
};
#endif //ASSIGNMENT16_EVENT_H
