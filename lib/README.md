Custom C Headders
=================

# colors.h
Enableing term colours.

```c
#define KNRM //Reset  
#define KRED //RED
#define KGRN //Green
#define KYEL //Yellow 
#define KBLU //Blue
#define KMAG //Magenta 
#define KCYN //Cyan
#define KWHT //White 
```

# debug.h
Creates logging with ANSI terminal colors.
Depends on colors.h
```c
#ifndef KNMR
    #include "colors.h"
#endif

#define debug
#define error
#define success
#define info
```

# kerndebug.h
Same as debug.h but using printk instead of printf to fit kernel debugging.



