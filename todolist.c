#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASK 100

struct Task {
    char description[100];
    char deadline[20];
};

void addTask() {
    FILE *file = fopen("tasks.txt", "a");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    struct Task newTask;
    printf("Enter task description: ");
    getchar();  // Consume newline
    fgets(newTask.description, sizeof(newTask.description), stdin);
    strtok(newTask.description, "\n"); // Remove newline character

    printf("Enter deadline (DD-MM-YYYY): ");
    scanf("%s", newTask.deadline);

    fprintf(file, "%s | %s\n", newTask.description, newTask.deadline);
    fclose(file);

    printf("Task added successfully!\n");
}

void viewTasks() {
    FILE *file = fopen("tasks.txt", "r");
    if (!file) {
        printf("No tasks found.\n");
        return;
    }

    struct Task task;
    printf("\nYour To-Do List:\n");
    printf("----------------------\n");

    while (fscanf(file, " %99[^|] | %19[^\n]\n", task.description, task.deadline) != EOF) {
        printf("Task: %s\nDeadline: %s\n", task.description, task.deadline);
        printf("----------------------\n");
    }
    fclose(file);
}

void deleteTasks() {
    FILE *file = fopen("tasks.txt", "w"); // Overwrites file
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    fclose(file);
    printf("All tasks deleted successfully!\n");
}

int main() {
    int choice;
    while (1) {
        printf("\nTo-Do List Application\n");
        printf("1. Add Task\n2. View Tasks\n3. Delete All Tasks\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: deleteTasks(); break;
            case 4: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice!\n");
        }
    }
}
