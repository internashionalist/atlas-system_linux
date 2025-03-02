#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/* Make sure the prototype matches your assembly function. */
extern int asm_strcasecmp(const char *s1, const char *s2);

/* A small helper to print both strcasecmp and asm_strcasecmp. */
static void do_test(const char *s1, const char *s2)
{
    int sysval = strcasecmp(s1, s2);
    int asmval = asm_strcasecmp(s1, s2);

    printf("Test: (\"%s\", \"%s\")\n", s1, s2);
    printf("  strcasecmp -> %d\n", sysval);
    printf("  asm_strcasecmp -> %d\n", asmval);

    if (sysval == asmval)
    {
        printf("  ==> MATCH\n\n");
    }
    else
    {
        printf("  ==> MISMATCH\n\n");
    }
}

int main(void)
{
    /* Feel free to add or modify test pairs here. */
    const char *testpairs[][2] = {
        {"Holberton School", "Holberton School"},
        {"Holberton School", "HOLBERTON SCHOOL"},
        {"Holberton School", "holberton socool"},
        {"Holberton School", "Holberton"},
        {"Holberton", ""},
        {"", "Holberton"},
        {"SameLength", "sAmeLength"},
        {"MixedCASE", "MIXEDcase"},
        {"abc", "ABC"},
        {" ", "\0"}, /* space vs empty */
        {"S", "\0"},
        {"\0", "S"},
    };

    size_t i;
    for (i = 0; i < sizeof(testpairs) / sizeof(testpairs[0]); i++)
    {
        do_test(testpairs[i][0], testpairs[i][1]);
    }

    return 0;
}
