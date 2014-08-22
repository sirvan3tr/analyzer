#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>

#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <math.h>


using namespace  std;

int main() {
    string line;

   // ifstream logfile("glassesonly.csv");
    ifstream logfile("mylog/summerlog.txt");
    ofstream outputfile ("btestsummer.csv", ios::app);
    int lineone, newday, secs, mins, hours, t, dayscount, linecount, prevdaycount;
    char extra;
    string  prevday = "";
    string currentday = "";
    string previp = "";
    string currentip = "";
    string delimiter = ",";
    linecount = 0;
    prevdaycount = 0;
    dayscount = 1;
    int sameip = 0;
    int uniqueipcount = 0;
    int startt = 0;
    int prevsameip = 0;
    int prevt = 0;
    int timediff = 0;
    int avgdivider = 0;
    int totaltimediff = 0;
    int dwelltimeavg = 0;
    set<string> ipset;

    int totallines = count(istreambuf_iterator<char>(logfile),
             istreambuf_iterator<char>(), '\n');
    //cout << totallines << endl;
    logfile.close();
    logfile.clear();
    //logfile.open("glassesonly.csv");
    logfile.open("mylog/summerlog.txt");
    if (logfile.is_open()) {
        while ( getline (logfile,line) ) {

            size_t pos = 0;
            string token;
            int count = 0;
                while ((pos = line.find(delimiter)) != string::npos) {
                        token = line.substr(0, pos);
                        if (count==0) {

                            if(token==prevday) {
                                prevdaycount = dayscount;
                                dayscount = dayscount +1;
                                newday = 0;
                            } else {
                                currentday = token;
                                prevdaycount = dayscount;
                                dayscount = 1;
                                newday = 1;
                            }
                        } else if (count==1) {
                            // token  = current time in this if loop
                            prevt = t;
                            stringstream ss;
                            ss << token;
                            ss >> hours >> extra
                               >> mins  >> extra
                               >> secs;
                            t = (hours*3600)+(mins*60)+secs;
                        } else if (count==4) {
                            // manage the ip addresses here
                            // if new day then reset set and then insert
                            if (token==currentip) {
                                sameip = 1;
                            } else {
                                prevsameip = sameip;
                                sameip = 0;
                                currentip = token;
                            }
                        }

                    line.erase(0, pos + delimiter.length());
                    count = count + 1;

                }
                //outputfile << line << endl;
                linecount = linecount+1;

                if (newday==1) {
                    sameip = 0;
                    uniqueipcount = 0;
                }

                if (sameip==0) {
                    timediff  = prevt - startt;
                    if (linecount>1) {
                    avgdivider = avgdivider+1;
                    totaltimediff = totaltimediff+timediff;
                    }
                    uniqueipcount = uniqueipcount + 1;
                }
                if ((sameip==0) && uniqueipcount ==1) {
                    uniqueipcount = 1;
                }
                /*
                if (newday==1) {
                cout << "-----------" << endl;

                cout << "Time: " << t << endl;
                cout << "Prev Time: " << prevt << endl;

                cout << "same ip? " << sameip << endl;
                //cout << "prev same ip? " << sameip << endl;
                cout << "Unique count: " << uniqueipcount << endl;
                cout << "Current day: " << currentday << endl;
                cout << "Prev day: " << prevday << endl;

                cout << totallines << endl;
                cout << linecount << " NEWLINE" << endl;

                //cout << dayscount << endl;
                cout << "prev day count: " << prevdaycount << endl;
                cout << "new day: " << newday << endl;

                }*/

                //cout << "the lines " << totallines << " " << linecount << endl;
                count = 0;
                if ((newday == 1) && linecount>1) {
                    dwelltimeavg = ceil(totaltimediff/avgdivider);
                    //cout << "avg dwell time: " << dwelltimeavg << endl;
                    avgdivider = 0;
                    totaltimediff = 0;

                        outputfile << prevday << ","
                                   << prevdaycount << ","
                                   //<< uniqueipcount << ","
                                   << dwelltimeavg << ","
                                   << ipset.size()
                                   << endl;
                    ipset.clear();
                    timediff = 0;
                }
                if (linecount==totallines) {
                    timediff  = prevt - startt;
                    avgdivider = avgdivider+1;
                    totaltimediff = totaltimediff+timediff;
                    ipset.insert(currentip);
                    //cout << "||||size of set" << ipset.size() << endl;

                    //cout << "boom" << endl;
                    dwelltimeavg = ceil(totaltimediff/avgdivider);
                    //cout << "avg dwell time: " << dwelltimeavg << endl;
                    avgdivider = 0;
                    totaltimediff = 0;
                    outputfile << currentday << ","
                                << dayscount << ","
                                //<< uniqueipcount << ","
                                << dwelltimeavg << ","
                                << ipset.size()
                                << endl;
                }
                if (sameip==0) {
                    startt = t;
                }
                ipset.insert(currentip);
                prevday = currentday;
                previp = currentip;
                prevsameip = sameip;

        }
        cout << "Total Downloads: " << linecount << endl;
        logfile.close();
    }
    else cout << "Unable to open file";
    return 0;
}
