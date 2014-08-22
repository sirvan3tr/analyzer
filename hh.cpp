#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>

#include <string>
#include <sstream>
#include <algorithm>


using namespace  std;

int main() {
    string line;

    ifstream logfile("glassesonly.csv");
    //ifstream logfile("mylog/glassesonly.csv");
    ofstream outputfile ("btest.txt", ios::app);
    int lineone, newday, secs, mins, hours, t, timediff, dayscount, linecount, prevdaycount;
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



    int totallines = count(istreambuf_iterator<char>(logfile), 
             istreambuf_iterator<char>(), '\n') + 1;
    //cout << totallines << endl;
    logfile.close();
    logfile.clear();
    logfile.open("glassesonly.csv");
    //logfile.open("mylog/glassesonly.csv");
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
                            stringstream ss;
                            ss << token;
                            ss >> hours >> extra
                               >> mins  >> extra
                               >> secs;
                            t = (hours*3600)+(mins*60)+secs;

                            //cout << t << endl;
                        } else if (count==4) {
                            // manage the ip addresses here
                            if (token==currentip) {
                                sameip = 1;
                            } else {
                                sameip = 0;
                                currentip = token;
                            }
                        }
                        
                    line.erase(0, pos + delimiter.length());
                    count = count + 1;

                }
                //outputfile << line << endl;
                if (newday==1) {
                    sameip = 0;
                }
                if (sameip==0) {
                    uniqueipcount = uniqueipcount + 1;
                }

                linecount = linecount+1;
           
                cout << "-----------" << endl;
                cout << "same ip? " << sameip << endl;
                cout << "Unique count: " << uniqueipcount << endl;
                cout << "Current day: " << currentday << endl;
                cout << "Time: " << t << endl;
                cout << totallines << endl;
                cout << linecount << " NEWLINE" << endl;
                
                cout << "Prev day: " << prevday << endl;
                cout << dayscount << endl;
                cout << "prev day count: " << prevdaycount << endl;
                cout << "new day: " << newday << endl;
                /**/
                //cout << "the lines " << totallines << " " << linecount << endl; 
                count = 0;
                if ((newday == 1) && linecount>1) {
                    /*if (linecount==totallines) {
                        outputfile << prevday << "," << prevdaycount << endl;
                        outputfile << currentday << "," << dayscount  << endl;                    
                    } else {*/
                        outputfile << prevday << "," << prevdaycount << "," << uniqueipcount << endl; 
                    //}
                } else if (linecount==totallines) {
                    outputfile << currentday << "," << dayscount << "," << uniqueipcount << endl;
                }
                if (newday==1) {
                    sameip = 0;
                    uniqueipcount = 1;
                }
                prevday = currentday;
                previp = currentip;
                
        }
        cout << "Total Downloads: " << linecount << endl;
        logfile.close();
    }
    else cout << "Unable to open file";
    return 0;
}
