#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <map>

using namespace std;

void *sysCall(void *param);
void useless() {
//does nothing just needed for map
}
inline vector<string> split(const string&,const string&);

int main(int argc, char* argv[]) {
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    string whole;
    map<std::string, void(*)()> cdMap{
            {"dir",      useless},
            {"help",     useless},
            {"vol",      useless},
            {"path",     useless},
            {"tasklist", useless},
            {"notepad",  useless},
            {"echo",     useless},
            {"color",    useless},
            {"ping",     useless}
    };
    //map cannot only have parameter !



    while (true) {
        cout << "==>";
        getline(cin, whole);
        auto in = split(whole, " ");  //split words into 2

        if (cdMap.find(in[0]) != cdMap.end()) {
            //word was found so copy it into command
            char *command = new char[whole.length() + 1];
            strcpy(command, whole.c_str());


            //create thread
            pthread_create(&tid, &attr, sysCall, command);
            pthread_join(tid,nullptr);
        }
        //exit method
        else if (in[0] == "exit" || in[0] == "quit") {
            cout << "Thx for using my shell:D";
            break;
        }
        //non valid words
        else{
            cout << "This is not a valid command, please try again" << endl;
        }
    }




    return 0;
}
void *sysCall(void *param) {
    char *command = static_cast<char *>(param);
    system(command);
    delete[] command; // free the allocated memory
    pthread_exit(nullptr);
    return nullptr;
}

inline vector<string> split(const string& in, const string& del){
    vector<string> sep;

    if(in.empty()) return sep;

    size_t pos;
    size_t lpos = 0;
    auto dlen = del.length();

    while((pos = in.find(del, lpos)) != string::npos) {
        sep.push_back(in.substr(lpos, pos - lpos));
        lpos = pos + dlen;
    }
    sep.push_back(in.substr(lpos, in.length()));
    return sep;

}
