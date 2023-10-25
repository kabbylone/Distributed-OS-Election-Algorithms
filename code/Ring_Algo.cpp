#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Pro {
    int id;
    bool act;
    Pro(int id) {
        this->id = id;
        act = true;
    }
};

class RingElection {
    public:
        int TotalProcess;
        vector<Pro> process;
        RingElection() {}
        void initialise() {
            cout << "No of processes 5" << endl;
            TotalProcess = 5;
            process.reserve(TotalProcess);
            for (int i = 0; i < process.capacity(); i++) {
                process.emplace_back(i);
            }
        }
        void Election() {
            cout << "Process no " << process[FetchMaximum()].id << " fails" << endl;
            process[FetchMaximum()].act = false;
            cout << "Election Initiated by 2" << endl;
            int initializedProcess = 2;
            int old = initializedProcess;
            int newer = old + 1;

            while (true) {
                if (process[newer].act) {
                    cout << "Process " << process[old].id << " pass Election(" << process[old].id << ") to" << process[newer].id << endl;
                    old = newer;
                }
                newer = (newer + 1) % TotalProcess;
                if (newer == initializedProcess) {
                    break;
                }
            }

            cout << "Process " << process[FetchMaximum()].id << " becomes coordinator" << endl;
            int coord = process[FetchMaximum()].id;
            old = coord;
            newer = (old + 1) % TotalProcess;

            while (true) {
                if (process[newer].act) {
                    cout << "Process " << process[old].id << " pass Coordinator(" << coord << ") message to process " << process[newer].id << endl;
                    old = newer;
                }
                newer = (newer + 1) % TotalProcess;
                if (newer == coord) {
                    cout << "End Of Election " << endl;
                    break;
                }
            }
        }
        int FetchMaximum() {
            int Ind = 0;
            int maxId = -9999;
            for (int i = 0; i < process.size(); i++) {
                if (process[i].act && process[i].id > maxId) {
                    maxId = process[i].id;
                    Ind = i;
                }
            }
            return Ind;
        }
};

int main() {
    RingElection object;
    object.initialise();
    object.Election();
    return 0;
}
