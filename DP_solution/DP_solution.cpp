#include <iostream>
using namespace std;

// GLOBAL Constants
const int maxn = 15;
int cities;
double cost[maxn][maxn];
double dp[(1 << maxn)][maxn];
bool visited[maxn];

double TSP(int mask, int position) {
    if(mask == (1 << cities) - 1) // since mask is all 1's, means we have visited all cities
        return cost[position][0];
    
    if(dp[mask][position] != -1) // we have computed this before
        return dp[mask][position];
    
    double ans = INT_MAX;

    for(int city = 0; city < cities; ++city) {
        if((mask & (1 << city)) == 0) // has the city been visited
        {
            // if not, we recursively call the function with updated mask. 
            ans = min(ans , cost[position][city] + TSP( mask | (1 << city) , city ));
        }
    }
    return dp[mask][position] = ans;
}
int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt", "w", stdout);
    cin >> cities;
    for(int i = 0; i < cities; ++i) visited[i] = 0;
    for(int i = 0; i < cities; ++i) {
        for(int j = 0; j < cities; ++j) 
            cin >> cost[i][j];
    }  
    
    for(int i = 0; i <= (1 << (cities+1)); ++i) {
        for(int j = 0; j <= cities; ++j) 
            dp[i][j] = -1;
    }
    cout << TSP(1,0) << endl;
}

