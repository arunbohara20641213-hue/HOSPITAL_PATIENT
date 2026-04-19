#include "hosp_common.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

static const char *const k_allowed_conditions[] = {
    "Normal",
    "Moderate",
    "Critical"
};

static const char *const k_allowed_wards[] = {
    "GynoWard",
    "OrthoWard",
    "CardioWard",
    "NeuroWard",
    "PediatricWard",
    "EmergencyWard",
    "ICUWard",
    "SurgicalWard",
    "GeneralWard",
    "MaternityWard"
};

static int is_in_whitelist(const char *value, const char *const *list, size_t list_count)
{
    size_t i;
    for (i = 0; i < list_count; ++i)
    {
        if (strcmp(value, list[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int hosp_validate_required_token(const char *value, size_t max_len)
{
    size_t i;
    size_t len;

    if (value == NULL)
    {
        return 0;
    }

    len = strlen(value);
    if (len == 0 || len >= max_len)
    {
        return 0;
    }

    for (i = 0; i < len; ++i)
    {
        if (isspace((unsigned char)value[i]))
        {
            return 0;
        }
    }

    return 1;
}

int hosp_validate_age(int age)
{
    return age > 0 && age <= 120;
}

int hosp_validate_condition(const char *condition)
{
    if (!hosp_validate_required_token(condition, HOSP_CONDITION_LEN))
    {
        return 0;
    }

    return is_in_whitelist(
        condition,
        k_allowed_conditions,
        sizeof(k_allowed_conditions) / sizeof(k_allowed_conditions[0]));
}

int hosp_validate_ward(const char *ward)
{
    if (!hosp_validate_required_token(ward, HOSP_WARD_LEN))
    {
        return 0;
    }

    return is_in_whitelist(
        ward,
        k_allowed_wards,
        sizeof(k_allowed_wards) / sizeof(k_allowed_wards[0]));
}

int hosp_validate_status(PatientStatus status)
{
    return status == PATIENT_ADMITTED ||
           status == PATIENT_DISCHARGED ||
           status == PATIENT_TRANSFERRED;
}

int hosp_validate_date(const char *date_yyyy_mm_dd)
{
    int year;
    int month;
    int day;

    if (date_yyyy_mm_dd == NULL || strlen(date_yyyy_mm_dd) != 10)
    {
        return 0;
    }

    if (sscanf(date_yyyy_mm_dd, "%4d-%2d-%2d", &year, &month, &day) != 3)
    {
        return 0;
    }

    if (month < 1 || month > 12)
    {
        return 0;
    }

    if (day < 1 || day > 31)
    {
        return 0;
    }

    return year >= 1900 && year <= 2100;
}

int hosp_validate_record(const HospitalRecord *record)
{
    int errors = HOSP_VALIDATION_OK;

    if (record == NULL)
    {
        return HOSP_ERROR_NULL_RECORD;
    }

    if (!hosp_validate_required_token(record->name, HOSP_NAME_LEN))
    {
        errors |= HOSP_ERROR_INVALID_NAME;
    }

    if (!hosp_validate_age(record->age))
    {
        errors |= HOSP_ERROR_INVALID_AGE;
    }

    if (!hosp_validate_required_token(record->address, HOSP_ADDRESS_LEN))
    {
        errors |= HOSP_ERROR_INVALID_ADDRESS;
    }

    if (!hosp_validate_condition(record->condition))
    {
        errors |= HOSP_ERROR_INVALID_CONDITION;
    }

    if (!hosp_validate_ward(record->ward))
    {
        errors |= HOSP_ERROR_INVALID_WARD;
    }

    if (!hosp_validate_status(record->status))
    {
        errors |= HOSP_ERROR_INVALID_STATUS;
    }

    if (!hosp_validate_date(record->admission_date))
    {
        errors |= HOSP_ERROR_INVALID_DATE;
    }

    return errors;
}

unsigned long hosp_checksum_record_v1(const HospitalRecord *record)
{
    const unsigned char *bytes;
    size_t i;
    unsigned long checksum = 5381UL;

    if (record == NULL)
    {
        return 0;
    }

    bytes = (const unsigned char *)record->name;
    for (i = 0; i < strlen(record->name); ++i)
    {
        checksum = ((checksum << 5) + checksum) + bytes[i];
    }

    checksum = ((checksum << 5) + checksum) + (unsigned long)record->age;

    bytes = (const unsigned char *)record->address;
    for (i = 0; i < strlen(record->address); ++i)
    {
        checksum = ((checksum << 5) + checksum) + bytes[i];
    }

    bytes = (const unsigned char *)record->condition;
    for (i = 0; i < strlen(record->condition); ++i)
    {
        checksum = ((checksum << 5) + checksum) + bytes[i];
    }

    bytes = (const unsigned char *)record->ward;
    for (i = 0; i < strlen(record->ward); ++i)
    {
        checksum = ((checksum << 5) + checksum) + bytes[i];
    }

    checksum = ((checksum << 5) + checksum) + (unsigned long)record->record_version;
    checksum = ((checksum << 5) + checksum) + (unsigned long)record->status;

    bytes = (const unsigned char *)record->admission_date;
    for (i = 0; i < strlen(record->admission_date); ++i)
    {
        checksum = ((checksum << 5) + checksum) + bytes[i];
    }

    return checksum;
}

void hosp_attach_integrity(HospitalRecord *record, int version, PatientStatus status, const char *date_yyyy_mm_dd)
{
    if (record == NULL)
    {
        return;
    }

    record->record_version = version;
    record->status = status;

    if (date_yyyy_mm_dd != NULL)
    {
        strncpy(record->admission_date, date_yyyy_mm_dd, HOSP_DATE_LEN - 1);
        record->admission_date[HOSP_DATE_LEN - 1] = '\0';
    }
    else
    {
        strcpy(record->admission_date, "1970-01-01");
    }

    record->checksum = hosp_checksum_record_v1(record);
}

int hosp_parse_legacy_record_line(const char *line, HospitalRecord *out_record)
{
    if (line == NULL || out_record == NULL)
    {
        return 0;
    }

    if (sscanf(line, "%49s %d %49s %99s %19s",
               out_record->name,
               &out_record->age,
               out_record->address,
               out_record->condition,
               out_record->ward) != 5)
    {
        return 0;
    }

    hosp_attach_integrity(out_record, HOSP_RECORD_VERSION_1, PATIENT_ADMITTED, "1970-01-01");
    return 1;
}

int hosp_parse_versioned_record_line(const char *line, HospitalRecord *out_record)
{
    int status;

    if (line == NULL || out_record == NULL)
    {
        return 0;
    }

    if (sscanf(line, "%49s %d %49s %99s %19s %d %lu %d %10s",
               out_record->name,
               &out_record->age,
               out_record->address,
               out_record->condition,
               out_record->ward,
               &out_record->record_version,
               &out_record->checksum,
               &status,
               out_record->admission_date) != 9)
    {
        return 0;
    }

    out_record->status = (PatientStatus)status;
    return 1;
}

int hosp_record_integrity_ok(const HospitalRecord *record)
{
    if (record == NULL)
    {
        return 0;
    }

    if (record->record_version != HOSP_RECORD_VERSION_1)
    {
        return 0;
    }

    return record->checksum == hosp_checksum_record_v1(record);
}

int hosp_read_next_valid_record(FILE *fp, HospitalRecord *out_record, int *corrupt_count, int *lines_read)
{
    char line[512];

    if (fp == NULL || out_record == NULL)
    {
        return 0;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        HospitalRecord candidate;
        int parsed;

        if (lines_read != NULL)
        {
            (*lines_read)++;
        }

        parsed = hosp_parse_versioned_record_line(line, &candidate);
        if (!parsed)
        {
            parsed = hosp_parse_legacy_record_line(line, &candidate);
        }

        if (!parsed)
        {
            if (corrupt_count != NULL)
            {
                (*corrupt_count)++;
            }
            continue;
        }

        if (hosp_validate_record(&candidate) != HOSP_VALIDATION_OK)
        {
            if (corrupt_count != NULL)
            {
                (*corrupt_count)++;
            }
            continue;
        }

        if (!hosp_record_integrity_ok(&candidate))
        {
            if (corrupt_count != NULL)
            {
                (*corrupt_count)++;
            }
            continue;
        }

        *out_record = candidate;
        return 1;
    }

    return 0;
}