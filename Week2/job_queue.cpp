#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HeapBuilder {
public:
 
    int LeftChild(int i) {
        return 2 * i + 1;
    }

    int RightChild(int i) {
        return 2 * i + 2;
    }

    void ShiftDown(int i, vector<pair<int, int64_t>>& data_in) {
        int64_t minIndex = i;

        int l = LeftChild(i);
        if (l < data_in.size()) {
            if (data_in[minIndex].second > data_in[l].second) {
                minIndex = l;
            }
            else if (data_in[minIndex].second == data_in[l].second && data_in[minIndex].first > data_in[l].first) {
                minIndex = l;
            }
        }
       
        int r = RightChild(i);
        if (r < data_in.size()) {
            if (data_in[minIndex].second > data_in[r].second) {
                minIndex = r;
            }
            else if (data_in[minIndex].second == data_in[r].second && data_in[minIndex].first > data_in[r].first) {
                minIndex = r;
            }
        }
        
        if (minIndex != i) {
            swap(data_in[i], data_in[minIndex]);
            ShiftDown(i, data_in);
        }     
        /*else {
            return;
        }*/
        
    }

    pair<int, int64_t> ExtractMin(vector<pair<int, int64_t>>& data_in) {
        return data_in[0];
    }

    void ChangePriority(int a, int b, vector<pair<int, int64_t>>& data_in) {
        data_in[a].second = b;
        swap(data_in[0], data_in[data_in.size() - 1]);
        ShiftDown(0, data_in);
    }

    void BuildHeap(vector<pair<int, int64_t>>& data_in) {
        for (int i = (data_in.size() - 1) / 2; i >= 0; i--) {
            ShiftDown(i, data_in);
        }
    }
};


class JobQueue {
private:
    int num_workers = 0;
    vector<int64_t> jobs;

    vector<pair<int64_t, int64_t>> start_times;

    void WriteResponse() const {
        for (int64_t i = 0; i < jobs.size(); i++) {
            cout << start_times[i].first << " " << start_times[i].second << "\n";
        }
    }

    void ReadData() {
        int64_t m;
        cin >> num_workers >> m;
        jobs.resize(m);
        for (int64_t i = 0; i < m; ++i) {
            cin >> jobs[i];
        }
    }

    void AssignJobs() {
        for (int i = 0; i < num_workers; i++) {
            start_times.push_back(make_pair(i, 0));
        }

        vector<pair<int, int64_t>> heap_data;
        if (num_workers <= jobs.size()) {
            for (int i = 0; i < num_workers; i++) {
                heap_data.push_back(make_pair(i, jobs[i]));
            }
        }
        else {
            for (int i = 0; i < jobs.size(); i++) {
                heap_data.push_back(make_pair(i, jobs[i]));
            }
        }
        

        HeapBuilder Next_free_time;
        Next_free_time.BuildHeap(heap_data);     
        if (num_workers <= jobs.size()) {
            for (int i = num_workers; i < jobs.size(); i++) {
                pair<int, int64_t> start_time = Next_free_time.ExtractMin(heap_data);
                start_times.push_back(start_time);
                Next_free_time.ChangePriority(0, start_time.second + jobs[i], heap_data);
            }
        }
        else {
            return;
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