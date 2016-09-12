#include<iostream>
using std::cout; using std::endl;

#include "class-10.h"

int main(){
  TextBuffer tb(5);
  tb.insert('c');
  cout << "First c: "<< tb << endl<<endl;
  tb.insert('a');
  tb.insert('t');
  cout << "Cat: "<< tb << endl<<endl;
  tb.del();
  cout << "Del: " << tb << endl<<endl;
  tb.left();
  cout << "left 1: "<<tb << endl<<endl;
  tb.insert('r');
  cout << "add r: "<<tb << endl<<endl;
  tb.right();
  cout << "right 1: "<<tb << endl<<endl;
  tb.insert('t');
  cout << "insert t: "<<tb << endl<<endl;
  tb.left();
  tb.left();
  cout << "left 2: "<<tb << endl<<endl;
  tb.insert('e');
  cout << "grow: "<<tb << endl<<endl;
  tb.right();
  tb.right();
  tb.insert('e');
  cout << "Final: "<<tb << endl<<endl;    
}
