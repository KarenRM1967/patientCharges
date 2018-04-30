/****************************************************
Karen Rees-Milton. Assignment1. 15Feb2018
A program that prepares a report on patient charges
****************************************************/
#include <iostream>
#include<iomanip>
#include<string>
#include<fstream>

using namespace std;

//function prototypes and constants
int getValidDays();
void displayEndingMsg();
char getValidRoomType();
double determineRoomRate(char);
bool validateReply(char);
string determineFullRoomType(char);
double computeCharge(int, double);
double accumulatePatientCharges(double, int);
double accumulateCharges(double);
string validateString(string);

const double TV_COST = 25.0;

int main()
{
	//housekeeping: Declare variables, open files, set output
	int days;
	char roomType, replyTV, replyPatients;
	double roomRate, roomCharge, totalCharges = 0.0;
	string patientName;
	bool hasTV, morePatients;

	ofstream fout("charges.dat");
	if (!fout.is_open())
	{
		cout << "Error opening file";
		system("pause");
		exit(-1);
	}

	fout << fixed << setprecision(2);

	fout << right << setw(40) << "CPA Private Hospital Room Charge" << endl
		<< setw(40) << "****************************    " << endl;

	fout << left << setw(25) << "Patient Name" << setw(15) << "Room Type"
		<< right << setw(15) << "# of Days" << setw(15) << "Room Charge"
		<< endl << endl;

	//input, processing, output
	do
	{
		cout << "Enter patient name ";
		getline(cin, patientName);
		while (patientName.empty())
			patientName = validateString(patientName);
		days = getValidDays();
		roomType = getValidRoomType();
		roomRate = determineRoomRate(roomType);
		roomCharge = computeCharge(days, roomRate);

		if (roomType == 'P' || roomType == 'S')
		{
			cout << "Do you want a television? Enter Y or N ";
			cin >> replyTV;
			hasTV = validateReply(replyTV);
			if (hasTV)
				roomCharge = accumulatePatientCharges(roomCharge, days);
		}

		totalCharges = accumulateCharges(roomCharge);

		fout << left << setw(25) << patientName << setw(15)
			<< determineFullRoomType(roomType)
			<< right << setw(15) << days << setw(15) << roomCharge
			<< endl << endl;

		cout << "Are there more patients (Y/N): ";
		cin >> replyPatients;
		morePatients = validateReply(replyPatients);
	} while (morePatients);

	fout << endl << endl << left << setw(20) << "Total charges"
		<< right << setw(50) << totalCharges << endl;

	displayEndingMsg();

	system("type charges.dat");
	system("pause");
}

//function that will input and validate the number of days
int getValidDays()
{
	int noDays;
	cout << "enter number of days patient will stay ";
	cin >> noDays;
	while (noDays < 0 || noDays > 180 || cin.fail())
	{
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Number must be >0 and <50. Re-enter ";
		cin >> noDays;
	}
	cin.ignore(80, '\n');
	return noDays;
}

//function that will print ending message
void displayEndingMsg()
{
	cout << "Program has ended" << endl;
}

//function that will input and validate a room type
char getValidRoomType()
{
	char roomType;
	cout << "Enter room type ";
	cin >> roomType;
	roomType = toupper(roomType);
	while (roomType != 'P' && roomType != 'S' && roomType != 'W')
	{
		cin.ignore(80, '\n');
		cout << "Invalid room type. Re-enter P, S or W only ";
		cin >> roomType;
		roomType = toupper(roomType);
	}
	cin.ignore(80, '\n');
	return roomType;
}


//function that will determine the room rate
double determineRoomRate(char roomType)
{
	double rate;
	switch (roomType)
	{
	case 'P':
		rate = 1000.;
		break;
	case 'S':
		rate = 750.;
		break;
	default:
		rate = 500.;
	}
	return rate;
}

//function to validate reply
bool validateReply(char reply)
{
	reply = toupper(reply);
	while (reply != 'Y' && reply != 'N')
	{
		cin.ignore(80, '\n');
		cout << "Error. You must enter Y or N ";
		cin >> reply;
		reply = toupper(reply);
	}
	cin.ignore(80, '\n');
	return (reply == 'Y');
}

//function to determine full room type from abbreviation
string determineFullRoomType(char roomType)
{
	string fullRoomType;
	switch (roomType)
	{
	case 'P':
		fullRoomType = "Private";
		break;
	case 'S':
		fullRoomType = "Semi-Private";
		break;
	default:
		fullRoomType = "Ward";
	}
	return fullRoomType;
}


//function to determine patient room charge
double computeCharge(int days, double roomRate)
{
	return days * roomRate;
}

//function to determine all charges for a patient
double accumulatePatientCharges(double roomCharge, int days)
{
	return roomCharge + days * TV_COST;

}

//function to accumulate charges for all patients
double accumulateCharges(double roomCharge)
{
	double totalCharges = 0.0;
	totalCharges += roomCharge;
	return totalCharges;
}

//function to validate string input for empty string
string validateString(string namePatient)
{
	cout << "Cannot be empty. Must enter a patient name ";
	getline(cin, namePatient);
	return namePatient;
}

/*******************************************
I/O dialogue
********************************************
Enter patient name John Smith
enter number of days patient will stay 3
Enter room type p
Do you want a television? Enter Y or N y
Are there more patients (Y/N): y
Enter patient name Jane Doe
enter number of days patient will stay 3
Enter room type p
Do you want a television? Enter Y or N n
Are there more patients (Y/N): y
Enter patient name
Cannot be empty. Must enter a patient name
Cannot be empty. Must enter a patient name John Wayne
enter number of days patient will stay 5 days
Enter room type ward
Are there more patients (Y/N): y
Enter patient name Bruce Willis
enter number of days patient will stay 333
Number must be >0 and <50. Re-enter -33
Number must be >0 and <50. Re-enter 33
Enter room type q
Invalid room type. Re-enter P, S or W only s
Do you want a television? Enter Y or N y
Are there more patients (Y/N): n
Program has ended
CPA Private Hospital Room Charge
****************************
Patient Name             Room Type            # of Days    Room Charge

John Smith               Private                      3        3075.00

Jane Doe                 Private                      3        3000.00

John Wayne               Ward                         5        2500.00

Bruce Willis             Semi-Private                33       25575.00



Total charges                                                 25575.00
Press any key to continue . . .
**********************************************************************/
