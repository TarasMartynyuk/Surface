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
ostream& operator<<(ostream& os, const Coords& coords) {
    os << "(" << coords.x << ", " << coords.y << ")";
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
        tiles_(width_, vector<TileInfo>(height_, TileInfo())),
        width_(width), height_(height){}

    TileInfo& tileAt(int x, int y) {
        return tiles_.at(x).at(y);
    }
    TileInfo& tileAt(const Coords& coords) {
        return tileAt(coords.x, coords.y);
    }
    bool inBounds(const Coords& coords) {
        return coords.x >= 0 && coords.x < width_ &&
               coords.y >= 0 && coords.y < height_;
    }
private:
    vector<vector<TileInfo>> tiles_;
};//endregion

void getAdjacentWaterTiles(const Coords& center, World& world, vector<Coords>& adj) {
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

    unordered_set<Coords> visited;
    visited.reserve(world.width_ * world.height_);
    vector<Coords> adjacent(4);
    stack<Coords> to_visit;

    to_visit.push(start);

    while (! to_visit.empty()) {

        auto& next = to_visit.top();
        to_visit.pop();

        getAdjacentWaterTiles(next, world, adjacent);
        for(auto& adj : adjacent) {
            if(visited.count(adj) == 0) {
                to_visit.push(adj);
            }
        }
//        assert(adjacent.capacity() == 4);

        visited.insert(next);
    }

    int lake_area = visited.size();
    for(auto& lake_coord : visited) {
        world.tileAt(lake_coord).lake_area = lake_area;
    }
}

int main()
{
    int kWidth;
    int kHeight;
    cin >> kWidth;    cin.ignore();
    cin >> kHeight;    cin.ignore();
    cerr << kWidth << endl;
    cerr << kHeight << endl;

    World world(kWidth, kHeight);
    bool any_land_found  = false;
    for (int i = 0; i < kHeight; i++) {
        string row;
        getline(cin, row);

//        assert(row.size() == world.width_);
//        cerr<< row << endl;
        for (int j = 0; j < row.size(); ++j) {
            world.tileAt(j, i).is_water = row.at(j) == 'O';
            any_land_found = row.at(j) == '#';
        }
    }

//    for (int i = 0; i < kWidth; ++i) {
//        for (int j = 0; j < kHeight; ++j) {
//            cerr << world.tileAt(i, j) << " ";
//        }
//        cerr << endl;
//    }

    int N;
    cin >> N; cin.ignore();
//    cerr << "queries: " << N << endl;


    for (int k = 0; k < N; ++k) {

        if (! any_land_found) {
//            cout << "360000" << endl;
            continue;
        }

        Coords discover_coords{};

        cin >> discover_coords.x >> discover_coords.y;
        cin.ignore();

        auto& tile = world.tileAt(discover_coords);
        if (!tile.is_water) {
            cout << 0 << endl;
            continue;
        }

        if (tile.lake_area == 0) {
            discover(discover_coords, world);
        }
//        assert(tile.lake_area != 0);
        cout << tile.lake_area << endl;
    }

}