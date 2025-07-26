#include "Sequence.h"
//Returneaza structura vida
Sequence init()
{
    Sequence s = NULL;
    return s;
}
//Returneaza maximul dintre 2 numere
int max(int a, int b)
{
    return (a > b) ? a : b;
}
//Returneaza inaltimea nodului s
int height(Sequence s)
{
    if (s == NULL)
        return 0;
    return s->height;
}
//Creeaza un nod nou
Sequence createNode(int value, int index)
{
    Sequence newNode = malloc(sizeof(struct sequence));
    newNode->value = value;
    newNode->index = index;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
//Rotire la dreapta
Sequence rotateright(Sequence s)
{
    Sequence a = s->left;
    Sequence b = a->right;
    //Rotire
    a->right = s;
    s->left = b;
    //Updatarea inaltimilor
    s->height = max(height(s->left), height(s->right)) + 1;
    a->height = max(height(a->left), height(a->right)) + 1;
    return a;
}
//Rotire la stanga
Sequence rotateleft(Sequence s)
{
    Sequence a = s->right;
    Sequence b = a->left;
    //Rotire
    a->left = s;
    s->right = b;
    //Updatarea inaltimilor
    s->height = max(height(s->left), height(s->right)) + 1;
    a->height = max(height(a->left), height(a->right)) + 1;
    return a;
}
//Returneaza diferenta de inaltime dintre subarborele stang si cel drept
int balance(Sequence s)
{
    if (s == NULL)
        return 0;
    return height(s->left) - height(s->right);
}
Sequence insert(Sequence data_structure, Type item, int index)
{
    //Cautare recursiva a locului corespunzator inserarii
    if (data_structure == NULL)
    {
        return createNode(item, index);
    }
    if (index < data_structure->index)
        data_structure->left = insert(data_structure->left, item, index);
    else if (index > data_structure->index)
        data_structure->right = insert(data_structure->right, item, index);
    else
        return data_structure;
    //Updatarea inaltimii
    data_structure->height = 1 + max(height(data_structure->left), height(data_structure->right));
    //Balansarea arborelui
    int b = balance(data_structure);
    if (b > 1 && index < data_structure->left->index)
        return rotateright(data_structure);
    if (b < -1 && index > data_structure->right->index)
        return rotateleft(data_structure);
    if (b > 1 && index > data_structure->left->index)
    {
        data_structure->left = rotateleft(data_structure->left);
        return rotateright(data_structure);
    }
    if (b < -1 && index < data_structure->right->index)
    {
        data_structure->right = rotateright(data_structure->right);
        return rotateleft(data_structure);
    }
    return data_structure;
}
//Functie de parcurgere in preordine
void preorder(Sequence root)
{
    if (root != NULL)
    {
        printf("%d ", root->index);
        preorder(root->left);
        preorder(root->right);
    }
}
//Functie care intoarce nodul cu indexul cel mai mic din arborele root
Sequence min_index(Sequence root)
{
    Sequence current = root;
    while (current && current->left != NULL)
        current = current->left;

    return current;
}
//Functie care scade indexul tuturor nodurilor care au indexul mai mic decat
//cel dat ca parametru
void subindex(Sequence root, int index)
{
    if (root != NULL)
    {
        if (root->index > index)
            root->index -= 1;
        subindex(root->left, index);
        subindex(root->right, index);
    }
}

Sequence delete (Sequence data_structure, int index)
{
    //Cautare recursiva a nodului
    if (data_structure == NULL)
        return data_structure;
    if (index < data_structure->index)
        data_structure->left = delete (data_structure->left, index);
    else if (index > data_structure->index)
        data_structure->right = delete (data_structure->right, index);
    else
    {
        //Cazul in care este frunza
        if (data_structure->left == NULL && data_structure->right == NULL)
        {
            free(data_structure);
            return NULL;
        }
        else
        {
            //Are un singur copil
            if (data_structure->left == NULL)
            {
                Sequence temp = data_structure->right;
                free(data_structure);
                return temp;
            }
            else if (data_structure->right == NULL)
            {
                Sequence temp = data_structure->left;
                free(data_structure);
                return temp;
            }
            //Cazul in care are 2 copii
            else
            {
                //temp retine succesorul inordine
                Sequence temp = min_index(data_structure->right);
                data_structure->index = temp->index;
                data_structure->right = delete (data_structure->right, temp->index);
            }
        }
    }
    //Updatarea inaltimii
    data_structure->height = 1 + max(height(data_structure->left), height(data_structure->right));
    //Balansarea arborelui
    int b = balance(data_structure);
    if (b > 1 && balance(data_structure->left) >= 0)
    {
        return rotateright(data_structure);
    }
    if (b > 1 && balance(data_structure->left) < 0)
    {
        data_structure->left = rotateleft(data_structure->left);
        return rotateright(data_structure);
    }
    if (b < -1 && balance(data_structure->right) <= 0)
    {

        return rotateleft(data_structure);
    }
    if (b < -1 && balance(data_structure->right) > 0)
    {
        data_structure->right = rotateright(data_structure->right);
        return rotateleft(data_structure);
    }
    subindex(data_structure, index);
    return data_structure;
}

Type lookup(Sequence data_structure, int index)
{

    Sequence aux = data_structure;
    //Cautarea nodului
    while (aux && aux->index != index)
    {
        if (index > aux->index)
            aux = aux->right;
        else
            aux = aux->left;
    }
    //Nodul nu a fost gasit
    if (aux == NULL)
        return -1;
    return aux->value;
}

Sequence set(Sequence data_structure, Type item, int index)
{
    Sequence aux = data_structure;
    //Cautarea nodului
    while (aux && aux->index != index)
    {
        if (index > aux->index)
            aux = aux->right;
        else
            aux = aux->left;
    }
    if (aux != NULL)
        aux->value = item;
    return data_structure;
}

int size(Sequence data_structure)
{
    Sequence aux = data_structure;
    //Gasirea nodului care are cel mai mare index
    while (aux != NULL && aux->right != NULL)
        aux = aux->right;
    return aux->index + 1;
}
//Funcie care creeaza un vector bazat pe valorile nodurilor din s
void avltoarray(Sequence s, int *values)
{
    if (s != NULL)
    {
        *(values + s->index) = s->value;
        avltoarray(s->left, values);
        avltoarray(s->right, values);
    }
}

Sequence *split(Sequence data_structure, int index)
{
    int dim = size(data_structure);
    Sequence *s = malloc(2 * sizeof(struct sequence));
    s[0] = init();
    s[1] = init();
    //values retine valorile nodurilor din data_structure
    int *values = calloc(dim + 1, sizeof(int));
    avltoarray(data_structure, values);
    int i;
    //parcurgere values
    for (i = 0; i < dim; i++)
    {
        //daca i<=index,atunci am inserat la s[0]
        if (i <= index)
        {
            s[0] = insert(s[0], values[i], i);
        }
        //daca i>index,atunci am inserat la s[1]
        else
        {
            s[1] = insert(s[1], values[i], i - index - 1);
        }
    }
    return s;
}

Sequence concat(Sequence data_structure1, Sequence data_structure2)
{
    //Am creat o structura noua care initial este data_structure1
    Sequence con = data_structure1;
    int dim2 = size(data_structure2);
    int *values = calloc(dim2 + 1, sizeof(int));
    //values retine valorile nodurile din data_structure2
    avltoarray(data_structure2, values);
    int i;
    int dim1 = size(data_structure1);
    //am parcurs values
    for (i = 0; i < dim2; i++)
    {
        //am inserat in con values[i] pe pozitia actualizata
        con = insert(con, values[i], dim1 + i);
    }
    return con;
}