#ifndef DLIST_H
#define DLIST_H

// ListNode class Constructor, Functions, and Destructor
template <typename T>
class ListNode{
public:
  ListNode(T d);
  virtual ~ListNode(){}
  T data;
  ListNode<T> *next;
  ListNode<T> *prev;
};

template <typename T>
ListNode<T>::ListNode(T d){
  data = d;
  next = 0;
  prev = 0;
}

// DList class Constructor, Functions, and Destructor
template <typename T>
class DList{
public:
  DList();
  bool isEmpty();
  bool contains(T d);
  void addFront(T d);
  T deleteFront();
  ListNode<T>* getFront();
  T getFrontData();
  void addBack(T d);
  T deleteBack();
  ListNode<T>* getBack();
  T getBackData();
  T deletePos(int p);
  void deletePosIfExists(T d);
  T getPos(int p);
  T& getPosRef(int p);
  std::string toString();
  int getSize(){
    return size;
  }
  virtual ~DList(){}
  int size;
//private:
  ListNode<T> *front;
  ListNode<T> *back;
  
};


template <typename T>
DList<T>::DList(){
  size = 0;
  front = 0;
  back = 0;
}

template <typename T>
bool DList<T>::isEmpty(){
  return (size == 0);
}

template <typename T>
bool DList<T>::contains(T d){
  bool found = false;

  ListNode<T> *current = front;
  while (current != 0 && !found){
    if (current->data == d){
      found = true;
    }
    current = current->next;
  }
  return found;
}

template <typename T>
void DList<T>::deletePosIfExists(T d){
  bool found = false;
  int count = 0;

  ListNode<T> *current = front;
  while (current != 0 && !found){
    if (current->data == d){
      found = true;
      if (count == 0){
        deleteFront();
      }
      else if ((count +1) == size){
        deleteBack();
      }
      else{
        deletePos(count);
      }
    }
    current = current->next;
    count += 1;
  }
}

template <typename T>
void DList<T>::addFront(T d){
  ListNode<T> *newNode = new ListNode<T>(d);
  if (isEmpty()){
    back = newNode;
  }
  else{
    front->prev = newNode;
  }
  newNode->next = front;
  front = newNode;
  ++size;
}

template <typename T>
T DList<T>::deleteFront(){
  ListNode<T> *ret = front;
  if (front->next == 0){
    back = 0;
  }
  else{
    front->next->prev = 0;
  }
  front = front->next;
  --size;

  T datum = ret->data;
  delete ret;
  return datum;
}

template <typename T>
ListNode<T>* DList<T>::getFront(){
  return front;

  //throw exception for empty list
}

template <typename T>
T DList<T>::getFrontData(){
  return front->data;

  //throw exception for empty list
}

template <typename T>
void DList<T>::addBack(T d){
  ListNode<T> *newNode = new ListNode<T>(d);
  if (isEmpty()){
    front = newNode;
  }
  else{
    back->next = newNode;
  }
  newNode->prev = back;
  back = newNode;
  ++size;
}

template <typename T>
T DList<T>::deleteBack(){
  ListNode<T> *ret = back;
  if (back->prev == 0){
    front = 0;
  }
  else{
    back->prev->next = 0;
  }
  back = back->prev;
  --size;

  T datum = ret->data;
  delete ret;
  return datum;
}

template <typename T>
ListNode<T>* DList<T>::getBack(){
  return back->data;

  //exception for empty list
}

template <typename T>
T DList<T>::getBackData(){
  return back->data;

  //exception for empty list
}

template <typename T>
T DList<T>::getPos(int p)
{
  int count = 0;

  ListNode<T>* current = front;
  while (count != p && current != 0)
  {
    // what if p is out of bounds
    current = current->next;
    ++count;
  }
  return current->data;
}

template <typename T>
T& DList<T>::getPosRef(int p){
  int count = 0;

  ListNode<T>* current = front;
  while (count != p && current != 0)
  {
    // what if p is out of bounds
    current = current->next;
    ++count;
  }
  return current->data;
}


template <typename T>
T DList<T>::deletePos(int p)
{
  int count = 0;

  ListNode<T>* current = front;
  while (count != p && current != 0)
  {
    // what if p is out of bounds
    current = current->next;
    ++count;
  }

  current->next->prev = current->prev;
  current->prev->next = current->next;
  current->next = 0;
  current->prev = 0;

  --size;
  T datum = current->data;
  delete current;
  return datum;
}

//template <typename T>
//std::string DList<T>::toString(){
//  std::string newstring = "";
//  for (int i = 0; i < getSize(); ++i){
//    newstring += stoi(getPos(i));
//  }
//  return newstring;
//}

template <typename T>
inline std::ostream&  operator<<(std::ostream& os, DList<T> other){
  ListNode<T>* curr = other.front;

  
  for (int i = 0; i < other.size; ++i){
    os << curr->data << " | ";
    if (curr->next != NULL){
      curr = curr->next;
    }
  }
  return os;
}


#endif