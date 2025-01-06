# C++ Programming Quiz - Answers and Explanations

### Question 1
**What is a pointer type in C++?**  

**Correct Answer:**  
**B. A type that holds an address as its value**  

A pointer stores the memory address of another variable, allowing indirect access to the value stored at that address.  

---

### Question 2
**What are the three distinct stages involved in transforming the original source code of a C++ application into a binary executable?**  

**Correct Answer:**  
**B. Pre-Processing, Compilation, Linking**  

- **Pre-Processing:** Handles macros, includes, and conditional compilation.  
- **Compilation:** Translates the source code to object files.  
- **Linking:** Combines object files to produce an executable.  

---

### Question 3
**What is the purpose of the constexpr keyword in C++?**  

**Correct Answer:**  
**B. To declare a constant expression that can be evaluated at compile time**  

`constexpr` ensures that a variable or function can be evaluated at compile time, improving performance and enabling safer code.  

---

### Question 4
**What does the static_assert() mechanism do in C++?**  

**Correct Answer:**  
**D. Generates a custom compiler error message if a specified condition is not met**  

`static_assert` allows checks at compile time, which helps catch errors early without running the program.  

---

### Question 5
**What’s wrong with the following main function that intends to print the first command-line argument?**  

```cpp
int main() {
    std::cout << argv[1] << std::endl;
    return 0;
}
```

**Correct Answer:**  
Missing `#include <iostream>`. The main function should also be defined as:  

```cpp
#include <iostream>
int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::cout << argv[1] << std::endl;
    }
    return 0;
}
```

---

### Question 6
**What’s missing in the following code that prevents `globalVar` from being accessed in file2.cpp?**  

**file1.cpp**  
```cpp
int globalVar = 10;
```

**file2.cpp**  
```cpp
void printGlobal() {
    std::cout << globalVar << std::endl;
}
```

**Correct Answer:**  
Add `extern int globalVar;` in file2.cpp.  

```cpp
extern int globalVar;
void printGlobal() {
    std::cout << globalVar << std::endl;
}
```

---

### Question 7
**What’s incorrect about the following attempt to create a local variable with program lifetime?**  

```cpp
void function() {
    static int counter = 0;
    counter++;
    std::cout << counter << std::endl;
}

int main() {
    for (int i = 0; i < 5; i++) {
        function();
    }
    std::cout << counter << std::endl;
    return 0;
}
```

**Correct Answer:**  
The `counter` variable is declared inside the `function()`, and cannot be accessed in `main()`. Remove `std::cout << counter` from `main()` or declare `counter` globally.  

---

### Question 8
**What potential issue exists in the following class definition?**  

```cpp
class ResourceManager {
private:
    int* data;
public:
    ResourceManager() {
        data = new int[100];
    }
    ~ResourceManager() {
        delete data;
    }
};
```

**Correct Answer:**  
`delete` should be `delete[]` to properly free the allocated array.  

```cpp
~ResourceManager() {
    delete[] data;
}
```

---

### Question 9
**Determine the output of the program when it's compiled and run with the command:**  

```bash
./program_name test_arg
```

**Code Breakdown**  

**File: main.cpp**  
```cpp
#include "resource.h"
#include <iostream>

extern int globalCounter;

void incrementGlobal() {
    static int localCounter = 0;
    localCounter++;
    globalCounter += localCounter;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::cout << "Argument: " << argv[1] << std::endl;
    }

    for (int i = 0; i < 3; i++) {
        incrementGlobal();
    }

    Resource r1(5);
    Resource r2 = r1;

    std::cout << "Global: " << globalCounter << std::endl;
    return 0;
}
```

**File: resource.h**  
```cpp
#ifndef RESOURCE_H
#define RESOURCE_H

class Resource {
private:
    int* data;
    static int resourceCount;

public:
    Resource(int size);
    Resource(const Resource& other);
    ~Resource();
};

#endif
```

**File: resource.cpp**  
```cpp
#include "resource.h"
#include <iostream>

int Resource::resourceCount = 0;

Resource::Resource(int size) : data(new int[size]) {
    resourceCount++;
    std::cout << "Resource created. Count: " << resourceCount << std::endl;
}

Resource::Resource(const Resource& other) : data(new int[*other.data]) {
    resourceCount++;
    std::cout << "Resource copied. Count: " << resourceCount << std::endl;
}

Resource::~Resource() {
    delete[] data;
    resourceCount--;
    std::cout << "Resource destroyed. Count: " << resourceCount << std::endl;
}
```

**File: global.cpp**  
```cpp
int globalCounter = 10;
```

**Expected Output:**  
```yaml
Argument: test_arg
Resource created. Count: 1
Resource copied. Count: 2
Global: 16
```
