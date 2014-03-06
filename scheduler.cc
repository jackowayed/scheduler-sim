#include <iostream>
#include <vector>

using namespace std;

void FifoSchedule(vector<int> & resources, vector<int> & requests, vector<vector<int> > & results) {
    int resourceIdx = 0;
    for (int i = 0; i < requests.size(); i++) {
        results.push_back(vector<int>());
        for (int res = 0; res < requests[i]; res++) {
            results[i].push_back(resourceIdx);
            resourceIdx++;
        }
    }
}

/*vector<vector<int> > SjnSchedule(vector<int> & resources, vector<int> & requests) {
    
  }*/

void PrintStats(vector<vector<int> > & schedule) {
    // avg time to completion.
    double sumCompletionTimes = 0;
    for (int i = 0; i < schedule.size(); i++) {
        // assumes that resource indices are sorted in the schedule
        sumCompletionTimes += schedule[i].back();
    }
    cout << "Avg time until scheduling: " << sumCompletionTimes / schedule.size() << endl;
}

int main() {
    cout << "Mesosphere challenge\n";
    int resourceStream[] = {1, 3, 2, 8, 3, 4, 5, 6, 1, 7, 8};
    vector<int> resources(resourceStream, resourceStream + sizeof(resourceStream) / sizeof(resourceStream[0]));

    int requestStream[] = {1, 1, 5};
    vector<int> requests(requestStream, requestStream + sizeof(requestStream) / sizeof(requestStream[0]));
    vector<vector<int> > fifoSched = vector<vector<int> >();
    FifoSchedule(resources, requests, fifoSched);
    
    for (int i = 0; i < fifoSched.size(); i++) {
        for (int j = 0; j < fifoSched[i].size(); j++) {
            cout << fifoSched[i][j] << " ";
        }
        cout << endl;
    }

    PrintStats(fifoSched);
}
