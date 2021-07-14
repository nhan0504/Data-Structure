#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HeapBuilder {
    private:
    vector<int> data_in;
    vector< pair<int, int> > swaps_pair;

    void WriteResponse() const {
        cout << swaps_pair.size() << endl;
        for (int i = 0; i < swaps_pair.size(); i++) {
            cout << swaps_pair[i].first << " " << swaps_pair[i].second << endl;
        }
    }

    void ReadData() {
        int n;
        cin >> n;
        data_in.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> data_in[i];
        }
    }

    int Parent(int i) {
        return (i - 1) / 2;
    }

    int LeftChild(int i) {
        return 2 * i + 1;
    }

    int RightChild(int i) {
        return 2 * i + 2;
    }

    void ShiftUp(int i, vector<int>& data_in, vector< pair<int, int> >& swaps_pair) {
        while (i > 0 && data_in[i] < data_in[Parent(i)]) {
            swap(data_in[i], data_in[Parent(i)]);
            swaps_pair.push_back(make_pair(i, Parent(i)));
            i = Parent(i);
        }
    }

    void ShiftDown(int i, vector<int>& data_in, vector< pair<int, int> >& swaps_pair) {
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
            swaps_pair.push_back(make_pair(i, minIndex));
        }
        else {
            return;
        }
        ShiftDown(minIndex, data_in, swaps_pair);
    }

    void GenerateSwaps() {
        swaps_pair.clear();
        for (int i = (data_in.size() - 1) / 2; i >= 0 ; i--) {
            ShiftDown(i, data_in, swaps_pair);
            //ShiftUp(i, data_in, swaps_pair);
        }
    }

    public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
