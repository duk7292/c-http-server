#include "helper.h"



void print_memory_usage()
{
    FILE *file = fopen("/proc/self/statm", "r");
    if (!file)
    {
        perror("fopen");
        return;
    }

    long size_pages, resident_pages;
    if (fscanf(file, "%ld %ld", &size_pages, &resident_pages) != 2)
    {
        perror("fscanf");
        fclose(file);
        return;
    }
    fclose(file);

    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // KB
    long virtual_kb = size_pages * page_size_kb;
    long resident_kb = resident_pages * page_size_kb;

    printf("Virtual Memory (VMS): %ld KB\n", virtual_kb);
    printf("Resident Memory (RSS): %ld KB\n", resident_kb);
}

char *str_append(char *strA, char *strB)
{
    strA = realloc(strA, (strlen(strA) + strlen(strB)) * sizeof(char));
    memcpy(strA + strlen(strA), strB, strlen(strB) + 1);

    return strA;
}
