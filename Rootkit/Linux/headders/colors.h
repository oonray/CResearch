/**
 * @author Alexander Bjornsrud
 * @brief color codes for terminals and logfiles
 * 
 * Defines BLANK,
 *         RED
 *         GREEN
 *         YELLO
 *         BLUE
 *         MAGENTA
 *         CYAN
 *         WHITE
 * 
 * Partially sourced from stack overflow.
 * Credit to user karlphillip
 * [StackOverflow] https://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix
 */

#ifndef __colors_h__
    #define __colors_h__
#endif

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"