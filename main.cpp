#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<stdlib.h>
#include<bits/stdc++.h>
#include<cstring>
#include<sstream>
#include<ctime>

using namespace std;

const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct date
{
	int dd;
	int mm;
	int yy;
};

struct PatientData
{
    char FirstName[20];
    char LastName[20];
    char Gender;		//M for male, F for Female, O for others
    char BloodGroup[4];
    int age;
    char PinCode[7];
    struct date Entry; //date of entry
    struct date Exit;	//date of exit
    char HospitalName[20];
    char contact[11];	//Contact Number
};

struct LogIn
{
    string Username;
    string Password;
};

int countLeapYears(int d,int m,int y)
{
    int years = y;

    // Check if the current year needs to be considered for the count of leap years or not
    if (m <= 2)
        years--;

    // An year is a leap year if it is a multiple of 4 multiple of 400 and not a multiple of 100.
    return years / 4 - years / 100 + years / 400;
}

int getDifference(int d1, int m1 , int y1)
{
    // COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE 'dt1'
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int y2=1900 + ltm->tm_year;
    int m2= 1 + ltm->tm_mon;
    int d2= ltm->tm_mday;
    // initialize count using years and day
    long int n1 = y1 * 365 + d1;

    // Add days for months in given date
    for (int i = 0; i < m1 - 1; i++)
        n1 += monthDays[i];

    // Since every leap year is of 366 days, Add a day for every leap year
    n1 += countLeapYears(d1,m1,y1);

    // SIMILARLY, COUNT TOTAL NUMBER OF DAYS BEFORE 'dt2'

    long int n2 = y2 * 365 + d2;
    for (int i = 0; i < m2 - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(d2,m2,y2);

    // return difference between two counts
    return (n2 - n1);
}

template<typename T> void printElement(T t, const int& width)
{
    cout << left << setw(width) << setfill(' ') << t;
}

class Hash
{
    int n = 98;
    // Pointer to an array containing buckets
    vector<vector<int>> v;
public:
    Hash();  // Constructor

    // inserts a key into hash table
    void insertItem(int x, string arr[][13]);

    // hash function to map values to key
    int hashFunction(int x)
    {
        return (x - 110000);
    }

    void displayHash(string arr[][13], int x);
};

Hash::Hash()
{
    v = vector<vector<int>>(98);
}

void Hash::insertItem(int x, string arr[][13]) //We store index in hash table
{
    int index = hashFunction(stoi(arr[x][0]));
    v[index].push_back(x);
}

void Hash::displayHash(string arr[][13], int x)
{
    const int nameWidth = 30;
    const int numWidth = 15;
    printElement("Patient's Name", nameWidth);
    printElement("Age", numWidth);
    printElement("Gender", numWidth);
    printElement("Duration*", numWidth);
    printElement("Pincode", numWidth);
    printElement("Contact Number", numWidth);
    cout<<"\n________________________________________________________________________________________________________";
   cout<<"\n\n";
   int prev, next, SizeofPrev, SizeofNext, DiffofPrev, DiffofNext, duration;
   string FullName;
   prev = hashFunction(x);
   next = hashFunction(x);
   SizeofPrev = v[prev].size();
   if(SizeofPrev != 0)
   {
       for(int j = 0; j<SizeofPrev; j++)
       {
           FullName = arr[v[prev][j]][1] + " " + arr[v[prev][j]][2];
           duration = getDifference(stoi(arr[v[prev][j]][10]), stoi(arr[v[prev][j]][11]), stoi(arr[v[prev][j]][12]));
           printElement(FullName, nameWidth);
           printElement(arr[v[prev][j]][3], numWidth);
           printElement(arr[v[prev][j]][4], numWidth);
           printElement(duration, numWidth);
           printElement(arr[v[prev][j]][0], numWidth);
           printElement(arr[v[prev][j]][5], numWidth);
           cout << endl;
       }
   }
   prev--;
   next++;
   do
   {
       SizeofPrev = v[prev].size();
       SizeofNext = v[next].size();
       while(SizeofPrev == 0)
       {
           prev--;
           if(prev < 0)
            break;
           SizeofPrev = v[prev].size();
       }
        while(SizeofNext == 0)
        {
            next++;
            if(next > 97)
                break;
            SizeofNext = v[next].size();
        }
        if(prev < 0 || next > 97)
           break;
        DiffofPrev = hashFunction(x) - prev;
        DiffofNext = next - hashFunction(x);
        if(DiffofPrev < DiffofNext)
        {
            for(int j = 0; j<v[prev].size(); j++)
            {
                FullName = arr[v[prev][j]][1] + " " + arr[v[prev][j]][2];
                duration = getDifference(stoi(arr[v[prev][j]][10]), stoi(arr[v[prev][j]][11]), stoi(arr[v[prev][j]][12]));
                printElement(FullName, nameWidth);
                printElement(arr[v[prev][j]][3], numWidth);
                printElement(arr[v[prev][j]][4], numWidth);
                printElement(duration, numWidth);
                printElement(arr[v[prev][j]][0], numWidth);
                printElement(arr[v[prev][j]][5], numWidth);
                cout << endl;
            }
            prev--;
        }
        else
        {
            for(int j = 0; j<v[next].size(); j++)
            {
                FullName = arr[v[next][j]][1] + " " + arr[v[next][j]][2];
                duration = getDifference(stoi(arr[v[next][j]][10]), stoi(arr[v[next][j]][11]), stoi(arr[v[next][j]][12]));
                printElement(FullName, nameWidth);
                printElement(arr[v[next][j]][3], numWidth);
                printElement(arr[v[next][j]][4], numWidth);
                printElement(duration, numWidth);
                printElement(arr[v[next][j]][0], numWidth);
                printElement(arr[v[next][j]][5], numWidth);
                cout << endl;
            }
            next++;
        }
    }while(prev >= 0 || next <= 97);
    while(prev >= 0)
    {
        if(v[prev].size() != 0)
        {
            for(int j = 0; j<v[prev].size(); j++)
            {
                FullName = arr[v[prev][j]][1] + " " + arr[v[prev][j]][2];
                duration = getDifference(stoi(arr[v[prev][j]][10]), stoi(arr[v[prev][j]][11]), stoi(arr[v[prev][j]][12]));
                printElement(FullName, nameWidth);
                printElement(arr[v[prev][j]][3], numWidth);
                printElement(arr[v[prev][j]][4], numWidth);
                printElement(duration, numWidth);
                printElement(arr[v[prev][j]][0], numWidth);
                printElement(arr[v[prev][j]][5], numWidth);
                cout << endl;
            }
        }
        prev--;
    }
    while(next <= 97)
    {
        if(v[next].size() != 0)
        {
            for(int j = 0; j<v[next].size(); j++)
                 {
                    FullName = arr[v[next][j]][1] + " " + arr[v[next][j]][2];
                    duration = getDifference(stoi(arr[v[next][j]][10]), stoi(arr[v[next][j]][11]), stoi(arr[v[next][j]][12]));
                    printElement(FullName, nameWidth);
                    printElement(arr[v[next][j]][3], numWidth);
                    printElement(arr[v[next][j]][4], numWidth);
                    printElement(duration, numWidth);
                    printElement(arr[v[next][j]][0], numWidth);
                    printElement(arr[v[next][j]][5], numWidth);
                    cout << endl;
                 }
        }
        next++;
    }
    cout<<"*Duration is the number of Days since the Patient was Discharged from the Hospital.\n";
}

void LoginPage();
void MainScreen();

void WelcomeNote()
{
cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
cout<<"\t\t\t\t\t@@ _______________________________________________________________________________________ @@\n";
cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
cout<<"\t\t\t\t\t@@|                                  WELCOME TO                                           |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                        COVID DATABASE MANAGEMENT SYSTEM                               |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|_______________________________________________________________________________________|@@\n";
cout<<"\t\t\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n\n\n\t\t\t\t\t";
system("pause");
system("cls");
}

int compareStrings(string arr[], string str, int last)
{
    for(int j = 0; j < last; j++)
    {
        if(arr[j] == str)
            return 0;
    }
    return -1;
}

void Login()
{
   string array[100];
   int loop = 0;
   string line;
   char y;
   string UserName, PassWord, UserPassInput;
   ifstream myfile("Info.txt", ios::in);
   if(myfile.is_open())
   {
        while(!myfile.eof())
        {
            getline(myfile, line, '\n');
            array[loop] = line;
            loop++;
        }
        myfile.close();
   }
   else
   {
       cout<<"Unable to open File";
   }
   cout << "==============================================" << endl;
   cout << "PLEASE ENTER LOGIN DETAILS:" << endl;
   cout << "==============================================" << endl;
   y = getchar();
   cout << "ENTER USERNAME: ";
   getline(cin, UserName, '\n');
   cout << "ENTER PASSWORD: ";
   getline(cin, PassWord, '\n');
   UserName.append(PassWord);
   int n = sizeof(array)/sizeof(array[0]);
   int result = compareStrings(array, UserName, n);
   if(result == -1)
   {
       cout<<"Wrong Username or Password.\nPlease Login Again.\n";
       system("pause");
       system("cls");
       Login();
   }
   else
   {
       system("pause");
       MainScreen();
   }
}

void Signup()
{
    char y;
    LogIn ID;
    system("cls");
    ofstream outfile;
    outfile.open("Info.txt", ios::app);
    if(!outfile)
	{
		cout<<"Error in opening file";
		return;
	}
    cout << "==============================================" << endl;
    cout << "REGISTER BELOW:" << endl;
    cout << "==============================================" << endl;
    y = getchar();
    cout << "ENTER USERNAME (UP TO 10 CHARACTERS LONG): ";
    getline(cin, ID.Username, '\n');
    outfile << ID.Username;
    cout << "ENTER PASSWORD (UP TO 10 CHARACTERS LONG): ";
    getline(cin, ID.Password, '\n');
    outfile << ID.Password << endl;
    cout << "==============================================" << endl;
    cout << endl;
    cout<<"You Have Successfully Registered.\nLogin to Continue.\n";
    outfile.close();
    system("pause");
    system("cls");
    LoginPage();
}

void LoginPage()
{
    int ch;
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t  COVID DATABASE MANAGEMENT SYSTEM  \n\n";
    cout<<"\n\n\t\t\t\t\t\tPlease,  Choose from the following Options: \n\n";
    cout<<"\t\t\t\t\t\t _________________________________________________________________ \n";
    cout<<"\t\t\t\t\t\t|                                           	                  |\n";
    cout<<"\t\t\t\t\t\t|             1  >> LOGIN, if already registered                  |\n";
    cout<<"\t\t\t\t\t\t|             2  >> SIGNUP, if you are a new user                 |\n";
    cout<<"\t\t\t\t\t\t|             3  >> EXIT                                          |\n";
    cout<<"\t\t\t\t\t\t|_________________________________________________________________|\n\n\n\n";
    a:
    cout<<"\t\t\t\t\t\tEnter your choice: ";
    cin>>ch;
    system("cls");
    switch(ch)
    {
        case 1:
            Login();
            break;
        case 2:
            cout<<"\n\n\n\n\t\t\t\t\t\t";
            Signup();
            break;
        case 3:
            cout<<"\n\n\n\n\t\t\t\t\t\t";
            cout<<"Thank you for Using this Application.";
            exit(0);
            break;
        default:
            cout<<"Invalid Choice\n\n\n";
            goto a;
            break;
    }
    cout<<"\n\n\n\n\n";
    system("pause");
}

bool isLeap(int year)
{
   return (((year % 4 == 0) &&  (year % 100 != 0)) || (year % 400 == 0));
}

bool CheckDate(int d, int m, int y)
{
    if (m < 1 || m > 12)
    return false;
    if (d < 1 || d > 31)
    return false;
    if (m == 2)
    {
        if (isLeap(y))
        return (d <= 29);
        else
        return (d <= 28);
    }
    if (m == 4 || m == 6 || m == 9 || m == 11)
        return (d <= 30);
    return true;
}

void FileInput()
{
    int EntryDuration, ExitDuration;
	char ch, x;
    int n, i;
    struct PatientData p;
    string y, filename;
    do
    {
        x = getchar();
      cout<<"Enter Blood Group (in Captials): ";
	  cin.get(p.BloodGroup, 4);
	   while (strcmp(p.BloodGroup, "A+") != 0 && strcmp(p.BloodGroup, "A-") != 0 &&  strcmp(p.BloodGroup, "B+") != 0 && strcmp(p.BloodGroup, "B-") != 0 && strcmp(p.BloodGroup, "AB+") != 0 && strcmp(p.BloodGroup, "AB-") != 0 && strcmp(p.BloodGroup, "O+") != 0 && strcmp(p.BloodGroup, "O-") != 0)
      {
          cout<<"Please enter a Correct Blood Group.\n";
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout<<"Enter Blood Group (in Capitals): ";
          cin.get(p.BloodGroup, 3);
      }
      filename.clear();
      filename.append(p.BloodGroup).append(".csv");
  	 fstream outfile;
     outfile.open(filename, ios::app);
    //check for file opening
	if(!outfile)
	{
		cout<<"Error in opening file";
		return;
	}
	  x = getchar();
      cout<<"\nEnter Patient's First Name: ";
      cin.get(p.FirstName, 20);
      x = getchar();
      cout<<"Enter Patient's Last Name: ";
      cin.get(p.LastName, 20);

      cout<<"Enter Gender(M:Male,F:Female,O:Others): ";
      cin>>p.Gender;
      p.Gender = toupper(p.Gender);
      while (p.Gender != 'M' && p.Gender != 'F' && p.Gender != 'O')
      {
          cout<<"Please enter a Correct Gender.\n";
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout<<"Enter Gender: ";
          cin>>p.Gender;
          p.Gender = toupper(p.Gender);
      }

      cout<<"Enter Patient's Age: ";
      cin>>p.age;
      while(p.age<=0)
      {
          cout<<"Please enter a valid age.\n";
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout<<"Enter Patient's Age: ";
          cin>>p.age;
      }

      x = getchar();
      cout<<"Enter Pincode: ";
      cin.get(p.PinCode, 7);
      while(stoi(p.PinCode) <= 110000 || stoi(p.PinCode) >= 110098)
      {
          cout<<"Please enter a correct Pincode.\n";
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout<<"Enter Pincode: ";
          cin.get(p.PinCode, 7);
      }

      a:
      cout<<"Enter date when admitted in the Hospital in the form dd[space]mm[space]yyyy: ";
      cin>>p.Entry.dd>>p.Entry.mm>>p.Entry.yy;
      while(!CheckDate(p.Entry.dd, p.Entry.mm, p.Entry.yy))
      {
          cout<<"Please enter a valid Date.\n";
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout<<"Enter date of Entry in the form dd[space]mm[space]yyyy: ";
          cin>>p.Entry.dd>>p.Entry.mm>>p.Entry.yy;
      }
      EntryDuration = getDifference(p.Entry.dd, p.Entry.mm, p.Entry.yy);

      cout<<"Enter date when discharged from the hospital in the form dd[space]mm[space]yyyy: ";
      cin>>p.Exit.dd>>p.Exit.mm>>p.Exit.yy;
      while(!CheckDate(p.Exit.dd, p.Exit.mm, p.Exit.yy))
      {
          cout<<"Please enter a valid Date.\n";
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout<<"Enter date of Exit in the form dd[space]mm[space]yyyy: ";
          cin>>p.Exit.dd>>p.Exit.mm>>p.Exit.yy;
      }
      ExitDuration = getDifference(p.Exit.dd, p.Exit.mm, p.Exit.yy);

      if(EntryDuration < ExitDuration)
      {
        cout<<"Please Check the Dates.\n";
        goto a;
      }

      x = getchar();
      cout<<"Enter Hospital Name: ";
      cin.get(p.HospitalName, 20);

      x = getchar();
      cout<<"Enter Contact Number: ";
      cin.get(p.contact, 11);
      outfile<<p.PinCode<<","<<p.FirstName<<","<<p.LastName<<","<<p.age<<","<<p.Gender<<","<<p.contact<<","<<p.HospitalName<<","<<p.Entry.dd<<","<<p.Entry.mm<<","<<p.Entry.yy<<","<<p.Exit.dd<<","<<p.Exit.mm<<","<<p.Exit.yy<<"\n";
		cout<<"\n\n";
		cout<<"Do you want to enter more(y/n)";
		cin>>ch;
		cout<<"\n";
		outfile.close();
    }while(ch=='y'||ch=='Y');
    system("pause");
    MainScreen();
}

void read_record()
{
    Hash h;
    char ch, BloodGroup[4], x;
    string filename;
    PatientData p;
    int PinCode;
    x = getchar();
    cout<<"Enter the Blood Group for which you want Plasma (in Capitals): ";
    cin.get(BloodGroup, 4);
    while (strcmp(BloodGroup, "A+") != 0 && strcmp(BloodGroup, "A-") != 0 &&  strcmp(BloodGroup, "B+") != 0 && strcmp(BloodGroup, "B-") != 0 && strcmp(BloodGroup, "AB+") != 0 && strcmp(BloodGroup, "AB-") != 0 && strcmp(BloodGroup, "O+") != 0 && strcmp(BloodGroup, "O-") != 0)
      {
          cout<<"Please enter a Correct Blood Group.\n";
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout<<"Enter the Blood Group for which you want Plasma (in Capitals): ";
          cin.get(p.BloodGroup, 3);
      }
    filename.append(BloodGroup).append(".csv");
    fstream infile;
    infile.open(filename,ios::in);
	if(!infile)
	{
		cout<<"Error in opening file";
		return;
	}
	cout<<"Enter your Pincode: ";
	cin>>PinCode;
	while(PinCode <= 110000 || PinCode >= 110098)
      {
          cout<<"Please enter a correct Pincode.\n";
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout<<"Enter Pincode: ";
          cin>>PinCode;
      }
      cout<<endl;
    // Read the Data from the file
    // as String Vector
    system("pause");
    system("cls");
    string data[100][13];
    string word, temp;
    int i =0, j = 0, c =0;
    while (infile >> temp)
    {
        // used for breaking words
        stringstream s(temp);
        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ','))
        {
            // add all the column data
            // of a row to a vector
            data[i][c] = word;
            c++;
        }
        h.insertItem(j, data);
        j++;
        s.clear();
     }
    h.displayHash(data, PinCode);
    cout<<"\n\n";
    system("pause");
    MainScreen();
}

void MainScreen()
{
    int ch;
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t  COVID DATABASE MANAGEMENT SYSTEM  \n\n";
    cout<<"\n\n\t\t\t\t\t\tPlease,  Choose from the following Options: \n\n";
    cout<<"\t\t\t\t\t\t _________________________________________________________________ \n";
    cout<<"\t\t\t\t\t\t|                                           	                  |\n";
    cout<<"\t\t\t\t\t\t|             1  >> Add New Patient Record                        |\n";
    cout<<"\t\t\t\t\t\t|             2  >> Search for Plasma Donors                      |\n";
    cout<<"\t\t\t\t\t\t|             3  >> Exit                                          |\n";
    cout<<"\t\t\t\t\t\t|_________________________________________________________________|\n\n\n\n";
    b:
    cout<<"t\t\t\t\t\tEnter your choice: ";
    cin>>ch;
    system("cls");
    switch(ch)
    {
        case 1:
            FileInput();
            break;
        case 2:
            read_record();
            break;
        case 3:
            cout<<"\n\n\n\n\t\t\t\tThank You for Using this Application.";
            exit(0);
            break;
        default:
            cout<<"Invalid Choice.\n\n\n";
            goto b;
            break;
    }
}


int main()
{
    WelcomeNote();
    LoginPage();
    return 0;
}
