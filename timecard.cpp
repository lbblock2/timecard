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
#define kMaxLine 64




class Timecard
{
public:
	Timecard(char filename[]) : numNewEntries(0) {
		fp.open(filename, fstream::in | fstream::out);
		if (!fp) {
			ofstream out(filename);
			string wage;
			cout << "Wage: ";
			cin >> wage;
			out << wage << endl;
			out.close();
			fp.open(filename, fstream::in | fstream::out);
		}
		// string line;
		// getline(fp, line);
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
		cout << "Date (mm/dd/yyyy): ";
		cin >> enty.date;
		cout << "Start time (hh:mm): ";
		cin >> enty.startTime;
		cout << "End time (hh:mm): ";
		cin >> enty.endTime;
		cout << "Task: ";
		getline(cin, enty.task);
		cout << "Notes: ";
		getline(cin, enty.notes);
		entries.resize(numNewEntries + 1);
		entries[numNewEntries++] = enty;
		cout << "entry added! Now " << numNewEntries << "added." << endl;
	}

	void saveFile() {
		string entystr;
		for(int i = 0; i < entries.size(); i++) {\
			Entry enty = entries[i];
			//print to file
			entystr = "e||" + enty.date + "||" + enty.startTime + "||"
								+ enty.endTime + "||" + enty.task + "||" + enty.notes;
			fp.seekp(0, fstream::end);
			fp << entystr;
			// fp << endl;
		}
	}

	void viewFile() {
		string line;
		fp.seekg(0, fstream::beg);
		while(getline(fp, line)) {
			cout << line << endl;
		}
	}

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
			case 'v':
				viewFile();
				break;
			// case 'e':
			// case 'd':
			case 's':
				saveFile();
				break;
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

	int getItemPos(string itemVar, string item, int categoryPos) {
		string fileLine;
		fp.seekg(categoryPos, ios::beg);
		while (getline(fp, fileLine)) {
			if (fileLine == itemVar + item) return fp.tellg();
		}
		return 0;
	}


	// int getYearPos(string year) {
	// 	string fileLine;
	// 	while(getline(fp, fileLine)) {
	// 		if (fileLine == "y" + year) return fp.tellg();
	// 	}
	// 	return 0;
	// }

	// int getMonthPos(string month, int yearPos) {
	// 	string fileLine;
	// 	fp.seekg(yearPos, ios::beg);
	// 	while(getline(fp, fileLine)) {
	// 		if (fileLine == "m" + month) return fp.tellg();
	// 	}
	// 	return 0;
	// }

	// int getEntryPos(string day, int monthPos) {
	// 	string fileLine;
	// 	fp.seekg()
	// }

	Entry *readEntry(int entyPos) {
		Entry *enty;
		string entyLine;
		fp.seekg(entyPos, ios::beg);
		getline(fp, entyLine);
		return enty;
	}

	Entry *getEntry(string date) {
		Entry enty;
		string month = date.substr(0, 2);
		string day = date.substr(3, 2);
		string year = date.substr(6);
		int yearPos = getItemPos("y", year, 0);
		if (yearPos == 0) return NULL;
		int monthPos = getItemPos("m", month, yearPos);
		if (monthPos == 0) return NULL;
		int entyPos = getItemPos("e", day, monthPos);
		if (entyPos == 0) return NULL;
		return readEntry(entyPos);
	}


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




