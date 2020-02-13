#ifndef Application_hpp
#define Application_hpp
#include "eventType.hpp"
#include "RecordType.hpp"

using namespace std;

class ApplicationType{
public:
  ApplicationType();
  void Run(); // select a command and execute
  int GetCommand(); // get an integer representing a proper command
  int AddRecordToList(); // read a record from keyboard and add to the list
  int ReadAllFromFile(); // read all the records in file and store in vector arrays
  int WriteAllToFile(); // write all photo records to disk.
  void DisplayAllOnScreen(); // write all the record in the list on the screeen
  int SearchByPrimaryKey(string inName); // Search a record by file name and return index of the record.
  RecordType* BinarySearchByPrimaryKey(string inName);// Search a record by file name and return index of the record.
  int RetrieveByPhotoName(); // find records by photoname
  int DeleteByPhotoName();  //  find  a  record  by  name  and  delete
  int RetrieveByEvent();    //  find  records  by  event
  int RetrieveByContents();  //  find  records  by  contents
  int AddEventToList(eventType &user_Event);
  eventType * SearchEventList(const string &inName);
  void DisplayEventList();
  int RetrieveFromEventList();
  void DisplayEventPhotos();
private:
  SortedList<eventType> eventList;
  SortedList<RecordType> photoList;
  int length;
  string inFileName;
  string outFileName;
};

ApplicationType::ApplicationType()
:length(0),inFileName("lab12_5.txt"),outFileName("lab12_5.txt"){
  this->photoList.MakeEmpty();
  this->eventList.MakeEmpty();
}


 // select a command and execute
void ApplicationType::Run(){
  int command;
  while ((command=this->GetCommand())) {
    switch (command) {
      case 0:
        return ;
      case 1:
      this->AddRecordToList();
      break;
      case 2:
      this->ReadAllFromFile();
      break;
      case 3:
      this->WriteAllToFile();
      break;
      case 4:
      this->DisplayAllOnScreen();
      break;
      case 5:
      this->RetrieveByPhotoName();
      break;
      case 6:
      this->DeleteByPhotoName();
      break;
      case 7:
      this->RetrieveByEvent();
      break;
      case 8:
      this->RetrieveByContents();
      break;
      case 9:
      this->DisplayEventList();
      break;
      case 10:
      this->RetrieveFromEventList();
      break;
      default :
      std::cout << "\tInvalid  operation  \n" << '\n';
      break;
    }
  }
}

// get an integer representing a proper command
int ApplicationType::GetCommand(){
  int temp;
  while (1) {
    cout << endl << endl;
    cout << "\t----  ID-Command ---------------------------------------------" << endl;
    cout << "\t|        1.Add a new record to list                           |" << endl;
    cout << "\t|        2.Read all records from disk                         |" << endl;
    cout << "\t|        3.Write all records to disk                          |" << endl;
    cout << "\t|        4.Display all record on screen                       |" << endl;
    cout << "\t|        5.Retrieve by photo name                             |" << endl;
    cout << "\t|        6.Delete by photo name                               |" << endl;
    cout << "\t|        7.Retrieve by event                                  |" << endl;
    cout << "\t|        8.Retrieve by content                                |" << endl;
    cout << "\t|        9.Display Event List                                 |" << endl;
    cout << "\t|        10.Retrieve by event list                            |" << endl;
    cout << "\t|        0.Quit                                               |" << endl;
    cout << "\t--------------------------------------------------------------" << endl;
    cout << "\t  Choose a Command-- >";

    if (cin.fail()|| !(cin>>temp) || temp<0 || temp>10)// input fail or input value is out
    {
      cout<<"\t ### Invalid Command Number. Select again ####"<<endl;
      cin.clear(); //clear flag
      cin.ignore(INT_MAX, '\n'); //empty input buffer
    } else {
      cin.clear(); // clear flag
      cin.ignore(INT_MAX, '\n'); // empty input buffer
      return temp;
    }
  }
}

// read a record from keyboard and add to the list
int ApplicationType::AddRecordToList(){
  RecordType user_Record;
  std::cout  << '\n';
  cout <<"\t*********   [   Add a Record to list   ]   *********" << endl;
  user_Record.ReadPhotoNameFromKB();
  user_Record.ReadEventNameFromKB();
  user_Record.ReadRecordFromKB();
  this->photoList.Add(user_Record);
  std::string eventName=user_Record.getEName();
  std::string photoName=user_Record.getPName()
  eventType user_Event(eventName,photoName);
  this->AddEventToList(user_Event);
  return 1;
}

// read all the records in file and store in vector arrays
int ApplicationType::ReadAllFromFile(){
  ifstream inFile(this->inFileName);
  RecordType tRecord;
  int result=1;
  int i=0;
  while (inFile) {
    if (result==0) {
      return result;
    }
    tRecord.ReadRecordFromFile(inFile);
    result=this->photoList.Add(tRecord);
    i++;
  }
  inFile.close();
  cout << "\t****   [   Reading from disk is completed   ]   ****" << endl;
  return result;
}

// write all photo records to disk.
int ApplicationType::WriteAllToFile(){
  ofstream outFile(this->outFileName);
  RecordType tRecord;
  this->photoList.ResetList();
  for (int i = 0; i < this->photoList.GetLength(); i++) {
    this->photoList.GetNextItem(tRecord);
    tRecord.WriteRecordToFile(outFile);
  }
  outFile.close();
  cout << "\t****   [   Writing to disk is completed   ]   ****" << endl;
  return 1;

}

void ApplicationType::DisplayAllOnScreen(){
  RecordType tRecord;
  this->photoList.ResetList();
  std::cout  << '\n';
  cout << "\t**********   [   Display on screen   ]   **********" << endl;
  for (int i = 0; i < this->photoList.GetLength(); i++) {
    std::cout << "\tRecord "<<i <<" : ";
    this->photoList.GetNextItem(tRecord);
    tRecord.DisplayOnScreen();
  }
}

// Search a record by file name and return index of the record.
int ApplicationType::SearchByPrimaryKey(string inName){
  RecordType tRecord;
  this->photoList.ResetList();
  int index=0;
  for (int i = 0; i < this->photoList.GetLength(); i++) {
    this->photoList.GetNextItem(tRecord);
    if(tRecord.IsEqual(inName)){
      index=i;
      return index;
    }
  }
  return -1;
}

// Search a record by file name and return index of the record.
RecordType* ApplicationType::BinarySearchByPrimaryKey(string inName){
  RecordType findRecord;
  findRecord.setPName(inName);
  RecordType *tRecord;
  this->photoList.ResetList();
  tRecord=this->photoList.RetrieveUsingBinarySearch(findRecord);
  return tRecord;
}

// find records by photoname
int ApplicationType::RetrieveByPhotoName(){
  string inName = "";
  std::cout  << '\n';
  cout<< "\t************ [   Find by PhotoName  ] ************" << '\n';
  cout.width(40);
  cout <<left << "\tEnter a Photo name to search --> ";
  cin >> inName;
  RecordType* tRecord = BinarySearchByPrimaryKey(inName);
  int index=SearchByPrimaryKey(inName);
  if (tRecord==NULL){
    cout << "\tNo such file information" << '\n';
    return 0;
  } else {
    cout.width(15);
    cout <<left <<"\tRecord "<<index <<" : ";
    tRecord->DisplayOnScreen();
    return 1;
  }
}

//  find  a  record  by  name  and  delete
int ApplicationType::DeleteByPhotoName(){
  RecordType *tRecord;
  std::string inName="";
  std::cout<< '\n';
  cout<< "\t*********** [  Delete record by name  ] ***********" << '\n';
  std::cout << "\tEnter a Photo name to erase --> ";
  std::cin >> inName;
  tRecord=BinarySearchByPrimaryKey(inName);
  this->photoList.Delete(*tRecord);
}

//  find  records  by  event
int ApplicationType::RetrieveByEvent(){
  RecordType tRecord;
  string inName = "";
  cout << "\t************ [   Find by EventName  ] ************" << '\n';
  cout.width(40);
  cout <<left << "\tEnter a Event name to search --> ";
  cin >> inName;
  int count=0;
  for (int i = 0; i < this->photoList.GetLength(); i++) {
    this->photoList.GetNextItem(tRecord);
    if (tRecord.IsEqualEvent(inName)){
      cout << "\tRecords " << i << "  :   ";
      tRecord.DisplayOnScreen();
      count++;
    }
  }
  if (count==0) {
    cout << "\tNo such file information" << '\n';
    return 0;
  } else{
    return 1;
  }
}

//  find  records  by  contents
int ApplicationType::RetrieveByContents(){
  RecordType tRecord;
  string inName = "";
  cout << "\t************ [   Find by Contents  ] ************" << '\n';
  cout.width(40);
  cout <<left << "\tEnter a key in Contents      --> ";
  cin >> inName;
  int count=0;
  for (int i = 0; i < this->photoList.GetLength(); i++) {
    this->photoList.GetNextItem(tRecord);
    if (tRecord.IsContentsIncluded(inName)){
      cout << "\tRecords " << i << "  :   ";
      tRecord.DisplayOnScreen();
      count++;
    }
  }
  if (count==0) {
    cout << "\tNo such file information" << '\n';
    return 0;
  } else{
    return 1;
  }
}

int ApplicationType::AddEventToList(eventType &user_Event){
  SortedList<string> tempList;
  eventType *tEvent;
  string temp;
  tempList.ResetList();
  for (int i = 0; i < this->eventList.GetLength(); i++) {
    tEvent=eventList.GetNextItemPtr();
    if (tEvent->GetEventName()==user_Event.GetEventName()) {
      user_Event.GetFileNameList(tempList);
      tempList.GetNextItem(temp);
      tEvent->AddFileName(temp);
      return 1;
    }
  }
  this->eventList.Add(user_Event);
  return 0;
}
eventType *ApplicationType::SearchEventList(const string &inName){
  eventType *tEvent;
  for (int i = 0; i < this->eventList.GetLength(); i++) {
    this->eventList.GetNextItem(*tEvent);
    if (tEvent->GetEventName()==inName) {
      return tEvent;
    }
  }
  return NULL;
}
void ApplicationType::DisplayEventList(){
  SortedList<string> tempList;
  string temp;
  eventType tEvent;
  tempList.ResetList();
  std::cout  << '\n';
  cout << "\t*********** [   Display Event List  ] ***********" << '\n';
  for (int i = 0; i < this->eventList.GetLength(); i++) {
    this->eventList.GetNextItem(tEvent);
    std::cout << "\tEvent "<<i <<" : ";
    std::cout << tEvent.GetEventName() << '\n';
    tEvent.GetFileNameList(tempList);
    std::cout << "\tMembers : ";
    for (int j = 0; j < tEvent.GetNumOfPhoto(); j++) {
      tempList.GetNextItem(temp);
      cout.width(3);
      std::cout <<left <<temp<< ' ';
    }
    std::cout << '\n';
    std::cout << '\n';
  }

}
int ApplicationType::RetrieveFromEventList(){
  string inName = "";
  std::cout  << '\n';
  cout<< "\t********* [   Retrieve From EventList  ] *********" << '\n';
  cout.width(40);
  cout <<left << "\tEnter Event name to search --> ";
  cin >> inName;
  eventType * tEvent = SearchEventList(inName);
  if (tEvent==NULL){
    cout << "\tNo such file information" << '\n';
    return 0;
  } else {
    RecordType * tRecord;
    SortedList<string> tempList;
    string temp;
    tempList.ResetList();
    tEvent->GetFileNameList(tempList);
    for (int i = 0; i < tEvent->GetNumOfPhoto(); i++) {
      tempList.GetNextItem(temp);
      tRecord=BinarySearchByPrimaryKey(temp);
      cout.width(15);
      cout <<left <<"\tRecord : ";
      tRecord->DisplayOnScreen();
    }


    return 1;
  }
}
void ApplicationType::DisplayEventPhotos(){
  string inName = "";
  std::cout  << '\n';
  cout<< "\t********* [   Retrieve From EventList  ] *********" << '\n';
  cout.width(40);
  cout <<left << "\tEnter Event name to search --> ";
  cin >> inName;
  eventType * tEvent = SearchEventList(inName);
  if (tEvent==NULL){
    cout << "\tNo such file information" << '\n';
    return ;
  } else {
    RecordType * tRecord;
    SortedList<string> tempList;
    string temp;
    tempList.ResetList();
    tEvent->GetFileNameList(tempList);
    for (int i = 0; i < tEvent->GetNumOfPhoto(); i++) {
      tempList.GetNextItem(temp);
      tRecord=BinarySearchByPrimaryKey(temp);
      cout.width(15);
      cout <<left <<"\tRecord : ";
      tRecord->DisplayOnScreen();
    }
    return ;
  }
}





#endif /*Application_hpp*/
