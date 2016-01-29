#include <iostream>
#include "BST.h"
#include "student.h"
#include "menu.h"
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;



int main(){
 
  //BST<Student> masterStud;
  //Student Brent(123, 444, "Brent", "Sophomore", "Computer Science", 3.7);
  //Student Bob(113, 444, "Bob", "Sophomore", "Computer Science", 3.7);
  //Student Jack(154, 444, "Jack", "Sophomore", "Computer Science", 3.7);

  //Student Bro(113, 0, "", "", "", 0.0);

  //if (Brent > Bob){
  //  cout << "True" << endl;
  //}
  //else{
  //  cout << "False" << endl;
  //}

  //masterStud.add(Brent);
  //masterStud.add(Bob);
  //masterStud.add(Jack);

  //cout << masterStud.contains(Bob) << endl;
  //cout << masterStud.contains(Bro) << endl;
  //masterStud.deleter(Bro);
  //cout << masterStud.contains(Bob) << endl;

  //cout << masterStud.getSize() << endl;

  //masterStud.print();
  Menu mainMenu;
  mainMenu.displayMenu();

  getchar();
}

