#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

/* Print format for schedules */
void PrintScheduleFormat() {
    cout << "Schedules are printed in format:" << endl;
    cout << "job_index: machineOne(resourceIndexOne) machineTwo(resourceIndexTwo) ..."
         << endl << endl;
}

/* Print schedules. Format is given in PrintScheduleFormat and in the README */
void PrintSchedule(vector<vector<int> > & schedule, vector<int> & resources) {
    for (int i = 0; i < schedule.size(); i++) {
        cout << i << ": ";
        for (int j = 0; j < schedule[i].size(); j++) {
            int resourceIdx = schedule[i][j];
            cout << resources[resourceIdx] << "(" << resourceIdx << ") ";
        }
        cout << endl;
    }
}

/* Print the average time until a job is scheduled.
   See assumptions in README. */
void PrintStats(vector<vector<int> > & schedule) {
    // avg time to completion.
    double sumCompletionTimes = 0;
    for (int i = 0; i < schedule.size(); i++) {
        // NOTE: assumes that resource indices are sorted in the schedule
        sumCompletionTimes += schedule[i].back();
    }
    cout << "Avg time until scheduling: " << sumCompletionTimes / schedule.size() << endl;
}

/* Schedule requests onto resources with FIFO strategy and put the
   resulting schedule in results.
   A schedule is a vector, with each element corresponding to one job.
   Each of these elements is a vector where each element is an int
   representing the index of one resource unit that will be given to this job.*/
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

/* Schedule requests onto resources with Shortest Job Next strategy.
   Same format as FifoSchedule */
void SjnSchedule(vector<int> & resources, vector<int> & requests,
                 vector<vector<int> > & results) {
    // Create a sorted vector of pairs of <requestSize, originalIndex>
    vector<pair<int, int> > requestsWithIndices;
    for (int i = 0; i < requests.size(); i++) {
        requestsWithIndices.push_back(pair<int, int>(requests[i], i));
    }
    sort(requestsWithIndices.begin(), requestsWithIndices.end(), compare);

    // Fifo schedule jobs now that they have been sorted smallest to largest
    vector<int> sortedRequests;
    for (int i = 0; i < requestsWithIndices.size(); i++) {
        sortedRequests.push_back(requestsWithIndices[i].first);
    }
    vector<vector<int> > sortedSchedule;
    FifoSchedule(resources, sortedRequests, sortedSchedule);

    // Use the FIFO schedule, but put thigns back in the old order.
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

    PrintScheduleFormat();

    cout << "FIFO Schedule" << endl;
    vector<vector<int> > fifoSched;
    FifoSchedule(resources, requests, fifoSched);
    PrintSchedule(fifoSched, resources);
    PrintStats(fifoSched);
    cout << endl << endl;


    cout << "Shortest Job Next Schedule" << endl;
    vector<vector<int> > sjnSchedule(requests.size());
    SjnSchedule(resources, requests, sjnSchedule);
    PrintSchedule(sjnSchedule, resources);
    PrintStats(sjnSchedule);
}
