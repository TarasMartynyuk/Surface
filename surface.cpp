#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <unordered_map>
#include <assert.h>
#include <unordered_set>

using namespace std;

//region struct
struct Coords { int x; int y; };
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
    World(int width, int height) : tiles_(height, vector<TileInfo>(width, TileInfo())) {}

    TileInfo& tileAt(int x, int y) {
        return tiles_.at(x).at(y);
    }
    TileInfo& tileAt(Coords coords) {
        return tileAt(coords.x, coords.y);
    }
private:
    vector<vector<TileInfo>> tiles_;
};//endregion

void discover(Coords coords, World& world) {
    //
    vector<Coords> lake;
    unordered_set<Coords> visited;
}

int main()
{
    int kWidth;
    cin >> kWidth; cin.ignore();
    int kHeight;
    cin >> kHeight; cin.ignore();

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
            // discover the lake by bfs
        }
        assert(tile.lake_area != 0);
        cout << tile.lake_area << endl;
    }
}