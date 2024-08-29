#include <ctype.h>
#include <cctype>
#include <regex>
#include <stdio.h>
#include "printer.cpp"
using namespace std;

int eof = 0;
class reader {
private:
  vector<string> tokens;
  int position = 0;
public:
  reader(vector<string> _tokens) {
    tokens = _tokens;
  }
  
  string next() {
    string str = tokens[position]; 
    position ++;
    return str;
  } 

  string peek() {
    return tokens[position];
  }

  bool is_empty() {
    return position == tokens.size() ? true : false;
  }

  int pos() {
    return position;
  }
};

vector<string> tokenize(string str) {
  regex pattern(R"([\s,]*(~@|[\[\]{}()'`~^@]|"(?:\\.|[^\\"])*"?|;.*|[^\s\[\]{}('"`,;)]*))");
  // cout << "Originial string: " << str << endl;

  vector<string> tokens;
  auto str_begin = sregex_iterator(str.begin(), str.end(), pattern);
  auto str_end = sregex_iterator();
  for(sregex_iterator i = str_begin; i != str_end; i++) {
    smatch match = *i;
    string match_str = match.str(1);
    if(!match_str.empty()) {
      tokens.push_back(match_str);
      // cout << ":" << match_str << "}" << endl;
    }
  }

  // cout << endl << "Tokens parsed" << endl;
  return tokens;
}


// Maintain a stack to track list
vector<unique_ptr<MalType>> CurrentList;

void read_form(reader* r, MalListType* list);

void read_list(reader* r, MalListType* list) {
  string current = r->next();
  // cout << "Current(From read list): " << current << endl;
  if(current == ")") {
    return;
  } else {
    read_form(r, list);
  }

}

bool isNumber(string str) {
  return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

unique_ptr<MalType> read_atom(reader* r) {
  string current = r->next();
  // cout << "Current(From read atom): " << current << endl;
  if(isNumber(current)) {
    unique_ptr<MalNumType> num = make_unique<MalNumType>(current);
    // list->MalList.push_back(std::move(num));
    return num;
  } else {
    unique_ptr<MalStrType> str = make_unique<MalStrType>(current);
    // list->MalList.push_back(std::move(str));
    return str;
  }

}

void read_form(reader* r, MalListType* list) {
  while(!r->is_empty()) {
    string current = r->peek();
    // cout << "Current(From read form): " << current << endl;
    // If encounters a list
    if(current == "(") {

      unique_ptr<MalListType> newlist = make_unique<MalListType>();
      // unique_ptr<MalStrType> lparen = make_unique<MalStrType>("(");
      // newlist->MalList.push_back(std::move(lparen));

      read_list(r, newlist.get());
      // unique_ptr<MalStrType> rparen = make_unique<MalStrType>(")");
      // newlist->MalList.push_back(std::move(rparen));
      list->MalList.push_back(std::move(newlist));
      eof++;
    } else if(current == ")") {
      read_list(r, list);
      eof--;
      return;
    } else {
      list->MalList.push_back(read_atom(r));
    }
    // cout << "Current position: " << r->pos() << endl;
  }
  
}

unique_ptr<MalListType> TypedTokens;

int read_str(string str) {
  vector<string> tokens = tokenize(str);
  reader r(tokens);
  TypedTokens = make_unique<MalListType>();
  read_form(&r, TypedTokens.get());
  if(eof > 0) {
    return 1;
  } else {
    return 0;
  }
// cout << "Tokens analyzed" << endl;

  // cout << "Completed" << endl;
}
