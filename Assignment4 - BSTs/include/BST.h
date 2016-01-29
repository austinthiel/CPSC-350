#ifndef BST_H
#define BST_H


#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

template <typename T>
class TreeNode{
public:

  TreeNode(T d){
    data = d;
    left = right = 0;
  }
  virtual ~TreeNode(){
    //hmmm?
  }

  TreeNode<T>* left;
  TreeNode<T>* right;
  T data;

};


template<typename T>
class BST{
public:
  BST(){
    size = 0;
    root = 0;
  }
  virtual ~BST(){
    //hmmmmmm?
  }
  int getSize(){
    return size;
  }
  bool isEmpty(){
    return(size == 0);
  }
  bool contains(T d);
  bool deleter(T k);
  void add(T d);
  void recadd(T d);
  void remove(T d);
  void print();
  void printHelper(TreeNode<T>* n);
  void addElement(T d);
  void printIfContains(T d);
  T returnIfContains(T d);
  T getMin();
  T getMax();
  TreeNode<T>* getNodeIfConstains(T d);
  TreeNode<T>* getSuccessor(TreeNode<T>* d);
  TreeNode<T>* getRoot();

private:
  void recAddHelper(T d, TreeNode<T>* &p);
  TreeNode<T>* root;
  int size;
};

template<typename T>
TreeNode<T>* BST<T>::getRoot(){
  return root;
}

template <typename T>
bool BST<T>::deleter(T k){   //we prepare for battle
  if (root == NULL) return false;  //like we’re ever this lucky

  TreeNode<T>* current = root;
  TreeNode<T>* parent = root;
  bool isLeft = true;

  while (!(current->data == k)){ //usual code to find the node       
    parent = current;
    if (k < current->data){  //need to go left

      isLeft = true;
      current = current->left;
    }
    else{ //need to go right

      isLeft = false;
      current = current->right;
    }
    if (current == NULL)  //the thing isn’t in the tree             
      return false;
  }


  //no children – this would be nice
  if (current->left == NULL && current->right == NULL){

    if (current == root)             // deleting root
      root = NULL;
    else if (isLeft)
      parent->left = NULL;     // disconnect from parent
    else
      parent->right = NULL;

    --size;
  }

  //one child – still not too bad
  // no right child, replace with left subtree
  else if (current->right == NULL){
    if (current == root)  //always have to check for root
      root = current->left;
    else if (isLeft)
      parent->left = current->left;
    else
      parent->right = current->left;
    --size;
  }
  // no left child, replace with right subtree
  else if (current->left == NULL){
    if (current == root)
      root = current->right;
    else if (isLeft)
      parent->left = current->right;
    else
      parent->right = current->right;
    --size;
  }
  else{  // two children – things are about to get scary

    // find successor of node to delete (current)
    TreeNode<T>* successor = getSuccessor(current);

    // connect parent of current to successor
    if (current == root)  //usual root check
      root = successor;
    else if (isLeft)
      parent->left = successor;
    else
      parent->right = successor;

    // connect successor to current's left child
    successor->left = current->left;
    --size;
  }
  return true;
}

//At this point we begin to cry and take a 4 hour nap.


template <typename T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* d){ //d to be deleted

  TreeNode<T>* sp = d;  //successor’s parent
  TreeNode<T>* successor = d;
  TreeNode<T>* current = d->right;   // go to right first
  while (current != NULL){

    sp = successor;
    successor = current;
    current = current->left;      // go to left
  }

  if (successor != d->right){  // descendant of right child

    sp->left = successor->right;
    successor->right = d->right;
  }
  return successor;
}


template <typename T>
void BST<T>::print(){
  printHelper(root);
}

template <typename T>
void BST<T>::printHelper(TreeNode<T>* n){
  //null check
  if (n == NULL){

  }
  else{
    if (n->left != NULL){ // move 2nd if statement here, remove the rest
      printHelper(n->left);
    }
    if (n != NULL){
      std::cout << n->data << endl;
    }
    if (n->right != NULL){
      printHelper(n->right);
    }
  }
  
  //null check
}

template <typename T>
void BST<T>::recadd(T d){
  recAddHelper(d, root);
}

template <typename T>
void BST<T>::recAddHelper(T d, TreeNode<T>* &p){
  if (p == 0){
    p = new TreeNode<T>(d);
  }
  else if (d > p->data){
    recAddHelper(d, p->right);
  }
  else{
    recAddHelper(d, p->left);
  }
}

template <typename T>
void BST<T>::add(T d){
  TreeNode<T>* newNode = new TreeNode<T>(d);
  bool isrightchild = false;
  if (root == 0){
    root = newNode;
    ++size;
    cout << "root added" << endl;
  }
  else{
    TreeNode<T>* curr = root;
    TreeNode<T>* parent = root;
    while (curr != 0){
      parent = curr;
      if (newNode->data > curr->data){
        curr = curr->right;
        isrightchild = true;
      }
      else{
        curr = curr->left;
        isrightchild = false;
      }
    }
    if (isrightchild){
      parent->right = newNode;
      cout << "right added" << endl;
      ++size;
    }
    else{
      parent->left = newNode;
      cout << "left added" << endl;
      ++size;
    }
  }
}

template <typename T>
bool BST<T>::contains(T d){
  bool ret = false;

  TreeNode<T>* curr = root;

  while (curr != 0){
    if (d > curr->data){
      curr = curr->right;
    }
    else if (d < curr->data){
      curr = curr->left;
    }
    else{
      ret = true;
      break;
    }
  }
  return ret;
}


template <typename T>
void BST<T>::printIfContains(T d){
  TreeNode<T>* curr = root;
  bool doesexist = false;

  while (curr != 0){
    if (d > curr->data){
      curr = curr->right;
    }
    else if (d < curr->data){
      curr = curr->left;
    }
    else{
      cout << curr->data;
      doesexist = true;
      break;
    }
  }
  if (!doesexist){
    cout << "\nObject does not exist\n" << endl;
  }
}

template <typename T>
T BST<T>::returnIfContains(T d){
  TreeNode<T>* curr = root;

  while (curr != 0){
    if (d > curr->data){
      curr = curr->right;
    }
    else if (d < curr->data){
      curr = curr->left;
    }
    else{
      return curr->data;
    }
  }

  cout << "\nObject does not exist\n" << endl;
  return 0;
}

template <typename T>
TreeNode<T>* BST<T>::getNodeIfConstains(T d){
  TreeNode<T>* curr = root;

  while (curr != 0){
    if (d > curr->data){
      curr = curr->right;
    }
    else if (d < curr->data){
      curr = curr->left;
    }
    else{
      return curr;
    }
  }

  cout << "\nObject does not exist\n" << endl;
  return 0;
}


template <typename T>
T BST<T>::getMin(){
  TreeNode<T>* curr = root;
  while (curr->left != 0){
    curr = curr->left;
  }
  return curr->data;
}

template <typename T>
T BST<T>::getMax(){
  TreeNode<T>* curr = root;
  while (curr->right != 0){
    curr = curr->right;
  }
  return curr->data;
}

#endif 
