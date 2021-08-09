#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class TreeOrders {
    int n;
    vector <int> key;
    vector <int> left;
    vector <int> right;

public:
    void read() {
        cin >> n;
        key.resize(n);
        left.resize(n);
        right.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> key[i] >> left[i] >> right[i];
        }
    }

    void in_order(int i) {  
        //if left child of node is nill -> print out left child
        if (left[i] != -1 && left[left[i]] == -1 && right[left[i]] == -1) {
            cout << key[left[i]] << " ";                               
        }
        else if(left[i] != -1) {
            in_order(left[i]);
        }  
        //Print out node after traversing all left subtree
        cout << key[i] << " ";
        //if right child of node is nill -> print out right child
        if (right[i] != -1 && left[right[i]] == -1 && right[right[i]] == -1) {
            cout << key[right[i]] << " ";
        }
        else if(right[i] != -1) {
            in_order(right[i]);
        }
    }

    void pre_order(int i) {
        cout << key[i] << " ";
        if (left[i] != -1 && left[left[i]] == -1 && right[left[i]] == -1) {
            cout << key[left[i]] << " ";
        }
        else if (left[i] != -1) {
            pre_order(left[i]);
        }
        if (right[i] != -1 && left[right[i]] == -1 && right[right[i]] == -1) {
            cout << key[right[i]] << " ";
        }
        else if (right[i] != -1) {
            pre_order(right[i]);
        }
    }

    void post_order(int i) {     
        if (left[i] != -1 && left[left[i]] == -1 && right[left[i]] == -1) {
            cout << key[left[i]] << " ";
        }
        else if (left[i] != -1) {
            post_order(left[i]);
        }
        if (right[i] != -1 && left[right[i]] == -1 && right[right[i]] == -1) {
            cout << key[right[i]] << " ";
        }
        else if (right[i] != -1) {
            post_order(right[i]);
        }
       cout << key[i] << " ";
    }
};

void print(vector<int> a) {
    for (size_t i = 0; i < a.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
}

int main_with_large_stack_space() {
    ios_base::sync_with_stdio(0);
    TreeOrders t;
    t.read();
    t.in_order(0);
    cout << endl;
    t.pre_order(0);
    cout << endl;
    t.post_order(0);
    cout << endl;
    return 0;
}

int main (int argc, char **argv){
    #if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
    const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0) {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                std::cerr << "setrlimit returned result = " << result << std::endl;
            }
        }
    }
    #endif
    return main_with_large_stack_space();
}

