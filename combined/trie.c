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

#define NSEC_PER_SEC 1000000000

//given two times, start and end, calculate the elapsed time from start to end and store it in delta
//taken with modifications from http://www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime/
//Since we're using CLOCK_MONOTONIC below, we don't need to worry about negative times
void timespec_diff(struct timespec *start, struct timespec *end, struct timespec *delta){
    if((end->tv_nsec - start->tv_nsec) < 0){
        delta->tv_sec = end->tv_sec - start->tv_sec - 1;
        delta->tv_nsec = NSEC_PER_SEC + end->tv_nsec - start->tv_nsec;
    } else {
        delta->tv_sec = end->tv_sec - start->tv_sec;
        delta->tv_nsec = end->tv_nsec - start->tv_nsec;
    }
}

//given a time t and a divisor d, put into delta the result of dividing the time t into d parts.
void timespec_div(struct timespec *t, int d, struct timespec *delta){
    uint64_t total = (NSEC_PER_SEC * t->tv_sec) + t->tv_nsec;
    total /= d;
    delta->tv_sec = total / NSEC_PER_SEC;
    delta->tv_nsec = total % NSEC_PER_SEC; 
}

int main(int argc, char** argv){
    if(argc != 5){
        printf("Usage: ./trie <count> <integer size in bytes> <input file> <trie type [1-4]>\n");
        exit(-1);
    }
    int i, ret;
    int count = atoi(argv[1]);
    int len = atoi(argv[2]);
    uint8_t randoms[count*len]; //store each integer as a bunch of adjacent bytes; this allows us to point to the first byte, but "bite" off the whole integer (har har).
    int FD = open(argv[3],O_RDONLY);
    int type = atoi(argv[4]);
    Trie *t = NULL;
    switch (type){
        case 1:
            t = make_trie(BIT);
            break;
        case 2:
            t = make_trie(DBLBIT);
            break;
        case 3:
            t = make_trie(NIBBLE);
            break;
        case 4:
            t = make_trie(BYTE);
            break;
        default:
            printf("I don't know what trie of type %d is!\n", type);
            exit(-2);
            break;
    }
    if(!FD){
        printf("Error opening %s for reading.\n", argv[1]);
        exit(-2);
    }
    //printf("reading %d integers of size %d bytes from %s...",count, len, argv[3]);
    for(i = 0; i < count; i += len){
        if(read(FD, (void*) &(randoms[i]), len) != len){
            printf("read() failed! exiting...\n");
            exit(-3);
        }
    }
    close(FD);
    //printf("done.\noperating on trie of type %d...",type);

    //Here's what we do:
    //for each integer:
    //  attempt to insert the integer, make sure it works by inspecting the return code
    //  attempt to insert the integer again, make sure it fails this time (as that integer was already inserted)
    //  search for the integer, make sure it exists in the trie by inspecting the return code
    //  delete the integer, make sure the deletion works by inspecting the return code
    //  search for the integer, make sure it doesn't exist, as it just got deleted
    //  delete the integer again, make sure this delete fails since the element is already gone.
    //This all assumes that the set of integers we store has no duplicates, as done by the generation process in the included python script.
    printf("%d,%d,%d,", count, len, type);
    struct timespec ts_before, ts_after, delta, divided;
    memset(&ts_before, 0, sizeof(struct timespec));
    memset(&ts_after, 0, sizeof(struct timespec));
    memset(&delta, 0, sizeof(struct timespec));
    memset(&divided, 0, sizeof(struct timespec));

    clock_gettime(CLOCK_MONOTONIC, &ts_before);
    //printf("inserting into trie %d...", j);
    for(i = 0; i < count; i += len){
        if(!trie_insert(t, (void*) &(randoms[i]), len)){
            printf("error inserting %u into trie!\n", randoms[i]);
        }
    }
    //printf("done.\n");
    clock_gettime(CLOCK_MONOTONIC, &ts_after);
    timespec_diff(&ts_before, &ts_after, &delta);
    timespec_div(&delta, count, &divided);
    printf("%li.%09u,%li.%09u,", 
           delta.tv_sec, delta.tv_nsec, 
           divided.tv_sec, divided.tv_nsec);
    
    clock_gettime(CLOCK_MONOTONIC, &ts_before);
    //printf("checking insert into trie %d...", j);
    for(i = 0; i < count; i += len){
        if(trie_insert(t, (void*) &(randoms[i]), len)){
            printf("error inserting %u into trie after it was already inserted!\n", randoms[i]);
        }
    }
    //printf("done.\n");
    clock_gettime(CLOCK_MONOTONIC, &ts_after); 
    timespec_diff(&ts_before, &ts_after, &delta);
    timespec_div(&delta, count, &divided);
    printf("%li.%09u,%li.%09u,", 
           delta.tv_sec, delta.tv_nsec, 
           divided.tv_sec, divided.tv_nsec);

    clock_gettime(CLOCK_MONOTONIC, &ts_before);
    //printf("searching in trie %d...", j);
    for(i = 0; i < count; i += len){
        if(!trie_search(t, (void*) &(randoms[i]), len)){
            printf("error searching for %u in trie!\n", randoms[i]);
        }
    }
    //printf("done.\n");
    clock_gettime(CLOCK_MONOTONIC, &ts_after); 
    timespec_diff(&ts_before, &ts_after, &delta);
    timespec_div(&delta, count, &divided);
    printf("%li.%09u,%li.%09u,", 
           delta.tv_sec, delta.tv_nsec, 
           divided.tv_sec, divided.tv_nsec);
   
    clock_gettime(CLOCK_MONOTONIC, &ts_before);
    //printf("deleting in trie %d...", j);
    for(i = 0; i < count; i += len){
        if(!trie_delete(t, (void*) &(randoms[i]), len)){
            printf("error deleting %u from trie!\n", randoms[i]);
        }
    }
    //printf("done.\n");
    clock_gettime(CLOCK_MONOTONIC, &ts_after); 
    timespec_diff(&ts_before, &ts_after, &delta);
    timespec_div(&delta, count, &divided);
    printf("%li.%09u,%li.%09u,", 
           delta.tv_sec, delta.tv_nsec, 
           divided.tv_sec, divided.tv_nsec);
   
    clock_gettime(CLOCK_MONOTONIC, &ts_before);
    //printf("checking delete in trie %d...", j);
    for(i = 0; i < count; i += len){
        if(trie_delete(t, (void*) &(randoms[i]), len)){
            printf("error deleting %u from trie after it was already deleted!!\n", randoms[i]);
        }
    }
    //printf("done.\n");
    clock_gettime(CLOCK_MONOTONIC, &ts_after); 
    timespec_diff(&ts_before, &ts_after, &delta);
    timespec_div(&delta, count, &divided);
    printf("%li.%09u,%li.%09u,", 
           delta.tv_sec, delta.tv_nsec, 
           divided.tv_sec, divided.tv_nsec);
   
    clock_gettime(CLOCK_MONOTONIC, &ts_before);
    //printf("making sure delete worked in trie %d...", j);
    for(i = 0; i < count; i += len){
        if(trie_search(t, (void*) &(randoms[i]), len)){
            printf("found %u in trie after it was supposed to be gone!\n", randoms[i]);
        }
    }
    //printf("done.\n");
    clock_gettime(CLOCK_MONOTONIC, &ts_after); 
    timespec_diff(&ts_before, &ts_after, &delta);
    timespec_div(&delta, count, &divided);
    printf("%li.%09u,%li.%09u", 
           delta.tv_sec, delta.tv_nsec, 
           divided.tv_sec, divided.tv_nsec);
   //printf("done.\n");
    /*
    printf("time delta: %li seconds, %u nanoseconds\n", 
            ts_after.tv_sec - ts_before.tv_sec,
            abs(ts_after.tv_nsec - ts_before.tv_nsec));
    */
    //unsigned long long delta = 1000000000 * (ts_after.tv_sec - ts_before.tv_sec) + abs(ts_after.tv_nsec - ts_before.tv_nsec);
    /*printf("%d,%d,%d,%li.%09u\n", 
            count, len, type, 
            ts_after.tv_sec - ts_before.tv_sec,
            abs(ts_after.tv_nsec - ts_before.tv_nsec));*/
    //printf("%d,%d,%d,%llu\n", count, len, type, delta);
    //memset(&ts_before, 0, sizeof(struct timespec));
    //memset(&ts_after, 0, sizeof(struct timespec));
    printf("\n");
}
