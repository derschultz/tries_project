#ifndef __TRIE_H_GUARD__
#define __TRIE_H_GUARD__

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

enum trie_action {
    SEARCH,
    DELETE
};

//store number of children in type
enum trie_type {
    BIT = 2,
    DBLBIT = 4,
    NIBBLE = 16,
    BYTE = 256
};

union eight_bit_value {
    uint8_t whole;
    struct {
        unsigned int n0:4;
        unsigned int n1:4;
    } nibbles;
    struct {
        unsigned int db0:2;
        unsigned int db1:2;
        unsigned int db2:2;
        unsigned int db3:2;
    } dblbits;
    struct {
        unsigned int b0:1;
        unsigned int b1:1;
        unsigned int b2:1;
        unsigned int b3:1;
        unsigned int b4:1;
        unsigned int b5:1;
        unsigned int b6:1;
        unsigned int b7:1;
    } bits;
} eight_bit_value;

typedef struct TrieNode {
    uint8_t endpoint;
    uint8_t value;
    enum trie_type type; //easier just to include this than a pointer to the root.
    struct TrieNode ** children;
} TrieNode;

typedef struct Trie {
    TrieNode ** children;
    enum trie_type type;
} Trie;

Trie* make_trie(enum trie_type type);

TrieNode* make_trie_node(uint8_t value, enum trie_type t);

//sz is in bytes.
//for insert, return 1 if successful, 0 otherwise
int trie_insert(Trie *t, void *item, int sz);

int trie_traverse(Trie* t, void* item, int sz, enum trie_action ta);

//for delete, return 1 if successfully deleted something, 0 otherwise
int trie_delete(Trie *t, void *item, int sz);

//for search, return 1 if the item given was found, 0 otherwise
int trie_search(Trie *t, void *item, int sz);
 
#endif //__TRIE_H_GUARD__
