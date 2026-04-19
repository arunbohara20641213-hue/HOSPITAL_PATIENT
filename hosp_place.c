#include<stdio.h>
#include<string.h>
#include "hosp_common.h"

//Kathmandu patients by Arun -1

void displayKathmanduPatients()
{
    struct hosp_write hpp;
    FILE *fp;
    int count = 0;
    int corrupt_count = 0;
    int lines_read = 0;
    char searchCity[HOSP_ADDRESS_LEN];

    fp = fopen("hospital.txt", "r");
    if(fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter city to filter: ");
    scanf("%49s", searchCity);
    printf("\n\nPatients from %s:\n", searchCity);
    printf("Name \t Age \t Address \t Condition \t Ward\n");

    while (hosp_read_next_valid_record(fp, &hpp, &corrupt_count, &lines_read))
    {
        if(strstr(hpp.address, searchCity) != NULL)
        {
            printf("%s\t%d\t%s\t%s\t%s\n", hpp.name, hpp.age, hpp.address, hpp.condition, hpp.ward);
            count++;
        }
    }

    if(count == 0)
    {
        printf("No patients found from %s.\n", searchCity);
    }
    printf("\nTotal patients from %s: %d\n", searchCity, count);

    if (corrupt_count > 0)
    {
        printf("Skipped corrupt/invalid records: %d (lines scanned: %d)\n", corrupt_count, lines_read);
    }

    fclose(fp);
}
int main()

{

    displayKathmanduPatients();
    return 0;
}

