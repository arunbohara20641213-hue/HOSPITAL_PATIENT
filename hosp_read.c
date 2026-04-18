#include<stdio.h>
#include<string.h>
#include "hosp_common.h"

//Kathmandu patients by Arun -1

void displayKathmanduPatients()
{
    struct hosp_write hpp;
    FILE *fp;
    fp = fopen("hospital.txt", "r");
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

//Age by Ankit -2

void hospitalage()
{
    struct hosp_write hpp[24];
    FILE *fp;
    int i;
    fp = fopen("hospital.txt", "r");
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

//Patient critical condition by Bikash -3

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

// Patient count by Kabir -4


int hospitalPatientCount()
{
    int i, w1 = 0, w2 = 0, w3 = 0, w4 = 0, w5 = 0, w6 = 0, w7 = 0, w8 = 0, w9 = 0, w10 = 0;
    struct hosp_write hpp[24];
     FILE *fp;
    fp = fopen("hospital.txt", "r");
    for (i = 0; i < 24; i++)
    {
        fscanf(fp, "%s %d %s %s %s", &hpp[i].name, &hpp[i].age, &hpp[i].address, &hpp[i].condition, &hpp[i].ward);
        if (strcmp(hpp[i].ward, "GynoWard") == 0)
        {
            w1++;
        }
        else if (strcmp(hpp[i].ward, "OrthoWard") == 0)
        {
            w2++;
        }
        else if (strcmp(hpp[i].ward, "CardioWard") == 0)
        {
            w3++;
        }
        else if (strcmp(hpp[i].ward, "NeuroWard") == 0)
        {
            w4++;
        }
        else if (strcmp(hpp[i].ward, "PediatricWard") == 0)
        {
            w5++;
        }
        else if (strcmp(hpp[i].ward, "EmergencyWard") == 0)
        {
            w6++;
        }
        else if (strcmp(hpp[i].ward, "ICUWard") == 0)
        {
            w7++;
        }
        else if (strcmp(hpp[i].ward, "SurgicalWard") == 0)
        {
            w8++;
        }
        else if (strcmp(hpp[i].ward, "GeneralWard") == 0)
        {
            w9++;
        }
        else if (strcmp(hpp[i].ward, "MaternityWard") == 0)
        {
            w10++;
        }
    }

    fclose(fp);
    printf("Total number of patients in GynoWard: %d\n", w1);

    //printf("Name \t Age \t Address \t Condition \t Ward Name \t Number of Patients\n");
    /*for (i = 0; i < 24; i++)
    {
        if (strcmp(hpp[i].ward_name, "GynoWard") == 0)
        {

            printf("%s \t %d \t %s \t %s \t %s \t %d\n", hpp[i].name, hpp[i].age, hpp[i].address, hpp[i].condition, hpp[i].ward_name, w1);
        }
    }
        */
    printf("Total number of patients in OrthoWard: %d\n", w2);
    /*for (i = 0; i < 24; i++)
    {
        if (strcmp(hpp[i].ward_name, "OrthoWard") == 0)
        {

            printf("%s \t %d \t %s \t %s \t %s \t %d\n", hpp[i].name, hpp[i].age, hpp[i].address, hpp[i].condition, hpp[i].ward_name, w2);
        }
    }
        */
    printf("Total number of patients in CardioWard: %d\n", w3);
    // for (i = 0; i < 24; i++)
    // {
    //     if (strcmp(hpp[i].ward_name, "CardioWard") == 0)
    //     {

    //         printf("%s \t %d \t %s \t %s \t %s \t %d\n", hpp[i].name, hpp[i].age, hpp[i].address, hpp[i].condition, hpp[i].ward_name, w3);
    //     }
    // }
    printf("Total number of patients in NeuroWard: %d\n", w4);
    // for (i = 0; i < 24; i++)
    // {
    //     if (strcmp(hpp[i].ward_name, "NeuroWard") == 0)
    //     {

    //         printf("%s \t %d \t %s \t %s \t %s \t %d\n", hpp[i].name, hpp[i].age, hpp[i].address, hpp[i].condition, hpp[i].ward_name, w4);
    //     }
    // }
    printf("Total number of patients in PediatricWard: %d\n", w5);
    // for (i = 0; i < 24; i++)
    // {
    //     if (strcmp(hpp[i].ward_name, "PediatricWard") == 0)
    //     {

    //         printf("%s \t %d \t %s \t %s \t %s \t %d\n", hpp[i].name, hpp[i].age, hpp[i].address, hpp[i].condition, hpp[i].ward_name, w5);
    //     }
    // }
    printf("Total number of patients in EmergencyWard: %d\n", w6);
    // for (i = 0; i < 24; i++)
    // {
    //     if (strcmp(hpp[i].ward_name, "EmergencyWard") == 0)
    //     {

    //         printf("%s \t %d \t %s \t %s \t %s \t %d\n", hpp[i].name, hpp[i].age, hpp[i].address, hpp[i].condition, hpp[i].ward_name, w6);
    //     }
    // }
    printf("Total number of patients in ICUWard: %d\n", w7);
    // for (i = 0; i < 24; i++)
    // {
    //     if (strcmp(hpp[i].ward_name, "ICUWard") == 0)
    //     {

    //         printf("%s \t %d \t %s \t %s \t %s \t %d\n", hpp[i].name, hpp[i].age, hpp[i].address, hpp[i].condition, hpp[i].ward_name, w7);
    //     }
    // }
    printf("Total number of patients in SurgicalWard: %d\n", w8);
    // for (i = 0; i < 24; i++)
    // {
    //     if (strcmp(hpp[i].ward_name, "SurgicalWard") == 0)
    //     {

    //         printf("%s \t %d \t %s \t %s \t %s \t %d\n", hpp[i].name, hpp[i].age, hpp[i].address, hpp[i].condition, hpp[i].ward_name, w8);
    //     }
    // }
    printf("Total number of patients in GeneralWard: %d\n", w9);
    // for (i = 0; i < 24; i++)
    // {
    //     if (strcmp(hpp[i].ward_name, "GeneralWard") == 0)
    //     {

    //         printf("%s \t %d \t %s \t %s \t %s \t %d\n", hpp[i].name, hpp[i].age, hpp[i].address, hpp[i].condition, hpp[i].ward_name, w9);
    //     }
    // }
    printf("Total number of patients in MaternityWard: %d\n", w10);

    // for (i = 0; i < 24; i++)
    // {
    //     if (strcmp(hpp[i].ward_name, "MaternityWard") == 0)
    //     {

    //         printf("%s \t %d \t %s \t %s \t %s \t %d\n", hpp[i].name, hpp[i].age, hpp[i].address, hpp[i].condition, hpp[i].ward_name, w10);
    //     }
    // }
return 0;
}
//The reason behind commit is the qn asked to count the number of patients in each ward but the code gives the full info of the patients in each ward. So I have commented the code which gives the full info of the patients in each ward and added the code which gives only the count of patients in each ward.



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
    int number;
    printf("Enter the project number to execute (1 for Kathmandu Patients, 2 for Oldest/Yongest Patient , 3 for Critical Condition, 4 for Patient Count): ");
    scanf("%d", &number);
    printf("Details of 24 Patients:\n");
    printf("Name \t Age \t Address \t Condition \t Ward\n");
    //  for(i = 1; i <= 24; i++)
    // {
    //    fscanf(fp, "%s %d %s %s %s", hpp.name, &hpp.age, hpp.address, hpp.condition, hpp.ward);
        
    //     printf("%s\t%d\t%s\t%s\t%s\n", hpp.name, hpp.age, hpp.address, hpp.condition, hpp.ward);
    // }
    //Call BEFORE fclose
    switch (number)
    {
    case 1:
        displayKathmanduPatients();
        break;
    case 2:
        hospitalage();
        break;
    case 3:
        hospitalcondition();
        break;
    case 4:
        hospitalPatientCount();
        break;
    default:
        printf("Invalid project number!\n");
        break;
    }
    // displayKathmanduPatients();
    // hospitalPatientCount();

    fclose(fp); // Close AFTER all file operations are done
    return 0;
}
