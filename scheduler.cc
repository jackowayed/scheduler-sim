#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > FifoSchedule(vector<int> & resources, vector<int> & requests) {
    vector<vector<int> > results = vector<vector<int> >();
    int resourceIdx = 0;
    for (int i = 0; i < requests.size(); i++) {
        results.push_back(vector<int>());
        for (int res = 0; res < requests[i]; res++) {
            results[i].push_back(resourceIdx);
            resourceIdx++;
        }
    }
    return results;
}

int main() {
    cout << "Mesosphere challenge\n";
    int resourceStream[] = {1, 3, 2, 8, 3, 4, 5, 6, 1, 7, 8};
    vector<int> resources(resourceStream, resourceStream + sizeof(resourceStream) / sizeof(resourceStream[0]));

    int requestStream[] = {2, 1};
    vector<int> requests(requestStream, requestStream + sizeof(requestStream) / sizeof(requestStream[0]));
    vector<vector<int> > fifoSched = FifoSchedule(resources, requests);
    
    for (int i = 0; i < fifoSched.size(); i++) {
        for (int j = 0; j < fifoSched[i].size(); j++) {
            cout << fifoSched[i][j] << " ";
        }
        cout << endl;
    }
}
