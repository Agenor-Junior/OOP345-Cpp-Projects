
# C++ Quiz – Smart Pointers, STL, and File Handling

### Question 1
**Which smart pointer automatically deallocates memory when the last reference to the object is destroyed?**  
**Correct Answer:**  
**C. std::shared_ptr**  
`std::shared_ptr` uses reference counting and deallocates memory when the last reference is destroyed.

---

### Question 2
**What's the output?**  

```cpp
list<int> lst = {1, 2, 3};
auto it = lst.begin();
lst.push_front(4);
cout << *it;
```

**Correct Answer:**  
**A. Undefined behavior**  
`push_front` invalidates the iterator, so dereferencing it leads to undefined behavior.

---

### Question 3
**Which of the following is not a library included in the algorithms category of the C++ STL?**  
**Correct Answer:**  
**C. iostream**  
`iostream` is part of the I/O stream library, not the algorithms category.

---

### Question 4
**Consider this code. What’s wrong with it?**  

```cpp
void processFile() {
    ifstream file("data.txt");
    if(!file)
        return;
    // Process file
}
```

**Correct Answer:**  
**B. Missing error handling for file operations**  
Although the file will be closed when `ifstream` goes out of scope, the code lacks proper error handling for file reading or processing.

---

### Question 5
**What is the issue in the following code?**  

```cpp
#include <memory>

int main() {
    std::shared_ptr<int> sp1(new int(10));
    std::shared_ptr<int> sp2(sp1.get());
    return 0;
}
```

**Correct Answer:**  
**D. Double deletion**  
`sp2` takes raw pointer ownership without knowing `sp1` already manages the object. This leads to double deletion when both smart pointers go out of scope.

---

### Question 6
**What will be the output of the following code?**  

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto it = std::find(v.begin(), v.end(), 3);
    if (it != v.end()) *it = 10;
    for (int i : v) std::cout << i << " ";
    return 0;
}
```

**Correct Answer:**  
**C. 1 2 10 4 5**  
`std::find` locates 3 and replaces it with 10. The modified vector is printed.

---

### Question 7
**What is the main issue with raw pointers?**  
**Correct Answer:**  
**C. Memory leaks and dangling pointers**  
Raw pointers can lead to memory leaks and dangling pointers if not managed correctly.

---

### Question 8
**Which statement about std::unique_ptr is FALSE?**  
**Correct Answer:**  
**D. Multiple unique_ptrs can share ownership of the same object**  
`std::unique_ptr` enforces unique ownership. Sharing ownership is the role of `std::shared_ptr`.

---

### Question 9
**What does the algorithms category of the C++ STL provide?**  
**Correct Answer:**  
**B. Common programming solutions that operate on ranges of elements**  
The STL algorithms provide solutions to operate on ranges of elements.

---

### Question 10
**Which of the following file open modes is used for appending content to an existing file?**  
**Correct Answer:**  
**B. std::ios::app**  
`std::ios::app` opens a file in append mode, adding content to the end of the file.

---

### Question 11
**Which algorithm would you use to find the first occurrence of an element in a container?**  
**Correct Answer:**  
**C. std::find**  
`std::find` searches for the first occurrence of an element in a container.

---

### Question 12
**When is the use of raw pointers preferred over smart pointers?**  
**Correct Answer:**  
**C. When interfacing with C libraries**  
Raw pointers are sometimes necessary for interoperability with C libraries.

---

### Question 13
**How does std::shared_ptr manage memory?**  
**Correct Answer:**  
**A. Reference counting**  
`std::shared_ptr` uses reference counting to manage memory.

---

### Question 14
**Which STL algorithm modifies the sequence in-place when the destination range is the same as source?**  
**Correct Answer:**  
**B. std::transform**  
`std::transform` modifies the sequence in-place if the destination range is the same as the source.
