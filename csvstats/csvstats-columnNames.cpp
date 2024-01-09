#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <float.h>
using namespace std;

int main( int argc, char *argv[]) {
	//check to make sure CSV file and separator included as argument
	if (argc < 3){
		cout << "Not enought arguments! Include file and separator." << endl;
		return -1;
	 }	

	ifstream t(argv[1]);
	if(t.is_open()) {
		string s;
		string colName;
		string sep(argv[2]);
		int col=0;
		double val;
		double largest=DBL_MIN; 
		double smallest=DBL_MAX;
		int counter= 0;
		double sum= 0;
		double av=0;
		int check=0;

		//have user chose column
		if (t >> s) {
			cout << s << endl;
			cout << "Type column name from above to print: " << endl;
			cin >> colName;
		}

		//ignore anything that's not a column name
		if (s.find(colName) == -1 || colName == sep) {
			cin.ignore();	
		} else {
			//column name to int
			for (int i=0; i<s.find(colName); i++) {
				string c(1, s[i]);
				if (c == sep) {
					col++;
				}
			}

			//find specified column
			cout << "Column contents: " << endl; 
			while(getline(t,s)) {
				int pos= -1;
				for (int i=0; i < col; i++) {
					pos= s.find(sep, pos+1);
				}
				int pos2= pos;
				pos2= s.find(sep, pos+1);
				string t= s.substr(pos+1, pos2-pos-1);
				cout << t << endl;
				
				//evaluate numbers in column for min, max, mean
				stringstream ts(t);
				if(ts >> val) {
					if (val > largest) {
						largest= val;
					}	
					if (val < smallest) {
						smallest= val;
					}
					counter++;
					sum+=val;
				}
			}
		}
		if (col > 2) {
			av= sum/counter; 
			cout << "File Stats: " << endl;
			cout << "Min: " << smallest << endl;
			cout << "Max: " << largest << endl;
			cout << "Mean: " << av << endl;
		}
	}
}
