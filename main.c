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
            printf("\n[Add Daily Tasks -Coming Soon]\n");
            break;
        case 2:
            printf("\n[View Tasks -Coming Soon]\n");
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