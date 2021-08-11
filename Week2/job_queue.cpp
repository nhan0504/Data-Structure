#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//class HeapBuilder {
//public:
// 
//    int LeftChild(int i) {
//        return 2 * i + 1;
//    }
//
//    int RightChild(int i) {
//        return 2 * i + 2;
//    }
//
//    void ShiftDown(int i, vector<pair<int, long long>>& data_in) {
//        int minIndex = i;
//
//        int l = LeftChild(i);
//        if (l < data_in.size()) {
//            if (data_in[minIndex].second > data_in[l].second) {
//                minIndex = l;
//            }
//            else if (data_in[minIndex].second == data_in[l].second && data_in[minIndex].first > data_in[l].first) {
//                minIndex = l;
//            }
//        }
//       
//        int r = RightChild(i);
//        if (r < data_in.size()) {
//            if (data_in[minIndex].second > data_in[r].second) {
//                minIndex = r;
//            }
//            else if (data_in[minIndex].second == data_in[r].second && data_in[minIndex].first > data_in[r].first) {
//                minIndex = r;
//            }
//        }
//        
//        if (minIndex != i) {
//            swap(data_in[i], data_in[minIndex]);
//            ShiftDown(minIndex, data_in);
//        }     
//        return;
//    }
//
//    pair<int, long long> ExtractMin(vector<pair<int, long long>>& data_in) {
//        return data_in[0];
//    }
//
//    void ChangePriority(int a, int b, vector<pair<int, long long>>& data_in) {
//        data_in[a].second = b;
//        ShiftDown(a, data_in);
//    }
//
//    void BuildHeap(vector<pair<int, long long>>& data_in) {
//        for (int i = (data_in.size() - 2) / 2; i >= 0; i--) {
//            ShiftDown(i, data_in);
//        }
//    }
//};


class JobQueue {
private:
    int num_workers = 0;
    vector<int64_t> jobs;

    //result
    vector<pair<int, long long>> assign_work;
    //hold heap data
    vector<pair<int, long long>> heap;

    void WriteResponse() const {
        for (int i = 0; i < jobs.size(); i++) {
            cout << assign_work[i].first << " " << assign_work[i].second << "\n";
        }
    }

    void ReadData() {
        int m;
        cin >> num_workers >> m;
        jobs.resize(m);
        for (int i = 0; i < m; i++) {
            cin >> jobs[i];
        }
    }

    void AssignJobs() {
        //Init heap
        for (int i = 0; i < num_workers; i++) {
            heap.push_back(make_pair(i, 0));
        } 

        for (int i = 0; i < jobs.size(); i++) {
            pair<int, long long> next_assign = heap[0];
            assign_work.push_back(next_assign);
            //Update finish time
            heap[0].second += jobs[i];
            SiftDown(0);
        }
        return;
    }

    int LeftChild(int i) {
        return 2 * i + 1;
    }

    int RightChild(int i) {
        return 2 * i + 2;
    }

    void SiftDown(int i) {
        int minIndex = i;

        int l = LeftChild(i);
        if (l < heap.size()) {
            if (heap[minIndex].second > heap[l].second) {
                minIndex = l;
            }
            else if (heap[minIndex].second == heap[l].second && heap[minIndex].first > heap[l].first) {
                minIndex = l;
            }
        }

        int r = RightChild(i);
        if (r < heap.size()) {
            if (heap[minIndex].second > heap[r].second) {
                minIndex = r;
            }
            else if (heap[minIndex].second == heap[r].second && heap[minIndex].first > heap[r].first) {
                minIndex = r;
            }
        }

        if (minIndex != i) {
            swap(heap[i], heap[minIndex]);
            SiftDown(minIndex);
        }
        return;
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