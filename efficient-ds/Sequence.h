#include <stdio.h>
#include <stdlib.h>
typedef int Type;
typedef struct sequence
{
    int value;
    struct sequence *left, *right;
    int height;
    int index;
} * Sequence;
Sequence init();
Sequence insert(Sequence data_structure, Type item, int index);
Sequence delete (Sequence data_structure, int index);
Type lookup(Sequence data_structure, int index);
Sequence
set(Sequence data_structure, Type item, int index);
int size(Sequence data_structure);
Sequence *split(Sequence data_structure, int index);
Sequence concat(Sequence data_structure1, Sequence data_structure2);
void preorder(Sequence root);