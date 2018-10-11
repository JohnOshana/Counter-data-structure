/*counter.h*/

//
// John Oshana
// U. of Illinois, Chicago
// CS 341, Fall 2018
// Project #03: Counter container
//
// The Counter container is a set with no duplicates.  However, it keeps
// a count of how many times an element was inserted, hence the name
// "Counter".  Users of the Counter container can test for set membership,
// as well as obtain an element's count.
// 
// Example:  suppose C is a Counter, and you insert the elements 3, 11, 
// 5, 11, 3, and 11.  Then C contains the elements {3, 5, 11}, where 3's 
// count is 2, 5's count is 1, and 11's count is 3.
//
// Given N elements, search operations are O(lgN), and insert is O(N); these
// are average-time complexities.  In terms of space, the container will 
// consume at most 4N space.
// 

#pragma once

#include <iostream>
#include <iterator>

using std::cout;  // for debug printing:
using std::endl;


template<typename T>
class Counter
{
private:
  
  class Node{
  public:
     
     T element;
     int counter;
     
     Node()
     :counter{0}
     {}
     
     ~Node(){
     }
      
  };
  
  
  class iterator
  {
    public:
    
        Node* current;
        int index;
        int size;
        
        iterator(Node* cnode, int _size){
        current = cnode;
        index = 0;
        size = _size;
        }
        
        iterator& operator++(){
            index++;
            
            if(!(index < size) && !(size < index))
                return *this;
            else
             return *this;
        }
        
        const T& operator*(){
            return current[index].element;
        }
        
        bool operator!=(const iterator& rhs){
             return false;
        }
  };

//Counter
private:
  Node *arr;
  int arrSize,capacity;
  

public:
  //
  // constructor:
  //
  Counter()
  {
    arrSize = 0;
    capacity = 4;
    arr = new Node[capacity];
  }
  
  
  //
  // copy constructor:
  //
  Counter(const Counter& other)
  {
    arr = new Node[other.capacity];
    arrSize = other.arrSize;
    capacity = other.capacity;
   
    
    for(int i = 0; i < other.arrSize; i++){
        arr[i].element = other.arr[i].element;
        arr[i].counter = other.arr[i].counter;
        }
  }
  
  
  //
  // destructor:
  // 
  ~Counter()
  { 
    delete[] arr;
  }

  //
  //Expand array function
  //
  void expand(){
  
  capacity *= 2;
  
  Node *tempArr = new Node[capacity];
  
  for(int i = 0; i < arrSize; i++){
      tempArr[i].element = arr[i].element;
      tempArr[i].counter = arr[i].counter;
  }
  delete[] arr;
  arr = tempArr;
  
  
  }
  
  //
  //Binary search to find element in logn time
  //
  int binarySearch(Node arr[], int l, int r, const T& e) const{
      if (r >= l) 
   { 
        int mid = l + (r - l)/2; 
  
        // If the element is at the mid
        if (!(arr[mid].element < e) && !(e<arr[mid].element))   
            return mid; 
  
        // If element is smaller than mid, then its on the left
        if ( e < arr[mid].element)  
            return binarySearch(arr, l, mid-1, e); 
  
        // Else element is in the right
        return binarySearch(arr, mid+1, r, e); 
   } 
  
   // If it was not found
   return -1; 
  }

  //
  // size()
  // 
  // Returns the # of elements in the set.
  // 
  // Time complexity: O(1).
  // 
  int size() const
  {
    return arrSize;
  }
  
  
  //
  // empty()
  //
  // Returns true if the set is empty, false if not.
  // 
  // Time complexity: O(1).
  // 
  bool empty() const
  {
    if(arrSize == 0)
        return true;
    else
    return false;
  }
  
  //
  // clear()
  //
  // Empties the set, deleting all elements and counts.
  //
  void clear()
  {
    Node *tempArr = new Node[capacity];
    
    delete[] arr;
    
    arr = tempArr;
    arrSize=0;
    
  }
  
  
  //
  // [e]
  //
  // Returns true if set contains e, false if not.
  //
  // NOTE: since the type of e is unknown, elements are compared using <. 
  // This implies 2 elements x and y are equal if (!(x<y)) && (!(y<x)).
  // 
  // Time complexity: average-case O(lgN).
  //
  bool operator[](const T& e)
  {
    int check = binarySearch(arr, 0, arrSize-1, e);
        if(check != -1)
            return true;
            else
    return false;
  }


  //
  // (e)
  // 
  // Returns a count of how many times e has been inserted into the set;
  // the count will be 0 if e has never been inserted.
  // 
  // NOTE: since the type of e is unknown, elements are compared using <. 
  // This implies 2 elements x and y are equal if (!(x<y)) && (!(y<x)).
  // 
  // Time complexity: average-case O(lgN).
  // 
  int operator()(const T& e) const
  {
   int check = binarySearch(arr, 0, arrSize-1, e);
    if(check == -1)
        return 0;
        else
    return arr[check].counter;
  }
  
  
  //
  // insert(e)
  // 
  // If e is not a member of the set, e is inserted and e's count set to 0.
  // If e is already in the set, it is *not* inserted again; instead, e's
  // count is increased by 1.  Sets are unbounded in size, and elements are
  // inserted in order as defined by T's < operator; this enables in-order 
  // iteration.
  // 
  // NOTE: since the type of e is unknown, elements are compared using <. 
  // This implies 2 elements x and y are equal if (!(x<y)) && (!(y<x)).
  // 
  // Time complexity: worst-case O(N).
  // Space complexity: 4N.
  //
  void insert(const T& e)
  {
  //Binary search check
  
  int check = binarySearch(arr, 0, arrSize-1, e);
  if(check!= -1)
      arr[check].counter++;
      
  if(check == -1){
  
  //check to see if array is full
  if(arrSize >= capacity)
      this->expand();
  
    int i; 
    for (i = arrSize-1; ( i >= 0  && e < arr[i].element); i--) {
       arr[i+1].element = arr[i].element; 
       arr[i+1].counter = arr[i].counter;
      }
    arr[i+1].element = e; 
    arr[i+1].counter = 0;
    arr[i+1].counter++;
    arrSize++;
    }
  }
  
  
  // 
  // += e
  //
  // Inserts e into the set; see insert.
  //
  // Time complexity: worst-case O(N).
  // Space complexity: 4N.
  // 
  Counter& operator+=(const T& e)
  {
    //
    // insert e into "this" set:
    //
    this->insert(e);

    // return "this" updated set:
    return *this;
  }
  
  
  //
  // lhs = rhs;
  //
  // Makes a deep copy of rhs (right-hand-side) and assigns into
  // lhs (left-hand-side).  Any existing elements in the lhs
  // are destroyed *before* the deep copy is made.
  // 
  // NOTE: the lhs is "this" object.
  //
  Counter& operator=(const Counter& rhs)
  {
    //
    // NOTE: where is the lhs in the function call?  The lhs operand is 
    // hidden --- it's "this" object.  So think this->operator=(rhs).  
    //

    // check for self-assignment:
    if (this == &rhs)  // S = S;
      return *this;
    
    
    //
    // TODO
    //
    while(this->capacity < rhs.capacity)
		this->expand();
		
    this->arrSize = rhs.arrSize;
    //this->capacity = rhs.capacity;
    
    for(int i = 0; i < rhs.arrSize; i++){
        this->arr[i].element = rhs.arr[i].element;
        this->arr[i].counter = rhs.arr[i].counter;
        }
    //
    // return "this" updated set:
    //
    return *this;
  }
  

  //
  // begin()
  // 
  // Returns an iterator denoting the first element of the set.  If the 
  // set is empty, begin() == end().  The iterator will advance through
  // the elements in order, as defined by T's < operator.
  //
  iterator begin()
  {
      //int afterIndex = arrSize+1;
      //Node* afterEnd = arr[afterIndex];
     // if(!(arrSize < 0) && !(0 < arrSize))
      //    return iterator(afterEnd);
     // else    
    return iterator(arr, arrSize);
  }
  
  
  //
  // end()
  // 
  // Returns an iterator denoting the end of the iteration space --- i.e.
  // one past the last element of the set.  If the set is empty, then
  // begin() == end().
  // 
  iterator end()
  {
     int afterIndex = arrSize+1;
     Node* afterEnd = &arr[afterIndex];
      
    return iterator(afterEnd, arrSize);
  }

};
