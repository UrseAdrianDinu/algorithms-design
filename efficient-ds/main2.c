#include "Sequence2.h"
int main()
{
    Sequence s = init();
    s = insert(s, 99, 0);
    s = insert(s, 21, 1);
    s = insert(s, 10, 2);
    s = insert(s, 12, 3);
    s = insert(s, 40, 4);
    s = insert(s, 521, 5);
    printf("Size = %d\n", size(s));
    afisare(s);
    printf("LOOKUP(2)=%d\n", lookup(s, 2));
    printf("SET(2)=500\n");
    set(s, 500, 2);
    printf("LOOKUP(2)=%d\n", lookup(s, 2));
    Sequence a = init();
    a = insert(a, 2131, 6);
    a = insert(a, 31, 7);
    a = insert(a, 133, 8);
    a = insert(a, 131, 9);
    a = insert(a, 141, 10);
    a = insert(a, 144, 11);
    a = insert(a, 122, 12);
    printf("Size = %d\n", size(a));
    afisare(a);
    printf("CONCAT\n");
    Sequence con = concat(s, a);
    printf("Size = %d\n", size(con));
    afisare(con);
    printf("SPLIT\n");
    Sequence *sp = split(con, 5);
    printf("Lower : ");
    afisare(sp[0]);
    printf("Greater : ");
    afisare(sp[1]);
    Sequence s3 = init();
    s3 = insert(s3, 1, 0);
    s3 = insert(s3, 2, 1);
    s3 = insert(s3, 3, 2);
    s3 = insert(s3, 4, 3);
    s3 = insert(s3, 5, 4);
    s3 = insert(s3, 6, 5);
    s3 = insert(s3, 7, 6);
    afisare(s3);
    printf("Delete 3\n");
    delete (s3, 3);
    afisare(s3);

    return 0;
}