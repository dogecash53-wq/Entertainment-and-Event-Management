#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;
const int TYPES = 3;

string eventName[MAX], eventDate[MAX], eventVenue[MAX];
int capacity[MAX];
string ticketType[TYPES] = {"Regular", "VIP", "Student"};
double price[MAX][TYPES];
int sold[MAX][TYPES];
int eventCount = 0;

int findEvent(string name) {
    for (int i = 0; i < eventCount; i++) {
        if (eventName[i] == name) return i;
    }
    return -1;
}

int getTotalSold(int index) {
    int total = 0;
    for (int i = 0; i < TYPES; i++) total += sold[index][i];
    return total;
}

double getRevenue(int index) {
    double total = 0;
    for (int i = 0; i < TYPES; i++)
        total += price[index][i] * sold[index][i];
    return total;
}

void addEvent() {
    if (eventCount == MAX) {
        cout << "\nEvent list is full.\n";
        return;
    }

    cout << "\n--- ADD NEW EVENT ---\n";
    cout << "Enter event name: ";
    cin >> ws;
    getline(cin, eventName[eventCount]);

    if (findEvent(eventName[eventCount]) != -1) {
        cout << "Event already exists.\n";
        return;
    }

    cout << "Enter event date: ";
    getline(cin, eventDate[eventCount]);
    cout << "Enter event venue: ";
    getline(cin, eventVenue[eventCount]);

    cout << "Enter event capacity: ";
    cin >> capacity[eventCount];
    while (capacity[eventCount] <= 0) {
        cout << "Enter a capacity greater than zero: ";
        cin >> capacity[eventCount];
    }

    for (int i = 0; i < TYPES; i++) {
        cout << "Enter " << ticketType[i] << " ticket price: ";
        cin >> price[eventCount][i];
        sold[eventCount][i] = 0;
    }

    eventCount++;
    cout << "\nEvent added successfully!\n";
}

void viewEvents() {
    if (eventCount == 0) {
        cout << "\nNo events available.\n";
        return;
    }

    cout << "\n--- EVENT LIST ---\n";
    for (int i = 0; i < eventCount; i++) {
        cout << "\nEvent Number: " << i + 1 << endl;
        cout << "Name: " << eventName[i] << endl;
        cout << "Date: " << eventDate[i] << endl;
        cout << "Venue: " << eventVenue[i] << endl;
        cout << "Capacity: " << capacity[i] << endl;
        cout << "Tickets Sold: " << getTotalSold(i) << endl;
        cout << "Available Slots: "
             << capacity[i] - getTotalSold(i) << endl;
    }
}

void searchEvent() {
    if (eventCount == 0) {
        cout << "\nNo events to search.\n";
        return;
    }

    string name;
    cout << "\nEnter event name to search: ";
    cin >> ws;
    getline(cin, name);

    int index = findEvent(name);
    if (index == -1) {
        cout << "Event not found.\n";
    } else {
        cout << "\n--- EVENT FOUND ---\n";
        cout << "Name: " << eventName[index] << endl;
        cout << "Date: " << eventDate[index] << endl;
        cout << "Venue: " << eventVenue[index] << endl;
        cout << "Capacity: " << capacity[index] << endl;
        cout << "Tickets Sold: " << getTotalSold(index) << endl;
        cout << "Available Slots: "
             << capacity[index] - getTotalSold(index) << endl;

        for (int i = 0; i < TYPES; i++) {
            cout << ticketType[i] << " Price: " << price[index][i] << endl;
            cout << ticketType[i] << " Sold: " << sold[index][i] << endl;
        }
        cout << "Total Revenue: PHP " << getRevenue(index) << endl;
    }
}

void sellTickets() {
    if (eventCount == 0) {
        cout << "\nNo events available.\n";
        return;
    }

    string name;
    cout << "\nEnter event name: ";
    cin >> ws;
    getline(cin, name);

    int index = findEvent(name);
    if (index == -1) {
        cout << "Event not found.\n";
        return;
    }

    cout << "\nChoose Ticket Type:\n";
    for (int i = 0; i < TYPES; i++)
        cout << i + 1 << ". " << ticketType[i]
             << " - PHP " << price[index][i] << endl;

    int choice;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice < 1 || choice > TYPES) {
        cout << "Invalid ticket type.\n";
        return;
    }

    int type = choice - 1;
    int quantity;
    cout << "Enter number of tickets: ";
    cin >> quantity;

    int available = capacity[index] - getTotalSold(index);

    if (quantity <= 0) {
        cout << "Invalid ticket quantity.\n";
    } else if (quantity > available) {
        cout << "Not enough available slots. Available: "
             << available << endl;
    } else {
        sold[index][type] += quantity;
        cout << "\nTicket registration successful!\n";
        cout << "Event: " << eventName[index] << endl;
        cout << "Ticket Type: " << ticketType[type] << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Total Payment: PHP "
             << quantity * price[index][type] << endl;
        cout << "Remaining Slots: "
             << capacity[index] - getTotalSold(index) << endl;
    }
}

void updateEvent() {
    if (eventCount == 0) {
        cout << "\nNo events available to update.\n";
        return;
    }

    string name;
    cout << "\nEnter event name to update: ";
    cin >> ws;
    getline(cin, name);

    int index = findEvent(name);
    if (index == -1) {
        cout << "Event not found.\n";
        return;
    }

    cout << "Enter new event name: ";
    getline(cin, eventName[index]);
    cout << "Enter new event date: ";
    getline(cin, eventDate[index]);
    cout << "Enter new event venue: ";
    getline(cin, eventVenue[index]);

    int totalSold = getTotalSold(index);
    cout << "Enter new event capacity: ";
    cin >> capacity[index];

    while (capacity[index] < totalSold) {
        cout << "Capacity cannot be lower than tickets already sold.\n";
        cout << "Enter capacity again: ";
        cin >> capacity[index];
    }

    for (int i = 0; i < TYPES; i++) {
        cout << "Enter new " << ticketType[i] << " ticket price: ";
        cin >> price[index][i];
    }

    cout << "\nEvent updated successfully!\n";
}

void salesSummary() {
    if (eventCount == 0) {
        cout << "\nNo sales records available.\n";
        return;
    }

    int allTickets = 0;
    double allRevenue = 0;

    cout << "\n--- EVENT SALES SUMMARY ---\n";
    for (int i = 0; i < eventCount; i++) {
        int totalSold = getTotalSold(i);
        double revenue = getRevenue(i);

        cout << "\nEvent: " << eventName[i] << endl;
        cout << "Tickets Sold: " << totalSold << endl;
        cout << "Available Slots: " << capacity[i] - totalSold << endl;
        cout << "Revenue: PHP " << revenue << endl;

        allTickets += totalSold;
        allRevenue += revenue;
    }

    cout << "\nTotal Events: " << eventCount << endl;
    cout << "Total Tickets Sold: " << allTickets << endl;
    cout << "Total Revenue: PHP " << allRevenue << endl;
}

int main() {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << " ENTERTAINMENT AND EVENT MANAGEMENT\n";
        cout << "====================================\n";
        cout << "1. Add New Event\n";
        cout << "2. View All Events\n";
        cout << "3. Search Event\n";
        cout << "4. Register / Sell Tickets\n";
        cout << "5. Update Event Information\n";
        cout << "6. Display Sales Summary\n";
        cout << "7. Exit\n";
        cout << "====================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addEvent(); break;
            case 2: viewEvents(); break;
            case 3: searchEvent(); break;
            case 4: sellTickets(); break;
            case 5: updateEvent(); break;
            case 6: salesSummary(); break;
            case 7: cout << "\nThank you for using the system!\n"; break;
            default: cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
