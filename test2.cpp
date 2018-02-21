#include "DocumentGenerator.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>

using namespace std;

int main(){
  string directory = "PresidentialSpeeches/ExampleInput/";

  DocumentGenerator dg(directory);

  cout << "map size is " << dg.myMap.size() << endl;
}
