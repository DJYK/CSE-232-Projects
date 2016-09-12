/*
David Kinchen 
2016-04-14
class-10.cpp
CSE 232 - Section 004

A text buffer class that does magic stuff.
Enjoy!
*/

#include <iostream>
using std::cout; using std::endl;
#include<iostream>
using std::ostream;
#include <iterator> 
using std::ostream_iterator;
#include <algorithm>

#include "class-10.h"

/**
 * Default constructor for class-10
 */
TextBuffer::TextBuffer(size_t s){
	capacity_ = s;
	size_ = 0;  //an empty buf_ is of size 0
	buf_ = new char[s]; //allocating memory for array buf_ to capacity s
	back_ = s-1;  //back of buffer is one less than capacity
	cursor_ = 0;  //starting position of cursor 
}

/**
 * Copy constructor
 */
TextBuffer::TextBuffer(TextBuffer& tb){
	capacity_ = tb.capacity_;
	size_ = tb.size_;
	cursor_ = tb.cursor_;
	back_ = tb.back_;
	buf_ = new char[capacity_];  //allocating memory again
	std::copy(tb.buf_, tb.buf_+size_, buf_); //copies everything to the new buf_
	
}

/**
 * Destructor
 * Seriously, destroys stuff.
 */
TextBuffer::~TextBuffer(){
	delete [] buf_;  // dealocates dynamically allocated buf_
}

/**
 * Swaps the values of two TextBuffers
 */
void TextBuffer::swap(TextBuffer& tb){  // swaps everything in this and tb
	std::swap(capacity_, tb.capacity_);
	std::swap(size_, tb.size_);
	std::swap(cursor_, tb.cursor_);
	std::swap(back_, tb.back_);
	std::swap(buf_, tb.buf_);
}

/**
 * Assignment operator
 * Copy and swap? 
 */
TextBuffer& TextBuffer::operator=(TextBuffer tb){
	swap(tb);  //calling swap on tb
	return *this;
}

/**
 * Doubles size of buf_, does copy, deletes old memory
 */
void TextBuffer::grow(){
	capacity_ *= 2;  // double capacity
	char* new_buf_ = new char[capacity_];  // allocate temp buf, new_buf_ 
	size_t back_of_gap = capacity_-back_;
	size_t back_1 = back_+1;
	
	std::copy(buf_, buf_+cursor_, new_buf_);  //copy for left of gap
	std::copy(buf_+back_1, buf_+capacity_, new_buf_+back_of_gap);  // copy for right of gap
	
	back_ = back_of_gap - 1;  // update back information
	std::swap(buf_, new_buf_);  // swap pointers
	delete [] new_buf_;  // dealocate temp buffer, new_buf_
	
}

/**
 * Returns true if the is no more gap
 * Returns false if otherwise
 */
bool TextBuffer::isfull(){
	bool result;
	if(back_ - cursor_ == 0)  // if the gap is 0, buf_ is full
		result = true;
	else
		result = false;
	return result;
}

/**
 * Returns true if there are no characters in buf_
 * Returns false if otherwise
 */
bool TextBuffer::isempty(){
	bool result;
	if( size_ == 0 )  // if size_ is equal to 0, then the buf_ is empty
		result = true;
	else
		result = false;
	return result;
}

/**
 * Inserts char c 
 * If buf_ is full, call grow() then insert
 * Otherwise, just insert
 */
void TextBuffer::insert(char c){
	if(isfull() == true){  // if buf_ is full, grow, then insert
		this->grow();
	}
	buf_[cursor_] = c;  // inserting char c at cursor_ in buf_
	cursor_ += 1;  // moving the cursor up one
	size_ += 1;  //increasing size by one
}

/**
 * If cursor_ is all the way to the left, do nothing and return false
 * Otherwise delete and return true
 */
bool TextBuffer::del(){
	bool result;
	if(cursor_ == 0)  // if cursor is all the way to left, set result to false
		result = false; 
	else{
		cursor_ -= 1;  // moving the cursor back one to "delete"
		size_ -= 1;  // also subtract one off size
		result = true;
	}
	return result;
}

/**
 * If cursor_ is all the way to the left, do nothing and return false
 * Otherwise move left and return true
 */
bool TextBuffer::left(){
	bool result;
	if(isempty() == true)  // if buf_ is empty, set result to false
		result = false;
	else if(cursor_ == 0)  // if cursor is all the way to the left, set result to false
		result = false;
	else{
		buf_[back_] = buf_[cursor_-1]; // move characters to right side of gap
		cursor_ -= 1; // move cursor back 1
		back_ -= 1;  // also move back, back 1 to maintain gap
		result = true;
	}
	return result;
}

/**
 * If curosr_ is all the way to the right, do nothing and return false
 * Otherwise move right and return true
 */
bool TextBuffer::right(){
	bool result;
	if(isempty() == true)  // if buf_ is empty, set result to false
		result = false;
	else if(cursor_ == back_) //logic for being all the way to right?
		result = false;
	else{
		buf_[cursor_] = buf_[back_+1]; // move characters back to left side of gap
		cursor_ += 1;  // move cursor up one
		back_ += 1;  // move back up one to maintain gap
		result = true;
	}
	return result;
}

/**
 * Ostream operator, first line prints out tb data, second line prints
 * the contents of the tb, third line prints a visual representation of the 
 * cursor location
 */
ostream& operator<<(ostream& out, TextBuffer &tb){
	out << "sz: " << tb.size_ << ", cap: " << tb.capacity_ << ", cur: " <<
	tb.cursor_ << ", bk: " << tb.back_ << endl;  // prints out first line
	
	for(unsigned int i=0; i<tb.capacity_; i++){  // loop to print out contents of buf_ for second line
		out << tb.buf_[i] << ",";
	}
	out << endl;
	//std::copy to print out third line
	std::copy(tb.buf_, tb.buf_+tb.cursor_, //copy to copy buf left of cursor to out
		ostream_iterator<char>(out));
	out << "|";
	std::copy(tb.buf_+tb.back_+1, tb.buf_+tb.capacity_, //copy to copy buf right of gap to out
		ostream_iterator<char>(out));
	
	out << endl;
	return out;
}


