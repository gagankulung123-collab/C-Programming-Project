#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Task
{
 char name[100];
 int isDone;
};

int main()
{
    int choice;
    struct Task tasks[10];
    int taskCount=0;
    int i;

    printf("========================\n");
    printf(" LIFE COMPANION SYSTEM  \n");
    printf("========================\n");
    printf("Welcome!\n");
    while (1)
    {
        printf("\n--- MAIN MENU ---\n");
        printf("1. Add Daily Tasks\n");
        printf("2. View Tasks\n");
        printf("3. Mood Check\n");
        printf("4. Motivation Boost\n");
        printf("5. Progress Report\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if(taskCount < 10)
            {
                printf("\nEnter task name: ");
                getchar();
                scanf("%[^\n]", tasks[taskCount].name);
                tasks[taskCount].isDone= 0;
                taskCount++;
                printf("Task added successfully!\n");
            }
            else
            {
                printf("\nTask list is full! Max 10 tasks.\n");
            }
            break;

        case 2:
            if(taskCount == 0)
            {
                printf("\nNo tasks added yet!\n");
            }
            else
            {
                printf("\n--- Your TASKS ---\n");
                for(int i=0; i < taskCount; i++)
                {
                    printf("%d. %s", i+1, tasks[i].name);
                    if(tasks[i].isDone == 1)
                    {
                        printf("[DONE]\n");
                    }
                    else
                    {
                        printf("[PENDING]\n");
                    }
                }
            }
            break;

        case 3:
            printf("\n[Mood Check -Coming Soon]\n");
            break;
        case 4:
            printf("\n[Motivation Boost -Coming Soon]\n");
            break;
        case 5:
            printf("\n[Progress Report -Coming Soon]\n");
            break;
        case 6:
            printf("\nGoodbye! Keep going strong!\n");
            exit(0);
        default:
            printf("\nInvalid choice! Please enter 1-6.\n");
        }
    }
    return 0;
}