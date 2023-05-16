#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

/*
Написати функцію-шаблон послідовного пошуку в масиві по
ключу. Функція повертає індекс останнього, знайденого елемента в
масиві, рівного ключу. Написати специфікацію функції-шаблон для типу
char*.
*/

template <typename T> int search(T arr[], int size, T &key) {
  int last_index = -1;
  for (int i = 0; i < size; i++) {
    if (arr[i] == key) {
      last_index = i;
    }
  }
  return last_index;
}

template<char*> int search(char* arr[], int size, char* &key) {
  int last_index = -1;
  for (int i = 0; i < size; i++) {
    if (arr[i] == key) {
      last_index = i;
    }
  }
  return last_index;
}

void exersice1() {
  const char* arr[] = {"apple", "banana", "cherry", "apple", "date", "berry"};
  int size = sizeof(arr) / sizeof(arr[0]);
  const char* key = "berry";
  int index = search(arr, size, key);
  std::cout << "Last index of " << key << " is " << index << std::endl;
}

/*
Написати функцію-шаблон функцію впорядкування методом швидкого впорядкування.
Написати специфікацію функції-шаблон для типу char*.
*/

template <typename T>
void quicksort(T arr[], int left, int right) {
    int i = left, j = right;
    T tmp;
    T pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (strcmp(arr[i], pivot) < 0)
            i++;
        while (strcmp(arr[j], pivot) > 0)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    } 

    if (left < j)
        quicksort(arr, left, j);
    if (i < right)
        quicksort(arr, i, right);
};

template <>
void quicksort<char*>(char* arr[], int left, int right) {
  int i = left, j = right;
    char* tmp;
    char* pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (strcmp(arr[i], pivot) < 0)
            i++;
        while (strcmp(arr[j], pivot) > 0)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }

    if (left < j)
        quicksort(arr, left, j);
    if (i < right)
        quicksort(arr, i, right);
};

void exersice2() {
    int size = 6;
    char numberslist[] = {'1', '3', '5', '4', '9', '8'};
    char* numbers[size] = {nullptr};
    for (int i = 0; i < size; i++) {
      numbers[i] = &numberslist[i];
    }

    quicksort(numbers, 0, size-1);
    for (int i = 0; i < size; i++) {
          cout << *numbers[i] << " ";
    }
}

/*
Створити параметризований масив з конструкторами,
деструктором і перевантаженими операторами [], =, +, +=,-,-=.
без використання STL
*/

template <typename T>
class Array {
private:
    T *data;
    int size;
public:
    Array() {
        data = nullptr;
        size = 0;
    }
    
    Array(int n) {
        if (n < 0) {
            cout << "Array size must be non-negative";
        } else {
          data = new T[n];
        size = n;
        }
    }
    
    Array(int n, T d) {
      if (n < 0) {
            cout << "Array size must be non-negative";
        } else {
          data = new T[n];
          size = n;
      for (int i = 0; i < n; i++) {
        data[i] = d;
      }
        }
    }

    Array(const Array &other) {
        size = other.size;
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    
    ~Array() {
        delete[] data;
    }
    
    T& operator[](int i) {
        if (i < 0 || i >= size) {
            cout << "Array index out of range";
        }
        return data[i];
    }
    
    Array& operator=(const Array &other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new T[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    Array operator+(const Array &other) {
        if (size != other.size) {
            cout << "Arrays must be of equal size";
        }
        Array result(size);
        for (int i = 0; i < size; i++) {
            result[i] = data[i] + other.data[i];
        }
        return result;
    }
    
    Array& operator+=(const Array &other) {
        if (size != other.size) {
            cout<<"Arrays must be of equal size";
        }
        for (int i = 0; i < size; i++) {
            data[i] += other.data[i];
        }
        return *this;
    }
    
    Array operator-(const Array &other) {
        if (size != other.size) {
            cout << "Arrays must be of equal size";
        }
        Array result(size);
        for (int i = 0; i < size; i++) {
            result[i] = data[i] - other.data[i];
        }
        return result;
    }

    Array& operator-=(const Array &other) {
    if (size != other.size) {
        cout << "Arrays must be of equal size";
    }
    for (int i = 0; i < size; i++) {
        data[i] -= other.data[i];
    }
    return *this;
  }

  void print() {
    for(int i = 0; i < this->size; i++ ) {
      cout << this->data[i] << " ";
    }
  }
};

void exersice3() {
  Array<int> r1(5, 4);
  Array<int>  r2(5, 6);
  cout << "First array" << endl;
  r1.print();
  cout << endl << "Second array" << endl;
  r2.print();
  cout << endl << "r1 + r2" << endl;
  r1 = r1 + r2;
  r1.print();
    cout << endl << "r1 - r2" << endl;
  r1 = r1 - r2;
  r2.print();
}

/*
Побудувати клас, що описує бінарне дерево стандартної форми.
Побудувати клас ітератор, що дозволяє обходити дерево. Написати
програму, яка проходить по бінарному дереву використовуючи ітератор.
*/

void MenuExample() {
	std::cout << "     Menu Example   \n";
	std::cout << "    1   Exersice 1  \n";
	std::cout << "    2   Exersice 2  \n";
  std::cout << "    3   Exersice 3  \n";
}

int main() {
  bool isSelected = false;
  while (!isSelected) {
    system("cls");
    MenuExample();
    int ch;
    cin >> ch;
    switch (ch) {
    case 1:
      exersice1();
      isSelected = true;
      break;
    case 2:
      exersice2();
      isSelected = true;
      break;
    case 3:
      exersice3();
      isSelected = true;
    default:
      break;
    }
  }
}