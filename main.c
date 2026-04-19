#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <windows.h>

typedef struct
{
    const char *label;
    const char *source_name;
    const char *exe_name;
} Module;

static const Module modules[] = {
    {"Enter Patient Data", "hosp_write.c", "hosp_write.exe"},
    {"Filter Patients by City", "hosp_place.c", "hosp_place.exe"},
    {"Find Oldest and Youngest Patients", "hosp_age.c", "hosp_age.exe"},
    {"List Critical Condition Patients", "hosp_condn.c", "hosp_condn.exe"},
    {"Count Patients by Ward", "hosp_count.c", "hosp_count.exe"},
    {"Hospital Query Menu", "hosp_read.c", "hosp_read.exe"}
};

static const size_t module_count = sizeof(modules) / sizeof(modules[0]);

static int get_launcher_directory(char *buffer, size_t buffer_size)
{
    DWORD length = GetModuleFileNameA(NULL, buffer, (DWORD)buffer_size);
    char *last_separator;

    if (length == 0 || length >= buffer_size)
    {
        return 0;
    }

    last_separator = strrchr(buffer, '\\');
    if (last_separator == NULL)
    {
        return 0;
    }

    *last_separator = '\0';
    return 1;
}

static int get_project_root(char *buffer, size_t buffer_size)
{
    char launcher_dir[512];
    char *last_separator;

    if (!get_launcher_directory(launcher_dir, sizeof(launcher_dir)))
    {
        return 0;
    }

    strncpy(buffer, launcher_dir, buffer_size - 1);
    buffer[buffer_size - 1] = '\0';

    last_separator = strrchr(buffer, '\\');
    if (last_separator == NULL)
    {
        return 0;
    }

    *last_separator = '\0';
    return 1;
}

static void build_path(char *buffer, size_t buffer_size, const char *directory, const char *name)
{
    snprintf(buffer, buffer_size, "%s\\%s", directory, name);
}

static int file_exists(const char *path)
{
    struct stat file_info;
    return stat(path, &file_info) == 0;
}

static int source_is_newer(const char *source_path, const char *exe_path)
{
    struct stat source_info;
    struct stat exe_info;

    if (stat(source_path, &source_info) != 0)
    {
        return -1;
    }

    if (stat(exe_path, &exe_info) != 0)
    {
        return 1;
    }

    return source_info.st_mtime > exe_info.st_mtime;
}

static int compile_module(const Module *module)
{
    char project_root[512];
    char exe_dir[512];
    char source_path[512];
    char exe_path[512];
    char command[512];

    if (!get_project_root(project_root, sizeof(project_root)) || !get_launcher_directory(exe_dir, sizeof(exe_dir)))
    {
        printf("Unable to resolve project paths.\n");
        return 0;
    }

    build_path(source_path, sizeof(source_path), project_root, module->source_name);
    build_path(exe_path, sizeof(exe_path), exe_dir, module->exe_name);
    snprintf(command, sizeof(command), "gcc \"%s\" \"%s\\hosp_common.c\" -o \"%s\"", source_path, project_root, exe_path);

    printf("\nCompiling %s...\n", module->label);
    int result = system(command);
    if (result != 0)
    {
        printf("Compilation failed for %s. Command: %s\n", module->label, command);
        return 0;
    }

    return 1;
}

static int ensure_module_ready(const Module *module)
{
    char project_root[512];
    char exe_dir[512];
    char source_path[512];
    char exe_path[512];
    int rebuild_required;

    if (!get_project_root(project_root, sizeof(project_root)) || !get_launcher_directory(exe_dir, sizeof(exe_dir)))
    {
        printf("Unable to resolve project paths.\n");
        return 0;
    }

    build_path(source_path, sizeof(source_path), project_root, module->source_name);
    build_path(exe_path, sizeof(exe_path), exe_dir, module->exe_name);

    if (!file_exists(exe_path))
    {
        if (!file_exists(source_path))
        {
            printf("Neither the executable nor the source file exists for %s.\n", module->label);
            return 0;
        }

        return compile_module(module);
    }

    rebuild_required = source_is_newer(source_path, exe_path);
    if (rebuild_required == 1)
    {
        return compile_module(module);
    }

    return 1;
}

static int run_module(const Module *module)
{
    char exe_dir[512];
    char exe_path[512];
    char command[1024];

    if (!ensure_module_ready(module))
    {
        return 0;
    }

    if (!get_launcher_directory(exe_dir, sizeof(exe_dir)))
    {
        printf("Unable to resolve launcher directory.\n");
        return 0;
    }

    build_path(exe_path, sizeof(exe_path), exe_dir, module->exe_name);
    snprintf(command, sizeof(command), "\"%s\"", exe_path);

    printf("\nLaunching %s...\n", module->label);
    if (system(command) != 0)
    {
        printf("Execution finished with an error for %s.\n", module->label);
        return 0;
    }

    printf("\n%s finished. Returning to the main menu.\n", module->label);
    return 1;
}

static int read_menu_choice(void)
{
    char input[32];
    char *end_ptr = NULL;
    long choice;

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        return -1;
    }

    choice = strtol(input, &end_ptr, 10);
    while (end_ptr != NULL && isspace((unsigned char)*end_ptr))
    {
        end_ptr++;
    }

    if (end_ptr == input || (end_ptr != NULL && *end_ptr != '\0'))
    {
        return -1;
    }

    return (int)choice;
}

static void show_menu(void)
{
    size_t i;

    printf("\n========================================\n");
    printf(" Hospital Management System Launcher\n");
    printf("========================================\n");

    for (i = 0; i < module_count; ++i)
    {
        printf("%zu. %s\n", i + 1, modules[i].label);
    }

    printf("0. Exit\n");
    printf("----------------------------------------\n");
    printf("Choose an option: ");
}

int main(void)
{
    int choice;

    for (;;)
    {
        show_menu();
        choice = read_menu_choice();

        if (choice == 0)
        {
            printf("Exiting the launcher. Goodbye.\n");
            break;
        }

        if (choice < 0 || choice > (int)module_count)
        {
            printf("Invalid selection. Please enter a number from 0 to %zu.\n", module_count);
            continue;
        }

        if (!run_module(&modules[choice - 1]))
        {
            printf("Unable to start the selected module.\n");
        }
    }

    return 0;
}