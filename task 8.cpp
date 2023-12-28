#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Boat {
public:
    int boatNumber;
    double totalMoney;
    int totalHours;
    int returnTime; // in 24-hour format, e.g., 1700 for 5 PM

    Boat(int number) : boatNumber(number), totalMoney(0), totalHours(0), returnTime(1000) {}

    bool isAvailable(int currentTime) {
        return currentTime >= returnTime;
    }

    bool hireBoat(int duration, int startTime) {
        // Check if the boat is available and within operating hours
        int endTime = startTime + duration;
        if (startTime < 1000 || endTime > 1700 || duration <= 0 || !isAvailable(startTime)) {
            cout << "Boat " << boatNumber << " cannot be hired at this time. Operating hours are from 10:00 to 17:00, or the boat is already booked." << endl;
            return false;
        }

        // Calculate cost
        double cost = (duration == 30) ? 12 : 20;
        totalMoney += cost;
        totalHours += duration / 60.0;

        returnTime = endTime;
        cout << "Boat " << boatNumber << " hired for $" << cost << ", return by " << returnTime << "." << endl;
        return true;
    }
};

void endOfDayReport(const vector<Boat>& boats) {
    double totalMoney = 0;
    double totalHours = 0;
    int unusedBoats = 0;
    int mostUsedBoat = 0;
    double maxHours = 0;

    for (const auto& boat : boats) {
        totalMoney += boat.totalMoney;
        totalHours += boat.totalHours;
        if (boat.totalHours == 0) {
            unusedBoats++;
        }
        if (boat.totalHours > maxHours) {
            maxHours = boat.totalHours;
            mostUsedBoat = boat.boatNumber;
        }
    }

    cout << "Total Money Taken: $" << totalMoney << endl;
    cout << "Total Hours Hired: " << totalHours << endl;
    cout << "Unused Boats: " << unusedBoats << endl;
    cout << "Most Used Boat: " << mostUsedBoat << endl;
}

int main() {
    vector<Boat> boats;
    for (int i = 1; i <= 10; ++i) {
        boats.emplace_back(i);
    }

    bool running = true;
    int currentTime = 1000; // Assuming the program starts at 10:00 AM
    while (running) {
        int boatNumber, duration, startTime;
        cout << "Enter boat number (1-10) to hire, or -1 to end: ";
        cin >> boatNumber;

        if (boatNumber == -1) {
            break;
        }

        if (boatNumber < 1 || boatNumber > 10) {
            cout << "Invalid boat number. Please try again." << endl;
            continue;
        }

        cout << "Enter hire duration (30 or 60 minutes): ";
        cin >> duration;
        cout << "Enter start time (1000 to 1700): ";
        cin >> startTime;

        // Update current time for availability check
        currentTime = startTime;

        if (!boats[boatNumber - 1].hireBoat(duration, startTime)) {
            cout << "Failed to hire boat. Please try again." << endl;
        }
    }

    endOfDayReport(boats);

    return 0;
}

