#ifndef MENU_H
#define MENU_H

#include <string>
#include "BST.h"
#include "student.h"
#include "faculty.h"
using namespace std;

class Menu{
public:
  int displayMenu();
  BST<Student> MasterStudent;
  BST<Faculty> MasterFaculty;
private:
  int input;
  void printStudents();
  void addStudent();
  void deleteStudent(int u_sid);
  void displayStudent();
  void printAllFaculty();
  void addFacultyMember();
  void deleteFacultyMember();
  void displayFacultyMember();
  void displayAdvisorOfStud();
  void displayStudentsOfFac();
  void changeStudentAdvisor(int u_sid, int u_aid);
  void removeStudentFromAdvisor(int u_aid, int u_sid);
  void saveBSTStud();
  void saveBSTFac();
  void saveBSTFacHelper(TreeNode<Faculty>* n, int count);
  void loadBSTFac();
  void loadBSTStud();

};

#endif