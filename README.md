# Hospital Patient Management System

This project stores and analyzes hospital patient records in a shared text file (`hospital.txt`).
Each C file implements a specific operation on the same 24-record dataset.

---

## Project Structure

```
Hospital/
├── hosp_write.c      # Creates and writes 24 patient records to hospital.txt
├── hosp_read.c       # Combined utility functions (city, age, condition, ward count)
├── hosp_place.c      # City-based patient filter
├── hosp_age.c        # Oldest and youngest patient finder
├── hosp_condn.c      # Critical condition filter
├── hosp_count.c      # Ward-wise patient count
├── main.c            # Separate launcher/orchestrator (not documented here)
├── output/
│   ├── hosp_read
│   └── hospital.txt
└── build/
	└── Debug/
```

---

## Patient Record Format

All modules use the same structure:

- `name` (string, no spaces)
- `age` (integer)
- `address` (string, no spaces)
- `condition` (string, no spaces)
- `ward` / `ward_name` (string, no spaces)

Data is read/written in this text format:

```text
Name Age Address Condition Ward
```

---

## Implemented Functions (Excluding `main.c` Functionality)

### `hosp_place.c`

- `displayKathmanduPatients()`
Prompts for a city name, scans `hospital.txt`, prints matching patients, and prints total matched count.

### `hosp_age.c`

- `hospitalage()`
Reads all 24 records, finds maximum and minimum age, and prints oldest and youngest patient names (including ties).

### `hosp_condn.c`

- `hospitalcondition()`
Reads records and prints only patients whose `condition` is exactly `Critical` in a formatted table.

### `hosp_count.c`

- `hospitalPatientCount()`
Reads records and prints total patient counts for these wards:
`GynoWard`, `OrthoWard`, `CardioWard`, `NeuroWard`, `PediatricWard`, `EmergencyWard`, `ICUWard`, `SurgicalWard`, `GeneralWard`, `MaternityWard`.

### `hosp_read.c`

This file currently contains the same core utility functions in one place:

- `displayKathmanduPatients()`
- `hospitalage()`
- `hospitalcondition()`
- `hospitalPatientCount()`

### `hosp_write.c`

This module handles data entry and writes 24 records into `hospital.txt`.

---

## Build and Run

Compile any module you want to run:

```bash
gcc hosp_write.c -o hosp_write
gcc hosp_place.c -o hosp_place
gcc hosp_age.c -o hosp_age
gcc hosp_condn.c -o hosp_condn
gcc hosp_count.c -o hosp_count
gcc hosp_read.c -o hosp_read
```

Run (examples):

```bash
./hosp_write
./hosp_place
./hosp_age
./hosp_condn
./hosp_count
./hosp_read
```

On Windows:

```bash
hosp_write.exe
hosp_place.exe
hosp_age.exe
hosp_condn.exe
hosp_count.exe
hosp_read.exe
```

---

## Important Notes

- Run `hosp_write` first to create/update `hospital.txt`.
- Most modules assume exactly 24 records.
- Input format is space-separated (`scanf("%s", ...)`), so multi-word names/addresses/conditions are not supported.
- Some filters are exact/case-sensitive (for example, `Critical` in condition check).

## Authors

- [@arunbohara20641213-hue](https://github.com/arunbohara20641213-hue)
- [@kabircsit25](https://github.com/kabircsit25/HOSPITAL_PATIENT)
- [@bikashcsit222](https://github.com/bikashcsit222)
- [@ankitcsit25](https://github.com/ankitcsit25)
