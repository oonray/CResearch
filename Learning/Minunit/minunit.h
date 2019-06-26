#undef NDEBUG
#ifndef _minuit_h
#define _minuit_h

#include <stdio.h>
#include <strings.h>

#include "dbg.h"
#include <stdlib.h>

#define mu_suite_start() char *message = NULL
#define mu_assert(test, message) if(!(test)){log_err(message);}