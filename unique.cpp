#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <iterator>

#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <math.h>


using namespace  std;

int main() {
    string line;

    ifstream logfile("mylog/glassesonly.csv");
    //ifstream logfile("mylog/summerlog.txt");
    ofstream outputfile ("uniqueviews.csv", ios::app);
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
    int maincount = 0;
    int avgdivider = 0;
    int totaltimediff = 0;
    int dwelltimeavg = 0;
    set<string> ipset;
    set<string> uniqueips;
    set<string> bytes;
    set<string> hashunique;
    int totalplays = 0;


    int totallines = count(istreambuf_iterator<char>(logfile),
             istreambuf_iterator<char>(), '\n');
    //cout << totallines << endl;
    logfile.close();
    logfile.clear();
    //logfile.open("glassesonly.csv");
    logfile.open("mylog/glassesonly.csv");
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
                        } else if (count==3) {
                            //int a[] = {66052, 66053, 66054, 361, 363, 502};

                            int value = atoi(token.c_str());
                            if (value < 600 ) {
                            //if (value < 1) {
                                maincount = 0;
                            } else if(value < 66060 && value > 66040) {
                               maincount = 0;
                            } else if(value > 8000 && value < 9000) {
                                maincount = 0;

                            } else {
                                cout << token << endl;
                                outputfile << token << endl;
                                maincount = 1;
                                totalplays = totalplays + 1;
                                bytes.insert(token);
                            }
                        } else if (count==4) {
                            //cout << token << endl;
                            if (maincount == 1) {
                                uniqueips.insert(token);
                            }
                            // manage the ip addresses here
                            // if new day then reset set and then insert
                            if (token==currentip) {
                                sameip = 1;
                            } else {
                                prevsameip = sameip;
                                sameip = 0;
                                currentip = token;
                            }
                        } else if (count==14) {
                            hashunique.insert(token);
                            //cout << token << endl;
                        } else if (count==17) {
                            // server to client bytes
                            //cout << token << endl;
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
/*
                        outputfile << prevday << ","
                                   << prevdaycount << ","
                                   //<< uniqueipcount << ","
                                   << dwelltimeavg << ","
                                   << ipset.size()
                                   << endl;
                                   */
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
                    /*
                    outputfile << currentday << ","
                                << dayscount << ","
                                //<< uniqueipcount << ","
                                << dwelltimeavg << ","
                                << ipset.size()
                                << endl;
                                */
                }
                if (sameip==0) {
                    startt = t;
                }
                ipset.insert(currentip);
                prevday = currentday;
                previp = currentip;
                prevsameip = sameip;

        }
        cout << "Total Page Views: " << linecount << endl;
        cout << "Total Unique Views: " << uniqueips.size() << endl;
        cout << "Total Plays: " << totalplays << endl;
        cout << "Unique Hash: " << hashunique.size() << endl;
        cout << "Number of unique file sizes: " << bytes.size() << endl;
        logfile.close();
    }
    else cout << "Unable to open file";
    return 0;
}
