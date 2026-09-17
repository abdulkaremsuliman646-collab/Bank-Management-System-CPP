#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
const string ClientsFileName = "Client.txt";
struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool deletmark =false;
};
void ShowMainMenuScreen()
{
    system("cls"); 
    cout << "==================================================\n";
    cout << "\t\tMain Menu Screen\n";
    cout << "==================================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Exit.\n";
    cout << "==================================================\n";
}
void ShowTransactionsMenuScreen()
{
    system("cls");
    cout << "==================================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "==================================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "==================================================\n";
}
void PrintClientRecord(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintAllClientsData(vector <sClient> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
        cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sClient Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
sClient ReadNewClient()
{
    sClient Client;
    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}
string ConvertRecordToLine(sClient Client, string Seperator ="#//#")
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}
void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}
void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName,
        ConvertRecordToLine(Client));
}
void AddClients()
{
    char AddMore = 'Y';
    do
    {
        system("cls");
        cout << "Adding New Client:\n\n";
        AddNewClient();
        cout << "\nClient Added Successfully, do you want to addmore clients ? Y / N ? ";
            cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}
vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; 
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); 
      
        
            vString.push_back(sWord);
        
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1); 
    }
    return vString;
}
sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData = SplitString(Line, Seperator);


    if (vClientData.size() >= 5)
    {
        Client.AccountNumber = vClientData[0];
        Client.PinCode = vClientData[1];
        Client.Name = vClientData[2];
        Client.Phone = vClientData[3];
        Client.AccountBalance = stod(vClientData[4]);
    }
    return Client;
}
vector <sClient> LoadCleintsDataFromFile(string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in); 
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        while (getline(MyFile, Line))
        {
    
            if (Line == "")
            {
                continue;
            }

            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}
bool PrintClientRecord(string AccountNumber, vector <sClient> vClients, sClient& FoundClient)
{
    
    for(sClient  Client : vClients) {
       if  (Client.AccountNumber == AccountNumber) 
       { 
           FoundClient = Client;
           return true;
            
        }
   }
    return false;
}
void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.PinCode;
    cout << "\nName : " << Client.Name;
    cout << "\nPhone : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
    for (sClient& c : vClients)
    {
        if (c.AccountNumber == AccountNumber)
        {
            c.deletmark = true;
            return true;
        }

    }
    return false;
}
vector <sClient> saveclientdatatofile(string FileName, vector <sClient>vClient)
{
    fstream myfile;
    myfile.open(FileName, ios::out);
    string dataline;
    if (myfile.is_open())
    {
        for (sClient c : vClient)
        {
            if (c.deletmark == false) {
                dataline = ConvertRecordToLine(c);
                myfile << dataline << endl;
            }

        }

    }
    return vClient;
}
bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient& Client)
{

    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>&vClients)
{
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients,
        Client))
    {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber,
                vClients);
            saveclientdatatofile(ClientsFileName, vClients);
          
            vClients = LoadCleintsDataFromFile(ClientsFileName);
            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber
            << ") is Not Found!";
        return false;
    }
}
string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}
sClient changeclientrecord(string AccountNumber) {
    sClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "\n\n\n enter pincode ";
    getline(cin >> ws, Client.PinCode);
    cout << "enter name  ";
    getline(cin, Client.Name);
    cout << "enter your phone ";
    getline(cin, Client.Phone);
    cout << "enter Acountnumber";
    cin >> Client.AccountBalance;
    return Client;
}
bool updateclient(vector<sClient>& vClients, string AccountNumber) {
    sClient Client;
    char answer = 'n';
    if (PrintClientRecord(AccountNumber, vClients, Client)) {
        PrintAllClientsData(vClients);
        cout << "\n are you sure you want update this client y / n? ";
        cin >> answer;
        if (tolower(answer) == 'y')
        {
            for (sClient& c : vClients)
            {
                if (c.AccountNumber == AccountNumber)
                {
                    c = changeclientrecord(AccountNumber);
                    break; 
                }
           }
            saveclientdatatofile(ClientsFileName, vClients);
            cout << "\n\n\nupate successfully";
            return true;
        }

    }
    else { cout << "\nI do not found it \n"; }
    return false;
}

void ShowTotalBalancesScreen(vector<sClient> vClients)
{
 
    system("cls");
    cout << "\n\t\tBalances List (" << vClients.size() << ") Client(s).\n";
    cout << "_____________________________________________________________________\n";
    cout << "| " << setw(15) << left << "Account Number";
    cout << "| " << setw(25) << left << "Client Name";
    cout << "| " << setw(12) << left << "Balance";
    cout << "\n_____________________________________________________________________\n";
    double TotalBalances = 0;
    for (sClient Client : vClients)
    {
        
        cout << "| " << setw(15) << left << Client.AccountNumber;
        cout << "| " << setw(25) << left << Client.Name;
        cout << "| " << setw(12) << left << Client.AccountBalance << endl;

        
        TotalBalances += Client.AccountBalance;
    }
    cout << "_____________________________________________________________________\n";

    cout << "\n\t\t Total Balances = " << TotalBalances << endl;
}
void withdraw(vector<sClient>& vClients)
{
    system("cls");
    cout << "-----------------------------------\n";
    cout << "\tWithdraw Screen\n";
    cout << "-----------------------------------\n";
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClientCard(Client);
    double withdrawAmount = 0;
    cout << "Please enter withdraw amount? \n";
    cin >> withdrawAmount;
    char Answer = 'n';
    cout << "\nAre you sure you want to perform this transaction? y/n ? ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance -= withdrawAmount;
                Client = C;
                break;
            }
        }
        saveclientdatatofile(ClientsFileName, vClients);
        cout << "\nDone Successfully. New balance is: " << Client.AccountBalance << endl;

    }
}
void deposet(vector<sClient>& vClients)
{
    system("cls");
    cout << "-----------------------------------\n";
    cout << "\tDeposit Screen\n";
    cout << "-----------------------------------\n";
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClientCard(Client);
    double DepositAmount = 0;
    cout << "please deposite amount! \n"; 
    cin >> DepositAmount;
    char Answer = 'n';
    cout << "\nAre you sure you want to perform this transaction? y/n ? ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += DepositAmount; 
                Client = C; 
                break;
            }
        }
        saveclientdatatofile(ClientsFileName, vClients);
        cout << "\nDone Successfully. New balance is: " << Client.AccountBalance << endl;
        
    }
 
}
 void trans (vector<sClient>& vClients) {

    short option = 0;
    string AccountNumber = "";
    sClient client;


    do
    {
        ShowTransactionsMenuScreen();

        cout << "Choose what do you want to do? [1 to 4]? ";
        cin >> option;


        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');

            option = 0;
        }

        switch (option)
        {
        case 1:
            deposet(vClients);
            break;
        case 2:
            withdraw(vClients);
            
            break;
        case 3:
            ShowTotalBalancesScreen(vClients);
            break;
        case 4:
            
            break;
      
        default:
            cout << "\nWrong Option! Please choose from 1 to 4.\n";
        }

        if (option != 4)
        {
            cout << "\n\nPress any key to go back to Transactions Menu...";
            system("pause>0");
        }

    } while (option != 4);

}

void youroption(vector<sClient>& vClients)   
{
    short option = 0;
    string AccountNumber = "";
    sClient client;


    do
    {
        ShowMainMenuScreen();

        cout << "Choose what do you want to do? [1 to 7]? ";
        cin >> option;


        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');

            option = 0;
        }

        switch (option)
        {
        case 1:
            PrintAllClientsData(vClients);
            break;
        case 2:
            AddClients();
            vClients = LoadCleintsDataFromFile(ClientsFileName);
            break;
        case 3:
            AccountNumber = ReadClientAccountNumber();
            DeleteClientByAccountNumber(AccountNumber, vClients);
            break;
        case 4:
            AccountNumber = ReadClientAccountNumber();
            updateclient(vClients, AccountNumber);
            break;
        case 5:
            AccountNumber = ReadClientAccountNumber();
            if (FindClientByAccountNumber(AccountNumber, vClients, client))
            {
                PrintClientCard(client);
            }
            else
            {
                cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
            }
            break;
        case 6: 
            trans(vClients);
            break;

        case 7:
            cout << "\nThanks for using our system! Goodbye 👋\n";
            break;
        default:
            cout << "\nWrong Option! Please choose from 1 to 6.\n";
        }

        if (option != 7)
        {
            cout << "\n\nPress any key to go back to Main Menu...";
            system("pause>0");
        }

    } while (option != 7);
}
int main()
{
    
    vector <sClient> vClients= LoadCleintsDataFromFile(ClientsFileName);

    youroption(vClients);
   
  
}