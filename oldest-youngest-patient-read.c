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
    struct hosp_write hpp[24];
    FILE *fp;
    int i;
    fp=fopen("hospital.txt","r");
    if (fp==NULL)
    {
        printf("Unable to find file");
    }
    else
    {
       for(i=0; i<24; i++)
       { //Copyinh whole line from the file
        fscanf(fp, "%s %d %s %s %s", &hpp[i].name, &hpp[i].age, &hpp[i].address, &hpp[i].condition, &hpp[i].ward);
       }
    }

    int oldest_age=hpp[0].age;
    int youngest_age=hpp[0].age;
    //int oldest_age_index=0;
    //int youngest_age_index=0;
    //Comparing & replacing the oldest and youngest age
    for(i=0; i<24; i++)
    {
        if(oldest_age<hpp[i].age)
        {
            oldest_age=hpp[i].age;
           // oldest_age_index=i;
        }
        if(youngest_age>hpp[i].age)
        {
            youngest_age=hpp[i].age;
            //youngest_age_index=i;
        }
    }

    //dispalying the oldest and youngest age
    //printf("Oldest age patients detail:\n");
    for(i=0; i<24; i++)
    {
        if(oldest_age==hpp[i].age)
        {
            printf("Oldest patient with age %d: %s\n", hpp[i].age, hpp[i].name);
        }
        if(youngest_age==hpp[i].age)
        {
            printf("Youngest patient with age %d: %s\n", hpp[i].age, hpp[i].name);
        }
    }
    fclose(fp);
    return 0;
}
