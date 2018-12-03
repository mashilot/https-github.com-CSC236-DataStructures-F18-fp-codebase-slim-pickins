// Final Project
/*-------------------------------------------------------------------------------
# Name:        Binary number addition
# Purpose:  The purpose of this project is to display a C++ object oriented representation 
# of a linked list by adding twwo binary numbers using a linked list
#
# Author:      Assignment concept: pearcej, converted to Python by nakazawam
#              and then back to C++ by nakazawam
#			Note: This program uses two bianary numbers in a linked list and adds them to give a total binary number.
#			Team Slim Pickin's
#			Expanded by Giorgi Lomia, Siso Mashilo, Yohannes Amsalu
#       
#
# Created:     21/09/2014	Modified 02/12/2018
#------------------------------------------------------------------------------*/
#include <stdlib.h>	// this library contains NULL
#include <assert.h>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
class Bit {

private:
	bool bitValue;
	Bit* nextBit;

public:
	Bit(bool value = false, Bit*next = NULL) {
		//constructor creates a new bit that is by default
		//false (i.e. 0) and references None'''
		bitValue = value;
		nextBit = next;
	}

	Bit* get_next_bit() {
		//accessor method that returns the next bit this one
		//is referencing. If this bit is the last one, it returns
		//NULL, of course
		return nextBit;
	}

	bool get_bit() {
		//accessor method that returns the values of this bit.
		return bitValue;
	}

	void set_bit(bool newValue) {
		//manipulator method to set the bit to whatever is input.
		//post: the bit value for this object is set to input parameter value.'''
		bitValue = newValue;
	}

	void add_next_bit(bool initValue) {
		// manipulator method that inserts a Bit object after this one with
		//the value that is the input parameter.
		//post: this Bit will reference the new one created, and the new one
		//    will have the value that is input into this function. '''
		nextBit = new Bit(initValue);
	}

	void clear_next_bit() {
		//Removes the reference to the next bit so that Python's garbage
		//collection will take care of this dereferenced object'''
		nextBit = NULL;
	}

	string to_string() {
		//returns a string representation of this bit for printing purposes.
		// The convention is that False --> "0" and True --> "1"'''
		if (bitValue)
			return "1";
		return "0";
	}
};


class BinaryNumber {

private:
	Bit* leastSignificantBit;   // in C++, we need to declare these variables
	int numBits;
	//------------------------------------------------------------

public:
	BinaryNumber() {
		// Initialize this binary number is empty  with no bits in it.'''
		leastSignificantBit = NULL;
		numBits = 0;
	}

	int __len__() {
		//post: returns number of items in the list
		return numBits;
	}

	Bit* get_least_significant_bit() {
		return leastSignificantBit;
	}

	int get_num_bits() {
		return numBits;
	}
	void incr_num_bits() {
		numBits++;
	}
	void make_start(Bit* start) {
		leastSignificantBit = start;
		return;
	}

	void convert_decimal_to_binary(int decimal) {
		//pre: The decimal input >= 0, leastSignificantBit = None
		//If there IS a number in this object already, it will be clobbered.
		//post: leastSignificantBit will point to the first link
		//of a linked list representing the "decimal" number in reverse
		//order (least to most significant bit)

		if (decimal < 0)
			return;

		// Now use an algorithm to convert a decimal number to binary.
		// Repeatedly divide the number by 2 and keep the remainder.
		// It will build the binary number this way.

		// Start the process with the first binary number.
		if (decimal % 2 == 1) {
			leastSignificantBit = new Bit(true);
		}
		else {
			leastSignificantBit = new Bit(false);
		}
		numBits += 1;

		// Now loop through the decimal and convert to binary.
		Bit* bitRef = leastSignificantBit;
		int remainder = 0;
		int quotient = decimal / 2;

		while (quotient > 0) {
			remainder = quotient % 2;
			quotient = quotient / 2;

			bitRef->add_next_bit(remainder == 1);
			bitRef = bitRef->get_next_bit();	// Advance the reference
			numBits += 1;
		}
	}

	string to_string() {
		// returns the string representation of this binary number.
		//post: The string representation of this BinaryNumber will be returned.
		//    if there is no linked list, a blank string, "" is returned
		Bit* bitRef = leastSignificantBit;
		string output = "";

		if (bitRef == NULL) {
			return output;
		}

		for (int i = 0; i < numBits; i++) {
			output = bitRef->to_string() + output;
			bitRef = bitRef->get_next_bit();
		}
		return output;
	}

	void remove_all() {
		//pre: none
		//post: All the links in the linked list started by leastSignificantBit
		//	will be de-allocated.'''

		if (leastSignificantBit == NULL) {
			return;
		}

		Bit* trailingBit = leastSignificantBit;
		Bit* leadingBit = trailingBit->get_next_bit();

		for (int i = 0; i < numBits - 1; i++) {
			trailingBit->clear_next_bit();
			delete trailingBit; // this operation explicitly deallocates
			trailingBit = leadingBit;
			leadingBit = leadingBit->get_next_bit();
		}

		leastSignificantBit = NULL;
		numBits = 0;
	}
	/*
	# You are to implement this function that will increment the binary
	# number stored in a linked list by one, making sure to propogate any
	# carries that are generated.
	# For example, if the number 15 is stored as "1111" and this
	# function is called,the result would be "10000" (really
	# represented as 0->0->0->0->1, where the carry "rippled" up the
	# bits, and an additional bit was added at the end because the 4th
	# 1 really became a "10"
	*/
	void increment() {
		//handles empty string
		if (leastSignificantBit == NULL) {
			return;
		}
		Bit* lastBit = leastSignificantBit;
		bool carry = 1;
		int i = 0;
		// the loop to go through all of the other elements
		while (i < numBits - 1) {
			//if the next element is 1 and we carry a 1 from previous addition
			if (lastBit->get_bit() == 1 && carry == 1) {
				lastBit->set_bit(0);			// make our current bit 0
				carry = 1;
			}
			// if the next element is 0 and we carry 1 from our previous addition 
			else if (lastBit->get_bit() == 0 && carry == 1) {
				lastBit->set_bit(1);			// make our current bit a 1
				carry = 0;						//reset our carry to 0
			}
			lastBit = lastBit->get_next_bit();	//go to the next one
			i++;
		}
		// if we carry 1 until the highest significance element
		if (lastBit->get_next_bit() == NULL && carry == 1) {
			lastBit->set_bit(0);
			lastBit->add_next_bit(1);		//add a node with 1
			numBits += 1;					//increase the size of the list
			carry = 0;						//make carry 0
		}


	}
	BinaryNumber add(BinaryNumber number) {
		/*This is an addition method that adds two binary number lists together and returns a binary list.
		*/
		//////////////DONOT TOUCH!!!!!!///////////////////////
		BinaryNumber final_answer;	//linked list we are building
		Bit* answer=new Bit(0);	//initial pointer
		Bit* potr = answer;//pointer to keep track of where our beggining is
		Bit* added_ptr = leastSignificantBit;//first number pointer
		Bit* adder_ptr = number.get_least_significant_bit();//second number pointer

		int size_of = max(numBits, number.get_num_bits());//the size of the biggest number
		int min_size = min(numBits, number.get_num_bits());//the size of the biggest number
		bool carry = 0;//initialize carry 
		//////////////DONOT TOUCH!!!!!!///////////////////////
		int i = 0;
		//While the smallest number has not run out
		while (i<(min_size)) {
			//if 1+1+1
			if (added_ptr->get_bit() == 1 && adder_ptr->get_bit() == 1 && carry==1) {
				answer->add_next_bit(1); //add 1 node
				carry = 1;	//make carry 1
			}
			//if 1+1+0
			else if (added_ptr->get_bit() == 1 && adder_ptr->get_bit() == 1 && carry == 0) {
				answer->add_next_bit(0);//add 0 node
				carry = 1;  //make carry 1

			}
			//if 0+1+0 or 1+0+0
			else if (((added_ptr->get_bit() == 0 && adder_ptr->get_bit() == 1)|| (added_ptr->get_bit() == 1 && adder_ptr->get_bit() == 0))&& carry == 0) {
				answer->add_next_bit(1); //add 1 node
				carry = 0;//make carry 0
			}
			//if 0+1+1 or 1+0+1
			else if (((added_ptr->get_bit() == 0 && adder_ptr->get_bit() == 1) || (added_ptr->get_bit() == 1 && adder_ptr->get_bit() == 0)) && carry == 1) {
				answer->add_next_bit(0);//add 0 node
				carry = 1;  //make carry 1

			}
			//if 0+0+1
			else if (added_ptr->get_bit() == 0 && adder_ptr->get_bit() == 0 && carry == 1) {
				answer->add_next_bit(1); //add 1 node
				carry = 0;//make carry 0
			}
			//if 0+0+0
			else if (added_ptr->get_bit() == 0 && adder_ptr->get_bit() == 0 && carry == 0) {
				answer->add_next_bit(0);//add 0 node
				carry = 0;//make carry 0

			}
			added_ptr = added_ptr->get_next_bit();//move a pointer for added
			adder_ptr = adder_ptr->get_next_bit();//move a pointer for adder
			answer = answer->get_next_bit();//move on to the next node
			final_answer.incr_num_bits();//increase the number of bits by 1
			i++;
		}

		int j = 0;
		//once we run out of the smallest number
		while(j<(size_of-min_size)){
			//we figure out which one is bigger
			if (numBits > number.get_num_bits()) {
				//if 1+1
				if (added_ptr->get_bit() == 1 && carry == 1) {
					answer->add_next_bit(0);//add 0 node
					carry = 1;//make carry 1
				}
				//if 0+1
				else if (added_ptr->get_bit() == 0 && carry==1) {
					answer->add_next_bit(1);//add 1 node
					carry = 0;//make carry 0
				}
				//if we do not carry anything
				else if (carry == 0) {
					answer->add_next_bit(added_ptr->get_bit());//add the whatever node we have to answer
					carry = 0;//make carry 0
				}
				added_ptr = added_ptr->get_next_bit();//move forward
			}//same thing but for the other number.
			else if (numBits < number.get_num_bits()) {
				if (adder_ptr->get_bit() == 1 && carry == 1) {
					answer->add_next_bit(0);//add 0 node
					carry = 1;//make carry 1
				}
				else if (adder_ptr->get_bit() == 0 && carry == 1) {
					answer->add_next_bit(1);//add 1 node
					carry = 0;//make carry 0
				}
				else if (carry == 0) {
					answer->add_next_bit(adder_ptr->get_bit());//add the whatever node we have to answer
					carry = 0;//make carry 0
				}
				adder_ptr = adder_ptr->get_next_bit();	//move forward
			}
			answer = answer->get_next_bit();//move forward
			final_answer.incr_num_bits();//increase numbits by 1
			j++;
		}
		//if after we are done going through all the numbers and our carry is still 1 we add another node.
		if (carry == 1) {
			answer->add_next_bit(1);
			answer = answer->get_next_bit();
			final_answer.incr_num_bits();
			carry = 0;
		}
		//////////////DONOT TOUCH!!!!!!///////////////////////
		potr = potr->get_next_bit(); //establish correct positioning to the correct node	
		final_answer.make_start(potr);//this becomes our new head
		return final_answer;//return the final answer
		//////////////DONOT TOUCH!!!!!!///////////////////////
	}
};

int main() {

	char slowexit;

	BinaryNumber added = BinaryNumber();	//initialize first number 
	BinaryNumber adder = BinaryNumber();	//initialize second number
	cout << "instantiation of testing list.\n" << endl;

	added.convert_decimal_to_binary(10);	//convert number to binary
	adder.convert_decimal_to_binary(20);	//convert number to binary
	cout  << "Adding  " << adder.to_string() << "  To  " << added.to_string()<< endl;

	cout << endl;
	BinaryNumber ans = added.add(adder);	//perform addition
	cout << "After addition: " << ans.to_string()<<endl;
	cin >> slowexit; //to keep window open in some cases

	return 0;
}

