#include "hwifo.h"

#include <stdlib.h>
#include <stdio.h>

/*
 * This implementation uses two single linked lists:
 *   - One has the mid element first back to the first element pushed onto hwifo
 *   - One has every element after the mid element from right after to the last
 * The first list is always at least as long as the second and at most longer
 * by one element.
 */

struct hwifo_link {
    struct hwifo_link* next;
    int data;
};

struct hwifo {
    // Everything before and including mid element
    struct hwifo_link* beforeIncMid;
    // Everything after mid element
    struct hwifo_link* after;
    // Last element in list (after mid element)
    struct hwifo_link* last;
    // Sizes for both lists
    int sizeBeforeIncMid;
    int sizeAfter;
};

// Ballances the hwifo
static void HWIFO_Ballance(struct hwifo* hwifo);

// Creates a halfway in first out type, returns NULL on error
struct hwifo* HWIFO_Create(void) {
    struct hwifo* hwifo = calloc(1, sizeof(struct hwifo));
    if (NULL == hwifo) {
        return NULL;
    }

    return hwifo;
}

// Destroys a halfway in first out type
void HWIFO_Destroy(struct hwifo* hwifo) {
    if (HWIFO_Empty(hwifo)) {
        return;
    }

    free(hwifo);
}

// Returns hwifo's size, returns -1 on error (for example hwifo is NULL)
int HWIFO_GetSize(struct hwifo* hwifo) {
    if (NULL == hwifo) {
        return -1;
    }

    return hwifo->sizeBeforeIncMid + hwifo->sizeAfter;
}

// Pushes element on hwifo, returns -1 on error
int HWIFO_Push(struct hwifo* hwifo, int data) {
    if (NULL == hwifo) {
        return -1;
    }

    struct hwifo_link* link = malloc(sizeof(struct hwifo_link));
    link->next = NULL;
    link->data = data;

    if (NULL == hwifo->last) {
        hwifo->after = link;
    } else {
        hwifo->last->next = link;
    }
    hwifo->last = link;
    hwifo->sizeAfter++;

    HWIFO_Ballance(hwifo);

    return 0;
}

// Stores next element of hwifo in data, returns -1 on error (or empty)
// data may be NULL
int HWIFO_Peek(struct hwifo* hwifo, int* data) {
    if (NULL == hwifo || hwifo->sizeBeforeIncMid == 0) {
        return -1;
    }

    if (data != NULL) {
        *data = hwifo->beforeIncMid->data;
    }
    
    return 0;
}

// Stores next element of hwifo in data, removes it,
// returns -1 on error (or empty)
// data may be NULL
int HWIFO_Pop(struct hwifo* hwifo, int* data) {
    if (HWIFO_Peek(hwifo, data)) {
        return -1;
    }

    struct hwifo_link* link = hwifo->beforeIncMid;
    hwifo->beforeIncMid = link->next;
    free(link);
    hwifo->sizeBeforeIncMid--;

    HWIFO_Ballance(hwifo);

    return 0;
}

// Empties hwifo, returns -1 on error
int HWIFO_Empty(struct hwifo* hwifo) {
    if (NULL == hwifo) {
        return -1;
    }

    while (hwifo->beforeIncMid != NULL) {
        struct hwifo_link* link = hwifo->beforeIncMid;
        hwifo->beforeIncMid = link->next;
        free(link);
    }
    hwifo->sizeBeforeIncMid = 0;

    while (hwifo->after != NULL) {
        struct hwifo_link* link = hwifo->after;
        hwifo->after = link->next;
        free(link);
    }
    hwifo->last = NULL;
    hwifo->sizeAfter = 0;

    return 0;
}

// Dumps all info of hwifo on console
int HWIFO_Dump(struct hwifo* hwifo) {
    if (NULL == hwifo) {
        return -1;
    }

    printf("sizeBeforeIncMid: %d\n", hwifo->sizeBeforeIncMid);
    struct hwifo_link* link = hwifo->beforeIncMid;
    while (link != NULL) {
        printf("%d, ", link->data);
        link = link->next;
    }
    printf("\n");

    printf("sizeAfter: %d\n", hwifo->sizeAfter);
    link = hwifo->after;
    while (link != NULL) {
        printf("%d, ", link->data);
        link = link->next;
    }
    printf("\n");

    return 0;
}

// Ballances the hwifo
void HWIFO_Ballance(struct hwifo* hwifo) {
    if (NULL == hwifo) {
        return;
    }

    while (hwifo->sizeAfter > hwifo->sizeBeforeIncMid) {
        struct hwifo_link* link = hwifo->after;
        hwifo->after = link->next;
        link->next = hwifo->beforeIncMid;
        hwifo->beforeIncMid = link;

        if (link == hwifo->last) {
            hwifo->last = NULL;
        }

        hwifo->sizeAfter--;
        hwifo->sizeBeforeIncMid++;
    }
}