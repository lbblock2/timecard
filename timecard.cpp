/*
 */
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define kNumMonths 12
#define kMaxFileLine 32
#define kMaxLine 64
#define kDateWidth 12
#define kSTimeWidth 8
#define kETimeWidth 8
#define kTaskWidth 16
#define kNotesWidth 16
#define kSeparator ' '




class Timecard
{
public:
	Timecard(char filename[]) : numNewEntries(0) {
		fp.open(filename, ios::in | ios::out);
		if (!fp) {
			ofstream out(filename);
			string wage;
			cout << "Wage: ";
			cin >> wage;
			out << wage << endl;
			out.close();
			fp.open(filename, ios::in | ios::out);
		}
		begin = fp.tellg();
		// string line;
		// getline(fp, line);
	}

	~Timecard(){ fp.close(); }

	void showHelp() {
		cout << "Available commands:" << endl;
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
		string ln = enty.task;
		getline(std::cin, ln);
		// cin >> enty.task;
		cout << "Notes: ";
		// cin >> enty.notes;
		getline(cin, enty.notes);
		entries.resize(numNewEntries + 1);
		entries[numNewEntries++] = enty;
		cout << "entry added! Now " << numNewEntries << " added." << endl;
	}


	template<typename T> void printElem(T t, int width) {
		fp << left << setw(width) << setfill(' ') << t;
	}

	void saveFile() {
		string entystr;
		if (numNewEntries == 0) return;
		for(int i = 0; i < numNewEntries; i++) {
			Entry enty = entries[i];
			//print to file
			// entystr = "e  " + enty.date + "  " + enty.startTime + "  "
			// 					+ enty.endTime + "  " + enty.task + "  " + enty.notes;
			fp.clear();
			fp.seekp(0, ios::end);
			// fp << entystr << endl;
			printElem("e", 2);
			printElem(enty.date, kDateWidth);
			printElem(enty.startTime, kSTimeWidth);
			printElem(enty.endTime, kETimeWidth);
			printElem(enty.task, kTaskWidth);
			printElem(enty.notes, kNotesWidth);
			fp << endl; 
			fp.clear();
		}
		entries.clear();
		numNewEntries = 0;
	}

	template<typename T> void coutElem(T t, int width) {
		cout << left << setw(width) << setfill(' ') << t;
	}
	// void parsePrintEnty(string entyLine) {
	// 	Entry enty;
	// 	enty.date = entyLine.substr(3, 10);
	// 	enty.startTime = entyLine.substr(15, 5);
	// 	enty.endTime = entyLine.substr(21, 5);
	// 	enty.task = entyLine.substr(27, 16);
	// 	enty.notes = entyLine.substr(43, 16);
	// 	enty.printEnty();
	// }

	void printHeader() {
		cout << endl;
		coutElem("Date:", kDateWidth);
		coutElem("Start:", kSTimeWidth);
		coutElem("End:", kETimeWidth);
		coutElem("Task:", kTaskWidth);
		coutElem("Notes:", kNotesWidth);
		cout << endl << "-------------------------------------------------------";
	}

	void viewFile() {
		string line;
		printHeader();
		fp.seekg(begin);
		fp.clear();
		while(getline(fp, line)) {
			if (fp.eof()) break;
			string line2 = line.substr(2);
			cout << line2 << endl;
		}
		cout << endl << "-------------------------------------------------------";
		cout << endl;
		fp.seekg(begin);
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
		
		
		// void printEnty() {
		// 	coutElem(date, kDateWidth);
		// 	coutElem(startTime, kSTimeWidth);
		// 	coutElem(endTime, kETimeWidth);
		// 	coutElem(task, kTaskWidth);
		// 	coutElem(notes, kNotesWidth);
		// 	cout << endl;
		// }

		string startTime;
		string endTime;
		string date;
		string task;
		string notes;
		double totalTime;
	};


	// string getYear(string year) {
	// 	string fileLine;
	// 	while(getline(fp, fileLine)) {
	// 		if (fileLine == "y" + year) return fileLine;
	// 	}
	// 	return NULL;
	// }

	int getItemPos(string itemVar, string item, int categoryPos) {
		string fileLine;
		fp.seekg(categoryPos, ios::beg);
		while (getline(fp, fileLine)) {
			if (fileLine == itemVar + item) return fp.tellg();
		}
		return 0;
	}


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

	streampos begin;

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




