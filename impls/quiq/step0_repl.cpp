#include <bits/stdc++.h>
#include <string>
using namespace std;

string getInput() {
  int in = ' ';
  string out;
  while(in != EOF && in != '\r' && in != '\n') {
    in = getchar();
      out += in;
  }
  return out;
}

int main() {
  while(true) {
    printf("user> ");
    string a = getInput();
    printf("%s", a.c_str());
  }
}
