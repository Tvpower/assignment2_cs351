#include <iostream>
#include <vector>
#include <map>
#include <functional>

using namespace std;

string getFirst(string a)
{
  for(auto b : a)
  {
    cout << b;
  }
}

void exeSystemCall(const string& a) {
  system(a.c_str());
}

int main(int argc, char* argv[]) {
  string in;

  map<string, function<void(const string&)>> cdMap{
          {"dir", exeSystemCall},
          {"help", exeSystemCall},
          {"vol", exeSystemCall},
          {"path", exeSystemCall},
          {"tasklist", exeSystemCall},
          {"notepad", exeSystemCall},
          {"echo", exeSystemCall},
          {"color", exeSystemCall},
          {"ping", exeSystemCall}
  };

  while (true) {
    cout << "==>";
    getline(cin, in);

    if (cdMap.find(in) != cdMap.end()) {
      cdMap[in]("ping 192.168.0.1");
    } else if (in == "exit") {
      break;
    } else {
      cout << "This is not a valid word, please try again" << endl;
    }
  }

  return 0;
}