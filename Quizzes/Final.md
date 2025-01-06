# OOP345 Fall 2024 – Final Key

## Part A: Short Answer (15%)

###  1.	Explain the difference between std::string and std::string_view. Under what circumstances would you choose one over the other? (5 marks)
**std::string:** A mutable string that manages its own memory. Used when you need to modify the string or own its contents.
#### **std::string_view:** A lightweight, non-owning view into a string's data. Used when you want to read string data without copying or modifying it, especially for performance-critical code.
#### **When to choose:**
- Use std::string when ownership or mutability is needed.
- Use std::string_view for read-only access to avoid unnecessary allocations or copying.


### 2.	Define RAII (Resource Acquisition Is Initialization). Provide an example of how it is used in modern C++. (5 marks)
RAII is a programming idiom where resource management (e.g., memory, file handles) is tied to object lifetime. Resources are acquired in the constructor and released in the destructor.
```cpp
#include <iostream>
#include <fstream>

class FileHandler {
public:
    FileHandler(const std::string& filename) : file(filename) {
        if (!file.is_open()) throw std::runtime_error("Failed to open file");
    }
    ~FileHandler() { file.close(); }
private:
    std::ofstream file;
};

int main() {
    try {
        FileHandler fh("example.txt");
        // File automatically closed at the end of scope
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
```

### 3. 	What is the purpose of std::variant? How does std::bad_variant_access relate to it? Provide an example. (5 marks)
**std::variant** is a type-safe union for storing multiple types. It ensures only one of its alternatives is active at any time.
#### **std::bad_variant_access:** Thrown when accessing the wrong type.
```cpp
#include <iostream>
#include <variant>

int main() {
    std::variant<int, std::string> v = "Hello";
    try {
        std::cout << std::get<int>(v) << "\n"; // Error: wrong type
    } catch (const std::bad_variant_access& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
```



## Part B: Debugging (25%)

 Analyze the following code snippet. Identify and explain the errors according to the C++17 standard and provide corrections. Your explanations should cover why each identified error is problematic and how your corrections address these issues, ensuring adherence to good memory management and object-oriented design principles. You can point out in the code and/or write about it in the answer section with the fix.
There are up to 5 errors in the code. 


```cpp
#include <iostream>
#include <variant>
#include <vector>
#include <algorithm>
#include <memory>
#include <thread>
#include <future>
#include <functional>

void funcA() {
    std::variant<int, std::string> v = 10;
    try {
        std::cout << std::get<std::string>(v) << "\n";
    } catch (const std::bad_variant_access& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void funcB() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::vector<int> filtered;
    std::copy_if(vec.begin(), vec.end(), filtered.begin(), [](int n) { return n % 2 == 0; });
}

void funcC() {
    std::unique_ptr<int> p = std::make_unique<int>(42); // returns a std::unique_ptr
    std::unique_ptr<int> q = p;
    std::cout << *q << "\n";
}

void funcD() {
    std::promise<int> prm;
    auto fut = prm.get_future();

    std::thread t([&prm]() {
        prm.set_value(42);
    });
    prm.set_value(100);
    t.join();

    std::cout << "Future result: " << fut.get() << "\n";
}

void funcE() {
    auto task = std::packaged_task<int()>([]() {
        return 42;
    });

    std::future<int> fut = std::async(std::launch::async, std::move(task));
    std::cout << "Result: " << fut.get() << "\n";
}

int main() {
    funcA();
    funcB();
    funcC();
    funcD();
    funcE();
    return 0;
}
```
## Answers:

1. ```std::get<std::string>(v) in funcA:```
- Error: Accessing an inactive variant alternative.
- Fix: Ensure correct type access: 
```std::cout << std::get<int>(v) << "\n";```

2. ```filtered.begin() in funcB:```
- Error: filtered is empty, causing undefined behavior.
- Fix: Create with a size to the filtered: 
```std::vector<int> filtered(5);```



3. ```std::unique_ptr ownership transfer in funcC:```
- Error: p is moved into q, leading to a double-deletion attempt.
- Fix: Use std::move: 
```std::unique_ptr<int> q = std::move(p);```


4. ```prm.set_value(100) in funcD:```
- Error: Cannot set a promise value multiple times.
- Fix: Remove the second set_value call.


5. ```std::async with std::packaged_task in funcE:```
- Error: Incorrect usage of std::packaged_task.
-	Fix: Execute the task explicitly.

```cpp
 auto task = std::packaged_task<int()>([]() { return 42; });
std::future<int> fut = task.get_future();
task(); // Explicitly execute the task
```

## Part C: Walkthrough (20%)
### Predict the output (14 lines) of the provided C++ code.

```cpp
#include <iostream>
#include <vector>

#define CALC(a, b) ((a) * (b))

#ifndef VAL
#define VAL 10
#endif

#if VAL > 5
    #define MSG "VAL is greater than 5"
#else
    #define MSG "VAL is 5 or less"
#endif

class A {
public:
    virtual void f() {
        std::cout << "A::f\n";
    }
};

class B {
public:
    virtual void f() {
        std::cout << "B::f\n";
    }
};

class C : public virtual A, public virtual B {
public:
    void f() override {
        std::cout << "C::f\n";
    }
};

    struct Node {
        int val;
        Node* nxt;
    };

int main() {
    int m = CALC(2 + 3, 4 + 5);
    std::cout << "Macro result: " << m << "\n";

    std::cout << MSG << "\n";

    #if VAL == 10
        std::cout << "Directive: VAL is 10\n";
    #else
        std::cout << "Directive: VAL is not 10\n";
    #endif

    int d[3] = {1, 2, 3};
    int* pd = d;
    std::cout << "Pointer to array: " << *pd << "\n";

    int md[2][2] = {{1, 2}, {3, 4}};
    int (*pmd)[2] = md;
    std::cout << "Multi-array element: " << pmd[1][1] << "\n";

    C obj;
    A* pa = &obj;
    B* pb = &obj;
    pa->f();
    pb->f();
    obj.f();

    int v1 = 5;
    int v2 = 3;
    std::cout << "AND: " << (v1 & v2) << "\n";
    std::cout << "OR: " << (v1 | v2) << "\n";
    std::cout << "XOR: " << (v1 ^ v2) << "\n";
    std::cout << "Shift left: " << (v1 << 2) << "\n";
    std::cout << "Shift right: " << (v2 >> 1) << "\n";


    Node* h = new Node{1, nullptr};
    Node* s = new Node{2, nullptr};
    h->nxt = s;

    std::cout << "Linked List: " << h->val << " -> " << h->nxt->val << "\n";

    delete h;
    delete s;

    return 0;
}
```
### OUTPUT: 
```
Macro result: 45
VAL is greater than 5
Directive: VAL is 10
Pointer to array: 1
Multi-array element: 4
C::f
C::f
C::f
AND: 1
OR: 7
XOR: 6
Shift left: 20
Shift right: 1
Linked List: 1 -> 2

```
---

## Part D: Programming (40%)

You are required to implement a basic task scheduler using container adapters, standard algorithms, and smart pointers. The scheduler will:
1.	Accept a series of tasks, each defined by a name (string) and a duration in seconds (integer). Use a container adapter (e.g., std::queue) to store the tasks. (4 marks)
2.	Sort tasks based on their duration in ascending order using an STL algorithm. (4 marks)
3.	Implement and use smart pointers (e.g., std::unique_ptr) to manage task objects dynamically.       (4 marks)
4.	Include the use of std::transform to preprocess task names (e.g., converting all names to uppercase). (4 marks)
5.	Execute the tasks sequentially, printing their names in the order they are executed. (4 marks)
6.	Track the total time elapsed using a std::accumulate operation. (4 marks)
7.	Handle invalid operations gracefully. (4 marks)
8.	Use a RAII mechanism to manage a resource during task execution. (4 marks)
9.	Ensure that your program is with at least two classes:
    - Task: Encapsulates a task's details. (4 marks)
    - TaskScheduler: Manages the tasks and their execution. (4 marks)


## One way to write it:


```cpp
#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
#include <memory>
#include <numeric>

class Task {
    std::string name;
    int duration;

public:
    Task(const std::string& taskName, int taskDuration) : name(taskName), duration(taskDuration) {}
    const std::string& getName() const { return name; }
    int getDuration() const { return duration; }
    void toUpperCase() {
        std::transform(name.begin(), name.end(), name.begin(), [](char c) {
            return c >= 'a' && c <= 'z' ? c - ('a' - 'A') : c; // can be pseudocode
        });
    }
};

class TaskScheduler {
    std::queue<std::unique_ptr<Task>> tasks;

public:
    void addTask(const std::string& name, int duration) {
        if (duration > 0)
            tasks.push(std::make_unique<Task>(name, duration));
    }

    void executeTasks() {
        std::vector<int> durations;
        while (!tasks.empty()) {
            auto& task = tasks.front();
            task->toUpperCase();
            std::cout << "Executing: " << task->getName() << " (" << task->getDuration() << "s)\n";
            durations.push_back(task->getDuration());
            tasks.pop();
        }
        int totalTime = std::accumulate(durations.begin(), durations.end(), 0);
        std::cout << "Total time: " << totalTime << "s\n";
    }
};

int main() {
    TaskScheduler scheduler;
    scheduler.addTask("Clean", 5);
    scheduler.addTask("Code", 10);
    scheduler.addTask("Exercise", 3);
    scheduler.executeTasks();
    return 0;
}
```
