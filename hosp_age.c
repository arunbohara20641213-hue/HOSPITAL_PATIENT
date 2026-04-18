#include <stdio.h>
#include "hosp_common.h"

void hospitalage()
{
    struct hosp_write hpp[24];
    FILE *fp;
    int i;
    fp = fopen("hospital.txt", "r");
    //fp = fopen("./output/hospital.txt", "r");
    if (fp == NULL)
    {
        printf("Unable to find file");
    }
    else
    {
        for (i = 0; i < 24; i++)
        { // Copying whole line from the file
            fscanf(fp, "%s %d %s %s %s", &hpp[i].name, &hpp[i].age, &hpp[i].address, &hpp[i].condition, &hpp[i].ward);
        }
    }

    int oldest_age = hpp[0].age;
    int youngest_age = hpp[0].age;
    int oldest_age_index = 0;
    int youngest_age_index = 0;
    // Comparing & replacing the oldest and youngest age
    for (i = 0; i < 24; i++)
    {
        if (oldest_age < hpp[i].age)
        {
            oldest_age = hpp[i].age;
            oldest_age_index = i;
        }
        if (youngest_age > hpp[i].age)
        {
            youngest_age = hpp[i].age;
            youngest_age_index = i;
        }
    }

    // dispalying the oldest and youngest age
    printf("Oldest age patients detail:\n");
    for (i = 0; i < 24; i++)
    {
        if (oldest_age == hpp[i].age)
        {
            printf("Oldest patient with age %d: %s\n", hpp[i].age, hpp[i].name);
        }
    }
    printf("\n");
    printf("Youngest age patients detail:\n");
    for (i = 0; i < 24; i++)
    {
        if (youngest_age == hpp[i].age)
        {
            printf("Youngest patient with age %d: %s\n", hpp[i].age, hpp[i].name);
        }
    }

    fclose(fp);
}

int main()
{
    FILE *fp;
    struct hosp_write hpp;
    //Path to the file is given as per the system, so it may be different for other system. So, change the path according to your system. For example, if you are using linux, then the path will be like this: fp = fopen("/home/user/HOSPITAL_PATIENT/output/hospital.txt", "r");

    //fp = fopen("C:/Users/hp/HOSPITAL_PATIENT/output/hospital.txt", "r");

    //path in main function is not required as the path is already given in the hospitalage function. So, I have commented the path in main function and added the path in hospitalage function. So, you can change the path in hospitalage function according to your system.
    
    fp = fopen("hospital.txt", "r");
    if(fp == NULL)
    {
        printf("Error opening file!");
        return 1;
    }
    hospitalage();

    fclose(fp); // Close AFTER all file operations are done
    return 0;
}