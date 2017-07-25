// g++ templates.cpp -std=c++11 -o templates;./templates

#include <iostream>
#include <vector>
#include <list>

// int max(int x, int y) {
//   return x > y ? x : y;
// }

// 1
template<typename T>
T max(T x, T y) {
  std::cout << typeid(T).name() << std::endl;
  return x > y ? x : y;
}

// 2
// Explicit instantiation
template char max(char x, char y);

// Explicit specialization
template<> const char * max<const char*>(const char *x, const char *y) {
  std::cout << "max<const char*>()" << std::endl;
  return strcmp(x, y) > 0 ? x : y;
}

// 3
// Non-type Template arguments
// template<typename T>
// T sum(T *pArr, int size) {
//   T sum{};
//   for (size_t i = 0; i < size; i++) {
//     sum += pArr[i];
//   }
//   return sum;
// }

// 4
template<typename T, int size>
T sum(T (&arr)[size]) {
  T sum{};
  for (size_t i = 0; i < size; i++) {
    sum += arr[i];
  }
  return sum;
}

// 5
void print() {
  std::cout << std::endl;
}

// Template parameter pack
template<typename T, typename...params>
void print(T a, params... args) {
  // std::cout << sizeof...(args) << std::endl;
  std::cout << a;
  if (sizeof...(args) != 0) {
    std::cout << ", ";
  }

  print(args...);
}

// 6
// Class templates

template<typename T, int size>
class Stack {

  T mBuffer[size];
  int mTop{ -1 };

public:

  void push(const T &elem) {
    mBuffer[++mTop] = elem;
  }

  void pop();
  // void pop() {
  //   --mTop;
  // }

  const T& top() const {
    return mBuffer[mTop];
  }

  bool isEmpty() {
    return mTop == -1;
  }

  static Stack create();
  // static Stack create() {
  //   return Stack<T, size>();
  // }
};

template<typename T, int size>
void Stack<T, size>::pop() {
  --mTop;
}

template<typename T, int size>
Stack<T, size> Stack<T, size>::create() {
  return Stack<T, size>();
}

// 7
// Class template explicit specialization
template<typename T>
class PrettyPrinter {

  T *mpData;

public:

  PrettyPrinter(T *data) : mpData(data) {

  }

  void print() {
    std::cout << "{ " << *mpData << " }" << '\n';
  }

  T * getData() {
    return mpData;
  }
};

// 7.1
template<>
class PrettyPrinter<char *> {

  char *mpData;

public:

  PrettyPrinter(char *data) : mpData(data) {

  }

  void print() {
    std::cout << "[ " << mpData << " ]" << '\n';
  }
};

// 7.2
// We can specialized just a function
template<>
void PrettyPrinter<std::vector<int>>::print() {
  std::cout << "> ";
  for (const auto &x : *mpData) {
    std::cout << x;
  }
  std::cout << " <" << '\n';
}

// 8
// Type Aliases
// usign UINT = unsigned int;
// UINT val{};
//
// using LLONG = long long;
// LLONG elem{};
//
// usign Teams = std::vector<std:list<int>>;
// Teams testingTeams;
// Teams::iterator it = testingTeams.begin();

const char * getErrorMessage(int e) {
  return "Empty";
}

// typedef const char *(*PFN)(int);
usign PFN = const char *(*)(int);
void showError(PFN pfn) {

}

// 8.1
// typedef std::vector<std:list<std::string>> Names;
usign Names = std::vector<std:list<std::string>>;
// 8.2
template<typename T>
using Names = std::vector<std::list<T>>;

int main() {
  // 1
  // auto result = max(static_cast<float>(3), 8.5f);
  // auto result = max<double>(3, 8.5f);

  // 2
  // const char *b{ "B" };
  // const char *a{ "A" };
  // auto result = max(a, b);

  // 3
  // int arr[]{ 3, 1, 9, 7 };
  // int result = sum(arr, 4);

  // 4
  // int arr[]{ 3, 1, 9, 7 };
  // int(&ref)[4] = arr;
  // int result = sum(arr);

  // std::cout << result << std::endl;

  // 5
  // print(1, 2.5f, 3, "4");

  // 6
  // Stack<float> s;
  // Stack<int, 10> s;
  // Stack<float, 10> s = Stack<float, 10>::create();
  // s.push(3);
  // s.push(1);
  // s.push(6);
  // s.push(9);
  //
  // while (!s.isEmpty()) {
  //   std::cout << s.top() << " " << '\n';
  //   s.pop();
  // }

  // 7
  int i = 5;
  float f = 8.2f;

  PrettyPrinter<int> p1(&i);
  p1.print();

  PrettyPrinter<float> p2(&f);
  p2.print();

  // 7.1
  char *c = (char*)"Hello World!";
  PrettyPrinter<char *> p3(c);
  p3.print();

  // 7.2
  std::vector<int> v{ 1, 2, 3, 4, 5, 6 };
  PrettyPrinter<std::vector<int>> pv(&v);
  pv.print();

  // 8
  // PFN pfn = getErrorMessage;
  // showError(pfn);

  // 8.1
  // Names names;
  // Names nnames;

  // 8.2
  // Names<std::string> names;
  // Names<Names<std::string>> nnames;

  return 0;
}
