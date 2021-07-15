#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class JobQueue {
    private:
    int num_workers;
    vector<int> jobs;

    vector<int> assigned_workers;
    vector<long long> start_times;

    void WriteResponse() const {
        for (int i = 0; i < jobs.size(); i++) {
            cout << assigned_workers[i] << " " << start_times[i] << "\n";
        }
    }

    void ReadData() {
        int m;
        cin >> num_workers >> m;
        jobs.resize(m);
        for (int i = 0; i < m; ++i) {
            cin >> jobs[i];
        }       
    }

    void AssignJobs() {
        vector<long long> next_free_time(num_workers, 0);
        for (int i = 0; i < jobs.size(); i++) {
            int worker = 0;
            for (int j = 0; j < num_workers; j++) {
                if (next_free_time[j] < next_free_time[0]) {
                    worker = j;
                    break;
                }               
            } 
            assigned_workers.push_back(worker);
            start_times.push_back(next_free_time[worker]);
            next_free_time[worker] += jobs[i];
        }
    }

    public:
    void Solve() {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}
