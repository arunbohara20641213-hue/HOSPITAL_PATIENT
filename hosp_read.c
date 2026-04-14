#include<stdio.h>
#include<string.h>
struct hosp_write
{
    char name[20];
    int age;
    char address[50];
    char condition[100];
    char ward[20];
};
void displayKathmanduPatients(FILE *fp)
{
    struct hosp_write hpp;
    int count = 0;
    char searchCity[20];
    printf("\nEnter city to filter: ");
    scanf("%s", searchCity);
    printf("\n\nPatients from %s:\n", searchCity);
    printf("Name \t Age \t Address \t Condition \t Ward\n");
    rewind(fp);
    for(int i = 0; i < 24; i++)
    {
        if(fscanf(fp, "%s %d %s %s %s", hpp.name, &hpp.age, hpp.address, hpp.condition, hpp.ward) != 5)
            break; // Stop if reading fails
        if(strstr(hpp.address, searchCity) != NULL)
        {
            printf("%s\t%d\t%s\t%s\t%s\n", hpp.name, hpp.age, hpp.address, hpp.condition, hpp.ward);
            count++;
        }
    }
    if(count == 0)
        printf("No patients found from %s.\n", searchCity);
        printf("\nTotal patients from %s: %d\n", searchCity, count);
}
int main()
{
    struct hosp_write hpp;
    int i;
    FILE *fp;
    fp = fopen("hospital.txt", "r");
    if(fp == NULL)
    {
        printf("Error opening file!");
        return 1;
    }
    printf("Details of 24 Patients:\n");
    printf("Name \t Age \t Address \t Condition \t Ward\n");
     for(i = 1; i <= 24; i++)
    {
       if(fscanf(fp, "%s %d %s %s %s", hpp.name, &hpp.age, hpp.address, hpp.condition, hpp.ward) != 5)
            break;
        printf("%s\t%d\t%s\t%s\t%s\n", hpp.name, hpp.age, hpp.address, hpp.condition, hpp.ward);
    }
    // Call BEFORE fclose
    displayKathmanduPatients(fp);

    fclose(fp); // Close AFTER all file operations are done
    return 0;
}
