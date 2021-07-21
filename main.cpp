#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

class ToDo
{
public:
    char todo[100];
    int date;
    float time;

    void showdata();
    void getdata();
};

void ToDo ::getdata()
{
    cout << "Enter the Date(DD/MM/YYYY) and Time(HH.MM)\n";
    cin >> date;
    cin >> time;
    cout << "\nEnter the task in todo list\n";
    cin.ignore();
    cin.getline(todo, 100);
}
void ToDo ::showdata()
{
    cout << date << " " << time << " " << todo;
}

void createTask();
void displayAll();
void modifyTask(int);
void deleteTask(int,int);
void displayGiven(int);
void quote();

int main()
{
    system("cls");
    int choice;
    long int dt;
    long tim;
    do
    {
        system("cls");
        time_t t = time(NULL);
        tm *tPtr = localtime(&t);
        cout << "\n\t\t :) TODO - THE TASK MANAGER\n\n";
        cout << "------------------------------------------------------------\n";
        cout << " Current Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
        cout << " Current Time: " << (tPtr->tm_hour % 12) << ":" << (tPtr->tm_min) << ":" << (tPtr->tm_sec) << endl;
        quote();
        cout << "\n************************************************************\n";
        cout << "\t1. Add task in ToDo List\n\t2. Display complete list \n\t3. Display Tasks of specific day\n\t4. Delete an task\n\t5. Modify a Task\n\t6. Exit\n";
        cout << "************************************************************\n";
        cout << "Enter your choice ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            createTask();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            cout << "Enter date to display all task on that day";
            cin >> dt;
            displayGiven(dt);
            break;
        case 4:
            cout << "Enter date and time  to be deleted";
            cin >> dt >> tim;
            deleteTask(dt,tim);
            break;
        case 5:
            cout << "Enter date to be modified";
            cin >> dt;
            modifyTask(dt);
            break;
        case 6:
            cin.get();
            exit(1);
            break;
        default:
            cout << "Invalid Choice";
            cin.ignore();
            cin.get();
            break;
        }
    } while (choice != 0);
}
void createTask()
{
    ToDo A;
    ofstream fout;
    fout.open("TODOList", ios::binary | ios::app);
    A.getdata();
    fout.write((char *)&A, sizeof(ToDo));
    fout.close();
    cout << "\n\nA Task Has Been Created \n";
    cin.ignore();
    cin.get();
}

void displayAll()
{
    ToDo A;
    ifstream fin;
    fin.open("TODOList", ios::binary);
    if (!fin)
    {
        cout << "Error in opening file . Press any key to contonue";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n\n\t\tDISPLAYING ALL RECORDS\n\n";
    cout << "Date     time\t Tasks\n";
    while (fin.read((char *)&A, sizeof(ToDo)))
    {
        A.showdata();
        cout << "\n----------------------------------------------------------------------------\n";
    }
    fin.close();
    cin.ignore();
    cin.get();
}

void deleteTask(int a, int b)
{
    int n = a;
    int m = b;
    ToDo A;
    ifstream fin;
    fin.open("TODOList", ios::binary);
    if (!fin)
    {
        cout << "Error in opening file . Press any key to contonue";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream fout;
    fout.open("Temp.dat", ios::out);
    fin.seekg(0, ios::beg);
    while (fin.read((char *)&A, sizeof(ToDo)))
    {
        if (A.date != n && A.time != m)
        {
            fout.write((char *)&A, sizeof(ToDo));
        }
    }
    fout.close();
    fin.close();
    remove("TODOList");
    rename("Temp.dat", "TODOList");
    cout << "\n\n\tTo Do task deleted";
    cin.ignore();
    cin.get();
}

void modifyTask(int n)
{
    bool found = false;
    ToDo B;
    fstream fl;
    fl.open("TODOList", ios::binary | ios::in | ios::out);
    if (!fl)
    {
        cout << "Error in opening file . Press any key to contonue";
        cin.ignore();
        cin.get();
        return;
    }
    while (!fl.eof() && found == false)
    {
        fl.read((char *)&B, sizeof(ToDo));
        if (B.date == n)
        {
            B.showdata();
            cout << "\n\nEnter new Task" << endl;
            B.getdata();
            int pos = (-1) * int(sizeof(B));
            fl.seekp(pos, ios::cur);
            fl.write((char *)&B, sizeof(ToDo));
            cout << "\n\n\t Task Updated";
            found = true;
        }
    }
    fl.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
    cin.ignore();
    cin.get();
}

void displayGiven(int n) // rahul
{
    ToDo dis;
    ifstream iFile;
    iFile.open("TODOList", ios::binary);
    if (!iFile)
    {
        cout << "Error in opening file . Press any key to contonue";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag = false;
    while (iFile.read((char *)&dis, sizeof(ToDo)))
    {
        if (dis.date == n)
        {
            dis.showdata();
            cout << "\n----------------------------------------------------------------------------\n";
            flag = true;
        }
    }
    iFile.close();
    if (flag == false)
        cout << "\n\nRecord does not exist";
    cin.ignore();
    cin.get();
}

void quote()
{
    srand((unsigned)time(0));
    cout << endl << " Your Quote of the Day: \n ";
    int quote = 1 + (rand() % 10);
    switch (quote)
    {
    case 1:
        cout << "Your Future Is Created by what you to,not tomorrow";
        break;
    case 2:
        cout << "Productivity Is never an accident .It is always the result of a commitement to excellence and intelligent planning.";
        break;
    case 3:
        cout << "Time is what we want Most , but what we use Worst";
        break;
    case 4:
        cout << "Time has a Wonderful way of showing us what really Matters";
        break;
    case 5:
        cout << "Remember, Today the is Tomorrrow You worried about Yesterday";
        break;
    case 6:
        cout << "Either You run the Day, Or the Day runs You.";
        break;
    case 7:
        cout << "The two most powerful warriors are patience and time.";
        break;
    case 8:
        cout << "Time is money.";
        break;
    case 9:
        cout << "Time waits for no one.";
        break;
    case 10:
        cout << "Lost time is never found again.";
        break;
    default:
        cout << "Error";
        break;
    }
}