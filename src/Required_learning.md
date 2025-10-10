# APUE Reference for Snake Game Implementation

This document maps **APUE chapters and sections** to the key parts of implementing a terminal-based Snake game in C++.

---

## 1️⃣ Terminal I/O & Non-blocking input

**Goal:** Capture user input (WASD or arrow keys) without blocking the game loop.

**APUE Reference:**  
- **Chapter 7: Terminal I/O**  
  - Section: *Terminal Attributes (`termios`)*  
    - `struct termios`  
    - `tcgetattr()`, `tcsetattr()`  
    - Disabling canonical mode (`ICANON`)  
    - Disabling echo (`ECHO`)  
  - Section: *File Status Flags (`fcntl`)*  
   - `O_NONBLOCK` for non-blocking input  

**Usage in Snake Game:**  
- Put terminal into raw/non-canonical mode for real-time key capture.  
- Use `fcntl()` to make `stdin` non-blocking.  
- Map keys to update `SnakeDir`.

---

## 2️⃣ Process Control & Sleep

**Goal:** Create a game loop with a timed delay to animate the snake.

**APUE Reference:**  
- **Chapter 6: Process Control**  
  - Section: *Sleep functions*  
    - `sleep()`, `usleep()`, `nanosleep()`  

**Usage in Snake Game:**  
- Add `usleep(200000)` in your game loop to slow down the snake movement so you can see it.

---

## 3️⃣ Signals (Optional but Useful)

**Goal:** Handle Ctrl+C or window resize gracefully.

**APUE Reference:**  
- **Chapter 10: Signals**  
  - `signal()`, `sigaction()`  

**Usage in Snake Game:**  
- Optional: Use for clean exit or pause/resume.

---

## 4️⃣ Memory Management

**Goal:** Snake as a linked list.

**APUE Reference:**  
- **Chapter 2: File I/O and System Calls**  
  - `malloc()`, `free()` and pointers (or `new`/`delete` in C++)  
  - Managing dynamic memory safely  

**Usage in Snake Game:**  
- Each snake segment is a dynamically allocated node.  
- Properly delete the tail to prevent memory leaks.

---

## 5️⃣ File Descriptors & Standard I/O

**Goal:** Understand `stdin` as a file descriptor for input.

**APUE Reference:**  
- **Chapter 3: I/O**  
  - Standard file descriptors (`STDIN_FILENO`)  
  - `read()` system call (can be used instead of `getchar()` for more control)  

**Usage in Snake Game:**  
- Use `STDIN_FILENO` with `read()` or `getchar()` in non-blocking mode to detect key presses.

