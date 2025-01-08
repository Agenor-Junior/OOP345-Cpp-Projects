# C++ Quiz – Header Guards, Macros, and Threading

### Question 1
**How can you prevent multiple inclusions of a header?**  
**Correct Answer:**  
**A. Both #pragma once and #ifndef**  
Both `#pragma once` and `#ifndef` can prevent multiple inclusions, ensuring the header is processed only once.

---

### Question 2
**In which scenario is a function macro potentially dangerous?**  

```cpp
#define SQUARE(x) x * x
```

**Correct Answer:**  
**D. Unexpected precedence**  
The macro expands without parentheses, leading to incorrect evaluations like `SQUARE(2 + 3)` becoming `2 + 3 * 2 + 3 = 11` instead of `25`.

---

### Question 3
**Which keyword is used to resolve ambiguity in the diamond problem?**  
**Correct Answer:**  
**C. virtual**  
The `virtual` keyword ensures proper inheritance and prevents multiple copies of the base class in the inheritance hierarchy.

---

### Question 4
**Given int arr[5], what's true about pointer arithmetic?**  

```cpp
int* ptr = arr;
ptr += 2;
```

**Correct Answer:**  
**B. ptr points to 3rd element**  
`ptr += 2` advances by `2 * sizeof(int)`, so `ptr` now points to `arr[2]`, the third element.

---

### Question 5
**What is the primary purpose of std::async?**  
**Correct Answer:**  
**A. Launch an asynchronous task**  
`std::async` launches an asynchronous task that runs in a separate thread.

---

### Question 6
**What's wrong with this thread code?**  

```cpp
void worker() { /* some work */ }
std::thread t(worker);
t.join();
t.join(); // Second join
```

**Correct Answer:**  
**A. Throws exception**  
A thread can only be joined once. The second `join()` call throws a `std::system_error`.

---

### Question 7
**What is the purpose of a nullptr in a linked list implementation?**  
**Correct Answer:**  
**B. To indicate the end of the list**  
`nullptr` is used to indicate the end of a linked list.

---

### Question 8
**What does bitwise left shift `<<` do?**  
**Correct Answer:**  
**C. Multiply by power of 2**  
`x << n` shifts `x` left by `n` bits, equivalent to multiplying by `2^n`.

---

### Question 9
**What’s the result of `5 & 3`?**  
**Correct Answer:**  
**A. 1**  
**Explanation:**  
- `5` in binary: `101`  
- `3` in binary: `011`  
- `5 & 3` performs a bitwise AND: `101 & 011 = 001` → `1`

---

### Question 10
**What does packaged_task primarily do?**  
**Correct Answer:**  
**C. Wrap callable object for async execution**  
`packaged_task` wraps a callable object and allows asynchronous execution.

---

### Question 11
**What is the time complexity of inserting an element at the head of a singly linked list?**  
**Correct Answer:**  
**D. O(1)**  
Insertion at the head only requires updating a pointer, making it constant time `O(1)`.

---

### Question 12
**What happens in this multithreading scenario?**  

```cpp
std::promise<int> p;
std::future<int> f = p.get_future();
p.set_value(42);
cout << f.get();
```

**Correct Answer:**  
**D. Prints 42**  
`std::promise` sets a value, and `std::future` retrieves it with `f.get()`, resulting in `42` being printed.
