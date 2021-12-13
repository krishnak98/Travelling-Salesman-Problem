#include <iostream>
#include <set>
using namespace std;

const int maxn = 1e3 + 5;
double cost[maxn][maxn];
int cities; 
int tour[maxn];

void getInitialTour() {
    // gets a initial tour using closest neighbor starting and ending at the 0th node
    tour[0] = 0;
    int curr = 0, minn, closest;
    set<int> visited;
    visited.insert(0);
    for(int i = 1; i < cities; ++i) {
        minn = INT_MAX;
        closest = -1;
        for(int j = 0; j < cities; ++j) {
            if(curr == j || visited.find(j) != visited.end()) continue;
            if(minn > cost[curr][j]) {
                // update nearest neighbor
                minn = cost[curr][j];
                closest = j;
            }
        }
        if(closest == -1) break;
        tour[i] = closest;
        curr = closest;
        visited.insert(curr);
    }
}


bool perform2OptIfPossible() {
    int curr_distance = 0, new_distance = 0;
    bool better = false;
    for (int i = 0; i < cities ; ++i) {
        // get distance of current path
        curr_distance += cost[tour[i]][tour[(i+1)%cities]];
    }
    int new_tour[cities];
    
    for (int i = 0; i < cities - 1; i++) {
        for (int k = i + 1; k < cities; k++)
        {
            // switch path i and k in the tour and check if distance is lower
            int dec = 0;
            for(int j = 0; j < cities; ++j) 
            { 
                if(j < i || j > k) {
                    // this part of the tour remains same
                    new_tour[j] = tour[j];
                }
                else {
                    new_tour[j] = tour[k-dec];
                    ++dec;
                }
            }

            // check if this tour is faster than original tour
            new_distance = 0;
            for (int i = 0; i < cities ; ++i) {
                // get distance of current path
                new_distance += cost[new_tour[i]][new_tour[(i+1)%cities]];
            }
            if(curr_distance > new_distance) {
                cout << curr_distance << " " << new_distance << endl;
                // better route found
                for(int l = 0; l < cities; ++l) tour[l] = new_tour[l];
                return true;
            }
        }
    }
    return false;
}


int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    for(int i = 0; i < maxn; ++i) {
        tour[i] = 0;
    }

    cin >> cities;
    for(int i = 0; i < cities; ++i) {
        for(int j = 0; j < cities; ++j) {
            cin >> cost[i][j];
        }
    }

    getInitialTour();
    int distance = 0;
     
    for(int i = 0; i < cities; ++i) {
        distance += cost[tour[i]][tour[(i+1)%cities]];
    }
       cout << "Initial distance " << distance << endl;

    while(true) {
        // keep continuing till we reach local minima
        bool better = perform2OptIfPossible();
        if(better == false) break;
    }

    distance = 0;
    for(int i = 0; i < cities; ++i) {
        distance += cost[tour[i]][tour[(i+1)%cities]];
    }

    cout << "Distance after 2-opt " << distance << endl;

    return 0;
}