#include <iostream>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

enum COMMANDS {UNKNOWN=0, SHUTDOWN, RESTART, SLEEP, HIBERNATE, LOGOUT, LOCK};
vector<string> names;

bool dirExists(string &path)
{
    struct stat info;

    if(stat( path.c_str(), &info ) != 0)
        return false;
    else if(info.st_mode & S_IFDIR)
        return true;
    else
        return false;
}

void getFileNames(vector<string> &s) {
    s.push_back("/actionShutdown.txt");
    s.push_back("/computerAction.txt");
    s.push_back("/actionSleep.txt");
    s.push_back("/actionHibernate.txt");
    s.push_back("/actionLock.txt");
}

string readFile(vector<string> &names, string &path, bool deleteFile) {
    ifstream f;
    string command, name;
    vector<string>::iterator i=names.begin();
    do {
        f.open(path+*i);
        if (!f)
            i++;
    } while (i<names.end() && !f);
    if (!f) {
        return "";
    }
    f>>command;
    f.close();
    cout << command <<endl;
    if (deleteFile && command!="")
        remove ((path+*i).c_str());
    return command;
}

COMMANDS getCommand(string command) {
    if (command=="shutdown")
        return SHUTDOWN;
    if (command=="restart")
        return RESTART;
    if (command=="sleep")
        return SLEEP;
    if (command=="hibernate")
        return HIBERNATE;
    if (command=="logout")
        return LOGOUT;
    if (command=="lock")
        return LOCK;
    return UNKNOWN;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cout << "Invocazione non corretta."<<endl;
        return 1;
    }
    int secs=atoi(argv[1]);
    if (secs<1 || secs > 1000) {
        cout << "Numero di secondi non corretto." << endl;
        return 1;
    }
    string path=argv[2];
    if (!dirExists(path)) {
        cout<<"Path non corretta."<<endl;
        return 1;
    }

    path=path+"/AssistantComputerControl";

    if (!dirExists(path)) {
        cout<<"Impossibile trovare la directory AssistantComputerControl."<<endl;
        return 1;
    }

    getFileNames(names);

    while (1) {
        COMMANDS c=getCommand(readFile(names, path, true));
        switch (c) {
            case UNKNOWN: cout<<"comando non disponibile"<<endl; break;
            case SHUTDOWN: system("cinnamon-session-quit --power-off"); break;
            case RESTART: system("cinnamon-session-quit --reboot"); break;
            case SLEEP: system("dbus-send --system --print-reply --dest=org.freedesktop.login1 /org/freedesktop/login1 \"org.freedesktop.login1.Manager.Suspend\" boolean:true"); break;
            case HIBERNATE: system("dbus-send --system --print-reply --dest=org.freedesktop.login1 /org/freedesktop/login1 \"org.freedesktop.login1.Manager.Hibernate\" boolean:true"); break;
            case LOGOUT: system("cinnamon-session-quit --logout"); break;
            case LOCK: system("cinnamon-screensaver-command -l -m \"Bloccato da google assistant\""); break;
        }
        sleep(180);
    }
    return 0;
}

