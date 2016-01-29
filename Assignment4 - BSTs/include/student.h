#ifndef STUDENT_H
#define STUDENT_H

using namespace std;

class Student{
public:
  Student();
  Student(int IDnum);
  Student(int IDnum, int facID, std::string namey, std::string slf, std::string maj, double gpa);
  int getID();
  bool operator==(Student& other);
  bool operator<(Student& other);
  bool operator>(Student& other);
  //virtual ~Student();
//private:
  int studentID;
  int advisor;
  //int* studentIDp;
  std::string name;
  std::string stringlevelfield;
  std::string major;
  double GPA;
};

inline ostream& operator<<(ostream& os, const Student& other){
  os << "Student ID: " << other.studentID << endl
    << "Advisor ID: " << other.advisor << endl
    << "Name: " << other.name.c_str() << endl
    << "Major: " << other.major.c_str() << endl
    << "Grade: " << other.stringlevelfield.c_str() << endl
    << "GPA: " << other.GPA << endl;
  return os;
}

# endif
