#include <iostream>
#include <pthread.h>
#include <unistd.h>


using namespace std;

void *systemCall(void *param);


int main(int argc, char* argv[]) {

    pthread_t tid;
    pthread_attr_t attr;
    string in;


    while (true) {
        cout << "==>";
        getline(cin, in);

        if (in == "exit" || in == "quit") {
            cout << "Thanks for using myShell!" << endl;
            break;
        }
        else{
            char *command = new char[in.length() + 1];
            strcpy(command, in.c_str());

            pthread_attr_init(&attr);
            pthread_create(&tid, &attr, systemCall, command);
            pthread_join(tid,NULL);
        }


    }
    return 0;
}
void *systemCall(void *param) {
    char *command = static_cast<char *>(param);
    system(command);
    delete[] command; // Free the allocated memory
    pthread_exit(nullptr);
}
