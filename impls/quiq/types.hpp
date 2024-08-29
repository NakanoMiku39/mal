#include <bits/stdc++.h>
#include <string>
#include <vector>
using namespace std;

class MalType {
public:
  virtual void dump() = 0;
  virtual ~MalType() = default;
};

class MalListType: public MalType {
private:

public:
  vector<unique_ptr<MalType>> MalList;
  MalListType() {
    // cout << "MalListType created" << endl;
  }
  
  MalListType(vector<unique_ptr<MalType>> _MalList) {
    MalList = std::move(_MalList);
  }

  void dump() {
// cout << "MalList dumped: " << endl;
    cout << "(";
    for(auto &i: MalList) {
      i->dump();
      if(i != MalList.back()) {
	cout << " ";
      }
    }
    cout << ")";
  }
};

class MalNumType: public MalType {
private:
  int value;
public:
  MalNumType(string num) {
    value = strtod(num.c_str(), nullptr);
    // cout << "MalNumType " << num << " created" << endl;
  }

  void dump() {
    cout << value;
  }
};

class MalStrType: public MalType {
  private:
  string name;
public:
  MalStrType(string _name) {
    name = _name;
    // cout << "MalNumType " << name << " created" << endl;
  }

  void dump() {
    cout << name;  
  }
};


 
