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

struct Event {
    // Two types of events: Arrival & Departure
    // isArrival events happen to both store and bank, others only happen to bank.
    bool isArrival, isNull;
    // timeOfEvent applies to both, tellerNum applies to only Departure
    int timeOfEvent, tellerNum;
    // Customer applies to only Arrival
    Customer customer;
    // events that takes a tellerNum are interpreted as tellers finishing
    Event(int timeOfEvent, int tellerNum) {
        this->isArrival = false;
        this->timeOfEvent = timeOfEvent;
        this->tellerNum = tellerNum;
        this->isNull = false;
    }
    // events that take a Customer are interpreted as customers arriving
    Event(int timeOfEvent, Customer customer) {
        this->isArrival = true;
        this->timeOfEvent = timeOfEvent;
        this->customer = customer;
        this->isNull = false;
    }
    //NULL event
    Event() {
        this->timeOfEvent = -1;
        this->isNull = true;
    }
};

class Bank {
private:
    std::array<Customer, 6> tellers;
    std::queue<Customer> line;
public:
    std::vector<int> waitTimes;
    Event onArrival(Event e);
    Event onTellerFinish(Event e);
};

class Store {
private:
    std::array<int, 6> lineTimes;
public:
    std::vector<int> waitTimes;
    void onArrival(Event e, int timePassed);
};

void printStats(std::vector<int>& waitTimes, const std::string& label);
void runSim(std::priority_queue<Event>& events);
bool operator<(const Event& a, const Event& b);

