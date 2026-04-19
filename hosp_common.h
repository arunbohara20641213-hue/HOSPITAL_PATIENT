#ifndef HOSP_COMMON_H
#define HOSP_COMMON_H

#include <stddef.h>
#include <stdio.h>

#define HOSP_MAX_PATIENTS 24
#define HOSP_NAME_LEN 50
#define HOSP_ADDRESS_LEN 50
#define HOSP_CONDITION_LEN 100
#define HOSP_WARD_LEN 20
#define HOSP_DATE_LEN 11
#define HOSP_RECORD_VERSION_1 1

typedef enum
{
    PATIENT_ADMITTED = 1,
    PATIENT_DISCHARGED = 2,
    PATIENT_TRANSFERRED = 3
} PatientStatus;

typedef enum
{
    HOSP_VALIDATION_OK = 0,
    HOSP_ERROR_NULL_RECORD = 1 << 0,
    HOSP_ERROR_INVALID_NAME = 1 << 1,
    HOSP_ERROR_INVALID_AGE = 1 << 2,
    HOSP_ERROR_INVALID_ADDRESS = 1 << 3,
    HOSP_ERROR_INVALID_CONDITION = 1 << 4,
    HOSP_ERROR_INVALID_WARD = 1 << 5,
    HOSP_ERROR_INVALID_STATUS = 1 << 6,
    HOSP_ERROR_INVALID_DATE = 1 << 7
} HospValidationError;

typedef struct hosp_write
{
    char name[HOSP_NAME_LEN];
    int age;
    char address[HOSP_ADDRESS_LEN];
    char condition[HOSP_CONDITION_LEN];
    char ward[HOSP_WARD_LEN];
    int record_version;
    unsigned long checksum;
    PatientStatus status;
    char admission_date[HOSP_DATE_LEN];
} HospitalRecord;

typedef HospitalRecord hosp_write;
typedef HospitalRecord hosp_read;

int hosp_validate_required_token(const char *value, size_t max_len);
int hosp_validate_age(int age);
int hosp_validate_condition(const char *condition);
int hosp_validate_ward(const char *ward);
int hosp_validate_status(PatientStatus status);
int hosp_validate_date(const char *date_yyyy_mm_dd);
int hosp_validate_record(const HospitalRecord *record);

unsigned long hosp_checksum_record_v1(const HospitalRecord *record);
void hosp_attach_integrity(HospitalRecord *record, int version, PatientStatus status, const char *date_yyyy_mm_dd);

int hosp_parse_legacy_record_line(const char *line, HospitalRecord *out_record);
int hosp_parse_versioned_record_line(const char *line, HospitalRecord *out_record);
int hosp_record_integrity_ok(const HospitalRecord *record);
int hosp_read_next_valid_record(FILE *fp, HospitalRecord *out_record, int *corrupt_count, int *lines_read);

#endif