#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    vector<int> reference =
        {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

    int delta = 3; // working set window size (Δ)

    cout << "Time | Page | Working Set | WS Size\n";
    cout << "-----------------------------------\n";

    for (int t = 0; t < reference.size(); t++) {
        set<int> workingSet;

        int start = max(0, t - delta + 1);
        for (int i = start; i <= t; i++) {
            workingSet.insert(reference[i]);
        }

        cout << t + 1 << "    | "
             << reference[t] << "    | {";

        bool first = true;
        for (int p : workingSet) {
            if (!first) cout << ",";
            cout << p;
            first = false;
        }

        cout << "}        | "
             << workingSet.size() << endl;
    }

    return 0;
}