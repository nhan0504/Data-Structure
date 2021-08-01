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

    vector <int> in_order(int i, vector<int>& result) {       
        if (left[left[i]] == -1 && right[left[i]] == -1) {
            result.push_back(key[left[i]]);    
            cout << key[left[i]] << endl;                             
        }
        else {
            in_order(left[i], result);
        }  
        result.push_back(key[i]);
        cout << key[i] << endl;
        if (left[right[i]] == -1 && right[right[i]] == -1) {
            result.push_back(key[right[i]]);
            cout << key[right[i]] << endl;
        }
        else {
            in_order(right[i], result);
        }
        return result;
    }

    vector <int> pre_order() {
        vector<int> result;    
        // Finish the implementation
        // You may need to add a new recursive method to do that
    
        return result;
    }

    vector <int> post_order() {
        vector<int> result;
        // Finish the implementation
        // You may need to add a new recursive method to do that
    
        return result;
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
    vector<int> result;
    print(t.in_order(0, result));
    //print(t.pre_order());
    //print(t.post_order());
    return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
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
