#include "hwifo.h"

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
    struct hwifo* test = HWIFO_Create();

    puts("...\nAdding six entries!");
    HWIFO_Push(test, 1);
    HWIFO_Push(test, 2);
    HWIFO_Push(test, 3);
    HWIFO_Push(test, 4);
    HWIFO_Push(test, 5);
    HWIFO_Push(test, 6);
    HWIFO_Dump(test);

    puts("...\nPopping one, pushing one!");
    HWIFO_Pop(test, NULL);
    HWIFO_Push(test, 7);
    HWIFO_Dump(test);

    puts("...\nPopping until empty!");
    while (HWIFO_GetSize(test) > 0) {
        HWIFO_Pop(test, NULL);
    }
    HWIFO_Dump(test);

    puts("...\nPushing three entries!");
    HWIFO_Push(test, 1);
    HWIFO_Push(test, 2);
    HWIFO_Push(test, 3);
    HWIFO_Dump(test);

    puts("...\nEmpty HWIFO!");
    HWIFO_Empty(test);
    HWIFO_Dump(test);

    puts("...\nPushing one, peeking!");
    HWIFO_Push(test, 1);
    int data = 666;
    HWIFO_Peek(test, &data);
    printf("Peeked: %d\n", data);
    HWIFO_Dump(test);

    HWIFO_Destroy(test);

    return EXIT_SUCCESS;
}