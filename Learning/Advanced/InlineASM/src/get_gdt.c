#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

unsigned long
get_gdt_base (void)
{
	unsigned char   gdtr[6];
	unsigned long   gdt	= 0;
 
	__asm__(".intel_syntax;"
            "sgdt [%0];"
            ".att_syntax;"
            :"=r"(gdtr));
	gdt = *((unsigned long *)&gdtr[2]);
 
	return (gdt);
}

void
test3 (void)
{
	unsigned int	gdt_base	= 0;
 
	gdt_base 	= get_gdt_base ();
 
	printf ("\n[+] Test 3: GDT\n");
	printf ("GDT base: 0x%x\n", gdt_base);
 
	if ((gdt_base >> 24) == 0xff) {
		printf ("Result  : VMware detected\n\n");
		return;
	}
 
	else {
		printf ("Result  : Native OS\n\n");
		return;
	}
}