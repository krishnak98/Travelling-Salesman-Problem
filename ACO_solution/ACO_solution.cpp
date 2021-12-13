#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int maxn = 1e3 + 5;
int cities;
double graph[maxn][maxn];
double pheromones[maxn][maxn];
double delta_pheromones[maxn][maxn];
double best_length = INT_MAX;
double best_route[maxn];
double probability[maxn][maxn];
int route[maxn][maxn];
int STARTING_CITY = 0; 
int iterations = 50;
int no_of_ants = 50; 
double pheramone_evaporation = 0.2;
double ALPHA = 0.5;
double BETA = 0.8;
double Q = 33523;

bool isValid(int ant) {
    for(int i = 0; i < cities - 1; ++i) {
        int cityi = route[ant][i];
        int cityj = route[ant][i+1];
        if(cityi < 0 || cityj < 0) return true;
        for(int j = 0; j < i-1; ++j) { 
            if(route[ant][i] == route[ant][j]) return true;
        }
    }
    if(route[ant][cities-1] == -1) return true;
    return false;
}

bool isVisited(int ant, int city) {
    for(int j = 0; j < cities; ++j) {
        if(route[ant][j] == city) return true;
    }
    return false;
}

double getLength(int ant) {
    double sum = 0.0;
	for (int j=0; j<cities; j++) {
		sum += graph[route[ant][j]][route[ant][(j+1)%cities]];
	}
	return sum;
}

double getProbability(int city_start, int curr_city, int ant) {
    double curr_eta = (double) pow(1.0 / graph[city_start][curr_city], BETA);
    double curr_tau = (double) pow( pheromones[city_start][curr_city], ALPHA);
    double sum = 0.0;
    for(int c = 0; c < cities; ++c) {
        if(!isVisited(ant, c)) {
            double eta = pow(1.0/graph[city_start][curr_city], BETA);
            double tau = (double) pow( pheromones[city_start][curr_city], ALPHA);
            sum += (eta * tau);
        }
    }
    return (curr_eta * curr_tau) / sum;
}

int getNextCity() {
    // generate random number
    double x = (double) rand() / (RAND_MAX);
    int i = 0;
    double sum = probability[i][0];
    while(sum < x) {
        ++i;
        sum += probability[i][0];
    }
    return probability[i][1];
}


void build(int ant) {
    route[ant][0] = STARTING_CITY;
    for(int i = 0; i < cities - 1; ++i) {
        int city_start = route[ant][i];
        int count = 0;
        for(int c = 0; c < cities; ++c) {
            if(city_start == c) continue;
            if(!isVisited(ant, c)) {
                probability[count][0] = getProbability(city_start, c, ant);
                probability[count][1] = c;
                ++count;
            }
        }
        if(count == 0) return;
        route[ant][i+1] = getNextCity();
    }
}


void resetRoutes() {
    for(int i = 0; i < no_of_ants; ++i) {
        for(int j = 0; j < cities; ++j) {
            route[i][j] = -1;
        }
    }
}

void updatePheromones() {
    for(int ant = 0; ant < no_of_ants; ++ant) {
        double route_length = getLength(ant);
        for(int c = 0; c < cities - 1; ++c) {
            int start_city = route[ant][c];
            int end_city = route[ant][c+1];
            delta_pheromones[start_city][end_city] += Q / route_length;
            delta_pheromones[end_city][start_city] += Q / route_length;
        }
    }
    for(int i = 0; i < cities; ++i) {
        for(int j = 0; j < cities; ++j) {
            pheromones[i][j] = (1 - pheramone_evaporation) * pheromones[i][j] + delta_pheromones[i][j];
            delta_pheromones[i][j] = 0;
        }
    }
}

void printPheromones() {
    for(int i = 0; i < cities; ++i) {
        for(int j = 0; j < cities; ++j) {
            cout << pheromones[i][j] << " ";
        }
        cout << endl;
    }
}

void optimize() {
    for(int i = 0; i < iterations; ++i) {
        cout << "Iteration " << i << endl;
        for(int ant = 0; ant < no_of_ants; ++ant) {
            while(isValid(ant)){
                for(int k = 0; k < cities; ++k) route[ant][k] = -1;
                build(ant);
            }
            double curr_length = getLength(ant);
            if(curr_length < best_length) {
                best_length = curr_length;
                for(int i = 0; i < cities; ++i) {
                    best_route[i] = route[ant][i];
                }
            }
        }
        updatePheromones();
        printPheromones();
        resetRoutes();
    }
}


int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
   
    cin >> cities;

    for(int i = 0; i < cities; ++i) {
        for(int j = 0; j < cities; ++j) {
            cin >> graph[i][j];
        }
    }

    for(int i = 0; i < cities; ++i) {
        for(int j = 0; j < cities; ++j) {
            pheromones[i][j] = 0.0;
            delta_pheromones[i][j] = 0.0;
            if(j < 2) {
                probability[i][j] = -1;
            }
        }
    }

    optimize();

    cout << best_length << endl;
    for(int i =0 ; i < cities; ++i) {
        cout << best_route[i] << " " ;
    }
    cout <<endl;

    return 0;
}