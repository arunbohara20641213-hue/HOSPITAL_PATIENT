#include<stdio.h>

struct hosp_write
{
    char name[20];
    int age;
    char address[50];
    char condition[100];
    char ward[20];
};

int main()
{
    struct hosp_write hpp;
    int i;
    FILE *fp;

    fp = fopen("hospital.txt", "w");
    if(fp == NULL)
    {
        printf("Error opening file!");
        return 1;
    }

    printf("Enter the Details of 24 Patients:\n");
    printf("Name | Age | Address | Condition | Ward\n");

    for(i = 1; i <= 24; i++)
    {
        printf("\nPatient %d:\n", i);

        printf("Name: ");
        scanf("%19s", hpp.name);

        printf("Age: ");
        scanf("%d", &hpp.age);

        printf("Address (no spaces): ");
        scanf("%49s", hpp.address); 

        printf("Condition (no spaces): ");
        scanf("%99s", hpp.condition);

        printf("Ward: ");
        scanf("%19s", hpp.ward);
        fprintf(fp, "%s %d %s %s %s\n",
                hpp.name, hpp.age, hpp.address, hpp.condition, hpp.ward);
    }

    printf("\nData saved successfully to hospital.txt\n");

    fclose(fp);
    return 0;
}
