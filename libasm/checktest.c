#include <stdio.h>
#include <assert.h>
#include <string.h>

extern int asm_strcasecmp(const char *s1, const char *s2);

int main(void)
{
    const char *S1 = "Holberton School";
    const char *S4 = "holberton socool";

    int sysval = strcasecmp(S1, S4);
    int asmval = asm_strcasecmp(S1, S4);

    printf("strcasecmp -> %d\n", sysval);
    printf("asm_strcasecmp -> %d\n", asmval);

    assert(sysval == asmval); /* The same check that fails. */
    return 0;
}
