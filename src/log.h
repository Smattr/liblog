#ifndef _LIBLOG_LOG_H_
#define _LIBLOG_LOG_H_

typedef enum {
    NONE = 0,
    ERROR = 1,
    WARNING = 2,
    INFO = 3,
    DEBUG = 4,
} level_t;

/* Initialise the log. You must pass either 'filename' or 'file' to indicate
 * where to log to. Subsequent calls to 'log_write' will only log the message
 * if their 'level' is less than or equal to the 'level' used to initialise the
 * log here. Pass 'append' as non zero if you want to append to an existing
 * file. Returns 0 on success, non-zero on failure.
 */
int log_init(level_t level, char *filename, FILE *file, int append);

/* Write a message to the log at level 'level'. Generally you will want to call
 * the following macro wrapper, rather than this function directly.
 */
void log_write(level_t level, char *file, int line, char *format, ...);
#define LOG(level, args...) \
    log_write(level, __FILE__, __LINE__, args)

/* Close the log and free resources. */
void log_close(void);

#endif
