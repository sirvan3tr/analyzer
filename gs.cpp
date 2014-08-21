#include <iostream>
#include <fstream>

using namespace  std;

int main() {
    string line;
    ifstream logfile ("aug1to5data.txt");
    ofstream outputfile ("glassesonly1to5.txt", ios::app);
    if (logfile.is_open()) {
        while ( getline (logfile,line) ) {
            if (line.find("glasses.mp4") != string::npos) {
                outputfile << line << endl;
            }
        }
        logfile.close();
    }
    else cout << "Unable to open file";
    return 0;
}
