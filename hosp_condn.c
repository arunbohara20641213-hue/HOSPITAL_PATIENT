#include<stdio.h>
#include<string.h>
#include "hosp_common.h"
void hospitalcondition()
{
    int i;
    struct hosp_write hpp[24];
    FILE *fp;
    fp = fopen("hospital.txt", "r");
    if(fp == NULL)
    {
        printf("Error opening file!\n");
    
    }
    printf("\nPatients with Critical Condition:\n\n");
    // Top border
    printf("+----------------+-----+----------------+----------------+---------------+\n");
    // Header
    printf("| %-14s | %-3s | %-14s | %-14s | %-13s |\n",
           "Name", "Age", "Address", "Condition", "Ward");
    // Separator
    printf("+----------------+-----+----------------+----------------+---------------+\n");
    for(i = 0; i < 24; i++)
    {
        if(fscanf(fp, "%s %d %s %s %s",
     hpp[i].name,
     &hpp[i].age,
      hpp[i].address,
      hpp[i].condition,
    hpp[i].ward) != 5)
        {
            break;
        }
        if(strcmp(hpp[i].condition, "Critical") == 0)
        {
            printf("| %-14s | %-3d | %-14s | %-14s | %-13s |\n",
                   hpp[i].name,
                   hpp[i].age,
                   hpp[i].address,
                   hpp[i].condition,
                   hpp[i].ward);
        }
    }
    // Bottom border
    printf("+----------------+-----+----------------+----------------+---------------+\n");
    fclose(fp);

}
int main()

{

    FILE *fp;
    struct hosp_write hpp;

    //Path to the file is given as per the system, so it may be different for other system. So, change the path according to your system. For example, if you are using linux, then the path will be like this: fp = fopen("/home/user/HOSPITAL_PATIENT/output/hospital.txt", "r");

    //fp = fopen("./output/hospital.txt", "r");

    //path in main function is not required as the path is already given in the hospitalcondition function. So, I have commented the path in main function and added the path in hospitalcondition function. So, you can change the path in hospitalcondition function according to your system.
    
    fp = fopen("hospital.txt", "r");
    if(fp == NULL)
    {
        printf("Error opening file!");
        return 1;
    }
    hospitalcondition();
}

