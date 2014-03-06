#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;


void PrintSchedule(vector<vector<int> > & schedule) {
    for (int i = 0; i < schedule.size(); i++) {
        for (int j = 0; j < schedule[i].size(); j++) {
            cout << schedule[i][j] << " ";
        }
        cout << endl;
    }
}

void PrintStats(vector<vector<int> > & schedule) {
    // avg time to completion.
    double sumCompletionTimes = 0;
    for (int i = 0; i < schedule.size(); i++) {
        // assumes that resource indices are sorted in the schedule
        sumCompletionTimes += schedule[i].back();
    }
    cout << "Avg time until scheduling: " << sumCompletionTimes / schedule.size() << endl;
}


void FifoSchedule(vector<int> & resources, vector<int> & requests,
                  vector<vector<int> > & results) {
    int resourceIdx = 0;
    for (int i = 0; i < requests.size(); i++) {
        results.push_back(vector<int>());
        for (int res = 0; res < requests[i]; res++) {
            results[i].push_back(resourceIdx);
            resourceIdx++;
        }
    }
}

/* Compare a pair<int,int> based on their first,
   with second being tiebreaker */
bool compare(pair<int,int> one, pair<int,int> two) {
    if (one.first != two.first) {
        return one.first < two.first;
    }
    return one.second < two.second;
}

void SjnSchedule(vector<int> & resources, vector<int> & requests,
                 vector<vector<int> > & results) {
    vector<pair<int, int> > requestsWithIndices;
    for (int i = 0; i < requests.size(); i++) {
        requestsWithIndices.push_back(pair<int, int>(requests[i], i));
    }
    sort(requestsWithIndices.begin(), requestsWithIndices.end(), compare);

    vector<int> sortedRequests;
    for (int i = 0; i < requestsWithIndices.size(); i++) {
        sortedRequests.push_back(requestsWithIndices[i].first);
    }
    vector<vector<int> > sortedSchedule;
    FifoSchedule(resources, sortedRequests, sortedSchedule);

    for (int i = 0 ; i < requestsWithIndices.size(); i++) {
        results[requestsWithIndices[i].second] = sortedSchedule[i];
    }
}

int main() {
    int resourceStream[] = {1, 3, 2, 8, 3, 4, 5, 6, 1, 7, 8, 2, 1, 7, 9, 6};
    vector<int> resources(resourceStream, resourceStream 
                          + sizeof(resourceStream) / sizeof(resourceStream[0]));

    int requestStream[] = {10, 1, 1};
    vector<int> requests(requestStream, requestStream
                         + sizeof(requestStream) / sizeof(requestStream[0]));

    vector<vector<int> > fifoSched;
    FifoSchedule(resources, requests, fifoSched);

    PrintSchedule(fifoSched);
    PrintStats(fifoSched);

    vector<vector<int> > sjnSchedule(requests.size());
    SjnSchedule(resources, requests, sjnSchedule);

    cout << "----" << endl;
    PrintSchedule(sjnSchedule);
    PrintStats(sjnSchedule);
}
