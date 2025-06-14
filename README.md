# C++ Command-Line TODO App

A simple command-line TODO list application written in C++. It allows you to create, view, edit, delete, and toggle completion of tasks, with all data saved to a local `tasks.txt` file for persistence.

---

## Features

- Add new tasks with descriptions
- View all tasks with status indicators
- Toggle tasks as complete or incomplete
- Delete tasks by ID
- Edit task descriptions
- Automatically saves and loads tasks from a file (`tasks.txt`)
- Auto-increments unique task IDs to prevent duplication

---

## How It Works

- All tasks are stored in a `std::vector<Task>`
- Each `Task` has:
  - a unique ID
  - a description
  - a completed flag (`true` or `false`)
- Tasks are saved in the format:

```
id|description|completed
```

---

## File Persistence

- On startup, tasks are loaded from `tasks.txt` (if it exists)
- Every change (add/edit/delete/toggle) automatically updates the file
- Format example:

```
1|Take out trash|0
2|Finish C++ project|1
```

---

## Usage

1. Clone the repo or copy the `.cpp` file
2. Compile with a C++ compiler (e.g. `clang++` or `g++`)

```bash
clang++ -std=c++17 -o todoapp CPPCLITODO.cpp
./todoapp
```

3.  Follow the on-screen menu prompts

## Screenshot
![Screenshot of TODO CLI App](screenshot.png)
