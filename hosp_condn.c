#include<stdio.h>
#include<string.h>
#include "hosp_common.h"
void hospitalcondition()
{
    struct hosp_write hpp;
    FILE *fp;
    int corrupt_count = 0;
    int lines_read = 0;

    fp = fopen("hospital.txt", "r");
    if(fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\nPatients with Critical Condition:\n\n");
    // Top border
    printf("+----------------+-----+----------------+----------------+---------------+\n");
    // Header
    printf("| %-14s | %-3s | %-14s | %-14s | %-13s |\n",
           "Name", "Age", "Address", "Condition", "Ward");
    // Separator
    printf("+----------------+-----+----------------+----------------+---------------+\n");

    while (hosp_read_next_valid_record(fp, &hpp, &corrupt_count, &lines_read))
    {
        if(strcmp(hpp.condition, "Critical") == 0)
        {
            printf("| %-14s | %-3d | %-14s | %-14s | %-13s |\n",
                   hpp.name,
                   hpp.age,
                   hpp.address,
                   hpp.condition,
                   hpp.ward);
        }
    }

    // Bottom border
    printf("+----------------+-----+----------------+----------------+---------------+\n");

    if (corrupt_count > 0)
    {
        printf("Skipped corrupt/invalid records: %d (lines scanned: %d)\n", corrupt_count, lines_read);
    }

    fclose(fp);

}
int main()

{
    hospitalcondition();
    return 0;
}

