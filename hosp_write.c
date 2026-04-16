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

    printf("Enter details of 24 patients (NO spaces in input)\n");

    for(i = 0; i < 24; i++)
    {
        printf("\nPatient %d\n", i + 1);

        printf("Name: ");
        scanf("%s", hpp.name);

        printf("Age: ");
        scanf("%d", &hpp.age);

        printf("Address: ");
        scanf("%s", hpp.address);

        printf("Condition: ");
        scanf("%s", hpp.condition);

        printf("Ward: ");
        scanf("%s", hpp.ward);

        fprintf(fp, "%s %d %s %s %s\n",
                hpp.name, hpp.age, hpp.address,
                hpp.condition, hpp.ward);
    }

    printf("\nData saved successfully to hospital.txt\n");

    fclose(fp);
    return 0;
}
