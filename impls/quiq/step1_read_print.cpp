#include "reader.cpp"
using namespace std;

string getInput() {
  int in = ' ';
  string out;
  while(in != EOF && in != '\n') {
    in = getchar();
      out += in;
  }

  return out;
}

int main() {
  while(true) {
    printf("user> ");
    string input = getInput();
    if(read_str(input) == 0) {
      pr_str(TypedTokens.get());
    } else {
      cout << "EOF";
    }
    cout << endl;
    // printf("%s", a.c_str());
  }
}

