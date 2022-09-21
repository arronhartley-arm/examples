/* Copyright (c) 2019 Arm Limited (or its affiliates). All rights reserved. */
/* Use, modification and redistribution of this file is subject to your possession of a     */
/* valid End User License Agreement for the Arm Product of which these examples are part of */
/* and your compliance with all applicable terms and conditions of such licence agreement.  */


#include <stdio.h>
#include <string.h>

extern void DisableSveTraps(void);
extern const char* SkipWhiteSpace(const char* p, const char* end);

#if 0
// Equivalent C version of SkipWhiteSpace
const char* SkipWhiteSpace(const char* p, const char* end) {
    while (p != end && (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t')) {
    p++;
    }
return p;
}
#endif

int main(void)
{
    const char* p = "   Hello   ";
    const char* end = p + strlen(p);
    const char* r;

    printf("\nSVE2 Skip White Space example using NMATCH instruction\n");

    DisableSveTraps();

    printf("Input string  = '%s'\n", p);
    r = SkipWhiteSpace(p, end);
    printf("Output string = '%s'\n", r);

    return 0;
}


