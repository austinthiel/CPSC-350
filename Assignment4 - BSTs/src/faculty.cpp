#include <iostream>
#include "faculty.h"

using namespace std;

Faculty::Faculty(){
  ID = 0;
  name = "";
  level = "";
  dept = "";
  //advisees is already empty
}

Faculty::Faculty(int m_ID){
  ID = m_ID;
  name = "VOID";
  level = "VOID";
  dept = "VOID";
}

Faculty::Faculty(int m_ID, string m_name, string m_level, string m_dept){
  ID = m_ID;
  name = m_name;
  level = m_level;
  dept = m_dept;
}

Faculty::~Faculty(){

}

bool Faculty::operator==(const Faculty &other) const{
  return this->ID == other.ID;
}

bool Faculty::operator<(Faculty other){
  return this->ID < other.ID;
}

bool Faculty::operator>(Faculty other){
  return this->ID > other.ID;
}

int Faculty::getID(){
  return this->ID;
}

std::string Faculty::getName(){
  return this->name;
}

std::string Faculty::getLevel(){
  return this->level;
}

std::string Faculty::getDept(){
  return this->dept;
}