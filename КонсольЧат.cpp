#include<iostream>
using namespace std;
#include "Chat.h"
int main()
{
    setlocale(LC_ALL, "rus");
    Chat chat;
    chat.start();
    while (chat.isChatWork())
    {
        chat.ShowLoginMenu();
        while (chat.getCurrentUser())
        {
            chat.ShowUserMenu();
        }
    }
    return 0;
}