# OOP345 Fall 2024 – Midterm Key

## Part A: Short Answer (15%)

### 1. Explain the concept of polymorphism in Object-Oriented Programming. How does C++ support polymorphism? (3%)
Polymorphism allows objects of different classes to be treated as objects of a common base class. In C++, polymorphism is supported through virtual functions. When a function is marked as virtual in the base class, derived class objects can override this function, and the most derived version is called, even when the object is referenced via a pointer or reference to the base class.

### 2. Explain the purpose of a move constructor in C++. How does it differ from a copy constructor? (3%)
A move constructor in C++ transfers ownership of resources from one object to another without copying, improving performance for large objects. It differs from the copy constructor because the move constructor avoids deep copying by "stealing" resources (pointers, dynamic memory) from the original object, which is left in a valid but unspecified state, whereas a copy constructor creates an exact copy of the object’s resources.

### 3. Explain the difference between lvalue references and rvalue references in C++. When would you use each? (3%)
Lvalue references (T&) refer to objects that have a persistent state (like variables), while rvalue references (T&&) refer to temporary objects (like those returned from expressions or functions). Lvalue references are used when you need to modify the original object, and rvalue references are used in move semantics to take advantage of temporary objects and avoid unnecessary copying.

### 4. Describe the purpose of the noexcept specifier in C++. How does it affect exception handling? (3%)
The noexcept specifier tells the compiler that a function does not throw exceptions. This allows optimizations because the compiler doesn't need to account for exceptions being thrown. If a function marked noexcept does throw, the program will call std::terminate() and abort. It's particularly useful for move constructors and destructors.

### 5. What is the Liskov Substitution Principle? Give example. (3%)
The Liskov Substitution Principle (LSP) is a principle in object-oriented programming that states that objects of a base class should be replaceable with objects of derived classes without altering the correctness of the program.  
**Example:**  
If Bird is a base class, and Penguin is a derived class, you should be able to use Penguin wherever Bird is expected, assuming Penguin adheres to the behavior of Bird.  

---

## Part B: Debugging (25%)

### Analyze the following code snippet. Identify and explain the errors according to the C++17 standard and provide corrections.###

```cpp
#include <iostream>
#include <cstring>

class Base {
public:
    virtual void process() const {
        std::cout << "Base process\n";
    }
    virtual ~Base() {}
};

class Derived : public Base {
private:
    char* data;
    size_t size;

public:
    Derived(const char* inputData) : size(strlen(inputData)) {
        data = new char[size + 1];
        strcpy(data, inputData);
        std::cout << "Derived constructor called\n";
    }

    ~Derived() {
        delete data;
        std::cout << "Derived destructor called\n";
    }

    Derived(const Derived& other) : size(other.size) {
        data = new char[size + 1];
        strcpy(data, other.data);
        std::cout << "Derived copy constructor called\n";
    }

    Derived& operator=(const Derived& other) {
        if (this != &other) {
            size = other.size;
            data = new char[size + 1];
            strcpy(data, other.data);
        }
        std::cout << "Derived copy assignment called\n";
        return *this;
    }

    Derived(Derived&& other) noexcept : size(other.size), data(other.data) {
        std::cout << "Derived move constructor called\n";
    }

    Derived& operator=(Derived&& other) noexcept {
        if (this != &other) {
            data = other.data;
            size = other.size;
        }
        std::cout << "Derived move assignment called\n";
        return *this;
    }

    void process() const override {
        std::cout << "Derived process with data: " << data << std::endl;
    }

    void throwException() const {
        throw std::runtime_error("Uncaught exception in Derived class");
    }
};

void testLSP(Base* base) {
    Derived* derived = dynamic_cast<Derived*>(base); 
    if (derived) { 
        derived->process(); 
    } else { 
        throw std::runtime_error("Invalid object type!"); 
    }
}

int main() {
    Derived d1("Test");
    Derived d2("Another Test");

    Derived d3 = d1;
    d2 = d1;

    Derived d4 = std::move(d1);
    d4 = std::move(d2);

    Base* basePtr = new Derived("LSP Test");
    testLSP(basePtr);
    delete basePtr;

    d4.throwException();

    return 0;
}
```
## Answers:

### 1. Memory Management - Destructor (4 points) 
**Issue:** In the destructor of the Derived class, delete data; is incorrect because data was allocated with new[] (array allocation). When deleting memory allocated with new[], the correct form is delete[], as the compiler needs to know it's deleting an array.
**Correction:** Replace delete data; with delete[] data; to ensure proper memory deallocation.

### 2. Copy Assignment Operator - Memory Leak (4 points)
**Issue:** In the copy assignment operator, data = new char[size + 1]; is used without first deleting the old memory that data points to. This leads to a memory leak because the previously allocated memory is not freed before reassigning the pointer.
**Correction:** Add delete[] data; before allocating new memory in the copy assignment operator to prevent memory leaks.

### 3. Move Assignment Operator - Resource Management (4 points)
**Issue:** In the move assignment operator, there is no cleanup of the existing data before taking ownership of the new one. This leads to potential memory leaks if the object being assigned already holds allocated memory.
**Correction:** Add delete[] data; before reassigning data in the move assignment operator to ensure proper resource management.

### 4. Move Constructor - Reset Moved Object (3 points)
**Issue:** In the move constructor, other.data is not set to nullptr after the move. This could result in a double free when the destructor of other is called, as both the current and moved-from objects would try to free the same memory.
**Correction:** Add other.data = nullptr; after moving data to the current object.

### 5.	Liskov Substitution Principle violation: (5 points)
**Issue:** The function testLSP(Base* base) incorrectly assumes that base will always point to a Derived object. This violates LSP.
**Correction:** Remove the use of dynamic_cast and instead rely on polymorphism by calling base->process();.

### 6. Uncaught Exceptions in the Code (5 points)
**Issue:** throwException() Method in Derived Class explicitly throws an exception but is not caught in the main() function where it's invoked. This will lead to an uncaught exception and program termination.
**Correction:** Use try-catch blocks





## Part C: Walkthrough (20%)
### Predict the output of the provided C++ code.

```cpp
#include <iostream>

template <typename T>
class Base {
public:
    Base(T val) : value(val) { std::cout << "Base Constructor\n"; }
    Base(const Base& other) : value(other.value) { std::cout << "Base Copy Constructor\n"; }
    Base(Base&& other) noexcept : value(std::move(other.value)) { std::cout << "Base Move Constructor\n"; }
    Base& operator=(const Base& other) {
        value = other.value;
        std::cout << "Base Copy Assignment\n";
        return *this;
    }
    Base& operator=(Base&& other) noexcept {
        value = std::move(other.value);
        std::cout << "Base Move Assignment\n";
        return *this;
    }
    virtual ~Base() { std::cout << "Base Destructor\n"; }

    virtual void Print() { std::cout << "Base Value: " << value << "\n"; }

protected: 
    T value;
};

template <typename T>
class Derived : public Base<T> {
public:
    Derived(T val) : Base<T>(val) { std::cout << "Derived Constructor\n"; }
    Derived(const Derived& other) : Base<T>(other) { std::cout << "Derived Copy Constructor\n"; }
    Derived(Derived&& other) noexcept : Base<T>(std::move(other)) { std::cout << "Derived Move Constructor\n"; }
    Derived& operator=(const Derived& other) {
        Base<T>::operator=(other);
        std::cout << "Derived Copy Assignment\n";
        return *this;
    }
    Derived& operator=(Derived&& other) noexcept {
        Base<T>::operator=(std::move(other));
        std::cout << "Derived Move Assignment\n";
        return *this;
    }
    ~Derived() { std::cout << "Derived Destructor\n"; }

    void Print() override { std::cout << "Derived Value: " << this->value << "\n"; }
};

void Process(void* ptr) {
    Base<int>* basePtr = static_cast<Base<int>*>(ptr);
    basePtr->Print();
}

int main() {
    Derived<int> d1(10);
    Derived<int> d2(20);

    auto lambda = [d1, &d2]() {
        d2 = std::move(d1);
        d2.Print();
        };
    lambda();

    void* ptr = &d2;
    Process(ptr);

    return 0;
}

```
### OUTPUT: 
```
Base Constructor
Derived Constructor
Base Constructor
Derived Constructor
Derived Move Assignment
Base Move Assignment
Derived Value: 10
Derived Value: 10
Derived Destructor
Base Destructor
Derived Destructor
Base Destructor
```
---

## Part D: Programming (40%)

### Translate the following description into appropriate C++ code.
-	**Create a class template Matrix ```<T>``` that represents a 2D matrix of any data type.**
- Include:
  - A constructor that takes two int parameters for rows and columns and initializes the matrix elements to zero.
  - An initializer list constructor to initialize the matrix with a 2D initializer list.
  - Overload the () operator to access elements of the matrix (both for getting and setting values).
  - Implement deep copy semantics with copy constructor and copy assignment operator.
  - Implement move semantics with move constructor and move assignment operator.
- Add a member function transpose() that returns a new Matrix<T> object which is the transpose of the original matrix (i.e. rows converted to columns and columns to rows).
- Use exception handling to manage out-of-bounds access with a custom exception class MatrixException.
- Demonstrate the Matrix class by:
  - Creating a Matrix<int> object and initializing it with values.
  - Transposing the matrix and displaying both the original and transposed matrices.
  - Handling exceptions when accessing invalid indices.

## One way to write it:


```cpp
#include <iostream>
#include <exception>

// Custom exception class for matrix out-of-bounds access
class MatrixException : public std::exception { 
    // by inheriting from std::exception, object of this class can fit in wherever std::exception is mentioned
public:
    const char* what()    {
        return "Matrix index out of bounds";
    }
};

// Matrix template class
template <typename T>
class Matrix {
private:
    int rows{}, cols{};      // Number of rows and columns
    T** data{};            // Pointer to a 2D array (dynamically allocated)

    // Helper function to allocate memory for the matrix
    void allocateMemory(int r, int c) {
        rows = r;
        cols = c;
        data = new T * [rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
        }
    }

    // Helper function to deallocate memory
    void deallocateMemory() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

public:
    // Constructor: Initializes the matrix with given rows and columns, all elements set to zero
    Matrix(int r, int c) {
        allocateMemory(r, c);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = 0;  // Initialize elements to zero
            }
        }
    }

    // Initializer like constructor
    Matrix(int r, int c, T** initData) {
        allocateMemory(r, c);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = initData[i][j];
            }
        }
    }

    // Destructor to deallocate memory
    ~Matrix() {
        deallocateMemory();
    }

    // Copy constructor (deep copy)
    Matrix(const Matrix& other) {
        allocateMemory(other.rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    // Copy assignment operator (deep copy)
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            // Deallocate existing memory and allocate new memory
            deallocateMemory();
            allocateMemory(other.rows, other.cols);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        return *this;
    }

    // Move constructor
    Matrix(Matrix&& other) noexcept : rows(other.rows), cols(other.cols), data(other.data) {
        other.data = nullptr;  // Set other.data to nullptr to avoid double deletion
        other.rows = 0;
        other.cols = 0;
    }

    // Move assignment operator
    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            // Deallocate current memory
            deallocateMemory();

            // Steal the resources
            rows = other.rows;
            cols = other.cols;
            data = other.data;

            // Nullify the moved-from object
            other.data = nullptr;
            other.rows = 0;
            other.cols = 0;
        }
        return *this;
    }

    T** getData() {
        return data;
    }

    // Overload operator() for accessing and modifying matrix elements
    T& operator()(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            throw MatrixException();  // Out of bounds
        }
        return data[r][c];
    }


    // Function to return the transpose of the matrix
    Matrix<T> transpose() const {
        Matrix<T> transposed(cols, rows);  // Transpose will swap rows and columns
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                transposed(j, i) = data[i][j]; // just [i][j] = [j][i]
            }
        }
        return transposed;
    }

    // Function to display the matrix
    void display() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};



int main() {
    try {

        // Create an emptry Matrix<int>
        Matrix<int> mat1(3, 3);
        mat1.display();		

        // Fill in values
        int value = 1;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                mat1(i,j) = value++;
            }
        }
        mat1.display();

        // Create a Matrix<int> and initialize with values from the 2D array of earlier matrix
        Matrix<int> mat2(3, 3, (int**)mat1.getData());

        // Display original matrix
        std::cout << "Original Matrix:" << std::endl;
        mat2.display();

        // Transpose the matrix and display it
        Matrix<int> transposedMat = mat2.transpose();
        std::cout << "\nTransposed Matrix:" << std::endl;
        transposedMat.display();

        //Demonstrate out-of-bounds exception
        std::cout << "\nAttempting to access an invalid index:" << std::endl;
        std::cout << mat2(3, 0) << std::endl;  // Invalid access, will throw an exception

    }
    catch (MatrixException& e) {
        std::cerr << "Error: " << e.what() << std::endl;  // Catch and display custom exception
    }

    return 0;
}

```
