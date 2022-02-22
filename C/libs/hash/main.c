#include <stdio.h>

#include "hash.h"

int main(void)
{
    hashtable_t *ht;
    ht = ht_create(3, STRING);
    for (int i = 0; i < 10; i++)
    {
    ht_insert(&ht, "bob", "secretary");
    ht_insert(&ht, "alice", "optometrist");
    ht_insert(&ht, "foo", "bar");
    char *name = ht_get(ht, "bob");
    printf("%s", name);
    }
    char *name = ht_get(ht, "alice");
    printf("%s", name);
    name = ht_get(ht, "foo");
    printf("%s", name);
    printf("%d", ht->size);
}