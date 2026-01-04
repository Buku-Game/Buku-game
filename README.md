# BUKU – Board Game Implementation in C (Initial Phase)

## 📌 Project Status
⚠️ **This project is in its initial development phase.**  
The current version focuses on defining the core data structures (TADs) and basic graphical visualization. Game rules, interactions, and full gameplay mechanics are still under development.

---

## 🎮 About the Project
This project is an academic implementation of the board game **BUKU**, developed in **C**, following strict requirements defined by the course instructor.

The main goal is to apply **Abstract Data Types (TADs)**, specifically **stacks**, combined with a **dynamic square matrix**, to represent the game board.

🔗 Reference links:
- BoardGameGeek: https://boardgamegeek.com/boardgame/432205/buku  
- Mancala Wiki: https://mancala.fandom.com/wiki/Buku  
- Project presentation video: https://youtu.be/FRm-1zFcOr8  

---

## 🧠 Technical Requirements
- Language: **C**
- Data Structure:
  - Stack (Pilha) implemented as a **TAD**
  - Game board represented as a **dynamic square matrix of stacks**
- The board size must be configurable (NxN)
- **Use of AI-generated code is not allowed**
- Teams of up to **3 members**

---

## 🧩 Current Implementation (Initial Phase)
At this stage, the project includes:
- Stack implementation using linked lists
- Board initialization as a matrix of stacks
- Basic push/pop operations
- Simple graphical visualization using **raylib**
- Rendering of the top value of each stack on the board

⚠️ **Game rules, player turns, scoring system, and win conditions are not yet implemented.**

---

## 🗂 Project Structure
├── main.c # Main program and graphical loop
├── arquivo.h # Stack TAD definitions and prototypes
├── arquivo.c # Stack TAD implementation
└── README.md


---

## 🛠 Technologies & Libraries
- **C (ANSI C)**
- **raylib** (for graphical rendering)

---

## 👥 Team
- Arthur Gomes  
- Gilvan Peace  

---

## 📅 Next Steps
Planned future developments include:
- Implementation of official BUKU game rules
- Player interaction and turn control
- Stack movement logic
- Dynamic board resizing
- Improved graphical interface

---

## 📢 Notes
This repository is intended **strictly for educational purposes**.  
All development follows the academic integrity rules established by the instructor.

If you have questions, feel free to contact the team members.
