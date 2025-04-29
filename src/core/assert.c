#include <config.h>
#include <KD/kd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

KD_API void KD_APIENTRY kdHandleAssertion(const KDchar *condition, const KDchar *filename, KDint linenumber)
{
    fprintf(stderr, "*** Assertion Failure ***");
    fprintf(stderr, " Condition  : %s", condition);
    fprintf(stderr, " File Name  : %s", filename);
    fprintf(stderr, " Line Number: %d", linenumber);

    kdExit(3);
}

KD_API void KD_APIENTRY kdLogMessage(const KDchar *string)
{
    size_t len = strlen(string);
    if (len <= 0) {
        return;
    }

    char* msg = 0;
    if (strcmp(&string[len - 1], "\n")) {
        msg = (char *)malloc(len + 2);
        strcpy(msg, string);
        strcat(msg, "\n");
    } else {
        msg = (char *)string;
    }

    fprintf(stdout, "%s", msg);

    if (msg != string) {
        free(msg);
    }
}
