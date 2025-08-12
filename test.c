#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp = fopen("Files/index.html", "rb");
    if (!fp) return 1;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char *buffer = malloc(size + 1);
    if (!buffer) return 1;

    fread(buffer, 1, size, fp);
    buffer[size] = '\0';

    printf("%s\n", buffer);

    free(buffer);
    fclose(fp);
    return 0;
}

