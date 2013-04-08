#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include "log.h"

static FILE *log;
static level_t logging_level;

int log_init(level_t level, char *filename, FILE *file, int append) {
    if (filename != NULL) {
        if (file != NULL) {
            /* You can't specify both. */
            return -1;
        }
        log = fopen(filename, append ? "a" : "w");
        if (log == NULL) {
            return -1;
        }
    } else if (file != NULL) {
        log = file;
    } else {
        /* Neither filename nor file set. */
        return -1;
    }
    logging_level = level;
    return 0;
}

static struct tm *now(void) {
    time_t t = time(NULL);
    return localtime(&t);
}

static char *level_to_string[] = {
    NULL,
    "Error",
    "Warning",
    "Information",
    "Debug",
};

void log_write(level_t level, char *file, int line, char *format, ...) {
    if (level > logging_level || log == NULL) {
        return;
    }

    struct tm *t = now();
    fprintf(log, "[%04d-%02d-%02d %02d:%02d:%02d] ", t->tm_year + 1900,
        t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

    if (logging_level == DEBUG) {
        fprintf(log, "%s:%d:", file, line);
    }

    fprintf(log, "%s: ", level_to_string[level]);

    va_list ap;
    va_start(ap, format);
    vfprintf(log, format, ap);
    va_end(ap);
    fprintf(log, "\n");

    if (logging_level == DEBUG) {
        /* Aide debugging. */
        fflush(log);
    }
}

void log_close(void) {
    fclose(log);
    log = NULL;
}
