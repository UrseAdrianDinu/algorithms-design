#include "Sequence2.h"
//Returneaza structura vida
Sequence init()
{
    Sequence s = NULL;
    return s;
}
Sequence insert(Sequence data_structure, Type item, int index)
{
    //Structura este vida
    if (data_structure == NULL)
    {
        data_structure = malloc(sizeof(struct sequence));
        data_structure->v = malloc(sizeof(int));
        *data_structure->v = item;
        data_structure->size = 1;
        return data_structure;
    }
    else
    {
        //Daca nu este vida,atunci am marit dimensiunea vectorului
        //L-am realocat si am pus pe ultima pozitie item
        data_structure->size++;
        data_structure->v = realloc(data_structure->v, data_structure->size * sizeof(int));
        data_structure->v[data_structure->size - 1] = item;
        return data_structure;
    }
}

Sequence delete (Sequence data_structure, int index)
{
    int i;
    //Am facut o shiftuire la stanga a elementelor de la pozitia index pana la final
    for (i = index; i < data_structure->size - 1; i++)
    {
        data_structure->v[i] = data_structure->v[i + 1];
    }
    //am scazut dimensiunea vectorului
    data_structure->size--;
    return data_structure;
}

Type lookup(Sequence data_structure, int index)
{
    //Returneaza elementul de pe pozitia index
    return data_structure->v[index];
}

Sequence set(Sequence data_structure, Type item, int index)
{
    //Seteaza elementul de pe pozitia index la item
    data_structure->v[index] = item;
    return data_structure;
}

int size(Sequence data_structure)
{
    //Returneaza dimensiunea vectorului
    return data_structure->size;
}

Sequence *split(Sequence data_structure, int index)
{
    //Am declarat un vector de structuri cu 2 elemente
    Sequence *sp = malloc(2 * sizeof(Sequence));
    //Am alocat memorie si am setat dimensiunile celor 2 elemente
    sp[0] = malloc(sizeof(struct sequence));
    sp[0]->size = index + 1;
    sp[1] = malloc(sizeof(struct sequence));
    sp[1]->size = data_structure->size - index - 1;
    sp[0]->v = data_structure->v; //Am copiat adresa vectorului din cadrul primului argument
    sp[1]->v = data_structure->v + index + 1; //Am copiat adresa vectorului + index + 1
    return sp;
}

Sequence concat(Sequence data_structure1, Sequence data_structure2)
{
    //Am declarat o structura noua
    Sequence s = malloc(sizeof(struct sequence));
    s->v = malloc((data_structure1->size + data_structure2->size) * sizeof(int));
    s->size = data_structure1->size + data_structure2->size;
    int i;
    //Am copiat elementele din data_structure1 si data_structure2
    //in structura noua
    for (i = 0; i < data_structure1->size + data_structure2->size; i++)
    {
        if (i < data_structure1->size)
        {
            s->v[i] = data_structure1->v[i];
        }
        else
        {
            s->v[i] = data_structure2->v[i - data_structure1->size];
        }
    }
    return s;
}
//Functie de afisare
void afisare(Sequence s)
{
    for (int i = 0; i < s->size; i++)
    {
        printf("%d ", s->v[i]);
    }
    printf("\n");
}
