
#include<iostream>
#include<iomanip>
#include<cstdlib>//needed for system cls
#include<fstream>
#include<cctype>


using namespace std;
class Bank_Account
{
    //defining
    int account_number;
    char name[50];
  int Money_Deposit;
    char type;
    
    public:
    void modify();//function to modify or add new data
    void report() const;//function to show data in tabular form
    int retacno()const;//function to return account number
    void dep(int x);//function to deposit money and add
    void draw(int x);//function to draw money and minus
    int retdeposit()const;//function to return balance amt
    void create_account();//function to get data from user
    void Display_Account()const;//function to show data on screen
    void Calculate_Interest();//function to calculate interest
    char rettype()const;//function to return type of account
};//class ends here..............

void Bank_Account::create_account(){
    system("clear");//(this will allow terminal to reclean it out)
    cout<<"\n\t Enter the account number : ";
    cin>>account_number;
    cout<<"\t Enter the name of the account holder : ";
    cin.ignore();
    cin.getline(name,50);//it means whatever we do here it need to store here and elmnt is 50
    cout<<"\t Enter the type of the account (C/S):";//to select the bank acc type
cin>>type;
cout<<endl;
type=toupper(type);//it will automatically correct to uppercase
cout<<"\n\t Enter the initial amount (>=500 for saving and >=1000 for current ): ";
cin>>Money_Deposit;
cout<<endl;
cout<<"\n\t Account Created... Thank you for choosing us";
cout<<endl;
}

void Bank_Account::Display_Account() const{
    cout<<"\n\t Bank Account Number"<<account_number<<endl;
    cout<<"\n\t Account holder Name : "<<name;
    cout<<"\n\t Type of account :"<<type<<endl;
    cout<<"\n\t Balance Amount :"<<Money_Deposit<<endl;
}
void Bank_Account::modify(){
cout<<"\n\t Account Number : "<<account_number<<endl;
cout<<"\n\t Modify Account Holder Name : ";
cin.ignore();
cin.getline(name,50);
cout<<"\n\t Modify Type of Account : ";
cin>>type;
type=toupper(type); //convert to upper case
cout<<"\t Modify Balance Amount : ";
cin>>Money_Deposit;
}
void Bank_Account::report()const{
    cout<< account_number<< setw(10)<<""<< name<<setw(10) <<type<< setw(6) << Money_Deposit << endl;
}
char Bank_Account::rettype() const{
    return type;;
}
void Bank_Account::dep(int x)
{
    Money_Deposit+=x;
}
void Bank_Account::draw(int x){
   Money_Deposit-=x;
}
int Bank_Account::retacno()const{
    return account_number;
}
int Bank_Account::retdeposit()const{
    return Money_Deposit;
}


//...........................................
//  Aba function Declare Garam
//........................................
void write_account();//function to write record in binary file
void display_details(int);//function to display account details given by user
void delete_account(int);//function to delete record of file
//creating account
void display_all();//function to display account details
void Money_Deposit_Withdraw(int, int);//function to deposit/withdraw money
void Updation_bank_account(int);//function to update account details or modify
void intro();   //introductory screen function

//..................
//Aba chai main function suru bho program ko
//........................

int main(){
    char ch;
    int num;
    intro();
    do{
        system("clear");

    cout<<"\t\t......................."<<endl;
    cout<<"\t\t......SABKO BANK......."<<endl;
    cout<<"\t\t......................."<<endl;
    cout<<endl;
    cout<<"\n\t---Main Menu"<<endl;
    cout<<"\n\t 1.Create Account"<<endl;
    cout<<"\n\t 2. Deposit Money"<<endl;
    cout<<"\n\t 3. Withdraw the Money."<<endl;
    cout<<"\n\t 4. Balance Enquiry"<<endl;
    cout<<"\n\t 5. Account Holders"<<endl;
    cout<<"\n\t 6. Close an account"<<endl;
    cout<<"\n\t 7. Modify a account"<<endl;
    cout<<"\n\t 9. Exit ";
    cout<<endl;
    cout<<"\t Enter your choice (1-9) :";
    cin>>ch;
    system("clear");

switch (ch)
{
case '1':
write_account();
break;
case '2':
system("cls");
cout<<"\n\t Enter the account number : ";
cin>>num;
Money_Deposit_Withdraw(num, 1);//deposit function
break;
case '3':
cout<<"\n\t Enter the account number :";
cin>>num;
Money_Deposit_Withdraw(num, 2);//withdraw function
break;
case '4':
cout<<"\n\t  Enter the account number : ";
cin>>num;//balance enquiry function
display_details(num);
break;
case '5':
display_all();//display all function
break;
case '6':
cout<<"\t Enter the account number : ";
cin>>num;
delete_account(num);//whatever the  value user is giving we use here
//close account function
break;
case '7':
cout<<"\t Enter the account Number :";
cin>>num;
Updation_bank_account(num);//modify account function
break;
case '8':
system("clear");
        cout<<"\t\n Thanks for using the system.";
            break;
    

default: cout<<"\a";
}
cin.ignore();
cin.get();
}while(ch!='8');
return 0;

}
//..........................
//Function to write in file
//..........................
void write_account()//function to write record in binary file
{
    Bank_Account ac;
    ofstream outFile;
    outFile.open("account.dat",ios::binary|ios::app);//it is saying first of all we store iofstream file and offstream have to open account.dat
ac.create_account();//first of all it will take data from user and convert into binary and call out the function
outFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
outFile.close();//it close and help to run our function
}
//...................................
//creating function for deleting account
//.....................................
void delete_account(int n){
    Bank_Account ac;
    ifstream inFile;//input file stram
    ofstream outFile;//output file stream
    inFile.open("account.dat",ios::binary);
    if(!inFile){
        cout<<"File couldnot open !! Press any key....";
        return;//it says if there is no such thing as infile it has to return
    }
    //if file is present then we will clik on infile.open and we will have to take the data
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
   //while checks infile and reintrepret and checks char presence and store in ac ans the size
   while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account)))
    {
       if(ac.retacno()!=n){
        outFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
       }
    }
   //to close whatever programme was running
    inFile.close();
    outFile.close();
    remove("account.dat");//now the data we have will be removed
    rename("Temp.dat","account.dat");//renaming rempdata as well as bank acc data
    cout<<"\t Account Closed or Removed..."<<endl;
}

// .......................................
// function to read specific data from file
// .......................................

void display_details(int n){//it means it will take one value i.e bank acc that we will use
Bank_Account ac;
bool flag=false;//whether initial flag is false
ifstream inFile;
inFile.open("account.dat",ios::binary);//to check whether the acc user is asking exists
if(!inFile){
    cout<<"File could not be open !! Press any key...";
    return;

}//if file is present
cout<<"\n Bank Account Details\n"<<endl;
while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account))){
    if (ac.retacno()==n){
        ac.Display_Account();
        flag=true;
    }
}
inFile.close();
if(flag==false){
    cout<<"\n\t Account number doesnot exist\n"<<endl;
}
}

// .......................................
// function to DEposit and withdraw money
// ......................................

void Money_Deposit_Withdraw(int n,int option )//withdraw and deposit function and option to know the withdraw or deposit
{
  int amt; //coz whatever the withdraw or deposit its same
   bool found=false;
   Bank_Account ac; //to access bank account
   fstream File;
   File.open("account.dat", ios::binary|ios::in|ios::out);//File handling only one file is use
   if(!File)
   {
        cout << "File couldnot be opened !! press any key...";
        return;
   }
   //to increment and check
   while (!File.eof() && found==false)
   {
    File.read(reinterpret_cast<char *> (&ac),sizeof(Bank_Account));
    //now passing the condition
    if(ac.retacno()==n){
        //if there is really an account we have to check
        ac.Display_Account();
        if(option==1)
        {
            cout<<"\n\t To Deposit Amount";
            cout<<"\t Enter the amount to be deposited :";
            cin>>amt;
            ac.dep(amt);
        }
        if(option==2)
        {
            cout<<"\n\t To Withdraw Amount";
            cout<<"\n\t Enter amount to be withdraw : ";
            cin>>amt;
            int bal=ac.retdeposit()-amt;
            if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
                cout<<"\t Insufficient Balance";
else{
                ac.draw(amt);}
        }// now casting into integer and returning the size of bank account
        int pos=(-1)*static_cast<int>(sizeof(ac));
        File.seekp(pos,ios::cur);//move the pointer to the position of the file
        File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));//write the record of the file like changes that happened
        cout<<"\n\t Record Updated"<<endl;
        found=true; //if not written it will throw an error as initial found will be false

    }
   }
   File.close();
   if(found == false){
    cout<<"\n\t Record not found"<<endl;//like there is no account or no amt

   }
   

}


// ...........................
// Displaying all data function
// ............................

void display_all()//function to display all account details account holders
{
    Bank_Account ac;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile){
        cout<<"File couldnot be opened !! Press any key...";
        return;
    }
    cout<<"\n\n\t Bank Account holder list\n\n"<<endl;
    cout<<"==================================================="<<endl;
    cout<<"A/c no.         Name             Type       Balance  "<<endl;
    cout<<"==================================================="<<endl;
    while(inFile.read(reinterpret_cast<char *>(&ac), sizeof(Bank_Account))){
        ac.report();
    }
    inFile.close();
}
//...................
//it is function for modifying the data
//....................................
void Updation_bank_account(int n){
    bool found=false; //to check
    //to access bank acc
    Bank_Account ac;
    fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);//open file in binary mode
    if(!File){
        cout<<"\t File could not be opened!! Press any key...";
        return;
    }
    while(!File.eof() && found==false){
        File.read(reinterpret_cast<char *>(&ac), sizeof(Bank_Account));//read the rcord of the file
        //checking if account exist
        if(ac.retacno()==n){
            ac.Display_Account();
            cout<<endl;
            cout<<"\t Enter the new detils of the account"<<endl;
            ac.modify();
            int pos = (-1)*static_cast<int>(sizeof(Bank_Account));//Move the pointer to the position of the file
            File.seekp(pos,ios::cur);//move the pointer to the position of the file
            File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));//write the record in file
            cout<<"\t Record Updated"<<endl;
            found=true;
        }
    }
    File.close();
    if(found==false){
        cout<<"\n\t Record Not Found"<<endl;
    }
}

void intro()
{
}
