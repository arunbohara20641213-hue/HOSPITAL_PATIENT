#include <stdio.h>
#include "hosp_common.h"

void hospitalage()
{
    struct hosp_write hpp[HOSP_MAX_PATIENTS];
    FILE *fp;
    int valid_count = 0;
    int corrupt_count = 0;
    int lines_read = 0;
    int i;

    fp = fopen("hospital.txt", "r");
    if (fp == NULL)
    {
        printf("Unable to find file\n");
        return;
    }

    while (valid_count < HOSP_MAX_PATIENTS &&
           hosp_read_next_valid_record(fp, &hpp[valid_count], &corrupt_count, &lines_read))
    {
        valid_count++;
    }

    fclose(fp);

    if (valid_count == 0)
    {
        printf("No valid patient records found.\n");
        if (corrupt_count > 0)
        {
            printf("Skipped corrupt/invalid records: %d (lines scanned: %d)\n", corrupt_count, lines_read);
        }
        return;
    }

    int oldest_age = hpp[0].age;
    int youngest_age = hpp[0].age;

    // Comparing & replacing the oldest and youngest age
    for (i = 0; i < valid_count; i++)
    {
        if (oldest_age < hpp[i].age)
        {
            oldest_age = hpp[i].age;
        }
        if (youngest_age > hpp[i].age)
        {
            youngest_age = hpp[i].age;
        }
    }

    // dispalying the oldest and youngest age
    printf("Oldest age patients detail:\n");
    for (i = 0; i < valid_count; i++)
    {
        if (oldest_age == hpp[i].age)
        {
            printf("Oldest patient with age %d: %s\n", hpp[i].age, hpp[i].name);
        }
    }
    printf("\n");
    printf("Youngest age patients detail:\n");
    for (i = 0; i < valid_count; i++)
    {
        if (youngest_age == hpp[i].age)
        {
            printf("Youngest patient with age %d: %s\n", hpp[i].age, hpp[i].name);
        }
    }

    if (corrupt_count > 0)
    {
        printf("\nSkipped corrupt/invalid records: %d (lines scanned: %d)\n", corrupt_count, lines_read);
    }
}

int main()
{
    hospitalage();
    return 0;
}