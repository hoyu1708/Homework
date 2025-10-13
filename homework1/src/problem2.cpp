#include <iostream>
#include <vector>
using namespace std;

void powerSetHelper(vector<char>& set, vector<char> subset, int index) {
    if (index == (int)set.size()) {
        cout << "{";
        for (int i = 0; i < (int)subset.size(); i++) {
            cout << subset[i];
            if (i < (int)subset.size() - 1)
                cout << ",";
        }
        cout << "}" << endl;
        return;
    }

    powerSetHelper(set, subset, index + 1);

    subset.push_back(set[index]);
    powerSetHelper(set, subset, index + 1);
}

int main() {
    vector<char> S = { 'a', 'b', 'c' };
    vector<char> subset;
    cout << "Power Set:" << endl;
    powerSetHelper(S, subset, 0);
}
