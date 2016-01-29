#include "menu.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "student.h"
#include "faculty.h"

using namespace std;

int Menu::displayMenu(){

  while (true){
    cout << "1. Print all students and their information (sorted by ascending id #)\n";
    cout << "2. Print all faculty and their information (sorted by ascending id #)\n";
    cout << "3. Find and display student information given the student id\n";
    cout << "4. Find and display faculty information given the faculty id\n";
    cout << "5. Given a student's id, print the name and info of their faculty advisor\n";
    cout << "6. Given a faculty id, print ALL the names and info of his/her advisees.\n";
    cout << "7. Add a new student\n";
    cout << "8. Delete a student given the id\n";
    cout << "9. Add a new faculty member\n";
    cout << "10. Delete a faculty member given the id\n";
    cout << "11. Change a student's advisor given the student id and the new faculty id\n";
    cout << "12. Remove an advisee from a faculty member given the ids\n";
    cout << "13. Rollback\n";
    cout << "14. Exit\n\n";

    int count = 0;

    cin >> input;
    //Code that checks for correct input
    count = 0;
    while (!cin)
    {
      if (count == 0){
        cout << "That was not an integer! Please enter an integer: ";
      }
      cin.clear();
      cin.ignore();
      cin >> input;
      count++;
    }
    cin.ignore();

    bool answergave = false;
   
    //create try catch to catch all bad inputs
    switch (input){
    case 1:
      printStudents();
      break;
    case 2:
      printAllFaculty();
      break;
    case 3:
      displayStudent();
      break;
    case 4:
      displayFacultyMember();
      break;
    case 5:
      displayAdvisorOfStud();
      break;
    case 6:
      displayStudentsOfFac();
      break;
    case 7:
      addStudent();
      break;
    case 8:
      cout << "Give the ID number of the student you wish to delete: ";
      int u_sid;
      cin >> u_sid;

      //Code that checks for correct input
      count = 0;
      while (!cin)
      {
        if (count == 0){
          cout << "That was not an integer! Please enter an integer: ";
        }
        cin.clear();
        cin.ignore();
        cin >> u_sid;
        count++;
      }

      deleteStudent(u_sid);
      break;
    case 9:
      addFacultyMember();
      break;
    case 10:
      deleteFacultyMember();
      break;
    case 11:
      cout << "ID# of student whos advisor you wish to change: ";
      int u_id;
      cin >> u_id;

      //Code that checks for correct input
      count = 0;
      while (!cin)
      {
        if (count == 0){
          cout << "That was not an integer! Please enter an integer: ";
        }
        cin.clear();
        cin.ignore();
        cin >> u_id;
        count++;
      }

      cout << "\nID# of faculty you wish to change the advisor to: ";
      int u_fid;
      cin >> u_fid;
      cout << endl;

      //Code that checks for correct input
      count = 0;
      while (!cin)
      {
        if (count == 0){
          cout << "That was not an integer! Please enter an integer: ";
        }
        cin.clear();
        cin.ignore();
        cin >> u_fid;
        count++;
      }

      changeStudentAdvisor(u_id, u_fid);
      break;
    case 12:
      cout << "\nID# of faculty you wish to remove a student from: ";
      int u_aid;
      cin >> u_aid;
      cout << endl;

      //Code that checks for correct input
      count = 0;
      while (!cin)
      {
        if (count == 0){
          cout << "That was not an integer! Please enter an integer: ";
        }
        cin.clear();
        cin.ignore();
        cin >> u_aid;
        count++;
      }
      
      cout << "ID# of student who you want to remove: ";
      int u_studentid;
      cin >> u_studentid;
      cout << endl;

      //Code that checks for correct input
      count = 0;
      while (!cin)
      {
        if (count == 0){
          cout << "That was not an integer! Please enter an integer: ";
        }
        cin.clear();
        cin.ignore();
        cin >> u_studentid;
        count++;
      }

      while(!answergave){
        
        string answer;
        cout << "\nDo you wish to coninue? (y/n)   Warning. Entering y will delete your student, while n cancels: ";
        cin >> answer;
        cout << endl;
        if (answer == "y"){
          removeStudentFromAdvisor(u_aid, u_studentid);
          answergave = true;
        }
        else if (answer == "n"){
          answergave = true;
        }
        else{
          cout << "\nIncorrect input. Please type either a (y) or an (n).\n" << endl;
        }
      }
      answergave = false;
      break;
    case 13:

    case 14:
      cout << "Exiting...";
      exit(1);
      break;
    default:
      cout << "\nInvalid input. Try again.\n" << endl;
      break;

    }
  }
}

//I was close to getting binary serialization to work but I couldn't get the code to append to the back of a binary file
//instead, everytime i appended it would add to the front and mess up my format order.

/*
//function that saves the studentTable

//function that saves the facultyTable
void Menu::saveBSTFac(){
  ofstream mfaculty;
  mfaculty.open("facultyTable.txt", ofstream::binary);
  mfaculty.close();
  saveBSTFacHelper(MasterFaculty.getRoot(), 0);
}

void Menu::saveBSTFacHelper(TreeNode<Faculty>* n, int count){
  int counter = count;
  int bstsize = MasterFaculty.getSize();
  ofstream mfaculty("facultyTable.txt", ofstream::out | ofstream::binary | ofstream::app);
  if (n == NULL){

  }
  else{
    if (count == 0){
      mfaculty.write(reinterpret_cast<char*>(&bstsize), sizeof(int));
    }
    if (n->left != NULL){
      ++counter;
      saveBSTFacHelper(n->left, counter);
    }
    if (n != NULL){
      int bufferID = n->data.ID;
      string bufferName = n->data.name + "\n";
      string bufferLevel = n->data.level + "\n";
      string bufferDept = n->data.dept + "\n";
      int adviseesize = n->data.advisees.getSize();
      mfaculty.write(reinterpret_cast<const char*>(&bufferID), sizeof(bufferID));
      mfaculty.write(bufferName.c_str(), bufferName.size());
      mfaculty.write(bufferLevel.c_str(), bufferLevel.size());
      mfaculty.write(bufferDept.c_str(), bufferDept.size());
      mfaculty.write(reinterpret_cast<const char*>(&adviseesize), sizeof(adviseesize));
      if (adviseesize > 0){
        for (int i = 0; i < adviseesize; ++i){
          int tempint = n->data.advisees.getPos(i);
          mfaculty.write(reinterpret_cast<char*>(&tempint), sizeof(tempint));
        }
      }
    }
    if (n->right != NULL){
      ++counter;
      saveBSTFacHelper(n->right, counter);
    }
  }
}

//function that checks for studentTable and loads it if it exists
void Menu::loadBSTStud(){
  ifstream mstudent("studentTable.bin");
  if (mstudent){

  }
  else{
    cout << "\nstudentTable does not exist\n" << endl;
  }
}
//function that checks for facultyTable and loads it if it exists
void Menu::loadBSTFac(){
  ifstream mfaculty("facultyTable.txt", ifstream::binary);
  if (mfaculty){
    int numoffac;
    int numofadvisees;
    int tempfacID;
    int tempAdID;
    string tempName = "";
    string tempLevel;
    string tempDep;
    

    mfaculty.read((char *)&numoffac, sizeof(int));
    cout << "num of fac: " << numoffac << endl;
    for (int i = 0; i < numoffac; ++i){
      DList<int> tempAdvisees;
      mfaculty.read((char*)&tempfacID, sizeof(int));
      getline(mfaculty, tempName);
      getline(mfaculty, tempLevel);
      getline(mfaculty, tempDep);
      cout << "here is my tempid: " << tempfacID << endl;
      cout << "here is my tempname: " << tempName << endl;
      cout << "here is my templevel: " << tempLevel << endl;
      cout << "here is my templevel: " << tempDep << endl;
      mfaculty.read((char*)&numofadvisees, sizeof(int));
      cout << "number of advisees: " << numofadvisees << endl;
      if (numofadvisees > 0); {
        for (int x = 0; x < numofadvisees; ++x){
          mfaculty.read((char*)&tempAdID, sizeof(int));
          tempAdvisees.addBack(tempAdID);
        }
        cout << "advisees: " << tempAdvisees << endl;
      }
    }
    
  }
  else{
    cout << "\nfacultyTable does not exist\n" << endl;
  }
}*/

// Case 1
void Menu::printStudents(){
  MasterStudent.print();
}

// Case 2
void Menu::printAllFaculty(){
  MasterFaculty.print();
}

// Case 3
void Menu::displayStudent(){
  cout << "Give the ID number of the student you wish to display: ";
  int u_sid;
  cin >> u_sid;

  //Code that checks for correct input
  int count = 0;
  while (!cin)
  {
    if (count == 0){
      cout << "That was not an integer! Please enter an integer: ";
    }
    cin.clear();
    cin.ignore();
    cin >> u_sid;
    count++;
  }

  Student despStud(u_sid);
  MasterStudent.printIfContains(despStud);

}

// Case 4
void Menu::displayFacultyMember(){
  cout << "ID# of Faculty Member you want to display: ";
  int u_id;
  cin >> u_id; // BREAKS IF NON-INT
  cout << endl; // whitespace

  //Code that checks for correct input
  int count = 0;
  while (!cin)
  {
    if (count == 0){
      cout << "That was not an integer! Please enter an integer: ";
    }
    cin.clear();
    cin.ignore();
    cin >> u_id;
    count++;
  }

  Faculty fac(u_id);

  MasterFaculty.printIfContains(fac);
}

// Case 5
void Menu::displayAdvisorOfStud(){
  cout << "\nGive ID# of a student to see his/or advisor: ";
  int u_id;
  cin >> u_id;
  cout << endl;

  //Code that checks for correct input
  int count = 0;
  while (!cin)
  {
    if (count == 0){
      cout << "That was not an integer! Please enter an integer: ";
    }
    cin.clear();
    cin.ignore();
    cin >> u_id;
    count++;
  }

  Student tempstud(u_id);

  if (MasterStudent.contains(tempstud)){
    TreeNode<Student>* currstudnode = MasterStudent.getNodeIfConstains(tempstud);
    int studentAdvisor = currstudnode->data.advisor;
    Faculty tempfac(studentAdvisor);
    MasterFaculty.printIfContains(tempfac);
  }
  else{
    cout << "\nSorry, that student does not exist.\n" << endl;
  }
}

// Case 6
void Menu::displayStudentsOfFac(){
  cout << "\nGive ID# of a faculty members to see his/or student(s): ";
  int u_id;
  cin >> u_id;

  //Code that checks for correct input
  int count = 0;
  while (!cin)
  {
    if (count == 0){
      cout << "That was not an integer! Please enter an integer: ";
    }
    cin.clear();
    cin.ignore();
    cin >> u_id;
    count++;
  }

  Faculty tempfac(u_id);

  if (MasterFaculty.contains(tempfac)){
    TreeNode<Faculty>* currfacnode = MasterFaculty.getNodeIfConstains(tempfac);
    for (int i = 0; i < currfacnode->data.advisees.size; ++i){
      int studid = currfacnode->data.advisees.getPos(i);
      Student tempstud(studid);
      MasterStudent.printIfContains(tempstud);
      cout << endl;
    }
  }
  else{
    cout << "\nSorry, that faculty member does not exist\n" << endl;
  }
}

// Case 7
void Menu::addStudent(){
  bool advisorexists = false;

  cout << "Student ID: ";
  int u_sid;
  cin >> u_sid;

  //Code that checks for correct input
  int count = 0;
  while (!cin)
  {
    if (count == 0){
      cout << "That was not an integer! Please enter an integer: ";
    }
    cin.clear();
    cin.ignore();
    cin >> u_sid;
    count++;
  }

  cout << "Advisor ID: ";
  int u_aid;
  cin >> u_aid;

  //Code that checks for correct input
  count = 0;
  while (!cin)
  {
    if (count == 0){
      cout << "That was not an integer! Please enter an integer: ";
    }
    cin.clear();
    cin.ignore();
    cin >> u_aid;
    count++;
  }

  cin.ignore(); // to get rid of extra endline

  cout << "Student Name: ";
  string u_name;
  getline(cin, u_name);

  cout << "Student Grade: ";
  string u_grade;
  getline(cin, u_grade);

  cout << "Student Major: ";
  string u_major;
  getline(cin, u_major);

  cout << "student GPA: ";
  double u_gpa;
  cin >> u_gpa;

  Faculty tempfac(u_aid);

  //Code that checks for correct input
  count = 0;
  while (!cin)
  {
    if (count == 0){
      cout << "That was not a float! Please enter an floating point number: ";
    }
    cin.clear();
    cin.ignore();
    cin >> u_gpa;
    count++;
  }

  if (MasterFaculty.contains(tempfac)){
    Student stud(u_sid, u_aid, u_name, u_grade, u_major, u_gpa);
    TreeNode<Faculty>* facnode = MasterFaculty.getNodeIfConstains(tempfac);
    facnode->data.advisees.addBack(u_sid);

    MasterStudent.add(stud);
  }
  else{
    cout << endl << "There was no advisor with that ID, student not added.\n" << endl;
  }
}

// Case 8
void Menu::deleteStudent(int u_sid){

  Student delStud(u_sid);
  if (MasterStudent.contains(delStud)){
    Student studactual = MasterStudent.returnIfContains(delStud);
    Faculty studAdvisor(studactual.advisor);
    TreeNode<Faculty>* advisornode = MasterFaculty.getNodeIfConstains(studAdvisor);
    advisornode->data.advisees.deletePosIfExists(u_sid);
    MasterStudent.deleter(delStud);
    cout << "\nDeletion successful\n" << endl;
  }
  else{
    cout << "\nThat student does not exist in our database.\n" << endl;
  }

}

// Case 9
void Menu::addFacultyMember(){
  cout << "Faculty ID : ";
  int u_id;
  cin >> u_id;

  //Code that checks for correct input
  int count = 0;
  while (!cin)
  {
    if (count == 0){
      cout << "That was not an integer! Please enter an integer: ";
    }
    cin.clear();
    cin.ignore();
    cin >> u_id;
    count++;
  }

  cin.ignore(); // to get rid of extra endline

  cout << "Faculty Name : ";
  string u_name;
  getline(cin, u_name);

  cout << "Faculty Level : ";
  string u_level;
  getline(cin, u_level);

  cout << "Faculty Dept : ";
  string u_dept;
  getline(cin, u_dept);

  Faculty fac(u_id, u_name, u_level, u_dept);

  MasterFaculty.add(fac);

}

// Case 10
void Menu::deleteFacultyMember(){
  bool candelete = true;

  cout << "ID# of Faculty Member you want to delete: ";
  int u_id;
  cin >> u_id;

  //Code that checks for correct input
  int count = 0;
  while (!cin)
  {
    if (count == 0){
      cout << "That was not an integer! Please enter an integer: ";
    }
    cin.clear();
    cin.ignore();
    cin >> u_id;
    count++;
  }

  Faculty fac(u_id);
  if (MasterFaculty.contains(fac)){
    TreeNode<Faculty>* currfacnode = MasterFaculty.getNodeIfConstains(fac);
    if (currfacnode->data.advisees.size != 0){
      if (currfacnode->data == MasterFaculty.getRoot()->data && currfacnode->left != 0){
        int adviseeamount = currfacnode->data.advisees.size;
        for (int i = 0; i < adviseeamount; ++i){
          int stud_id = currfacnode->data.advisees.getPos(0);
          int fac_id = currfacnode->left->data.ID;
          changeStudentAdvisor(stud_id, fac_id);
        }
        cout << "\nDeletion successful\n" << endl;
      }
      else if (currfacnode->data == MasterFaculty.getRoot()->data && currfacnode->right != 0){
        int adviseeamount = currfacnode->data.advisees.size;
        for (int i = 0; i < adviseeamount; ++i){
          int stud_id = currfacnode->data.advisees.getPos(0);
          int fac_id = currfacnode->right->data.ID;
          changeStudentAdvisor(stud_id, fac_id);
        }
        cout << "\nDeletion successful\n" << endl;
      }
      else if (!(currfacnode->data == MasterFaculty.getRoot()->data)){
        int adviseeamount = currfacnode->data.advisees.size;
        for (int i = 0; i < adviseeamount; ++i){
          int stud_id = currfacnode->data.advisees.getPos(0);
          int fac_id = MasterFaculty.getRoot()->data.ID;
          changeStudentAdvisor(stud_id, fac_id);
        }
        cout << "\nDeletion successful\n" << endl;
      }
      else{
        cout << "\nCannot delete faculty member because students must have an advisor.\n" << endl;
        candelete = false;
      }
    }
  }
  if (candelete){
    MasterFaculty.deleter(fac);
  }
  
}

// Case 11
void Menu::changeStudentAdvisor(int u_sid, int u_aid){

  Student tempstud(u_sid);
  Faculty tempfac(u_aid);

  if (MasterStudent.contains(tempstud)){
    if (MasterFaculty.contains(tempfac)){
      TreeNode<Student>* currstud = MasterStudent.getNodeIfConstains(tempstud);
      Faculty oldfac(currstud->data.advisor);
      TreeNode<Faculty>* oldfacnode = MasterFaculty.getNodeIfConstains(oldfac);
      oldfacnode->data.advisees.deletePosIfExists(u_sid);
      TreeNode<Faculty>* newfacnode = MasterFaculty.getNodeIfConstains(tempfac);
      newfacnode->data.advisees.addBack(u_sid);
      currstud->data.advisor = u_aid;

      cout << "\nChange of advisor successful.\n" << endl;
    }
    else{
      cout << "\nThat faculty member does not exist in our database.\n" << endl;
    }
  }
  else{
    cout << "\nThat student does not exist in our database.\n" << endl;
  }
}

// Case 12
void Menu::removeStudentFromAdvisor(int u_aid, int u_sid){

  Student tempstud(u_sid);
  Faculty tempfac(u_aid);

  if (MasterFaculty.contains(tempfac)){
    if (MasterStudent.contains(tempstud)){
      deleteStudent(u_sid);
    }
    else{
      cout << "\nThat student does not exist in our database.\n" << endl;
    }
  }
  else{
    cout << "\nThat faculty member does not exist in our database.\n" << endl;
  }

}

