/*
 */
#include <stdio.h>
#include <time.h>
#include <iostream.h>
#include <istream.h>
#include <fstream.h>
#include <string.h>
#include <vector.h>
using namespace std;

#define kNumMonths 12
#define kMaxLine 256




class timecard
{
public:
	timecard(string filename) : numNewEntries = 0 {
		fp = fopen(filename, "r+");
		string line;

	}

	~timecard(){ fclose(fp) }

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
	// 	for(int i = 0; i < entries.size(); i++) {\
	// 		//print to file
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
		time_t startTime;
		time_t endTime;
		string task;
		string notes;
		double totalTime;
	};

	FILE *fp;
	int numNewEntries;
	vector<Entry> entries(numNewEntries);
	double grandTotal;
	double wage;

};


int main() {
	time_t initTime = time(0);
	struct tm *	now = localtime(&initTime);
	int currYear = now->tm_year + 1900;
	int currMonth = now->tm_mon + 1;
	cout << "Welcome to Timecard!" << endl;
	string filename;
	cout << "Timecard Filenmae: ";
	cin >> filename;
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




