#include <iostream>
#include "student.h"

using namespace std;

Student::Student(){
  studentID = 0;
  advisor = 0;
  name = "";
  major = "";
  stringlevelfield = "";
  GPA = 0.0;
  //studentIDp = &studentID;
}

Student::Student(int IDnum){
  studentID = IDnum;
  advisor = 0;
  name = "VOID";
  stringlevelfield = "VOID";
  major = "VOID";
  GPA = 0.0;
}

Student::Student(int IDnum, int facID, string namey, string slf, string maj, double gpa){
  studentID = IDnum;
  advisor = facID;
  name = namey;
  stringlevelfield = slf;
  major = maj;
  GPA = gpa;
  //studentIDp = &studentID;
}

int Student::getID(){
  return studentID;
}

bool Student::operator==(Student& other){
  return (studentID == other.studentID);
}

bool Student::operator<(Student& other){
  return(studentID < other.studentID);
}

bool Student::operator>(Student& other){
  return(studentID > other.studentID);
}

