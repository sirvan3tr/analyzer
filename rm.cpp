#include <iostream>
#include <fstream>

using namespace  std;

int main() {
    string line;
    ifstream logfile ("mylog/summerlog.txt");
    ofstream outputfile ("newwwwwfile.txt", ios::app);
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
