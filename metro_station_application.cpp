#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

struct Station {
    double distance;
    double time;
    unordered_set<string> connections;
};

class Graph {
    unordered_map<string, Station> stations;

public:
    void addStation(const string& name, double distance, double time, const unordered_set<string>& connections) {
        Station station;
        station.distance = distance;
        station.time = time;
        station.connections = connections;
        stations[name] = station;
    }

    void addEdge(const string& station1, const string& station2, double distance, double time) {
        stations[station1].connections.insert(station2);
        stations[station2].connections.insert(station1);
    }

    bool stationExists(const string& name) {
        return stations.find(name) != stations.end();
    }

    void displayAllStations() {
        cout << "Chennai Metro Stations:\n";
        for (const auto& entry : stations) {
            cout << "- " << entry.first << endl;
        }
        cout << endl;
    }

    void displayMetroMap() {
        cout << "Chennai Metro Map:\n";
        for (const auto& entry : stations) {
            cout << entry.first << " -> ";
            for (const auto& neighbor : entry.second.connections) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    double calculateFare(double distance) {
        // Fare calculation logic based on distance
        // Modify this as per the fare structure of Chennai Metro
        if (distance <= 2)
            return 10;
        else if (distance <= 4)
            return 20;
        else if (distance <= 6)
            return 30;
        else
            return 40;
    }

    double findShortestDistance(const string& source, const string& destination) {
        unordered_map<string, double> distances;
        unordered_map<string, string> previous;
        for (const auto& entry : stations) {
            distances[entry.first] = numeric_limits<double>::max();
        }

        distances[source] = 0;

        priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
        pq.push({0, source});

        while (!pq.empty()) {
            string current = pq.top().second;
            pq.pop();

            for (const auto& neighbor : stations[current].connections) {
                double weight = stations[current].distance;
                if (distances[current] + weight < distances[neighbor]) {
                    distances[neighbor] = distances[current] + weight;
                    previous[neighbor] = current;
                    pq.push({distances[neighbor], neighbor});
                }
            }
        }

        return distances[destination];
    }

    double findShortestTime(const string& source, const string& destination) {
        unordered_map<string, double> times;
        unordered_map<string, string> previous;
        for (const auto& entry : stations) {
            times[entry.first] = numeric_limits<double>::max();
        }

        times[source] = 0;

        priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
        pq.push({0, source});

        while (!pq.empty()) {
            string current = pq.top().second;
            pq.pop();

            for (const auto& neighbor : stations[current].connections) {
                double weight = stations[current].time;
                if (times[current] + weight < times[neighbor]) {
                    times[neighbor] = times[current] + weight;
                    previous[neighbor] = current;
                    pq.push({times[neighbor], neighbor});
                }
            }
        }

        return times[destination];
    }

    vector<string> findShortestPathByDistance(const string& source, const string& destination) {
        unordered_map<string, double> distances;
        unordered_map<string, string> previous;
        for (const auto& entry : stations) {
            distances[entry.first] = numeric_limits<double>::max();
        }

        distances[source] = 0;

        priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
        pq.push({0, source});

        while (!pq.empty()) {
            string current = pq.top().second;
            pq.pop();

            for (const auto& neighbor : stations[current].connections) {
                double weight = stations[current].distance;
                if (distances[current] + weight < distances[neighbor]) {
                    distances[neighbor] = distances[current] + weight;
                    previous[neighbor] = current;
                    pq.push({distances[neighbor], neighbor});
                }
            }
        }

        vector<string> shortestPath;
        string current = destination;
        while (previous.find(current) != previous.end()) {
            shortestPath.push_back(current);
            current = previous[current];
        }
        shortestPath.push_back(source);

        reverse(shortestPath.begin(), shortestPath.end());

        return shortestPath;
    }

    vector<string> findShortestPathByTime(const string& source, const string& destination) {
        unordered_map<string, double> times;
        unordered_map<string, string> previous;
        for (const auto& entry : stations) {
            times[entry.first] = numeric_limits<double>::max();
        }

        times[source] = 0;

        priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
        pq.push({0, source});

        while (!pq.empty()) {
            string current = pq.top().second;
            pq.pop();

            for (const auto& neighbor : stations[current].connections) {
                double weight = stations[current].time;
                if (times[current] + weight < times[neighbor]) {
                    times[neighbor] = times[current] + weight;
                    previous[neighbor] = current;
                    pq.push({times[neighbor], neighbor});
                }
            }
        }

        vector<string> shortestPath;
        string current = destination;
        while (previous.find(current) != previous.end()) {
            shortestPath.push_back(current);
            current = previous[current];
        }
        shortestPath.push_back(source);

        reverse(shortestPath.begin(), shortestPath.end());

        return shortestPath;
    }
};

void displayMenu() {
    cout << "-----------------------\n";
    cout << "Chennai Metro Navigation\n";
    cout << "-----------------------\n";
    cout << "1. Display All Stations\n";
    cout << "2. Display Metro Map\n";
    cout << "3. Find Shortest Distance\n";
    cout << "4. Find Shortest Path\n";
    cout << "5. Calculate Fare\n";
    cout << "6. Exit\n";
    cout << "-----------------------\n";
    cout << "Enter your choice: ";
}

int main() {
    Graph metroNetwork;

    // Adding stations
    metroNetwork.addStation("Central", 0, 0, {"Egmore", "Park"});
    metroNetwork.addStation("Egmore", 1, 2, {"Central", "Nungambakkam"});
    metroNetwork.addStation("Park", 2, 3, {"Central", "Nungambakkam", "Kodambakkam"});
    metroNetwork.addStation("Nungambakkam", 4, 5, {"Egmore", "Park", "Kodambakkam", "Teynampet"});
    metroNetwork.addStation("Kodambakkam", 6, 7, {"Park", "Nungambakkam", "Teynampet", "Vadapalani"});
    metroNetwork.addStation("Teynampet", 8, 9, {"Nungambakkam", "Kodambakkam", "Vadapalani", "Ashok Nagar"});
    metroNetwork.addStation("Vadapalani", 10, 11, {"Kodambakkam", "Teynampet", "Ashok Nagar", "Arumbakkam"});
    metroNetwork.addStation("Ashok Nagar", 12, 13, {"Teynampet", "Vadapalani", "Arumbakkam"});
    metroNetwork.addStation("Arumbakkam", 14, 15, {"Vadapalani", "Ashok Nagar"});

    // Adding edges
    metroNetwork.addEdge("Central", "Egmore", 1, 2);
    metroNetwork.addEdge("Central", "Park", 2, 3);
    metroNetwork.addEdge("Egmore", "Nungambakkam", 3, 4);
    metroNetwork.addEdge("Park", "Nungambakkam", 4, 5);
    metroNetwork.addEdge("Park", "Kodambakkam", 2, 3);
    metroNetwork.addEdge("Nungambakkam", "Kodambakkam", 2, 3);
    metroNetwork.addEdge("Nungambakkam", "Teynampet", 3, 4);
    metroNetwork.addEdge("Kodambakkam", "Teynampet", 3, 4);
    metroNetwork.addEdge("Kodambakkam", "Vadapalani", 2, 3);
    metroNetwork.addEdge("Teynampet", "Vadapalani", 2, 3);
    metroNetwork.addEdge("Teynampet", "Ashok Nagar", 4, 5);
    metroNetwork.addEdge("Vadapalani", "Ashok Nagar", 4, 5);
    metroNetwork.addEdge("Vadapalani", "Arumbakkam", 2, 3);
    metroNetwork.addEdge("Ashok Nagar", "Arumbakkam", 2, 3);

    int choice;
    string source, destination;
    double shortestDistance, shortestTime, fare;
    vector<string> shortestPath;

    do {
        displayMenu();
        cin >> choice;
        cout << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                metroNetwork.displayAllStations();
                break;
            case 2:
                metroNetwork.displayMetroMap();
                break;
            case 3:
               cout << "Enter source station: ";
               cin >> source;
               cout << "Enter destination station: ";
    cin.ignore();
    getline(cin, destination);
    cout << endl;
    shortestDistance = metroNetwork.findShortestDistance(source, destination);
    cout << "Shortest Distance: " << shortestDistance << " km\n";
    break;
            case 4:
                cout << "Enter source station: ";
                cin >> source;
                cout << "Enter destination station: ";
                cin >> destination;
                cout << endl;
                shortestPath = metroNetwork.findShortestPathByDistance(source, destination);
                                cout << "Shortest Path by Distance: ";
                for (const auto& station : shortestPath) {
                    cout << station << " -> ";
                }
                cout << endl;

                shortestPath = metroNetwork.findShortestPathByTime(source, destination);
                cout << "Shortest Path by Time: ";
                for (const auto& station : shortestPath) {
                    cout << station << " -> ";
                }
                cout << endl;
                break;
            case 5:
                cout << "Enter distance traveled (in km): ";
                double distance;
                cin >> distance;
                fare = metroNetwork.calculateFare(distance);
                cout << "Fare: Rs. " << fare << endl;
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }

        cout << endl;
    } while (choice != 6);

    return 0;
}