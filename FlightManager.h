#ifndef FLIGHTMANAGER_H
#define FLIGHTMANAGER_H

#include <vector>
#include <string>
#include "Flight.h"
using namespace std;

class FlightManager {

private:
    vector<Flight> flights;
    int selectedIndex;   // index of selected flight 

public:
    FlightManager();

    // Load file
    bool loadFlights(const string& filename);
    bool loadPassengers(const string& filename);

    // Display then select option
    void displayFlightList() const;
    bool selectFlight(int choice);

    // Get file
    Flight* getSelectedFlight();
    bool hasSelectedFlight() const { return selectedIndex != -1; }

    // save
    bool savePassengers(const string& filename) const;


    int getFlightCount() const { return flights.size(); }
};

#endif
