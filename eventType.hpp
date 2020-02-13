#ifndef eventType_hpp
#define eventType_hpp
#include "MySortedList.hpp"
using namespace std;
class eventType {
private:
  string eventName;
  SortedList<string> memPhotoList;
  int numOfphoto;

public:
  eventType();
  eventType (string &eventName, string &photoName);
  string GetEventName() const;
  void GetFileNameList(SortedList<string> &tempList);
  void AddFileName(string &photoName);
  int GetNumOfPhoto() const;
};
eventType::eventType():eventName(""),numOfphoto(0){}
eventType::eventType (string &eventName, string &photoName) : eventName(eventName),numOfphoto(1){
  this->memPhotoList.Add(photoName);
}
string eventType::GetEventName() const{ return this->eventName ; }

void eventType::GetFileNameList(SortedList<string> &tempList){
  string *temp;
  this->memPhotoList.ResetList();
  for (int i = 0; i < this->memPhotoList.GetLength(); i++) {
    temp =this->memPhotoList.GetNextItemPtr();
    tempList.Add(*temp);
  }
}
void eventType::AddFileName(string &photoName){
  this->memPhotoList.Add(photoName);
  this->numOfphoto++;
}
int eventType::GetNumOfPhoto() const{ return this->numOfphoto; }

#endif /*eventType_hpp*/
