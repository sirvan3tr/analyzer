#include <iostream>
#include <fstream>

using namespace  std;

int main() {
	string line;

	ifstream logfile ("newfile.txt");
	ofstream outputfile ("thefile.txt", ios::app);
	if (logfile.is_open()) {
		while ( getline (logfile,line) ) {
			string delimiter = "\t";
			size_t pos = 0;
			string token;

			//if (line.find("#") != string::npos) {
			//} else {
				while ((pos = line.find(delimiter)) != string::npos) {
				    token = line.substr(0, pos);
				    cout << pos << endl;
				    //if (pos != 0) {
				    	outputfile << token << ",";
				    //}
				    line.erase(0, pos + delimiter.length());
				} // while loop for inline
				outputfile << line << endl;
			//}

		} // while loop for line
		logfile.close();
	} // if log file is open
	else cout << "Unable to open file"; 
	return 0;
}