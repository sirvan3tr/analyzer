#include <iostream>
#include <fstream>

using namespace  std;

int main() {
    string line;

    ifstream logfile ("mylog/summerlog.txt");
    ofstream outputfile ("mylog/g.txt", ios::app);
    if (logfile.is_open()) {
        while ( getline (logfile,line) ) {
            string delimiter = "\t";
            size_t pos = 0;
            string token;
            if(line.find("40s_EXTENED_VERSION.mp4") != string::npos) {
                while ((pos = line.find(delimiter)) != string::npos) {
                    token = line.substr(0, pos);
                        outputfile << token << ",";
                    line.erase(0, pos + delimiter.length());
                }
                outputfile << line << endl;
            }
        }
        logfile.close();
    }
    else cout << "Unable to open file";
    return 0;
}
