#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HeapBuilder {
public:
    int Parent(int i) {
        return (i - 1) / 2;
    }

    int LeftChild(int i) {
        return 2 * i + 1;
    }

    int RightChild(int i) {
        return 2 * i + 2;
    }

    void ShiftDown(int i, vector<long long>& data_in) {
        int minIndex = i;
        int l = LeftChild(i);
        if (l < data_in.size() && data_in[minIndex] > data_in[l]) {
            minIndex = l;
        }
        int r = RightChild(i);
        if (r < data_in.size() && data_in[minIndex] > data_in[r]) {
            minIndex = r;
        }
        if (minIndex != i) {
            swap(data_in[i], data_in[minIndex]);
        }
        else {
            return;
        }
        ShiftDown(minIndex, data_in);
    }

    long long ExtractMin(vector<long long>& data_in) {
        return data_in[0];
    }

    void ChangePriority(int a, long long b, vector<long long>& data_in) {
        data_in[a] = b;
        swap(data_in[0], data_in[data_in.size() - 1]);
        ShiftDown(0, data_in);
    }

    void BuildHeap(vector<long long>& data_in) {
        for (int i = (data_in.size() - 1) / 2; i >= 0; i--) {
            ShiftDown(i, data_in);
        }
    }
};


class JobQueue {
    private:
    int num_workers = 0;
    vector<int> jobs;

    vector<int> assigned_workers;
    vector<long long> start_times;

    void WriteResponse() const {
        /*for (int i = 0; i < jobs.size(); i++) {
            cout << assigned_workers[i] << " " << start_times[i] << "\n";
        }*/
        for (int i = 0; i < jobs.size(); i++) {
            cout << start_times[i] << "\n";
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
        start_times.resize(num_workers);
        vector<long long> heap_data(num_workers, 0);
        for (int i = 0; i < num_workers; i++) {
            heap_data[i] = jobs[i];
        }
        HeapBuilder Next_free_time;
        Next_free_time.BuildHeap(heap_data);
        for (int i = num_workers; i < jobs.size(); i++) {
            long long start_time = Next_free_time.ExtractMin(heap_data);
            start_times.push_back(start_time);
            Next_free_time.ChangePriority(0, start_time + jobs[i], heap_data);           
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
