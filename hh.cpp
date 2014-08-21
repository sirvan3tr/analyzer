#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>

#include <string>
#include <sstream>


using namespace  std;

int main() {
    string line;

    ifstream logfile ("glassesonly.csv");
    ofstream outputfile ("excel/mylog/g.txt", ios::app);
    int secs, mins, hours, t, timediff, dayscount;
    char extra;
    if (logfile.is_open()) {
        while ( getline (logfile,line) ) {
            string delimiter = ",";
            size_t pos = 0;
            string token;
            string prevday;
            size_t count = 0;
                while ((pos = line.find(delimiter)) != string::npos) {
                    token = line.substr(0, pos);
                        if (count==1) {
                            // token  = current time in this if loop
                            stringstream ss;
                            ss << token;
                            ss >> hours >> extra
                               >> mins  >> extra
                               >> secs;
                            t = (hours*3600)+(mins*60)+secs;

                            cout << t << endl;
                        } else if (count==0) {
                            if(token==prevday) {
                                dayscount = dayscount +1;
                            } else {
                                dayscount = 0;
                            }
                            cout << token << endl;
                            token = prevday;
                        }
                        //outputfile << token << " ";
                    line.erase(0, pos + delimiter.length());
                    count = count + 1;

                }
                //outputfile << line << endl;
                cout << "NEWLINE" << endl;
                count = 0;
                cout << dayscount << endl;
        }
        logfile.close();
    }
    else cout << "Unable to open file";
    return 0;
}
