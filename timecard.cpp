/*
 */
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define kNumMonths 12
#define kMaxFileLine 32




class Timecard
{
public:
	Timecard(char filename[]) : numNewEntries(0) {
		fp.open(filename, fstream::in | fstream::out);
		string line;

	}

	~Timecard(){ fp.close(); }

	void showHelp() {
		cout << "Open" << endl;
		cout << "Add" << endl;
		cout << "View" << endl;
		cout << "Edit" << endl;
		cout << "Delete" << endl;
		cout << "Save" << endl;
		cout << "Quit" << endl;
		cout << "help" << endl;
	}


	void addEntry(){
		Entry enty;
		cout << "Start time: ";
		cin >> enty.startTime;
		cout << "End time: ";
		cin >> enty.endTime;
		cout << "Task: ";
		getline(cin, enty.task);
		getline(cin, enty.notes);
		entries.resize(entries.size() + 1);
		entries[numNewEntries++] = enty;
		cout << "entry added!" << endl;
	}

	// void saveFile() {
	//	string entystr;
	// 	for(int i = 0; i < entries.size(); i++) {\
	//		Entry enty = entires[i];
	// 		//print to file
	//		entystr = "e||" + enty.date + "||" + enty.startTime + "||"
	//							+ enty.endTime + "||" + enty.task + "||" + enty.notes;
	// 		fp << entrystr;
	// 	}
	// }

	void actOnCommand(std::string command, int *quitSignal) {
		char cmnd = tolower(command[0]);
		switch(cmnd) {
			case 'h' :
				showHelp();
				break;
			// case 'o':
			case 'a':
				addEntry();
				break;
			// case 'v':
			// case 'e':
			// case 'd':
			// case 's':
				case 'q':
				*quitSignal = 0;
				break;
			default:
				showHelp();
		}
	}	

private:

	struct Entry{
		string startTime;
		string endTime;
		string date;
		string task;
		string notes;
		double totalTime;
	};


	string getYear(string year) {
		string fileLine;
		while(getline(fp, fileLine)) {
			if (fileLine == "y" + year) return fileLine;
		}
		return NULL;
	}

	// Entry getEntry(string date) {
	// 	string month = date.substr(0, 2);
	// 	string day = date.substr(3, 2);
	// 	string year = date.substr(6);
	// 	string yearln = getYear(year);
	// }


	fstream fp;
	int numNewEntries;
	vector<Entry> entries;
	double grandTotal;
	double wage;

};


int main() {
	time_t initTime = time(0);
	struct tm *	now = localtime(&initTime);
	int currYear = now->tm_year + 1900;
	int currMonth = now->tm_mon + 1;
	cout << "Welcome to Timecard!" << endl << "Timecard Filename: ";
	char filename[kMaxFileLine];
	cin.getline(filename, kMaxFileLine);
	Timecard card(filename);
	std::string command;
	int quitSignal = 1;
	while (quitSignal == 1) {
		cout << "Command: ";
		cin >> command;
		card.actOnCommand(command, &quitSignal);
	}
	cout << "Over and out!" << endl;
}




