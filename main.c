#include <stdio.h>
#include <stdlib.h> //This is standard library used to use exit(), rand() & remove() function
#include <string.h>
#include <time.h> //This is time and date library used to get current time and local time to convert time to date

struct Task  // Structure that groups task data together istead of separate variables
{
    char name[100];
    int isDone;  //Tracks task completion status
};

struct Task tasks[10];
int taskCount = 0;
char currentUser[100];

void saveTasks() // User defined function that saves tasks in humam readable file
{
    time_t t = time(NULL);  //time_t t is special data type for storing time values
                            //time(NULL) gets the current time from computer clock
    struct tm *today = localtime(&t);

    char filename[150];
    sprintf(filename, "tasks_%s.txt", currentUser);
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Error saving tasks!\n");
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
    printf("Tasks saved to: tasks_%s.txt\n", currentUser);
    printf("Total tasks saved: %d\n", taskCount);
}

void saveTasksData()
{
    char filename[150];
    sprintf(filename, "tasks_data_%s.txt", currentUser);
    FILE *file = fopen(filename, "w");
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
    char filename[150];
    sprintf(filename, "tasks_data_%s.txt", currentUser);
    FILE *file = fopen(filename, "r");
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

void registerUser()
{
    char username[100];
    char password[100];

    printf("\n--- REGISTER ---\n");
    printf("Enter Username: ");
    getchar();
    scanf("%[^\n]", username);

    printf("Enter Password: ");
    getchar();
    scanf("%[^\n]", password);

    FILE *file = fopen("users.txt", "a");

    if (file == NULL)
    {
        printf("Error saving user!\n");
        return;
    }

    fprintf(file, "%s|%s\n", username, password);
    fclose(file);

    strcpy(currentUser, username);
    FILE *session = fopen("session.txt", "w");
    if (session != NULL)
    {
        fprintf(session, "%s", currentUser);
        fclose(session);
    }
    printf("\nRegistration successful!\n");
}

int loginUser()
{
    char username[100];
    char password[100];
    char fileUser[100];
    char filePass[100];

    printf("\n--- LOGIN ---\n");
    printf("Enter username: ");
    getchar();
    scanf("%[^\n]", username);

    printf("Enter password: ");
    getchar();
    scanf("%[^\n]", password);

    FILE *file = fopen("users.txt", "r");

    if (file == NULL)
    {
        printf("\nNo users registered yet! Please register first.\n");
        return 0;
    }

    while (fscanf(file, "%[^|]|%[^\n]\n", fileUser, filePass) == 2)
    {
        if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0)
        {
            fclose(file);
            strcpy(currentUser, username);
            FILE *session = fopen("session.txt", "w");
            if (session != NULL)
            {
                fprintf(session, "%s", currentUser);
                fclose(session);
            }

            printf("\nLogin Successful! Welcome Back %s!\n", username);
            return 1;
        }
    }
    fclose(file);
    printf("\nWrong username or password! Please try again.\n");
    return 0;
}
int main()
{
    int choice;
    int loginChoice;
    int loggedIn = 0;

    printf("========================\n");
    printf(" LIFE COMPANION SYSTEM  \n");
    printf("========================\n");

    FILE *session = fopen("session.txt", "r");
    if (session != NULL)
    {
        fscanf(session, "%s", currentUser);
        fclose(session);
        taskCount = 0;
        memset(tasks, 0, sizeof(tasks));
        loadTasks();
        printf("\nAuto login as %s!\n", currentUser);
        loggedIn = 1;
    }

    while (loggedIn == 0)
    {

        printf("\n1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("\nEnter choice: ");
        scanf("%d", &loginChoice);

        if (loginChoice == 1)
        {
            registerUser();
            loggedIn = 1;
        }
        else if (loginChoice == 2)
        {
            loggedIn = loginUser();
        }
        else if (loginChoice == 3)
        {
            printf("\nGoodbye!\n");
            exit(0);
        }
        else
        {
            printf("\nInvalid choice!\n");
        }
    }

    if (loggedIn == 1 && taskCount == 0)
    {
        loadTasks();
        printf("\nWelcome %s! Your tasks have been loaded.\n", currentUser);
    }

    while (1)
    {
        printf("\n--- MAIN MENU ---\n");
        printf("1. Add Daily Tasks\n");
        printf("2. View Tasks\n");
        printf("3. Motivation Boost\n");
        printf("4. Progress Report\n");
        printf("5. Switch User\n");
        printf("6. Exit\n");

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
                printf("\n--- YOUR TASKS ---\n");
                for (int i = 0; i < taskCount; i++)
                {
                    printf("%d. %s", i + 1, tasks[i].name);
                    if (tasks[i].isDone == 1)
                    {
                        printf(" [DONE]\n");
                    }
                    else
                    {
                        printf(" [PENDING]\n");
                    }
                }

                printf("\nEnter task numbers to mark as done (e.g. 1 2 3) (0 to skip): ");
                int markChoice;
                while (scanf("%d", &markChoice) && markChoice != 0)
                {
                    if (markChoice > 0 && markChoice <= taskCount)
                    {
                        tasks[markChoice - 1].isDone = 1;
                        printf("Task %d marked as done!\n", markChoice);
                    }
                    else
                    {
                        printf("Invalid task number!\n");
                    }
                }

                printf("\nEnter task numbers to delete (e.g. 1 2 3) (0 to skip): ");
                int deleteChoice;
                while (scanf("%d", &deleteChoice) && deleteChoice != 0)
                {
                    if (deleteChoice > 0 && deleteChoice <= taskCount)
                    {
                        for (int j = deleteChoice - 1; j < taskCount - 1; j++)
                        {
                            tasks[j] = tasks[j + 1];
                        }
                        taskCount--;
                        printf("Task %d deleted successfully!\n", deleteChoice);
                    }
                    else
                    {
                        printf("Invalid task number!\n");
                    }
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
            printf("============================\n");
            printf("%s\n", quotes[random]);
            break;
        }
        case 4:
        {
            int completed = 0;
            int pending = 0;
            for (int i = 0; i < taskCount; i++)
            {
                if (tasks[i].isDone == 1)
                {
                    completed++;
                }
                else
                {
                    pending++;
                }
            }

            int productivity = 0;
            if (taskCount > 0)
            {
                productivity = (completed * 100) / taskCount;
            }

            printf("\n--- PROGRESS REPORT ---\n");
            printf("Total Tasks   : %d\n", taskCount);
            printf("Completed     : %d\n", completed);
            printf("Pending       : %d\n", pending);
            printf("Productivity  : %d%%\n", productivity);

            if (productivity == 100)
            {
                printf("Excellent! All tasks completed!\n");
            }
            else if (productivity >= 50)
            {
                printf("Good job! Keep going!\n");
            }
            else if (productivity > 0)
            {
                printf("Keep pushing! You can do it!\n");
            }
            else
            {
                printf("No tasks completed yet! Start now!\n");
            }
            break;
        }
        case 5:
            saveTasks();
            saveTasksData();

            remove("session.txt");
            printf("\nSwitching user...\n");

            taskCount = 0;
            memset(tasks, 0, sizeof(tasks));
            loggedIn = 0;

            while (loggedIn == 0)
            {
                printf("\n1. Register\n");
                printf("2. Login\n");
                printf("3. Exit\n");
                printf("\nEnter choice: ");
                scanf("%d", &loginChoice);

                if (loginChoice == 1)
                {
                    registerUser();
                    loggedIn = 1;
                }
                else if (loginChoice == 2)
                {
                    loggedIn = loginUser();
                }
                else if (loginChoice == 3)
                {
                    printf("\nGoodbye! Have a Great Day!\n");
                    exit(0);
                }
                else
                {
                    printf("\nInvalid choice!\n");
                }
            }

            taskCount = 0;
            memset(tasks, 0, sizeof(tasks));
            loadTasks();
            printf("\nWelcome %s! Your tasks have been loaded.\n", currentUser);
            break;

        case 6:
            saveTasks();
            saveTasksData();
            printf("\nHave a Good Day! Keep going strong!\n");
            exit(0);
        default:
            printf("\nInvalid choice! Please enter 1-6.\n");
        }
    }
    return 0;
}