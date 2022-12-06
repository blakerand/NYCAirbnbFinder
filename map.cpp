#include <unordered_map>
#include <vector>
#include <utility>
#include <iostream>
using namespace std;

class Map {
  public:
    void insert(int price1, string name1, string neighbourhood1);
    void size();
    vector<string> search(int price_, string neighbourhood_);
  private:
    unordered_map <string, vector<string> > values;
};

void Map::insert(int price1, string name1, string neighbourhood1) {
  string key = to_string(price1) + neighbourhood1;
  values[key].push_back(name1);
}

void Map::size() {
  cout << values.size();
}

vector<string> Map::search(int price_, string neighbourhood_) {
  string key = to_string(price_) + neighbourhood_;
  int i = 0;

  try {
    return values.at(key);
  } catch (const std::out_of_range& oor) {
    vector<string> empty;
    return empty;
  }
}

