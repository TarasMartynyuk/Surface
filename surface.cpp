#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

class Graph {
    vector<list < int>> edges_;

public:
    Graph(int& edges_count)
        : edges_(edges_count) {}

    void addAdge(int start, int finish) {
        edges_[start].push_back(finish);
    }

    const list<int>& adj(int p) {
        return edges_.at(p);
    }
};

int main()
{
    int L;
    cin >> L; cin.ignore();
    int H;
    cin >> H; cin.ignore();
    for (int i = 0; i < H; i++) {
        string row;
        getline(cin, row);
    }
    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        int X;
        int Y;
        cin >> X >> Y; cin.ignore();
    }
    for (int i = 0; i < N; i++) {

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << "answer" << endl;
    }
}