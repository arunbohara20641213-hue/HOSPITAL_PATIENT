
#include <stdio.h>
struct hosp_read
{
    char name[50];
    int age;
    char address[50];
    char condition[50];
    char ward_name[50];
};
int main()
{
    int i, w1 = 0, w2 = 0, w3 = 0, w4 = 0, w5 = 0, w6 = 0, w7 = 0, w8 = 0, w9 = 0, w10 = 0;
    struct hosp_read hpp[24];
    FILE *fp;
    fp = fopen("hospital.txt", "r");
    for (i = 0; i < 24; i++)
    {
        fscanf(fp, "%s %d %s %s %s", &hpp[i].name, &hpp[i].age, &hpp[i].address, &hpp[i].condition, &hpp[i].ward_name);
        if (strcmp(hpp[i].ward_name, "GynoWard") == 0)
        {
            w1++;
        }
        else if (strcmp(hpp[i].ward_name, "OrthoWard") == 0)
        {
            w2++;
        }
        else if (strcmp(hpp[i].ward_name, "CardioWard") == 0)
        {
            w3++;
        }
        else if (strcmp(hpp[i].ward_name, "NeuroWard") == 0)
        {
            w4++;
        }
        else if (strcmp(hpp[i].ward_name, "PediatricWard") == 0)
        {
            w5++;
        }
        else if (strcmp(hpp[i].ward_name, "EmergencyWard") == 0)
        {
            w6++;
        }
        else if (strcmp(hpp[i].ward_name, "ICUWard") == 0)
        {
            w7++;
        }
        else if (strcmp(hpp[i].ward_name, "SurgicalWard") == 0)
        {
            w8++;
        }
        else if (strcmp(hpp[i].ward_name, "GeneralWard") == 0)
        {
            w9++;
        }
        else if (strcmp(hpp[i].ward_name, "MaternityWard") == 0)
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
