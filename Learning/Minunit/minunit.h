#undef NDEBUG
#ifndef __color_h
#include "colors.h"
#endif
#ifndef __dbg_h__
#include "dbg.h"
#endif
#ifndef _minuit_h
#define _minuit_h

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#define mu_suite_start() char *message = NULL
#define mu_assert(test, message) if(!(test)){log_err(message); return message;}
#define mu_run_test(test) debug("\n%s%s------%s------%s%s",KINF,KGRN," " #test,KNRM,KINF);message = test();test_run++;if(message) return message;
 