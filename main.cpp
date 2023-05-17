#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

enum CHOICE {
    ADD = 1,
    VIEW_TASKS = 2,
    COMPLETE_TASK = 3,
    DELETE_TASK = 4,
    QUIT_TASK_MANAGER = 5
};

struct Task {
    int id;
    std::string title;
    std::string description;
    bool completed;

    Task(int id, const std::string& title, const std::string& description)
        : id(id), title(title), description(description), completed(false) {}
};

class TaskManager {
public:
   
    void addTask(const std::string& title, const std::string& description) {
        tasks.push_back(Task(nextId++, title, description));
    }

    void deleteTaskById(int id) {
        auto it = std::find_if(tasks.begin(), tasks.end(),
            [id](const auto& task) { return task.id == id; });

        if (it != tasks.end()) {
            tasks.erase(it);
        }
    }

    void completeTask(int id) {
        auto it = std::find_if(tasks.begin(), tasks.end(),
            [id](const auto& task) { return task.id == id; });

        if (it != tasks.end()) {
            it->completed = true;
        }
    }

    std::vector<Task> getAllTasks() const {
        return tasks;
    }

private:
    std::vector<Task> tasks;
    int nextId = 1;
};

std::string getUserInput(const std::string& prompt) {
    std::string input;

    std::cout << prompt;
    std::getline(std::cin, input);

    return input;
}

void printTaskList(const std::vector<Task>& taskList) {
    for (const auto& task : taskList) {
        std::cout << "ID: " << task.id << std::endl;
        std::cout << "Title: " << task.title << std::endl;
        std::cout << "Description: " << task.description << std::endl;
        std::cout << "Status: " << (task.completed ? "Completed" : "Not completed") << std::endl << std::endl;
    }
}

int main() {
    TaskManager taskManager;
   
    while (true) {

        std::cout << "Select an option:" << std::endl;
        std::cout << "1. Add new task" << std::endl;
        std::cout << "2. View task list" << std::endl;
        std::cout << "3. Complete task" << std::endl;
        std::cout << "4. Delete task" << std::endl;
        std::cout << "5. Quit" << std::endl;

        int choice = std::stoi(getUserInput("Enter your choice: "));

        switch (choice) {
        case ADD: { 
            std::string title = getUserInput("Enter task title: ");
            std::string description = getUserInput("Enter task description: ");

            taskManager.addTask(title, description);
            std::cout << "Task added successfully!" << std::endl;

            break;
        }
        case VIEW_TASKS: { 
            auto taskList = taskManager.getAllTasks();

            if (taskList.empty()) {
                std::cout << "No tasks found." << std::endl;
            }
            else {
                printTaskList(taskList);
            }

            break;
        }
        case COMPLETE_TASK: {
            int taskId = std::stoi(getUserInput("Enter task ID: "));
            taskManager.completeTask(taskId);
            std::cout << "Task marked as completed." << std::endl;

            break;
        }
        case DELETE_TASK: { 
            int taskId = std::stoi(getUserInput("Enter task ID: "));
            taskManager.deleteTaskById(taskId);
            std::cout << "Task deleted successfully." << std::endl;

            break;
        }
        case QUIT_TASK_MANAGER:
            std::cout << "Goodbye!" << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}