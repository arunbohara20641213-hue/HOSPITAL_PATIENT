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
    int main(){
    int i;
    struct hosp_write hpp[24];
    FILE *fp;
    fp=fopen("./output/hospital.txt","r");
    for(i=0;i<24;i++)
    {
        fscanf(fp,"%s %d %s %s %s" ,&hpp[i].name,&hpp[i].age,&hpp[i].address,&hpp[i].condition,&hpp[i].ward);
        if(strcmp(hpp[i].condition,"Critical") == 0)
        {
            printf("%s \t %d \t %s \t %s \t %s\n",hpp[i].name,hpp[i].age,hpp[i].address,hpp[i].condition,hpp[i].ward);
        } 
    }
    fclose(fp);
    return 0;
}