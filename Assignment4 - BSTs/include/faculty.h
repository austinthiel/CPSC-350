#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include "dlist.h"

class Faculty{
private:

public:

  int ID;
  std::string name;
  std::string level;
  std::string dept;
  DList<int> advisees;

  Faculty();
  Faculty(int m_ID);
  Faculty(int m_ID, std::string m_name, std::string m_level, std::string m_dept);
  virtual ~Faculty();
  bool operator==(const Faculty &other) const;
  bool operator<(Faculty other);
  bool operator>(Faculty other);
  int getID();
  std::string getName();
  std::string getLevel();
  std::string getDept();
};

inline std::ostream& operator<<(std::ostream& os, Faculty& other){
  os << "Faculty ID: " << other.ID << std::endl
    << "Name: " << other.name.c_str() << std::endl
    << "Level: " << other.level.c_str() << std::endl
    << "Dept: " << other.dept.c_str() << std::endl
    << "Advisees: " << other.advisees << std::endl;
  return os;
}

#endif