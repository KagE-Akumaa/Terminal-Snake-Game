# 🐍 Terminal Snake Game (C++)

A classic Snake game implemented entirely in **C++**, playable right in your terminal!  
Built from scratch — no external libraries used for rendering or input, just pure system programming with **termios** and **unistd** for real-time keyboard handling.

---

## 🎮 Features

- ✅ **Raw mode input** — real-time key detection without pressing Enter  
- ✅ **Smooth movement** — dynamic grid updates with instant redraws  
- ✅ **Food spawning** — random generation using `<random>`  
- ✅ **Score tracking** — shows your current score on screen  
- ✅ **Game over detection** — ends when the snake hits the wall or itself  
- ✅ **Cross-platform (Linux / macOS)** — runs in any POSIX-compatible terminal  

---

## 🧱 Tech Stack

- **Language:** C++17  
- **Core Libraries:** `<iostream>`, `<termios.h>`, `<unistd.h>`, `<fcntl.h>`, `<vector>`, `<random>`  
- **Environment:** Ubuntu (Terminal-based execution)  

---

## 🕹️ Controls

| Key | Action |
|-----|---------|
| `W` or `↑` | Move Up |
| `A` or `←` | Move Left |
| `S` or `↓` | Move Down |
| `D` or `→` | Move Right |
| `Q` | Quit Game |

---

## 🚀 How to Run

### 1️⃣ Clone the Repository
```bash
git clone https://github.com/KagE-Akumaa/Terminal-Snake-Game.git
cd Terminal-Snake-Game
