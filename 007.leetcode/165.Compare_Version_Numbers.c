#include "stdio.h"
#include "stdbool.h"
#include "limits.h"
#include "math.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "sys/types.h"
#include "assert.h"

int
compareVersion (char *version1, char *version2)
{
    if (!strlen (version1) || !strlen (version2) || (strcmp (version1, version2) == 0)) {
        return 0;
    }

    int v1MajorVersion;
    int v2MajorVersion;

    while (*version1 != '\0' || *version2 != '\0') {
        if ('.' == *version1) {
            ++version1;
        }

        if ('.' == *version2) {
            ++version2;
        }

        if ('\0' != *version1) {
            v1MajorVersion = strtol (version1, &version1, 10);
        } else {
            v1MajorVersion = 0;
        }

        if ('\0' != *version2) {
            v2MajorVersion = strtol (version2, &version2, 10);
        } else {
            v2MajorVersion = 0;
        }

        if (v1MajorVersion > v2MajorVersion) {
            return 1;
        } else if (v2MajorVersion > v1MajorVersion) {
            return -1;
        }
    }

    return 0;
}