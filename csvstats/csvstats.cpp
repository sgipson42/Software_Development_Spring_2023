#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <float.h>
using namespace std;
//argv[1] = file
//argv[2] = separator 
int main( int argc, char *argv[]) {
	//check to make sure CSV file and separator are included as arguments
	if (argc < 3){
		cout << "Not enough arguments! Include file and separator." << endl;
		return -1;
	 }	

	ifstream t(argv[1]);
	if(t.is_open()) {
		string s;
		string sep(argv[2]);
		int col;
		double val;
		double largest=DBL_MIN; 
		double smallest=DBL_MAX;
		int counter= 0;
		double sum= 0;
		double av=0;
		
		cout << "Please enter a column number to print." << endl;
		
		if (cin >> col) {
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
			//print stats of the column so long as it contains only numbers
			if (col > 2) {	
				av= sum/counter; 
				cout << "File Stats: " << endl;
				cout << "Min: " << smallest << endl;
				cout << "Max: " << largest << endl;
				cout << "Mean: " << av << endl;
			}
		}
	} else {
		cin.ignore();
	}
	return 0;
}
