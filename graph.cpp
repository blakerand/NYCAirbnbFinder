#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Graph{
private:
   map<string, vector<pair<string, int> > > mp;

public:
    void insert(int price, string name, string neighborhood);
    void print(int price, string neighborhood);
    void printWholeGraph();
    vector<string> search(int price, string neighborhood);
};

//insert the edge into the adjacency list
void Graph::insert(int price, string name, string neighborhood){
    vector<pair<string, int> > airbnbs = mp[neighborhood];
    airbnbs.push_back(make_pair(name, price));
    mp[neighborhood] = airbnbs;
}

//search function to search the graph for the specified price and neighborhood. Search the adjacency list
//at the neighborhood specified and searches through that list for the prices
vector<string> Graph::search(int price, string neighborhood) {
    vector<string> airbnbs;
    try {
        for (int i =0; i < mp[neighborhood].size(); i++){
            if (mp[neighborhood][i].second == price){
                airbnbs.push_back(mp[neighborhood][i].first);
            }
        }
    } catch (const std::out_of_range& oor) {
        vector<string> empty;
        return empty;
    }
    
    return airbnbs;
}

//test function to print the graph
void Graph::printWholeGraph() {
    for(auto it = mp.begin(); it != mp.end(); it++) {
        cout << it->first;
        for(int i = 0; i < it->second.size(); i++) {
            cout << it->second[i].first << " " << it->second[i].second << endl;
        }

    }
}

