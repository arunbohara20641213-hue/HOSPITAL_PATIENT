#include<stdio.h>
#include <time.h>
#include "hosp_common.h"

static void current_date_yyyy_mm_dd(char *buffer, size_t size)
{
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);

    if (tm_now == NULL)
    {
        snprintf(buffer, size, "1970-01-01");
        return;
    }

    strftime(buffer, size, "%Y-%m-%d", tm_now);
}

static void print_validation_errors(int errors)
{
    if (errors & HOSP_ERROR_INVALID_NAME)
    {
        printf("- Name is invalid (required, no spaces, max 49 chars).\n");
    }
    if (errors & HOSP_ERROR_INVALID_AGE)
    {
        printf("- Age is invalid (must be 1 to 120).\n");
    }
    if (errors & HOSP_ERROR_INVALID_ADDRESS)
    {
        printf("- Address is invalid (required, no spaces, max 49 chars).\n");
    }
    if (errors & HOSP_ERROR_INVALID_CONDITION)
    {
        printf("- Condition must be one of: Normal, Moderate, Critical.\n");
    }
    if (errors & HOSP_ERROR_INVALID_WARD)
    {
        printf("- Ward is invalid. Use a supported ward token (e.g., ICUWard).\n");
    }
}

int main()
{
    struct hosp_write hpp;
    int i;
    FILE *fp;
    char admission_date[HOSP_DATE_LEN];

    fp = fopen("hospital.txt", "w");
    if(fp == NULL)
    {
        printf("Error opening file!");
        return 1;
    }

    printf("Enter details of 24 patients (NO spaces in input)\n");

    current_date_yyyy_mm_dd(admission_date, sizeof(admission_date));

    for(i = 0; i < 24; i++)
    {
        int errors;
        do
        {
            printf("\nPatient %d\n", i + 1);

            printf("Name: ");
            scanf("%49s", hpp.name);

            printf("Age: ");
            scanf("%d", &hpp.age);

            printf("Address: ");
            scanf("%49s", hpp.address);

            printf("Condition (Normal/Moderate/Critical): ");
            scanf("%99s", hpp.condition);

            printf("Ward: ");
            scanf("%19s", hpp.ward);

            hosp_attach_integrity(&hpp, HOSP_RECORD_VERSION_1, PATIENT_ADMITTED, admission_date);
            errors = hosp_validate_record(&hpp);
            if (errors != HOSP_VALIDATION_OK)
            {
                printf("Invalid input for Patient %d. Please re-enter:\n", i + 1);
                print_validation_errors(errors);
            }
        } while (errors != HOSP_VALIDATION_OK);

        fprintf(fp, "%s %d %s %s %s %d %lu %d %s\n",
                hpp.name,
                hpp.age,
                hpp.address,
                hpp.condition,
                hpp.ward,
                hpp.record_version,
                hpp.checksum,
                hpp.status,
                hpp.admission_date);
    }

    printf("\nData saved successfully to hospital.txt\n");

    fclose(fp);
    return 0;
}
