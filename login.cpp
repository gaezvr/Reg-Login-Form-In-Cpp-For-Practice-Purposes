#include <iostream>
#include <fstream> // reading and writing files
using namespace std;

class Menu 
{
    private:
        friend class Register;
        friend class Login;

    public:
        string getUsername ()
        {
            return "Enter a username: ";
        }

        string getPassword ()
        {
            return "Enter a password: ";
        }

        string getChoice ()
        {
            return "Choice: ";
        }

        void displayDashboard ()
        {
            // Display dashboard:
            cout << "Successfully logged in!" << endl;
            cout << endl;
            cout << "Welcome back!" << endl;
            cout << endl;
            cout << "DASHBOARD" << endl;
            cout << "No new messages." << endl; // example of what could appear on the user's dashboard
            cout << endl;            
            this->exit();
        }

        void exit ()
        {
            system("exit"); // exits program
        }

        void clear ()
        {
            cout << "\x1B[2J\x1B[H"; // No iba el system clear co
        }

        string errorMessage ()
        {
            return "Invalid login!";
        }

        void mainMenu ()
        {
            cout << endl;
            cout << "Main Menu: " << endl;
            cout << "-------------------------------" << endl;
            cout << "0. Register" << endl;
            cout << "1. Login" << endl;
            cout << endl;
        }
};

class Credentials
{
    private:
        string username, password;
        string un, pw, temp;
        ifstream read;
        ofstream file;
        friend class Register;
        friend class Login;

    public:
        void setPassword ()
        {
            cin >> this->password;
        }

        void setUsername ()
        {
            cin >> this->username;
        }

        void openFile ()
        {
            this->read.open(this->username + ".txt");
        }

        void closeFile()
        {
            this->read.close();
        }

        void getUsernameFromFile ()
        { 
            getline(read, this->un);
            this->un.erase(0, 10);
        }

        void getPasswordFormFile ()
        {
            getline(read, this->pw);
            this->pw.erase(0, 10);
        }
};

class Register : public Credentials, public Menu
{
    public:
        void registration()
        {
            this->setUsername();
            this->setPassword();
            this->openRegistrationFile();
            file << "Username: " << this->username << endl << "Password: " << this->password;
            cout << "Welcome " << this->username << "!" << endl;
            this->closeRegistrationFile();
        }

        void closeRegistrationFile()
        {
            this->file.close();
        }

        void openRegistrationFile()
        {
            file.open(this->username + ".txt");
        }
};

class Login : public Credentials, public Menu
{
    public:
        bool isLoggedIn()
        {
            return (this->un == this->username && this->pw == this->password);
        }

        void login()
        {
           
            cout << "Login: " << endl << this->getUsername();
            this->setUsername();
            cout << this->getPassword();
            this->setPassword();

            this->openFile();
            this->getUsernameFromFile();
            this->getPasswordFormFile();
            
            if (this->isLoggedIn())
            {
                this->displayDashboard();
            }
            else
            {
                this->clear();
                cout << this->errorMessage() << endl;
                this->exit();
            }

            this->closeFile();
        }
};

int main(void)
{
    Menu m;
    Login l;
    Register r;
    bool choice;

    m.mainMenu();
    cin >> choice;

    if (choice)
    {
        l.login();
    }
    else
    {
        r.registration();
    }
    return 0;
}