/*
============================================
 TODO CLI Application - C++ Implementation
============================================

 Description:
   A simple command-line TODO list manager
   built in C++ that allows users to:
     - Add new tasks
     - View all tasks
     - Edit task descriptions
     - Toggle completion status
     - Delete tasks
   All tasks are stored in a local text file
   for persistent storage across sessions.

 Author:  Eric Zimmer
 Created: June 14, 2025
 
 File Format:
   tasks.txt stores each task in the format:
   id|description|completed
   Example:
   1|Take out trash|0
   2|Finish C++ project|1

 Compilation:
   clang++ -std=c++17 -o todoapp CPPCLITODO.cpp

 Usage:
   ./todoapp

 Requirements:
   - C++17 or higher
   - Cross-platform (Linux, macOS, Windows)

============================================
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class Task {
private:
    static int nextId;
    int id;
    std::string description;
    bool completed;

public:
    // Constructor with initializer list
    Task(const std::string& description)
        : id(nextId++), description(description), completed(false) {}

    // Getters
    static int getNextId() {
        return nextId;
    }
    int getId() const {
        return id;
    }
    const std::string& getDescription() const {
        return description;
    }
    bool isCompleted() const {
        return completed;
    }

    // Setters
    static void setNextId(int id) {
        nextId = id;
    }
    void setId(int id) {
        this->id = id;
    }
    void setDescription(const std::string& description) {
        this->description = description;
    }
    void setCompleted(bool completed) {
        this->completed = completed;
    }
};


/*
====== Function declarations ======
*/
void printMenu();
int getMenuInput();
void addTask(std::vector<Task>& tasks);
void viewTasks(const std::vector<Task>& tasks);
void toggleTaskComplete(std::vector<Task>& tasks);
void deleteTask(std::vector<Task>& tasks);
void editTask(std::vector<Task>& tasks);
void loadTasksFromFile(std::vector<Task>& tasks);
void saveTasksToFile(const std::vector<Task>& tasks);


// Tracks auto-increment id for tasks
int Task::nextId = 1;
const std::string TASKS_FILE = "tasks.txt";


int main() {
    // Vector to store tasks
    std::vector<Task> tasks;
    loadTasksFromFile(tasks);

    while (true) {
        // Get menu input
        int menuInput = getMenuInput();
        
        switch(menuInput) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                toggleTaskComplete(tasks);
                break;
            case 4:
                deleteTask(tasks);
                break;
            case 5:
                editTask(tasks);
                break;
            case 6:
                std::cout << "Exiting... " << std::endl;
                return 0;
        }
    }

    return 0;
}


void printMenu() {
    /*
    This function prints the menu.
    */
    std::cout << "====== TODO MENU ======" << std::endl;
    std::cout << "1. Add a task\n"
    "2. View all tasks\n"
    "3. Toggle task as complete/incomplete\n"
    "4. Delete a task\n"
    "5. Edit a task description\n"
    "6. Exit" << std::endl;
    std::cout << "=======================\n";
}


int getMenuInput() {
    /*
    This function gets the input for the menu options and returns it.
    */
    while (true) {
        printMenu();
        int choice;
        if (std::cin >> choice && choice >= 1 && choice <= 6) {
            return choice;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
        }
    }
}


void addTask(std::vector<Task>& tasks) {
    /*
    This function creates a new task object and adds it to the task vector.
    */
    std::cin.ignore(); // Clear newline from previous input
    std:: string description;
    std::cout << "Enter task description: ";
    std::getline(std::cin, description); // Get input

    Task newTask(description); // Create new task object
    tasks.push_back(newTask); // Add new task to tasks vector

    std::cout << "Task added.\n" << std::endl; // Confirm message
    saveTasksToFile(tasks);
}


void viewTasks(const std::vector<Task>& tasks) {
    /*
    This function prints all of the tasks from the tasks vector.
    */
   // Check if there are tasks.
    if (tasks.empty()) {
        std::cout << "No tasks to display.\n";
        return;
    }

    // Print the tasks from tasks vector
    std::cout << "\n====== TASK LIST ======\n";
    for (const Task& task : tasks) {
        std::cout << "[" << (task.isCompleted() ? "x" : " ") << "] "
                  << task.getId() << ": " << task.getDescription() << "\n";
    }
    std::cout << "=======================\n" << std::endl;
}


void toggleTaskComplete(std::vector<Task>& tasks) {
    /*
    This function toggles a task as complete/incomplete.
    */
   // Check for empty tasks vector
    if (tasks.empty()) {
        std::cout << "No tasks to toggle.\n";
        return;
    }

    // Print current tasks
    std::cout << "\nCurrent tasks:\n";
    for (const Task& task : tasks) {
        std::cout << "[" << (task.isCompleted() ? "x" : " ") << "] "
                  << task.getId() << ": " << task.getDescription() << "\n";
    }

    std::cout << std::endl;

    // Get ID of task to toggle
    int id;
    std::cout << "Enter the ID of the task to toggle completion: ";
    if (!(std::cin >> id)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input.\n";
        return;
    }

    // Iterator through tasks until we found the correct task
    for (Task& task : tasks) {
        if (task.getId() == id) {
            // Toggle complete
            task.setCompleted(!task.isCompleted());
            // Confirm message
            std::cout << "Task " << id << " marked as "
                      << (task.isCompleted() ? "complete." : "incomplete.") << "\n" << std::endl;
            // Save to file
            saveTasksToFile(tasks);
            return;
        }
    }

    // Unable to find task with given ID
    std::cout << "Task with ID " << id << " not found.\n" << std::endl;
}


void deleteTask(std::vector<Task>& tasks) {
    /*
    This function deletes a task from the tasks vector.
    */
   // Check for empty tasks vector
    if (tasks.empty()) {
        std::cout << "No tasks to delete.\n";
        return;
    }

    // Print all tasks
    std::cout << "\nCurrent tasks:\n";
    for (const Task& task : tasks) {
        std::cout << "[" << (task.isCompleted() ? "x" : " ") << "] "
                  << task.getId() << ": " << task.getDescription() << "\n";
    }

    // Get id of the task to delete
    int id;
    std::cout << "Enter the ID of the task to delete: ";
    if (!(std::cin >> id)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input.\n";
        return;
    }

    // User iterator to remove the task from the tasks vector
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->getId() == id) {
            tasks.erase(it);
            std::cout << "Task " << id << " deleted.\n" << std::endl;
            saveTasksToFile(tasks);
            return;
        }
    }

    // Unable to find task with given ID
    std::cout << "Task with ID " << id << " not found.\n" << std::endl;
}


void editTask(std::vector<Task>& tasks) {
    /*
    This function edits the description of an existing task.
    */
    // Check if there are any tasks
    if (tasks.empty()) {
        std::cout << "No tasks to edit.\n";
        return;
    }

    // Display current tasks
    std::cout << "\nCurrent tasks:\n";
    for (const Task& task : tasks) {
        std::cout << "[" << (task.isCompleted() ? "x" : " ") << "] "
                  << task.getId() << ": " << task.getDescription() << "\n";
    }

    std::cout << std::endl;

    // Get task ID
    int id;
    std::cout << "Enter the ID of the task to edit: ";
    if (!(std::cin >> id)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input.\n";
        return;
    }

    // Look for the task with the given ID
    for (Task& task : tasks) {
        if (task.getId() == id) {
            std::cin.ignore(); // Clear newline from previous input
            std::string newDesc;
            std::cout << "Enter new description: ";
            std::getline(std::cin, newDesc);

            task.setDescription(newDesc);
            std::cout << "Task " << id << " updated.\n" << std::endl;
            saveTasksToFile(tasks); // Save updated tasks
            return;
        }
    }

    // Task ID not found
    std::cout << "Task with ID " << id << " not found.\n" << std::endl;
}


void loadTasksFromFile(std::vector<Task>& tasks) {
    /*
    This function loads the tasks from the TASKS_FILE file.
    Each task is expected to be in the format: id|description|completed
    */
   // Open file for reading
    std::ifstream file(TASKS_FILE);
    // Exit if the file cannot be opened
    if (!file.is_open()) return;

    std::string line;
    // Read each line from the file
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, desc, completedStr;

        // Split line into id, description, and completed
        if (std::getline(ss, idStr, '|') &&
            std::getline(ss, desc, '|') &&
            std::getline(ss, completedStr)) {

            int id = std::stoi(idStr); // Convert id string to int
            bool completed = (completedStr == "1"); // Convert completed to bool

            Task task(desc); // Create task
            task.setCompleted(completed); // Set completed
            task.setId(id); // Set ID

            tasks.push_back(task); // Add task to vector

            // Update Task::nextId to avoid collisions
            if (id >= Task::getNextId()) 
                Task::setNextId(id + 1);
        }
    }

    file.close();
}


void saveTasksToFile(const std::vector<Task>& tasks) {
    /*
    This function saves the tasks to the TASKS_FILE file.
    */
    std::ofstream file(TASKS_FILE);
    // Write each task to file
    for (const Task& task : tasks) {
        file << task.getId() << "|" << task.getDescription() << "|"
             << (task.isCompleted() ? "1" : "0") << "\n";
    }
    file.close();
}