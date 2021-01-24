//
// Created by alexa on 24/01/2021.
//

#ifndef BLACKFORGE_DBG_H
#define BLACKFORGE_DBG_H

#include <errno.h>

const struct colors {
    const char Black[7];
    const char Red[7];
    const char Green[7];
    const char Magenta[7];
    const char Reset[6];
} colors {
        "Esc[30",
        "Esc[31",
        "Esc[32",
        "Esc[25",
        "Esc[0",
};

#define get_errno() (errno == 0 ? "None" : strerror(errno))
#define log_msg(T, M, ...) fprintf(stderr,"%s[" T "]%s [%s | %s | %d]: " M "\n",colors.Magenta,colors.Reset, __FILE__, __func__, __LINE__, ##__VA_ARGS__);
#define log_err(T, M, ...) fprintf(stderr,"%s[" T "]%s [%s | %s | %d] [errno | %s]: " M "\n",colors.Magenta,colors.Reset, __FILE__, __func__, __LINE__, get_errno() , ##__VA_ARGS__);

#define log_info(M,...)  log_msg("INFO",msg, ##__VA_ARGS__);
#define log_error(M,...){ log_err("ERROR",M,##__VA_ARGS__); }
#define check(A, M, ...){ if(!(A)){ log_error(M, ##__VA_ARGS__); errno=0; goto error; }}
#define check_memory(A) check((A),"Memory Error");

#endif //BLACKFORGE_DBG_H
