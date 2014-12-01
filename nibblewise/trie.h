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
    uint8_t endpoint : 1; //0 -> no, 1 -> yes
    uint8_t value : 4 ;
    struct TrieNode * children[16];
} TrieNode;

//root node
typedef struct Trie {
    TrieNode * children[16];
} Trie;

void print_value(void *item, int sz);

Trie* make_trie();

TrieNode* make_trie_node(uint8_t value);

//sz is in bytes.
//for insert, return 1 if successful, 0 otherwise
int trie_insert(Trie *t, void *item, int sz);

int trie_traverse(Trie* t, void* item, int sz, enum trie_action ta);

//for delete, return 1 if successfully deleted something, 0 otherwise
int trie_delete(Trie *t, void *item, int sz);

//for search, return 1 if the item given was found, 0 otherwise
int trie_search(Trie *t, void *item, int sz);

#endif //__TRIE_H_GUARD__
