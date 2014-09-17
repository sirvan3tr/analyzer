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

    //ifstream logfile("mylog/glassesonly.csv");
    ifstream logfile("mylog/summerlog.txt");
    ofstream outputfile ("uniqueviews.csv", ios::app);
    int lineone, newday, secs, mins, hours, t, dayscount, linecount, prevdaycount;
    char extra;
    string  prevday = "";
    string  currentvideoname = "";
    string currentday = "";
    string previp = "";
    string currentip = "";
    string delimiter = ",";
    linecount = 0;
    prevdaycount = 0;
    dayscount = 1;
    int sameip = 0;
    int samevid = 0;
    int uniqueipcount = 0;
    int startt = 0;
    int prevsameip = 0;
    int prevt = 0;
    int timediff = 0;
    int maincount = 0;
    int avgdivider = 0;
    int totaltimediff = 0;
    int dwelltimeavg = 0;
    int specificvidcount = 0;
    set<string> ipset;
    set<string> uniqueips;
    set<string> bytes;
    set<string> hashunique;
    set<string> uniquevideos;
    int totalplays = 0;
    int sec5, sec10, sec15, sec20, sec25, sec30, sec35, sec40, secplus = 0;

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
                        } else if (count==3) {
                            // File size - bytes
                            float value = atoi(token.c_str());
                            float sec = value/769629;
                            if (value < 769629 ) {
                                maincount = 0;
                            } else {
                                //cout << value/1000000 << "mb" << endl;

                                if(sec <= 5) {
                                    sec5 = sec5 + 1;
                                } else if(sec >= 6 && sec <= 10) {
                                    sec10 = sec10 + 1;
                                } else if(sec >= 11 && sec <= 15) {
                                    sec15 = sec15 + 1;
                                } else if(sec >= 16 && sec <= 20) {
                                    sec20 = sec20 + 1;
                                } else if(sec >= 21 && sec <= 25) {
                                    sec25 = sec25 + 1;
                                } else if(sec >= 26 && sec <= 30) {
                                    sec30 = sec30 + 1;
                                } else if(sec >= 31 && sec <= 35) {
                                    sec35 = sec35 + 1;
                                } else if(sec >= 36 && sec <= 40) {
                                    sec40 = sec40 + 1;
                                } else if(sec > 40) {
                                    secplus = secplus + 1;
                                    cout << value/769629 << " seconds" << endl;
                                }
                                outputfile << token << endl;
                                maincount = 1;
                                totalplays = totalplays + 1;
                                bytes.insert(token);
                            }
                        } else if (count==4) {
                            if (maincount == 1) {
                                //uniqueips.insert(token);
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
                        } else if(count == 7) {
                            // video name
                            //if (maincount == 1 && (token == "/133376/01_glasses.mp4" || token == "/133376/02_glasses.mp4" ||token == "/133376/03_glasses.mp4" ||token == "/133376/04_glasses.mp4" ||token == "/133376/05_glasses.mp4")) {
                            if (maincount == 1) {
                                uniqueips.insert(currentip);
                                samevid = 1;
                                specificvidcount = specificvidcount + 1;
                            } else {
                                samevid = 0;
                            }
                            uniquevideos.insert(token);

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
        cout << "Number of videos: " << uniquevideos.size() << endl;
        cout << "Specific Video Count: " << specificvidcount << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "5 Video count: " << sec5 << endl;
        cout << "10 Video count: " << sec10 << endl;
        cout << "15 Video count: " << sec15 << endl;
        cout << "20 Video count: " << sec20 << endl;
        cout << "25 Video count: " << sec25 << endl;
        cout << "30 Video count: " << sec30 << endl;
        cout << "35 Video count: " << sec35 << endl;
        cout << "40 Video count: " << sec40 << endl;
        cout << "Over 40seconds Video count: " << sec40 << endl;


        logfile.close();
    }
    else cout << "Unable to open file";
    return 0;
}
