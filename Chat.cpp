#include<iostream>
#include "Chat.h"
using namespace std;
void Chat::start()
{
    isChatWork_ = true;
}

std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const
{
    for (auto& user : userList_)
    {
        if (login == user.getUserLogin())
            return std::make_shared <User> (user);
    }
    return nullptr;
}

std::shared_ptr<User> Chat::getUserByName(const std::string& name) const
{
    for (auto& user : userList_)
    {
        if (name == user.getUserName())
            return std::make_shared<User>(user);
    }
    return nullptr;
}

void Chat::login()
{
    std::string login, password;
    char operation;
    do
    {
        std::cout << "login:   ";
        std::cin >> login;
        std::cout << "password:   ";
        std::cin >> password;

        currentUser_ = getUserByLogin(login);
        if (currentUser_ == nullptr || (password != currentUser_->getUserPassword()))
        {
            currentUser_ == nullptr;
            std::cout << "login failed..." << std::endl;
            std::cout << "(0) exit or any key repeat:    ";
            std::cin >> operation;
            if (operation == '0')
                break;
        }
    } while (!currentUser_);
}


void Chat::signUp()
{
    std::string login, password, name;
    std::cout << "login:               ";
    std::cin >> login;
    std::cout << "password:            ";
    std::cin >> password;
    std::cout << "Name:                ";
    std::cin >> name;
    if (getUserByLogin(login) || login == "all")
    {
        throw UserLoginExp();
    }
    if (getUserByName(name) || name == "all")
    {
        throw UserNameExp();
    }
    User user = User(login, password, name);
    userList_.push_back(user);
    currentUser_ = std::make_shared<User>(user);
}

void Chat::ShowAllUsersName() const
{
    cout << "users" << endl;
    for (auto& user : userList_)
    {
        cout << user.getUserName();
        cout << endl;
        if (currentUser_->getUserLogin() == user.getUserLogin())
        {
            cout << "(me)";
            cout << endl;
        }
        cout << endl;
    }
}
void Chat::ShowLoginMenu()
{
    currentUser_ = nullptr;
    char operation;
    do
    {
        std::cout << "(1) Login" << std::endl;
        std::cout << "(2) signUp" << std::endl;
        std::cout << "(0) Shutdown" << std::endl;
        std::cin >> operation;
        switch (operation)
        {
        case '1':
            login();
            break;
        case '2':
            try
            {
                signUp();
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
            break;
        case '0':
            isChatWork_ = false;
            break;
        default:
            std::cout << "1 or 2..." << std::endl;
            break;
        }
    } while (!currentUser_ && isChatWork_);
}

void Chat::ShowUserMenu()
{
    char operation;
    std::cout << "Hi,    " << currentUser_->getUserName() << std::endl;
    while (currentUser_)
    {
        std::cout << "Menu: (1) Show Chat  | (2) Add message  | (3) Users  | (0) Logout ";
        std::cout << std::endl;
        cout << ">>";
        std::cin >> operation;
        switch (operation)
        {
        case '1':
            showChat();
            break;
        case '2':
            addMessage();
            break;
        case '3':
            ShowAllUsersName();
            break;
        case '0':
            currentUser_ = nullptr;
            break;
        default:
            std::cout << " Unknown choice..." << std::endl;
            break;
        }
    }
}



//void Chat::addMessage()
//{
//    std::string to, text;
//    std::cout << "To (name or ALL):                  ";
//    std::cin >> to;
//    std::cout << "text:                  ";
//    std::cin.ignore();
//    getline([&] to , [&] text;);
//    if (!(to == "all" || getUserByName(to)))
//    {
//        std::cout << "error send message: can not finde" << to << std::endl;
//        return;
//    }
//    if (to == "all")
//    {
//        messageList_.push_back (Message(from: currentUser_->getUserLogin(), to : "all", text;));
//    }
//    else
//    {
//        messageList_.push_back (Message(from: currentUser_->getUserLogin(), to : getUserByName(to)->getUserLogin(), text; ));
//    }
//}

void Chat::showChat() const
{
    std::string from, to;
    std::cout << "-----------×ÀÒ-----------" << std::endl;
    for (auto& mess :  messageList_)
    {
        if (currentUser_->getUserLogin() == mess.getFrom() || currentUser_->getUserLogin() == mess.getTo() || mess.getTo() == "all")
        {
            from = (currentUser_->getUserLogin() == mess.getFrom()) ? "me" : getUserByLogin(mess.getFrom())->getUserName();
        }
        if (mess.getTo() == "all")
        {
            to = "(all)";
        }
        else
        {
            to = (currentUser_->getUserLogin() == mess.getTo()) ? "me" : getUserByLogin(mess.getTo())->getUserName();
        }
        std::cout << "Message from" << from << "to" << to << std::endl;
        std::cout << "text:       " << mess.getText() << std::endl;
    }
    std::cout << "---------------------------------------------------------" << std::endl;
}

void Chat::addMessage()
{
    std::string to, text;
    std::cout << "To (name or ALL):                  ";
    std::cin >> to;
    std::cout << "text:                  ";
    std::cin.ignore();
    std::getline (std::cin >> to,  text);
    if (!(to == "all" || getUserByName(to)))
    {
        std::cout << "error send message: can not finde" << to << std::endl;
        return;
    }
    if (to == "all")
    {
        messageList_.push_back (Message(currentUser_->getUserLogin(),"all", text));
    }
    else
    {
        messageList_.push_back (Message(currentUser_->getUserLogin(), getUserByName(to)->getUserLogin(), text ));
    }
}
//void Chat::ShowAllUsersName() const
//{
//    cout << "users" << endl;
//    for (auto& User : userList_)
//        {
//        cout << User.getUserName();
//        cout << endl;
//        if (currentUser_->getUserLogin() == User.getUserLogin())
//            {
//            cout << "(me)";
//            cout << endl;
//            }
//        cout << endl;
//        }
//}
