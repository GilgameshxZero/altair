#include <iostream>
#include <vector>
using namespace std;
 
vector<int> sequence;
int a, b;
 
bool search(int start, int end) {
  sequence.push_back(start);
  if (end == start) {
    return true;
  }
  
  if (10 * start + 1 < end) {
    if (search(10 * start + 1, end)) {
      return true;
    }
    sequence.pop_back();
  }
  if (2 * start < end) {
    if (search(2 * start, end)) {
      return true;
    }
    sequence.pop_back();
  }
  return false;
}
 
int main() {
  cin >> a >> b;
  
  if (search(a, b)) {
    cout << "YES";
  } else {
    cout << "NO";
  }
}
