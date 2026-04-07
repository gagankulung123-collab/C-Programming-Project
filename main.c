#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Task
{
    char name[100];
    int isDone;
};

struct Task tasks[10];
int taskCount = 0;

void saveTasks()
{
    time_t t = time(NULL);
    struct tm *today = localtime(&t);

    FILE *file = fopen("tasks.txt", "a");

    if (file == NULL)
    {
        printf("Errir saving  tasks!\n");
        return;
    }
    fprintf(file, "\nDate: %d-%02d-%02d\n", today->tm_year + 1900, today->tm_mon + 1, today->tm_mday);
    for (int i = 0; i < taskCount; i++)
    {
        if (tasks[i].isDone == 1)
        {
            fprintf(file, "%d. %s [DONE]\n", i + 1, tasks[i].name);
        }
        else
        {
            fprintf(file, "%d. %s [PENDING]\n", i + 1, tasks[i].name);
        }
    }
    fclose(file);
    printf("Tasks saved to: tasks.txt\n");
    printf("Total tasks saved: %d\n", taskCount);
}

void saveTasksData()
{
    FILE *file = fopen("tasks_data.txt", "w");
    if (file == NULL)
    {
        printf("Error saving task data!\n");
        return;
    }
    for (int i = 0; i < taskCount; i++)
    {
        fprintf(file, "%s|%d\n", tasks[i].name, tasks[i].isDone);
    }
    fclose(file);
}

void loadTasks()
{
    FILE *file = fopen("tasks_data.txt", "r");
    if (file == NULL)
    {
        return;
    }
    while (taskCount < 10)
    {
        int result = fscanf(file, "%[^|]|%d\n", tasks[taskCount].name, &tasks[taskCount].isDone);
        if (result != 2)
        {
            break;
        }
        taskCount++;
    }
    fclose(file);
}
int main()
{
    int choice;
    loadTasks();

    printf("========================\n");
    printf(" LIFE COMPANION SYSTEM  \n");
    printf("========================\n");
    printf("Welcome!\n");
    while (1)
    {
        printf("\n--- MAIN MENU ---\n");
        printf("1. Add Daily Tasks\n");
        printf("2. View Tasks\n");
        printf("3. Motivation Boost\n");
        printf("4. Progress Report\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (taskCount < 10)
            {
                printf("\nEnter task name: ");
                getchar();
                scanf("%[^\n]", tasks[taskCount].name);
                tasks[taskCount].isDone = 0;
                taskCount++;
                printf("Task added successfully!\n");
            }
            else
            {
                printf("\nTask list is full! Max 10 tasks.\n");
            }
            break;

        case 2:
            if (taskCount == 0)
            {
                printf("\nNo tasks added yet!\n");
            }
            else
            {
                printf("\n--- Your TASKS ---\n");
                for (int i = 0; i < taskCount; i++)
                {
                    printf("%d. %s", i + 1, tasks[i].name);
                    if (tasks[i].isDone == 1)
                    {
                        printf("[DONE]\n");
                    }
                    else
                    {
                        printf("[PENDING]\n");
                    }
                }
                int markChoice;
                printf("\nEnter task number to mark as done (0 to skip): ");
                scanf("%d", &markChoice);

                if (markChoice > 0 && markChoice <= taskCount)
                {
                    tasks[markChoice - 1].isDone = 1;
                    printf("Task %d marked as done!\n", markChoice);
                }
                else if (markChoice != 0)
                {
                    printf("Invalid Task number!\n");
                }

                int deleteChoice;
                printf("\nEnter task nuber you want to delete(0 to skip): ");
                scanf("%d", &deleteChoice);
                if (deleteChoice > 0 && deleteChoice <= taskCount)
                {
                    for (int i = deleteChoice - 1; i < taskCount - 1; i++)
                    {
                        tasks[i] = tasks[i + 1];
                    }
                    taskCount--;
                    printf("Task %d deleted successfully!\n", deleteChoice);
                }
                else if (deleteChoice != 0)
                {
                    printf("Invalid Task number!\n");
                }
            }
            break;

        case 3:
        {
            char *quotes[] = {
                "Don't give up! Success takes time!",
                "Believe in yourself! You are stronger than you think!",
                "Every day is a new opportunity! Grab it!",
                "Hard work always pays off! Keep going!",
                "You are capable of amazing things!",
                "Stay focused and never stop trying!",
                "Success is not final, failure is not fatal!",
                "Dream big and work hard!"};
            int totalQuotes = 8;
            int random = rand() % totalQuotes;
            printf("\nMotivation Quote of the Day!\n");
            printf("%s\n", quotes[random]);
            break;
        }
        case 4:
            printf("\n[Progress Report -Coming Soon]\n");
            break;
        case 5:
            saveTasks();
            saveTasksData();
            printf("\nGoodbye! Keep going strong!\n");
            exit(0);
        default:
            printf("\nInvalid choice! Please enter 1-5.\n");
        }
    }
    return 0;
}