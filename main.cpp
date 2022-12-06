#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include "map.cpp"
#include "graph.cpp"
using namespace std;


vector<vector <string> > readFile(Map &map, Graph &graph) {
    ifstream file("AB_NYC_2019.csv");
    string line;
    vector<vector <string> > airbnbs;

    if (file.is_open()) {
        getline(file, line);
        getline(file, line);
        
        while (!file.eof()) {
            getline(file, line);

            stringstream temp(line);
            string column;
            string row[16];

            int i = 0;
            while (getline(temp, column, ',') && i < 16) {
                row[i] = column;
                i++;
            }
            string id, name, neighborhood, price, longitude, latitude;
            id = row[0];
            name = row[1];
            neighborhood = row[5];
            price = row[9];
            latitude = row[6];
            longitude = row[7];
            vector <string> airbnb;
            airbnb.push_back(price);
            airbnb.push_back(name);
            airbnb.push_back(neighborhood);

            airbnbs.push_back(airbnb);
        }
    }
    return airbnbs;
}

void initializeMap(Map &map, vector<vector <string> > airbnbs) {
    for (int i = 0; i < airbnbs.size(); i++) {
        try {
            map.insert(stoi(airbnbs[i][0]), airbnbs[i][1], airbnbs[i][2]);
        } catch (const std::invalid_argument& ia) {
        }
    }
}

void initializeGraph(Graph &graph, vector<vector <string> > airbnbs) {
    for (int i = 0; i < airbnbs.size(); i++) {
        try {
            graph.insert(stoi(airbnbs[i][0]), airbnbs[i][1], airbnbs[i][2]);
        } catch (const std::invalid_argument& ia) {
        }
    }
}


int main() {
    Map map;
    Graph graph;
    
    cout << "Welcome to Airbnb Finder" << endl;
    cout << "Initializing map and graph..." << endl;
    vector<vector <string> > airbnbs = readFile(map, graph);

    auto mapStart = chrono::high_resolution_clock::now();
    initializeMap(map, airbnbs);
    auto mapEnd = chrono::high_resolution_clock::now();

    auto graphStart = chrono::high_resolution_clock::now();
    initializeGraph(graph, airbnbs);
    auto graphEnd = chrono::high_resolution_clock::now();

    auto mapDuration = chrono::duration_cast<chrono::microseconds>(mapEnd - mapStart);
    auto graphDuration = chrono::duration_cast<chrono::microseconds>(graphEnd - graphStart);

    cout << "Map initialization time: " << mapDuration.count() << " microseconds" << endl;
    cout << "Graph initialization time: " << graphDuration.count() << " microseconds" << endl;

    string neighborhoodToSearch;
    int priceToSearch;

    
    cout << "\nWe are here to help you find the best Airbnb in NYC for your desired trip! " <<
    "What NYC neighborhood would you like to stay in? ";
    cin >> neighborhoodToSearch;
    cout << "What price would you like to spend per night: ";
    cin >> priceToSearch;

    cout << "Here are all the Airbnbs using a map in " << neighborhoodToSearch << " for $" << priceToSearch << " a night is:" << endl;


    auto mapSearchStart = chrono::high_resolution_clock::now();
    vector<string> airbnbMap = map.search(priceToSearch, neighborhoodToSearch);
    auto mapSearchEnd = chrono::high_resolution_clock::now();
    auto mapSearchDuration = chrono::duration_cast<chrono::microseconds>(mapSearchEnd - mapSearchStart);

    if (airbnbMap.size() == 0) {
        cout << "No Airbnbs that match your requirements found in the map!" << endl;
    } else {
        for (int i = 0; i < airbnbMap.size(); i++) {
            cout << airbnbMap[i] << endl;
        }
    }

    cout << "\nHere are all the Airbnbs using a graph in " << neighborhoodToSearch << " for $" << priceToSearch << " a night is:" << endl;

    auto graphSearchStart = chrono::high_resolution_clock::now();
    vector<string> airbnbGraph = graph.search(priceToSearch, neighborhoodToSearch);
    auto graphSearchEnd = chrono::high_resolution_clock::now();
    auto graphSearchDuration = chrono::duration_cast<chrono::microseconds>(graphSearchEnd - graphSearchStart);

    if (airbnbGraph.size() == 0) {
        cout << "No Airbnbs that match your requirements found in the graph!" << endl;
    } else {
        for (int i = 0; i < airbnbGraph.size(); i++) {
            cout << airbnbGraph[i] << endl;
        }
    }

    if (airbnbMap.size() != 0 && airbnbGraph.size() != 0) {
        cout << "\nTotal count of Airbnbs using a map: " <<  airbnbMap.size() << endl;
        cout << "Total count of Airbnbs using a graph: " << airbnbGraph.size() << endl;
    }

    cout << "Map search time: " << mapSearchDuration.count() << " microseconds" << endl;
    cout << "Graph search time: " << graphSearchDuration.count() << " microseconds" << endl;

}