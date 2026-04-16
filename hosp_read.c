#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct hosp_write {
    char name[20];
    int age;
    char address[50];
    char condition[100];
    char ward[20];
};

// Windows-safe case-insensitive compare
int compareIgnoreCase(char *a, char *b) {
    while (*a && *b) {
        if (tolower(*a) != tolower(*b))
            return 0;
        a++;
        b++;
    }
    return *a == *b;
}

void displayKathmanduPatients(FILE *fp) {
    struct hosp_write hpp;
    int count = 0;
    char searchCity[20];

    printf("\nEnter city to filter: ");
    scanf("%s", searchCity);

    printf("\n\nPatients from %s:\n", searchCity);
    printf("Name\tAge\tAddress\t\tCondition\tWard\n");

    while (fscanf(fp, "%s %d %s %s %s",
                  hpp.name,
                  &hpp.age,
                  hpp.address,
                  hpp.condition,
                  hpp.ward) == 5) {

        if (compareIgnoreCase(hpp.address, searchCity)) {
            printf("%s\t%d\t%s\t%s\t%s\n",
                   hpp.name,
                   hpp.age,
                   hpp.address,
                   hpp.condition,
                   hpp.ward);

            count++;
        }
    }

    if (count == 0) {
        printf("No patients found from %s.\n", searchCity);
    }

    printf("\nTotal patients from %s: %d\n", searchCity, count);
}

int main() {
    FILE *fp;

    fp = fopen("hospital.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    displayKathmanduPatients(fp);

    fclose(fp);
    return 0;
}