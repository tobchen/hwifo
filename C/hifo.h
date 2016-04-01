#ifndef HIFO_H
#define HIFO_H

struct hifo;

// Creates a halfway in first out type, returns NULL on error
struct hifo* HIFO_Create(void);

// Destroys a halfway in first out type
void HIFO_Destroy(struct hifo* hifo);

// Returns hifo's size, returns -1 on error (for example hifo is NULL)
int HIFO_GetSize(struct hifo* hifo);

// Pushes element on hifo, returns -1 on error
int HIFO_Push(struct hifo* hifo, int data);

// Stores next element of hifo in data, returns -1 on error (or empty)
// data may be NULL
int HIFO_Peek(struct hifo* hifo, int* data);

// Stores next element of hifo in data, removes it,
// returns -1 on error (or empty)
// data may be NULL
int HIFO_Pop(struct hifo* hifo, int* data);

// Empties hifo, returns -1 on error
int HIFO_Empty(struct hifo* hifo);

// Dumps all info of hifo on console
int HIFO_Dump(struct hifo* hifo);

#endif // HIFO_H