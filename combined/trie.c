#include "trie.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

Trie* make_trie(enum trie_type t){
    Trie *ret = malloc(sizeof(Trie));
    ret->children = (TrieNode**) malloc(((int) t) * (sizeof (TrieNode*)));
    int i;
    for(i = 0; i < (int) t; i++){
        ret->children[i] = NULL;
    }
    ret->type = t;
    return ret;
}

TrieNode* make_trie_node(uint8_t value, enum trie_type t){
    TrieNode* ret = malloc(sizeof(TrieNode));
    ret->value = value;
    ret->endpoint = 0;
    ret->children = (TrieNode**) malloc (((int) t) * (sizeof (TrieNode*)));
    int i;
    for(i = 0; i < (int) t; i++){
        ret->children[i] = NULL;
    }
    return ret;
}

int trie_insert(Trie *t, void *item, int sz){
    uint8_t *byte = (uint8_t*) item;
    union eight_bit_value *curr = (union eight_bit_value*) byte;
    int i; //loop counter
    TrieNode *currNode = NULL;

    switch (t->type) {
        case BIT:
            if(t->children[curr->bits.b0] == NULL){
                t->children[curr->bits.b0] = make_trie_node(curr->bits.b0, t->type);
            }
            currNode = t->children[curr->bits.b0];
            if(currNode->children[curr->bits.b1] == NULL){
                currNode->children[curr->bits.b1] = make_trie_node(curr->bits.b1, t->type);
            }
            currNode = currNode->children[curr->bits.b1];
            if(currNode->children[curr->bits.b2] == NULL){
                currNode->children[curr->bits.b2] = make_trie_node(curr->bits.b2, t->type);
            }
            currNode = currNode->children[curr->bits.b2];
            if(currNode->children[curr->bits.b3] == NULL){
                currNode->children[curr->bits.b3] = make_trie_node(curr->bits.b3, t->type);
            }
            currNode = currNode->children[curr->bits.b3];
            if(currNode->children[curr->bits.b4] == NULL){
                currNode->children[curr->bits.b4] = make_trie_node(curr->bits.b4, t->type);
            }
            currNode = currNode->children[curr->bits.b4];
            if(currNode->children[curr->bits.b5] == NULL){
                currNode->children[curr->bits.b5] = make_trie_node(curr->bits.b5, t->type);
            }
            currNode = currNode->children[curr->bits.b5];
            if(currNode->children[curr->bits.b6] == NULL){
                currNode->children[curr->bits.b6] = make_trie_node(curr->bits.b6, t->type);
            }
            currNode = currNode->children[curr->bits.b6];
            if(currNode->children[curr->bits.b7] == NULL){
                currNode->children[curr->bits.b7] = make_trie_node(curr->bits.b7, t->type);
            }
            currNode = currNode->children[curr->bits.b7];

            if(sz == 1) { 
                if(currNode->endpoint){ return 0; } //value already in trie.
                currNode->endpoint = 1; 
                return 1; 
            } //one byte long -> done now.

            for(i = 1; i < sz; i++) { //iterate over rest of bytes in input
                curr = (union eight_bit_value*) &(byte[i]);
                if(currNode->children[curr->bits.b0] == NULL){
                    currNode->children[curr->bits.b0] = make_trie_node(curr->bits.b0, t->type);
                }
                currNode = currNode->children[curr->bits.b0];
                if(currNode->children[curr->bits.b1] == NULL){
                    currNode->children[curr->bits.b1] = make_trie_node(curr->bits.b1, t->type);
                }
                currNode = currNode->children[curr->bits.b1];
                if(currNode->children[curr->bits.b2] == NULL){
                    currNode->children[curr->bits.b2] = make_trie_node(curr->bits.b2, t->type);
                }
                currNode = currNode->children[curr->bits.b2];
                if(currNode->children[curr->bits.b3] == NULL){
                    currNode->children[curr->bits.b3] = make_trie_node(curr->bits.b3, t->type);
                }
                currNode = currNode->children[curr->bits.b3];
                if(currNode->children[curr->bits.b4] == NULL){
                    currNode->children[curr->bits.b4] = make_trie_node(curr->bits.b4, t->type);
                }
                currNode = currNode->children[curr->bits.b4];
                if(currNode->children[curr->bits.b5] == NULL){
                    currNode->children[curr->bits.b5] = make_trie_node(curr->bits.b5, t->type);
                }
                currNode = currNode->children[curr->bits.b5];
                if(currNode->children[curr->bits.b6] == NULL){
                    currNode->children[curr->bits.b6] = make_trie_node(curr->bits.b6, t->type);
                }
                currNode = currNode->children[curr->bits.b6];
                if(currNode->children[curr->bits.b7] == NULL){
                    currNode->children[curr->bits.b7] = make_trie_node(curr->bits.b7, t->type);
                }
                currNode = currNode->children[curr->bits.b7];
            }
            if(currNode->endpoint){ return 0; } //value already in trie
            currNode->endpoint = 1;
            return 1;
            break;

        case DBLBIT:
            if(t->children[curr->dblbits.db0] == NULL){
                t->children[curr->dblbits.db0] = make_trie_node(curr->dblbits.db0, t->type);
            }
            currNode = t->children[curr->dblbits.db0];
            if(currNode->children[curr->dblbits.db1] == NULL){
                currNode->children[curr->dblbits.db1] = make_trie_node(curr->dblbits.db1, t->type);
            }
            currNode = currNode->children[curr->dblbits.db1];
            if(currNode->children[curr->dblbits.db2] == NULL){
                currNode->children[curr->dblbits.db2] = make_trie_node(curr->dblbits.db2, t->type);
            }
            currNode = currNode->children[curr->dblbits.db2];
            if(currNode->children[curr->dblbits.db3] == NULL){
                currNode->children[curr->dblbits.db3] = make_trie_node(curr->dblbits.db3, t->type);
            }
            currNode = currNode->children[curr->dblbits.db3];

            if(sz == 1) { 
                if(currNode->endpoint){ return 0; } //value already in trie.
                currNode->endpoint = 1; 
                return 1; 
            } //one byte long -> done now.

            for(i = 1; i < sz; i++) { //iterate over rest of bytes in input
                curr = (union eight_bit_value*) &(byte[i]);
                //printf("byte %d has value %d\n", i, curr->whole);
                if(currNode->children[curr->dblbits.db0] == NULL){
                    currNode->children[curr->dblbits.db0] = make_trie_node(curr->dblbits.db0, t->type);
                }
                currNode = currNode->children[curr->dblbits.db0];
                if(currNode->children[curr->dblbits.db1] == NULL){
                    currNode->children[curr->dblbits.db1] = make_trie_node(curr->dblbits.db1, t->type);
                }
                currNode = currNode->children[curr->dblbits.db1];
                if(currNode->children[curr->dblbits.db2] == NULL){
                    currNode->children[curr->dblbits.db2] = make_trie_node(curr->dblbits.db2, t->type);
                }
                currNode = currNode->children[curr->dblbits.db2];
                if(currNode->children[curr->dblbits.db3] == NULL){
                    currNode->children[curr->dblbits.db3] = make_trie_node(curr->dblbits.db3, t->type);
                }
                currNode = currNode->children[curr->dblbits.db3];
            }
            if(currNode->endpoint){ return 0; } //value already in trie
            currNode->endpoint = 1;
            return 1;
            break;

        case NIBBLE:
            if(t->children[curr->nibbles.n0] == NULL){
                t->children[curr->nibbles.n0] = make_trie_node(curr->nibbles.n0, t->type);
            }
            currNode = t->children[curr->nibbles.n0];
            if(currNode->children[curr->nibbles.n1] == NULL){
                currNode->children[curr->nibbles.n1] = make_trie_node(curr->nibbles.n1, t->type);
            }
            currNode = currNode->children[curr->nibbles.n1];

            if(sz == 1) { 
                if(currNode->endpoint){ return 0; } //value already in trie.
                currNode->endpoint = 1; 
                return 1; 
            } //one byte long -> done now.

            for(i = 1; i < sz; i++) { //iterate over rest of bytes in input
                curr = (union eight_bit_value*) &(byte[i]);
                if(currNode->children[curr->nibbles.n0] == NULL){
                    currNode->children[curr->nibbles.n0] = make_trie_node(curr->nibbles.n0, t->type);
                }
                currNode = currNode->children[curr->nibbles.n0];
                if(currNode->children[curr->nibbles.n1] == NULL){
                    currNode->children[curr->nibbles.n1] = make_trie_node(curr->nibbles.n1, t->type);
                }
                currNode = currNode->children[curr->nibbles.n1];
            }
            if(currNode->endpoint){ return 0; } //value already in trie
            currNode->endpoint = 1;
            return 1;
            break;

        case BYTE:
            if(t->children[curr->whole] == NULL){
                t->children[curr->whole] = make_trie_node(curr->whole, t->type);
            }
            currNode = t->children[curr->whole];

            if(sz == 1) { 
                if(currNode->endpoint){ return 0; } //value already in trie.
                currNode->endpoint = 1; 
                return 1; 
            } //one byte long -> done now.

            for(i = 1; i < sz; i++) { //iterate over rest of bytes in input
                curr = (union eight_bit_value*) &(byte[i]);
                if(currNode->children[curr->whole] == NULL){
                    currNode->children[curr->whole] = make_trie_node(curr->whole, t->type);
                }
                currNode = currNode->children[curr->whole];
            }
            if(currNode->endpoint){ return 0; } //value already in trie
            currNode->endpoint = 1;
            return 1;
            break;

        default:
            printf("Don't know how to insert with trie type %d!\n", t->type);
            exit(-1);
            break;
    }
}

int trie_traverse(Trie* t, void* item, int sz, enum trie_action ta){
    uint8_t *byte = (uint8_t*) item;
    union eight_bit_value *curr = (union eight_bit_value*) byte;
    int i; //loop counter
    TrieNode *currNode = NULL; //for work besides the root node

    switch (t->type) {
        case BIT:
            if(t->children[curr->bits.b0] == NULL){
                return 0;
            }
            currNode = t->children[curr->bits.b0];
            if(currNode->children[curr->bits.b1] == NULL){
                return 0;
            }
            currNode = currNode->children[curr->bits.b1];
            if(currNode->children[curr->bits.b2] == NULL){
                return 0;
            }
            currNode = currNode->children[curr->bits.b2];
            if(currNode->children[curr->bits.b3] == NULL){
                return 0;
            }
            currNode = currNode->children[curr->bits.b3];
            if(currNode->children[curr->bits.b4] == NULL){
                return 0;
            }
            currNode = currNode->children[curr->bits.b4];
            if(currNode->children[curr->bits.b5] == NULL){
                return 0;
            }
            currNode = currNode->children[curr->bits.b5];
            if(currNode->children[curr->bits.b6] == NULL){
                return 0;
            }
            currNode = currNode->children[curr->bits.b6];
            if(currNode->children[curr->bits.b7] == NULL){
                return 0;
            }
            currNode = currNode->children[curr->bits.b7];

            if(sz == 1) { 
                if(currNode->endpoint){ 
                    if(ta == DELETE){
                        currNode->endpoint = 0;
                    } 
                    return 1;
                } else {
                    return 0;
                }
            } //one byte long -> done now.

            for(i = 1; i < sz; i++) { //iterate over rest of bytes in input
                curr = (union eight_bit_value*) &(byte[i]); 
                if(currNode->children[curr->bits.b0] == NULL){
                    return 0;
                }
                currNode = currNode->children[curr->bits.b0];
                if(currNode->children[curr->bits.b1] == NULL){
                    return 0;
                }
                currNode = currNode->children[curr->bits.b1];
                if(currNode->children[curr->bits.b2] == NULL){
                    return 0;
                }
                currNode = currNode->children[curr->bits.b2];
                if(currNode->children[curr->bits.b3] == NULL){
                    return 0;
                }
                currNode = currNode->children[curr->bits.b3];
                if(currNode->children[curr->bits.b4] == NULL){
                    return 0;
                }
                currNode = currNode->children[curr->bits.b4];
                if(currNode->children[curr->bits.b5] == NULL){
                    return 0;
                }
                currNode = currNode->children[curr->bits.b5];
                if(currNode->children[curr->bits.b6] == NULL){
                    return 0;
                }
                currNode = currNode->children[curr->bits.b6];
                if(currNode->children[curr->bits.b7] == NULL){
                    return 0;
                }
                currNode = currNode->children[curr->bits.b7];
            }
            if(currNode->endpoint){ 
                if(ta == DELETE){
                    currNode->endpoint = 0;
                }
                return 1;
            } 
            return 0;

            break;

        case DBLBIT:
            if(t->children[curr->dblbits.db0] == NULL){
                return 0;
            }
            currNode = t->children[curr->dblbits.db0];
            if(currNode->children[curr->dblbits.db1] == NULL){
                return 0;
            }
            currNode = currNode->children[curr->dblbits.db1];
            if(currNode->children[curr->dblbits.db2] == NULL){
                return 0;
            }
            currNode = currNode->children[curr->dblbits.db2];
            if(currNode->children[curr->dblbits.db3] == NULL){
                return 0;
            }
            currNode = currNode->children[curr->dblbits.db3];

            if(sz == 1) { 
                if(currNode->endpoint){ 
                    if(ta == DELETE){
                        currNode->endpoint = 0;
                    } 
                    return 1;
                } else {
                    return 0;
                }
            } //one byte long -> done now.

            for(i = 1; i < sz; i++) { //iterate over rest of bytes in input
                curr = (union eight_bit_value*) &(byte[i]); 
                if(currNode->children[curr->dblbits.db0] == NULL){
                    return 0;
                }
                currNode = currNode->children[curr->dblbits.db0];
                if(currNode->children[curr->dblbits.db1] == NULL){
                    return 0;
                }
                currNode = currNode->children[curr->dblbits.db1];
                if(currNode->children[curr->dblbits.db2] == NULL){
                    return 0;
                }
                currNode = currNode->children[curr->dblbits.db2];
                if(currNode->children[curr->dblbits.db3] == NULL){
                    return 0;
                }
                currNode = currNode->children[curr->dblbits.db3];
            }
            if(currNode->endpoint){ 
                if(ta == DELETE){
                    currNode->endpoint = 0;
                }
                return 1;
            } 
            return 0;

            break;

        case NIBBLE:
            if(t->children[curr->nibbles.n0] == NULL){
                return 0;
            }
            currNode = t->children[curr->nibbles.n0];
            if(currNode->children[curr->nibbles.n1] == NULL){
                return 0;
            }
            currNode = currNode->children[curr->nibbles.n1];

            if(sz == 1) { 
                if(currNode->endpoint){ 
                    if(ta == DELETE){
                        currNode->endpoint = 0;
                    } 
                    return 1;
                } else {
                    return 0;
                }
            } //one byte long -> done now.

            for(i = 1; i < sz; i++) { //iterate over rest of bytes in input
                curr = (union eight_bit_value*) &(byte[i]); 
                if(currNode->children[curr->nibbles.n0] == NULL){
                    return 0;
                }
                currNode = currNode->children[curr->nibbles.n0];
                if(currNode->children[curr->nibbles.n1] == NULL){
                    return 0;
                }
                currNode = currNode->children[curr->nibbles.n1];
            }
            if(currNode->endpoint){ 
                if(ta == DELETE){
                    currNode->endpoint = 0;
                }
                return 1;
            } 
            return 0;

            break;

        case BYTE:
            if(t->children[curr->whole] == NULL){
                return 0;
            }
            currNode = t->children[curr->whole];

            if(sz == 1) { 
                if(currNode->endpoint){ 
                    if(ta == DELETE){
                        currNode->endpoint = 0;
                    } 
                    return 1;
                } else {
                    return 0;
                }
            } //one byte long -> done now.

            for(i = 1; i < sz; i++) { //iterate over rest of bytes in input
                curr = (union eight_bit_value*) &(byte[i]); 
                if(currNode->children[curr->whole] == NULL){
                    return 0;
                }
                currNode = currNode->children[curr->whole];
            }
            if(currNode->endpoint){ 
                if(ta == DELETE){
                    currNode->endpoint = 0;
                }
                return 1;
            } 
            return 0;

            break;

        default:
            printf("Don't know how to traverse with trie type %d!\n", t->type);
            exit(-2);
            break;
    }
}

int trie_delete(Trie *t, void *item, int sz){
    return trie_traverse(t, item, sz, DELETE);
}

int trie_search(Trie *t, void *item, int sz){
    return trie_traverse(t, item, sz, SEARCH);
}
#define NRANDOM 1000
int main(){
    Trie * tries[4];
    tries[0] = make_trie(BIT);
    tries[1] = make_trie(DBLBIT);
    tries[2] = make_trie(NIBBLE);
    tries[3] = make_trie(BYTE);
    int i, ret, j;
    int len = sizeof(uint32_t);
    uint32_t randoms[NRANDOM];
    int FD = open("/dev/urandom",O_RDONLY);
    printf("generating random numbers...");
    for(i = 0; i < NRANDOM; i++){
        read(FD, (void*) &(randoms[i]), len);
    }
    printf("done.\n");

    struct timespec ts_before, ts_after;
    memset(&ts_before, 0, sizeof(struct timespec));
    memset(&ts_after, 0, sizeof(struct timespec));

    for(j = 0; j < 4; j++){
        clock_gettime(CLOCK_MONOTONIC, &ts_before);
        printf("working on trie %d.\n", j);
        Trie *t = tries[j];
        printf("inserting into trie %d...", j);
        for(i = 0; i < NRANDOM; i++){
            if(!trie_insert(t, (void*) &(randoms[i]), len)){
                printf("error inserting %u into trie!\n", randoms[i]);
            }
        }
        printf("done.\n");

        printf("searching in trie %d...", j);
        for(i = 0; i < NRANDOM; i++){
            if(!trie_search(t, (void*) &(randoms[i]), len)){
                printf("error searching for %u in trie!\n", randoms[i]);
            }
        }
        printf("done.\n");
        
        printf("deleting in trie %d...", j);
        for(i = 0; i < NRANDOM; i++){
            trie_delete(t, (void*) &(randoms[i]), len);
        }
        printf("done.\n");

        printf("making sure delete worked in trie %d...", j);
        for(i = 0; i < NRANDOM; i++){
            if(trie_search(t, (void*) &(randoms[i]), len)){
                printf("found %u in the trie after it was supposed to be gone!\n", randoms[i]);
            }
        }
        printf("done.\n");
        clock_gettime(CLOCK_MONOTONIC, &ts_after); 
        
        printf("time delta: %li seconds, %u nanoseconds\n", 
                ts_after.tv_sec - ts_before.tv_sec,
                abs(ts_after.tv_nsec - ts_before.tv_nsec));

        memset(&ts_before, 0, sizeof(struct timespec));
        memset(&ts_after, 0, sizeof(struct timespec));
    }
}
