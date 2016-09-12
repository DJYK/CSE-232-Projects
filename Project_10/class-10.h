#ifndef TEXT_BUFFER
#define TEXT_BUFFER

#include<iostream>
using std::ostream;
#include<algorithm>
using std::swap;

class TextBuffer{
private:
  char* buf_;
  size_t size_;
  size_t capacity_;
  size_t cursor_;
  size_t back_;
  void grow();
  void swap(TextBuffer&);

public:
  TextBuffer(size_t s=10);
  TextBuffer(TextBuffer&);
  ~TextBuffer();
  TextBuffer& operator=(TextBuffer); // copy and swap;
  bool isfull();
  bool isempty();
  void insert(char);
  bool del();
  bool left();
  bool right();
  friend ostream& operator<<(ostream& out, TextBuffer &tb);
};

#endif
