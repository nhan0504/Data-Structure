#include <iostream>
#include <vector>

using namespace std;

class Solver {
	typedef unsigned long long ull;
	string s;

public:	
	ull hash_func(const string& s) const {
		static const size_t multiplier = 263;
		static const size_t prime = 1000000007;
		ull hash = 0;
		for (int i = s.size() - 1; i >= 0; i--) {			
			hash = (hash * multiplier + s[i]) % prime;			
		}		
		return hash; 
	}

	Solver(string s) : s(s) {

	}

	vector<ull> PrecomputedHashes(string t, int p) {
		vector<ull> H(t.size() - p + 1, 0);
		string S = t.substr(t.size() - p, p);
		H[t.size() - p] = hash_func(S);
		static const size_t prime = 1000000007;
		static const size_t x = 263;
		int64_t y = 1;
		for (int i = 1; i <= p; i++) {
			y = (y * x) % prime;
		}
		for (int i = t.size() - p - 1; i >= 0; i--) {
			H[i] = (x * H[i + 1] + t[i] - (y * t[i + p]) % prime) % prime;
		}

		return H;
	}

	bool AreEqual(string a, string b) {
		bool equal = true;
		for (size_t i = 0; i < a.size(); i++) {
			if (a[i] != b[i]) {
				equal = false;
			}
		}
		return equal;
	}

	bool ask(int a, int b, int l) {
		bool result = false;
		vector<ull> H = PrecomputedHashes(s, l);
		if (H[a] == H[b]) {
			result =  AreEqual(s.substr(a, l), s.substr(b, l));
		}
		return result;
	}
};

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
