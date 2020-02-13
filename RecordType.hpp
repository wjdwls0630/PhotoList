#ifndef RecordType_hpp
#define RecordType_hpp

using namespace std;

class RecordType {
public:
  string getPName() ;
  string getEName() ;
  void setPName(const std::string &photoName);
  void setEName(const std::string &eventName);
  int ReadPhotoNameFromKB(); // read photo name from keyboard
  void GenFileName(string& name); //generate an unique file name using the current time.
  int ReadEventNameFromKB(); // read event name from Keyboard
  int ReadRecordFromKB(); // read a record from keyboard
  int ReadRecordFromFile(ifstream& inFile); // read a record from file
  void WriteRecordToFile(ofstream& outFile); // write a record to file
  void DisplayOnScreen(); // display a record on screen
  bool IsEqual(string name); // compare photoName with input string
  bool IsEqualEvent(string name); /// compare event name
  bool IsContentsIncluded(string name); /// compare event name
  int Compare(string nameKey);
  bool operator<(RecordType inItem); // operator overloading
  bool operator>(RecordType inItem); // operator overloading

private:
  string photoName;
  string eventName;
  int size;
  string contents;
};
string RecordType::getPName() { return this->photoName; }
string RecordType::getEName() { return this->eventName; }
void RecordType::setPName(const std::string &photoName){ this->photoName=photoName;}
void RecordType::setEName(const std::string &eventName){ this->eventName=eventName;}

// read photo name from keyboard
int RecordType::ReadPhotoNameFromKB(){
  string user_pName;
  cout.width(40);
  cout <<left <<"\tPhoto Name(Enter 'gen' to AutoGenerate) --> ";
  std::cin >> user_pName;
  if (cin.fail()) {
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    return 0;
  }
  if (user_pName=="gen") {
    GenFileName(this->photoName);
  } else{
    this->photoName=user_pName;
  }
  return 1;
}

//generate an unique file name using the current time.
void RecordType::GenFileName(string& name){
  // Declaring argument for time()
  time_t tt;
  // Declaring variable to store return value of localtime()
  struct tm * ti;
  // Applying time()
  time (&tt);
  // Using localtime()
  ti = localtime(&tt);
  stringstream ss;
  ss << setw(4)<<ti->tm_year+1900<<setfill('0')<<setw(2)<<ti->tm_mon+1<<setfill('0') <<setw(2)<<ti->tm_mday<<setfill('0')<<setw(2)<<ti->tm_hour<<setfill('0')<<setw(2) <<ti->tm_min<<setfill('0')<<setw(2)<<ti->tm_sec<<"\0";
  string ymd=ss.str();
  name=ymd;
}

// read event name from Keyboard
int RecordType::ReadEventNameFromKB(){
  cout.width(40);
  cout <<left <<"\tEvent Name                              --> ";
  cin >> this->eventName;
  cout.width(40);
  cout <<left<< "\tEvent size (Please enter digit number)  --> ";
  cin >> this->size;
  if (cin.fail()) {
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    return 0;
  }
  return 1;
}

// read a record from keyboard
int RecordType::ReadRecordFromKB(){
  cout.width(40);
  cout<<left << "\tContents                                --> ";
  std::cin >> this->contents;

  if (cin.fail()) {
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    return 0;
  }
  return 1;
}

// read a record from file
int RecordType::ReadRecordFromFile(ifstream& inFile){
  if (inFile.fail()||(!inFile)) {
    return 0;
  } else{
    inFile>>this->photoName>>this->eventName>>this->size>>this->contents;
    return 1;
  }
}

// write a record to file
void RecordType::WriteRecordToFile(ofstream& outFile){
  if (outFile.fail()) {
    std::cout << "cannot opening file" << '\n';
  }
  outFile<<this->photoName<<' '<<this->eventName<<' '<<this->size<<' '<<this->contents<<'\n';
}

// display a record on screen
void RecordType::DisplayOnScreen(){
  cout.width(15);
  std::cout <<left<<this->photoName<<" . ";
  cout.width(12);
  cout<<left<<this->eventName<<" . ";
  cout.width(3);
  cout<<left<<this->size<<" . ";
  cout<<this->contents<<'\n';
}
// compare photoName with input string
bool RecordType::IsEqual(string name) { return name==this->photoName; }
/// compare event name
bool RecordType::IsEqualEvent(string name){ return name==this->eventName; }
/// compare event name
bool RecordType::IsContentsIncluded(string name){
  if (this->contents.find(name)!=-1) {
    return true;
  } else{
    return false;
  }
}
int RecordType::Compare(string nameKey){
  if (this->photoName<nameKey) {
    return -1;
  } else if (this->photoName==nameKey) {
    return 0;
  } else {
    return 1;
  }
}
bool RecordType::operator<(RecordType inItem){ return inItem.photoName<this->photoName; }
bool RecordType::operator>(RecordType inItem){ return inItem.photoName<this->photoName; }

#endif /*RecordType_hpp*/
