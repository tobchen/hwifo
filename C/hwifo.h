#ifndef HWIFO_H
#define HWIFO_H

struct hwifo;

// Creates a halfway in first out type, returns NULL on error
struct hwifo* HWIFO_Create(void);

// Destroys a halfway in first out type
void HWIFO_Destroy(struct hwifo* hwifo);

// Returns hwifo's size, returns -1 on error (for example hwifo is NULL)
int HWIFO_GetSize(struct hwifo* hwifo);

// Pushes element on hwifo, returns -1 on error
int HWIFO_Push(struct hwifo* hwifo, int data);

// Stores next element of hwifo in data, returns -1 on error (or empty)
// data may be NULL
int HWIFO_Peek(struct hwifo* hwifo, int* data);

// Stores next element of hwifo in data, removes it,
// returns -1 on error (or empty)
// data may be NULL
int HWIFO_Pop(struct hwifo* hwifo, int* data);

// Empties hwifo, returns -1 on error
int HWIFO_Empty(struct hwifo* hwifo);

// Dumps all info of hwifo on console
int HWIFO_Dump(struct hwifo* hwifo);

#endif // HWIFO_H