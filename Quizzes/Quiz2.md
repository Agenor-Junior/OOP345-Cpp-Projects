# Object-Oriented Software Development Using C++ - Quiz #2 [2.5%]

### Question 1
**In C++, which principle states that objects of a derived class should be able to replace objects of the base class without affecting the correctness of the program?**  
**Correct Answer:**  
**B. Liskov Substitution Principle**  
The Liskov Substitution Principle ensures that derived classes can replace base classes without altering the desired behavior of the program.

---

### Question 2
**Which type of cast in C++ is used for converting between related classes in a class hierarchy?**  
**Correct Answer:**  
**C. dynamic_cast**  
`dynamic_cast` is used to safely cast pointers or references within a class hierarchy.

---

### Question 3
**Find and fix the error in the following code:**  

```cpp
class Base {
public:
    virtual void print() { cout << "Base" << endl; }
};

class Derived : Base {
public:
    void print() { cout << "Derived" << endl; }
};

int main() {
    Base* ptr = new Derived();
    ptr->print();
    return 0;
}
```

**Correct Answer:**  
The destructor of `Base` should be virtual to ensure proper deletion of derived class objects.  

```cpp
virtual ~Base() {}
delete ptr;
```

---

### Question 4
**Which relationship in C++ represents a "whole-part" scenario where the part cannot exist without the whole?**  
**Correct Answer:**  
**D. Composition**  
In composition, the lifecycle of the part is managed by the whole object.

---

### Question 5
**What is the output of the following code?**  

```cpp
#include <iostream>
using namespace std;

template <typename T>
class Counter {
private:
    static int count;
public:
    Counter() { ++count; }
    static int getCount() { return count; }
};

template <typename T>
int Counter<T>::count = 0;

int main() {
    Counter<int> c1, c2;
    Counter<double> c3;

    cout << Counter<int>::getCount() << " ";
    cout << Counter<double>::getCount() << " ";
    cout << Counter<float>::getCount();
    return 0;
}
```

**Correct Answer:**  
**Output:**  
```yaml
2 1 0
```
**Explanation:**  
- `Counter<int>` has two instances (`c1` and `c2`), so its count is 2.  
- `Counter<double>` has one instance (`c3`), so its count is 1.  
- `Counter<float>` has no instances, so its count remains 0.

---

### Question 6
**Which of the following is true about class variables in C++?**  
**Correct Answer:**  
**C. All of the above**  
Class variables are declared using the `static` keyword and are shared by all instances of the class.

---

### Question 7
**What is the output of the following code?**  

```cpp
#include <iostream>
using namespace std;

class A {
public:
    static int x;
    static void print() { cout << x << " "; }
};

class B : public A {
public:
    static int x;
    static void print() { cout << x << " "; }
};

int A::x = 1;
int B::x = 2;

int main() {
    A a;
    B b;
    A* ptr = &b;
    a.print();
    b.print();
    ptr->print();
    return 0;
}
```

**Correct Answer:**  
**Output:**  
```yaml
1 2 1
```
**Explanation:**  
- `A::x` is 1 and `B::x` is 2.  
- `ptr->print()` calls `A::print()`, not `B::print()`, since `print` is static and not virtual.

---

### Question 8
**What's wrong or missing with this class template definition?**  

```cpp
template <typename T>
class Stack {
private:
    T* elements;
    int top;
    int capacity;

public:
    Stack(int size) {
        elements = new T[size];
        capacity = size;
        top = -1;
    }

    void push(T item) {
        if (top == capacity - 1) {
            throw "Stack Overflow";
        }
        elements[++top] = item;
    }

    T pop() {
        if (top == -1) {
            throw "Stack Underflow";
        }
        return elements[top--];
    }
};
```

**Correct Answer:**  
Destructor is missing to delete allocated memory.  

```cpp
~Stack() {
    delete[] elements;
}
```

---

### Question 9
**What is the primary purpose of class templates in C++?**  
**Correct Answer:**  
**C. To generate generic classes**  
Class templates allow the creation of generic classes that can work with any data type.

---

### Question 10
**What is the output of the following code?**  

```cpp
class Base {
public:
    virtual void show() { cout << "Base"; }
};

class Derived : public Base {
public:
    void show() { cout << "Derived"; }
};

int main() {
    Base* b = new Derived();
    b->show();
    delete b;
    return 0;
}
```

**Correct Answer:**  
**Output:**  
```yaml
Derived
```
**Explanation:**  
Because `show` is a virtual function, the `Derived` class's method is called, not the `Base` class's method.
