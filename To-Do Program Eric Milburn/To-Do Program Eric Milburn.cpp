#include <iostream>
#include <string>
using namespace std;

const int MAX_TASKS = 100; // Maximum number of tasks the list can hold

// Function Declarations
void ShowMenu();
void AddTask(string tasks[], int priorities[], bool completed[], int& taskCount);
void ViewTasks(const string tasks[], const int priorities[], const bool completed[], int taskCount);
void MarkCompleted(bool completed[], int taskCount);
void MarkAllCompleted(bool completed[], int& taskCount);
void SortTasksByPriority(string tasks[], int priorities[], bool completed[], int indices[], int taskCount);

int main() {
    // Arrays to store task descriptions, priorities, and completion status
    string tasks[MAX_TASKS];
    int priorities[MAX_TASKS];
    bool completed[MAX_TASKS] = { false };
    int taskCount = 0; // Keeps track of how many tasks have been stored

    string input;
    char choice;
    bool running = true;

    while (running) {
        ShowMenu(); // Display the menu options to the user
        getline(cin, input);

        if (input.length() != 1) {
            cout << "Invalid input. Please enter a single character option.\n";
            continue;
        }

        choice = input[0];

        // Perform action based on the users choice
        switch (choice) {
        case 'a':
        case 'A':
            AddTask(tasks, priorities, completed, taskCount);
            break;
        case 'v':
        case 'V':
            ViewTasks(tasks, priorities, completed, taskCount);
            break;
        case 'm':
        case 'M':
            MarkCompleted(completed, taskCount);
            break;
        case 'x':
        case 'X':
            MarkAllCompleted(completed, taskCount);
            break;
        case 'q':
        case 'Q':
            cout << "Exiting the program. Goodbye!\n";
            running = false;
            break;
        default:
            cout << "Invalid option. Try again.\n";
            break;
        }
    }

    return 0;
}

// Displays the main menu to the user
void ShowMenu() {
    cout << "\n--- To-Do List Menu ---\n";
    cout << "A - Add Task\n";
    cout << "V - View Tasks\n";
    cout << "M - Mark Task as Completed\n";
    cout << "X - Mark ALL Tasks as Completed and Reset\n";
    cout << "Q - Quit\n";
    cout << "Enter your choice: ";
}

// Adds a new task with description and priority
void AddTask(string tasks[], int priorities[], bool completed[], int& taskCount) {
    if (taskCount >= MAX_TASKS) {
        cout << "No more tasks can be added. The list is full.\n";
        return;
    }

    cout << "Enter a task description: ";
    getline(cin, tasks[taskCount]);

    cout << "Enter the task priority (1 = highest, 10 = lowest): ";
    cin >> priorities[taskCount];

    while (cin.fail() || priorities[taskCount] < 1 || priorities[taskCount] > 10) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a number between 1 and 10: ";
        cin >> priorities[taskCount];
    }
    cin.ignore();

    completed[taskCount] = false; // Set the task as not completed
    ++taskCount; // Increment the task count

    cout << "Task was added successfully.\n";
}

// Displays the remaining tasks sorted by priority
void ViewTasks(const string tasks[], const int priorities[], const bool completed[], int taskCount) {
    int indices[MAX_TASKS];
    for (int i = 0; i < taskCount; ++i) {
        indices[i] = i; // Initialize indices to current positions
    }

    // Sort indices based on the task priority
    SortTasksByPriority(const_cast<string*>(tasks), const_cast<int*>(priorities), const_cast<bool*>(completed), indices, taskCount);

    cout << "\n--- Tasks To-Do (sorted by priority) ---\n";
    for (int i = 0; i < taskCount; ++i) {
        int originalIndex = indices[i];
        if (!completed[originalIndex]) {
            cout << "Task ID #" << originalIndex << " | Priority " << priorities[originalIndex] << ": " << tasks[originalIndex] << "\n";
        }
    }
}

// Marks a task as completed based on user input
void MarkCompleted(bool completed[], int taskCount) {
    string input;
    int index;
    cout << "Enter the task number you would like to mark as completed (0 to " << taskCount - 1 << "): ";
    getline(cin, input);

    try {
        index = stoi(input);
        if (index >= 0 && index < taskCount) {
            completed[index] = true;
            cout << "Task has been marked as completed.\n";
        }
        else {
            cout << "Your input was out of range or invalid.\n";
        }
    }
    catch (...) {
        cout << "Invalid input. Please try again and enter a valid number.\n";
    }
}

// Marks all the current tasks as completed and resets task count
void MarkAllCompleted(bool completed[], int& taskCount) {
    for (int i = 0; i < taskCount; ++i) {
        completed[i] = true;
    }
    cout << "All tasks have been marked as completed. The task list has been reset.\n";
    taskCount = 0;
}

// Sorts the task indices based on their associated priorities using selection sort
void SortTasksByPriority(string tasks[], int priorities[], bool completed[], int indices[], int taskCount) {
    for (int i = 0; i < taskCount - 1; ++i) {
        for (int j = i + 1; j < taskCount; ++j) {
            if (priorities[indices[j]] < priorities[indices[i]]) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }
}
