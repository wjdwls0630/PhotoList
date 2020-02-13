#ifndef Comparer_hpp
#define Comparer_hpp

//class Comparer declaration
template<typename T>
class Comparer {
private:
  int compare_count;
  int swap_count;
  bool (*comp)(const T &, const T &);
protected:
  virtual bool compare_impl(const T &a, const T &b);
  virtual void swap_impl(T & a, T &b);
public:

  Comparer (const int &sortDirection);
  void reset();
  bool compare(const T & a, const T &b) ;
  void swap(T & a, T &b);
  int comparisons() const;
  int swaps() const;
};

//class Comparer definition

template<typename T> bool Comparer<T>::compare_impl(const T &a, const T &b){ return this->comp(a,b); }
template<typename T> void Comparer<T>::swap_impl(T & a, T &b){
  T temp = a;
  a=b;
  b=temp;
}

template<typename T>Comparer<T>::Comparer (const int &sortDirection)
:compare_count(0),swap_count(0){
  if (sortDirection==1) {
    comp=[](const T &a,const T &b)->bool{return a<b;};
  } else {
    comp=[](const T &a,const T &b)->bool{return a>b;};
  }
}

template<typename T> void Comparer<T>::reset() { compare_count=swap_count=0; }
template<typename T> bool Comparer<T>::compare(const T & a, const T &b) {
  this->compare_count++;
  return this->compare_impl(a,b);
}
template<typename T> void Comparer<T>::swap(T & a, T &b) {
  this->swap_count++;
  this->swap_impl(a,b);
}
template<typename T> int Comparer<T>::comparisons() const { return this->compare_count; }
template<typename T> int Comparer<T>::swaps() const { return this->swap_count; }

#endif /* Comparer_hpp */
