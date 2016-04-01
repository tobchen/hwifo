#include "hifo.h"

#include <stdlib.h>
#include <stdio.h>

/*
 * This implementation uses two single linked lists:
 *   - One has the mid element first back to the first element pushed onto hifo
 *   - One has every element after the mid element from right after to the last
 * The first list is always at least as long as the second and at most longer
 * by one element.
 */

struct hifo_link {
    struct hifo_link* next;
    int data;
};

struct hifo {
    // Everything before and including mid element
    struct hifo_link* beforeIncMid;
    // Everything after mid element
    struct hifo_link* after;
    // Last element in list (after mid element)
    struct hifo_link* last;
    // Sizes for both lists
    int sizeBeforeIncMid;
    int sizeAfter;
};

// Ballances the hifo
static void HIFO_Ballance(struct hifo* hifo);

// Creates a halfway in first out type, returns NULL on error
struct hifo* HIFO_Create(void) {
    struct hifo* hifo = calloc(1, sizeof(struct hifo));
    if (NULL == hifo) {
        return NULL;
    }

    return hifo;
}

// Destroys a halfway in first out type
void HIFO_Destroy(struct hifo* hifo) {
    if (HIFO_Empty(hifo)) {
        return;
    }

    free(hifo);
}

// Returns hifo's size, returns -1 on error (for example hifo is NULL)
int HIFO_GetSize(struct hifo* hifo) {
    if (NULL == hifo) {
        return -1;
    }

    return hifo->sizeBeforeIncMid + hifo->sizeAfter;
}

// Pushes element on hifo, returns -1 on error
int HIFO_Push(struct hifo* hifo, int data) {
    if (NULL == hifo) {
        return -1;
    }

    struct hifo_link* link = malloc(sizeof(struct hifo_link));
    link->next = NULL;
    link->data = data;

    if (NULL == hifo->last) {
        hifo->after = link;
    } else {
        hifo->last->next = link;
    }
    hifo->last = link;
    hifo->sizeAfter++;

    HIFO_Ballance(hifo);

    return 0;
}

// Stores next element of hifo in data, returns -1 on error (or empty)
// data may be NULL
int HIFO_Peek(struct hifo* hifo, int* data) {
    if (NULL == hifo || hifo->sizeBeforeIncMid == 0) {
        return -1;
    }

    if (data != NULL) {
        *data = hifo->beforeIncMid->data;
    }
    
    return 0;
}

// Stores next element of hifo in data, removes it,
// returns -1 on error (or empty)
// data may be NULL
int HIFO_Pop(struct hifo* hifo, int* data) {
    if (HIFO_Peek(hifo, data)) {
        return -1;
    }

    struct hifo_link* link = hifo->beforeIncMid;
    hifo->beforeIncMid = link->next;
    free(link);
    hifo->sizeBeforeIncMid--;

    HIFO_Ballance(hifo);

    return 0;
}

// Empties hifo, returns -1 on error
int HIFO_Empty(struct hifo* hifo) {
    if (NULL == hifo) {
        return -1;
    }

    while (hifo->beforeIncMid != NULL) {
        struct hifo_link* link = hifo->beforeIncMid;
        hifo->beforeIncMid = link->next;
        free(link);
    }
    hifo->sizeBeforeIncMid = 0;

    while (hifo->after != NULL) {
        struct hifo_link* link = hifo->after;
        hifo->after = link->next;
        free(link);
    }
    hifo->last = NULL;
    hifo->sizeAfter = 0;

    return 0;
}

// Dumps all info of hifo on console
int HIFO_Dump(struct hifo* hifo) {
    if (NULL == hifo) {
        return -1;
    }

    printf("sizeBeforeIncMid: %d\n", hifo->sizeBeforeIncMid);
    struct hifo_link* link = hifo->beforeIncMid;
    while (link != NULL) {
        printf("%d, ", link->data);
        link = link->next;
    }
    printf("\n");

    printf("sizeAfter: %d\n", hifo->sizeAfter);
    link = hifo->after;
    while (link != NULL) {
        printf("%d, ", link->data);
        link = link->next;
    }
    printf("\n");

    return 0;
}

// Ballances the hifo
void HIFO_Ballance(struct hifo* hifo) {
    if (NULL == hifo) {
        return;
    }

    while (hifo->sizeAfter > hifo->sizeBeforeIncMid) {
        struct hifo_link* link = hifo->after;
        hifo->after = link->next;
        link->next = hifo->beforeIncMid;
        hifo->beforeIncMid = link;

        if (link == hifo->last) {
            hifo->last = NULL;
        }

        hifo->sizeAfter--;
        hifo->sizeBeforeIncMid++;
    }
}