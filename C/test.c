#include "hifo.h"

#include <stdlib.h>
#include <stdio.h>

/*
 * Note: This is the worst test ever. Well, there are probably worst test, but
 * this is the almost-worst test ever!
 * Please don't e-mail me saying this is the worst or almost-worst test ever.
 * I know. Did it anyway. I'm THIS cool!
 *
 * Don't e-mail me telling me I'm not cool.
 */

int main(void) {
    struct hifo* test = HIFO_Create();

    puts("...\nAdding six entries!");
    HIFO_Push(test, 1);
    HIFO_Push(test, 2);
    HIFO_Push(test, 3);
    HIFO_Push(test, 4);
    HIFO_Push(test, 5);
    HIFO_Push(test, 6);
    HIFO_Dump(test);

    puts("...\nPopping one, pushing one!");
    HIFO_Pop(test, NULL);
    HIFO_Push(test, 7);
    HIFO_Dump(test);

    puts("...\nPopping until empty!");
    while (HIFO_GetSize(test) > 0) {
        HIFO_Pop(test, NULL);
    }
    HIFO_Dump(test);

    puts("...\nPushing three entries!");
    HIFO_Push(test, 1);
    HIFO_Push(test, 2);
    HIFO_Push(test, 3);
    HIFO_Dump(test);

    puts("...\nEmpty HWIFO!");
    HIFO_Empty(test);
    HIFO_Dump(test);

    puts("...\nPushing one, peeking!");
    HIFO_Push(test, 1);
    int data = 666;
    HIFO_Peek(test, &data);
    printf("Peeked: %d\n", data);
    HIFO_Dump(test);

    HIFO_Destroy(test);

    return EXIT_SUCCESS;
}