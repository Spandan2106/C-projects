#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logger.h"

#define BUF_SIZE 1024

static void get_timestamp(char *buf, size_t n) {
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);
    strftime(buf, n, "[%Y-%m-%d %H:%M:%S]", lt);
}

void log_action(const char *fmt, ...) {
    char timebuf[32];
    get_timestamp(timebuf, sizeof timebuf);

    printf("%s ", timebuf);

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    putchar('\n');
}

void create_file() {
    char *filename = malloc(BUF_SIZE);
    if (!filename) { perror("malloc"); return; }

    printf("Enter new filename: ");
    if (!fgets(filename, BUF_SIZE, stdin)) { free(filename); return; }
    filename[strcspn(filename, "\n")] = 0;

    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("fopen");
        free(filename);
        return;
    }
    log_action("Created file '%s'", filename);
    printf("Enter text (end with a single dot on a line):\n");
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, stdin) > 0) {
        if (strcmp(line, ".\n") == 0) break;
        fputs(line, f);
    }
    free(line);
    fclose(f);
    free(filename);
}

void append_file() {
    char *filename = malloc(BUF_SIZE);
    if (!filename) { perror("malloc"); return; }

    printf("Enter filename to append: ");
    if (!fgets(filename, BUF_SIZE, stdin)) { free(filename); return; }
    filename[strcspn(filename, "\n")] = 0;

    FILE *f = fopen(filename, "a");
    if (!f) {
        perror("fopen");
        free(filename);
        return;
    }
    log_action("Appending to '%s'", filename);
    printf("Enter text (end with a single dot on a line):\n");
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, stdin) > 0) {
        if (strcmp(line, ".\n") == 0) break;
        fputs(line, f);
    }
    free(line);
    fclose(f);
    free(filename);
}

void read_file() {
    char *filename = malloc(BUF_SIZE);
    if (!filename) { perror("malloc"); return; }

    printf("Enter filename to read: ");
    if (!fgets(filename, BUF_SIZE, stdin)) { free(filename); return; }
    filename[strcspn(filename, "\n")] = 0;

    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("fopen");
        free(filename);
        return;
    }
    log_action("Reading '%s'", filename);
    char buffer[BUF_SIZE];
    while (fgets(buffer, BUF_SIZE, f)) {
        fputs(buffer, stdout);
    }
    fclose(f);
    free(filename);
}

int main() {
    while (1) {
        printf(
            "\nMini File Editor\n"
            "1) Create new file\n"
            "2) Append to file\n"
            "3) Read file\n"
            "4) Exit\n"
            "Choose: "
        );

        char choice = getchar();
        while (getchar() != '\n');  // flush

        switch (choice) {
            case '1': create_file(); break;
            case '2': append_file(); break;
            case '3': read_file(); break;
            case '4': log_action("Exiting editor"); return 0;
            default: printf("Invalid option.\n");
        }
    }
}