#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <unordered_map>
#include <assert.h>
#include <unordered_set>
#include <stack>
#include <sstream>

using namespace std;

//region struct
struct Coords { int x; int y; };
bool operator== (const Coords& left, const Coords& right) {
    return  left.x == right.x && left.y == right.y;
}
namespace std {
    template<>
    struct hash<Coords> {
        size_t operator() (const Coords& coords) const {
            return hash<int>()(coords.x) + hash<int>()(coords.y);
        }
    };
}
struct TileInfo {
    TileInfo() : is_water(false), lake_area(0) {}
    bool is_water;
    int lake_area;
};
ostream& operator<< (ostream& os, const TileInfo& t) {
    os << "(" << (t.is_water ? "O" : "#") << " : " << t.lake_area << ")";
}
class World {
public:
    const int width_;
    const int height_;

    World(int width, int height) :
        tiles_(height, vector<TileInfo>(width, TileInfo())),
        width_(width), height_(height){}

    TileInfo& tileAt(int x, int y) {
        return tiles_.at(x).at(y);
    }
    TileInfo& tileAt(Coords coords) {
        return tileAt(coords.x, coords.y);
    }
    bool inBounds(const Coords& coords) {
        return coords.x >= 0 || coords.x < width_ ||
               coords.y >= 0 || coords.y < height_;
    }
private:
    vector<vector<TileInfo>> tiles_;
};//endregion

void getAdjacent(Coords center, World& world, vector<Coords>& adj) {
    adj.clear(); // does not change the capacity
    Coords left{ center.x - 1, center.y };
    if (world.inBounds(left) && world.tileAt(left).is_water) {
        adj.push_back(left);
    }

    Coords top { center.x, center.y + 1 };
    if(world.inBounds(top) && world.tileAt(top).is_water) {
        adj.push_back(top);
    }

    Coords right { center.x + 1, center.y };
    if(world.inBounds(right) && world.tileAt(right).is_water) {
        adj.push_back(right);
    }

    Coords bot { center.x, center.y - 1 };
    if(world.inBounds(bot) && world.tileAt(bot).is_water) {
        adj.push_back(bot);
    }
}

void discover(Coords start, World& world) {
    vector<Coords> lake_coords;

    unordered_set<Coords> visited;
    vector<Coords> adjacent(4);
    stack<Coords> to_visit;

    to_visit.push(start);

    while (! to_visit.empty()) {

        auto& next = to_visit.top();
        to_visit.pop();

        getAdjacent(next, world, adjacent);
        for(auto adj : adjacent) {
            to_visit.push(adj);
        }

        visited.insert(next);
    }

    int lake_area = lake_coords.size();
    for(auto& lake_coord : lake_coords) {
        world.tileAt(lake_coord).lake_area = lake_area;
    }
}

int main()
{
    stringstream ss;
    ss << 4 << endl <<
       4 << endl <<
       "####\n"  <<
          "##O#\n" <<
          "#OO#\n" <<
          "####\n" <<
             "3\n" <<
            "0 0\n" <<
            "1 2\n" <<
            "2 1\n";

    stringstream& cin = ss;


    int kWidth;
    int kHeight;
    cin >> kWidth;    cin.ignore();
    cin >> kHeight;    cin.ignore();


    World world(kWidth, kHeight);
    for (int i = 0; i < kHeight; i++) {
        string row;
        getline(cin, row);
        cerr<< row << endl;
        for (int j = 0; j < row.size(); ++j) {
            world.tileAt(i, j).is_water = row.at(j) == 'O';
        }
    }

    for (int i = 0; i < kHeight; ++i) {
        for (int j = 0; j < kWidth; ++j) {
            cerr << world.tileAt(i, j) << " ";
        }
        cerr << endl;
    }

    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        Coords discover_coords;
        cin >> discover_coords.x >> discover_coords.y; cin.ignore();

        auto& tile = world.tileAt(discover_coords);
        if(! tile.is_water) {
            cout << 0 << endl;
            continue;
        }

        if(tile.lake_area == 0) {
           discover(discover_coords, world);
        }
        assert(tile.lake_area != 0);
        cout << tile.lake_area << endl;
    }
}