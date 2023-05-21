#include<iostream>
#include<fstream>
using namespace std;

bool status;
int userIndex, transactions[100], loggInCount,money, currentUserId=-1;
string currentUser="none", name, mail, pass;

class User
{
    string mail,password,name;
    int balance;
    public:
        string  getMail()
{
    return mail;
}
string  getPass()
{
    return password;
}
string  getName()
{
    return name;
}
int  getBalance()
{
    return balance;
}
void  set_mail(string mail)
{
    this->mail=mail;
}
void  set_pass(string password)
{
    this->password=password;
}
void  set_name(string name)
{
    this->name=name;
}
void  set_balance(int balance)
{
    this->balance=balance;
}

    void print()
    {
        cout<<"Name: "<<getName()<<endl;
        cout<<"Mail: "<<getMail()<<endl;
        cout<<endl<<"Balance: "<<getBalance()<<" Taka"<<endl;
        cout<<endl<<endl;
    }
};

class Transaction
{
    string sender, receiver;
    int previousBalance, amount;

    public:
        string  get_sender()
{
    return sender;
}
string  get_receiver()
{
    return receiver;
}
int  get_previousBalance()
{
    return previousBalance;
}
int  get_amount()
{
    return amount;
}
void  set_sender(string sender)
{
    this->sender=sender;
}
void  set_receiver(string receiver)
{
    this->receiver=receiver;
}
void  set_prev_balance(int previousBalance)
{
    this->previousBalance=previousBalance;
}
void  set_amount(int amount)
{
    this->amount=amount;
}
};

User customer[100];
Transaction bussniness[100][5000];

inline void options()
{
    cout<<"1. Create new account"<<endl;
    cout<<"2. Sign in"<<endl;
    cout<<"3. Sign out"<<endl;
    cout<<"4. Reset Password"<<endl;
    cout<<"5. Send Money"<<endl;
    cout<<"6. View Transactions"<<endl;
    cout<<"7. View Customer List"<<endl;
    cout<<"8. Exit"<<endl;
    cout<<"9. View Logg in History"<<endl<<endl;
}

void createAccount()
{
    if(status)
    {
        cout<<"Please sign out of "<<currentUser<<" first"<<endl<<endl;
        return;
    }
    cout<<"Enter mail: "; cin>>mail;

    if(mail=="back")
    {
        cout<<endl; return;
    }

    cout<<"Enter password :"; cin>>pass;

    if(pass=="back")
    {
        cout<<endl; return;
    }

    cout<<"Enter Name: "; cin>>name;

    if(name=="back")
    {
        cout<<endl; return;
    }

    customer[userIndex].set_mail(mail);
    customer[userIndex].set_pass(pass);
    customer[userIndex].set_balance(500);
    bussniness[userIndex][0].set_prev_balance(500);
    customer[userIndex++].set_name(name);

    cout<<"Account created successfully"<<endl<<endl;
}

void signIn()
{
    if(status) cout<<"Already logged in, sign out first"<<endl<<endl;
    else
    {
        cout<<"Enter mail: "; cin>>mail;

        if(mail=="back")
        {
            cout<<endl; return;
        }

        cout<<"Enter password: "; cin>>pass;

        if(pass=="back")
        {
            cout<<endl; return;
        }

        bool permission=false;
        for(int i=0;i<userIndex;++i)
        {
            if(customer[i].getMail()==mail and customer[i].getPass()==pass)
            {
                permission=true, currentUserId=i; break;
            }
        }
        if(permission)
        {
            status=true, currentUser=mail, cout<<"Logged in";

            cout<<endl<<endl;
        }
        else cout<<"Email not found or Invalid password."<<endl<<endl;
    }
}

void signOut()
{
    if(!status) cout<<"Not signed in"<<endl<<endl;
    else status=false, currentUserId=-1, cout<<"Logged out"<<endl<<endl;
}

void reset_pass()
{
    if(status)
    {
        cout<<"Enter new password: "; cin>>pass;

        if(pass=="back")
        {
            cout<<endl; return;
        }

        if(pass==customer[currentUserId].getPass()) cout<<"Current password cannot be the new password"<<endl<<endl;
        else
        {
            customer[currentUserId].set_pass(pass);
            cout<<"Password Reset Successfully"<<endl<<endl;
        }
    }
    else
    {
        cout<<"Not logged in"<<endl<<endl;
        return;
    }
}

void send_money()
{
    if(status)
    {
        cout<<"Enter Recipient mail: "; cin>>mail;

        if(mail=="back")
        {
            cout<<endl; return;
        }

        cout<<"Amount to be sent: "; cin>>money;
        int id_receiver=-1;

        for(int i=0;i<userIndex;++i)
        {
            if(customer[i].getMail()==mail)
            {
                id_receiver=i; break;
            }
        }

        if(id_receiver==-1)
        {
            cout<<"Email not found"<<endl<<endl; return;
        }
        else if(mail==currentUser)
        {
            cout<<"Cannot send to own account"<<endl<<endl; return;
        }
        else
        {
            if(customer[currentUserId].getBalance()>=money)
            {
                bussniness[currentUserId][transactions[currentUserId]].set_amount(money);
                bussniness[currentUserId][transactions[currentUserId]].set_sender("none");
                bussniness[currentUserId][transactions[currentUserId]].set_receiver(customer[id_receiver].getName());

                int bal;
                bal=customer[currentUserId].getBalance();
                bal-=money;
                customer[currentUserId].set_balance(bal);

                bussniness[currentUserId][transactions[currentUserId]].set_prev_balance(bal);
                ++transactions[currentUserId];

                bussniness[id_receiver][transactions[id_receiver]].set_amount(money);
                bussniness[id_receiver][transactions[id_receiver]].set_sender(customer[currentUserId].getName());
                bussniness[id_receiver][transactions[id_receiver]].set_receiver("none");

                bal=customer[id_receiver].getBalance();
                bal+=money;
                customer[id_receiver].set_balance(bal);

                bussniness[id_receiver][transactions[id_receiver]].set_prev_balance(bal);
                ++transactions[id_receiver];

                cout<<"Transaction Successful"<<endl<<endl;
            }
            else cout<<"Insufficient Balance"<<endl<<endl;
        }
    }
    else cout<<"Not logged in."<<endl<<endl;
}

void view_transactions()
{
    if(status)
    {
        cout<<"Account Holder: "<<customer[currentUserId].getName()<<endl<<endl;
        if(transactions[currentUserId]==0) cout<<"No transactions have been made"<<endl;
        else
        {
            for(int i=0;i<transactions[currentUserId];++i)
            {
                cout<<"Transaction-"<<i+1<<endl;
                if(bussniness[currentUserId][i].get_sender()!="none")
                {
                    cout<<"Sender: "<<bussniness[currentUserId][i].get_sender()<<endl;
                }
                if(bussniness[currentUserId][i].get_receiver()!="none")
                {
                    cout<<"Receiver: "<<bussniness[currentUserId][i].get_receiver()<<endl;
                }
                cout<<"Amount: "<<bussniness[currentUserId][i].get_amount()<<" Taka"<<endl;
                cout<<"Current Balance: "<<bussniness[currentUserId][i].get_previousBalance()<<" Taka"<<endl<<endl;
            }
        }
    }
    else cout<<"Not logged in"<<endl<<endl;
}

void view_customer_list()
{

    if(userIndex)
    {
        for(int i=0;i<userIndex;++i)
        {
            customer[i].print();
        }
    }
    else cout<<"No account created"<<endl<<endl;

}

int main()
{
    ifstream loggg("loggIn.txt");

    loggg>>currentUser>>currentUserId>>userIndex;

    if(currentUser!="none") status=true;

    loggg.close();

    ifstream inp("Users.txt");//user info

    for(int i=0;i<userIndex;++i)
    {
        inp>>mail>>name>>pass>>money;
        customer[i].set_mail(mail);
        customer[i].set_name(name);
        customer[i].set_pass(pass);
        customer[i].set_balance(money);
    }
    inp.close();

    ifstream inp1("Transactions.txt");//transaction info

    char sender_or_receiver;
    int no_of_transaction;
    for(int i=0;i<userIndex;++i)
    {
        inp1>>no_of_transaction;
        for(int k=0;k<no_of_transaction;++k)
        {
            inp1>>sender_or_receiver>>name;
            if(sender_or_receiver=='s')
            {
                bussniness[i][k].set_sender(name);
                bussniness[i][k].set_receiver("none");
            }
            else if(sender_or_receiver=='r')
            {
                bussniness[i][k].set_receiver(name);
                bussniness[i][k].set_sender("none");
            }
            inp1>>money; bussniness[i][k].set_amount(money);
            inp1>>money; bussniness[i][k].set_prev_balance(money);
        }
        transactions[i]=no_of_transaction;
    }

    inp1.close();

    int choice;

    while(true)
    {
        options();

        if(status) cout<<"Current User: "<<customer[currentUserId].getName()<<endl<<endl;

        cout<<"Choice: "; cin>>choice;
        if(choice==8) break;
        switch(choice)
        {
            case 1: createAccount(); break;

            case 2: signIn(); break;

            case 3: signOut(); break;

            case 4: reset_pass(); break;

            case 5: send_money(); break;

            case 6: view_transactions(); break;

            case 7: view_customer_list(); break;
        }
    }

    ofstream logg("current logged in and total user number.txt");

    if(status) logg<<currentUser<<endl<<currentUserId<<endl;
    else logg<<"none"<<endl<<-1<<endl;

    logg<<userIndex<<endl;
    logg.close();

    ofstream out("Users.txt");

    for(int i=0;i<userIndex;++i)
    {
        out<<customer[i].getMail()<<endl;
        out<<customer[i].getName()<<endl;
        out<<customer[i].getPass()<<endl;
        out<<customer[i].getBalance()<<endl;
    }
    out.close();

    ofstream out1("Transactions.txt");

    for(int i=0;i<userIndex;++i)
    {
        out1<<transactions[i]<<endl;
        for(int k=0;k<transactions[i];++k)
        {
            if(bussniness[i][k].get_sender()!="none") out1<<'s'<<endl<<bussniness[i][k].get_sender()<<endl;
            if(bussniness[i][k].get_receiver()!="none") out1<<'r'<<endl<<bussniness[i][k].get_receiver()<<endl;
            out1<<bussniness[i][k].get_amount()<<endl;
            out1<<bussniness[i][k].get_previousBalance()<<endl;
        }
    }

    out1.close();

    return 0;
}
