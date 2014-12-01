#include "trie.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

Trie* make_trie(){
    Trie *ret = malloc(sizeof(Trie));
    int i;
    for(i = 0; i < 256; i++){
        ret->children[i] = NULL;
    }
    return ret;
}

TrieNode* make_trie_node(uint8_t value){
    TrieNode* ret = malloc(sizeof(TrieNode));
    ret->value = value;
    int i;
    for(i = 0; i < 256; i++){
        ret->children[i] = NULL;
    }
    return ret;
}

void print_value(void *item, int sz){
    int i = 0;
    printf("print_value:\n");
    uint8_t* u8ptr = (uint8_t*) item;
    union eight_bit_value byte;
    for(i = sz-1; i >= 0; i--){
        byte.whole = u8ptr[i];
        printf("byte %d value: %d\n", i, byte.whole);
        printf("%d",byte.bits.b7);
        printf("%d",byte.bits.b6);
        printf("%d",byte.bits.b5);
        printf("%d",byte.bits.b4);
        printf("%d",byte.bits.b3);
        printf("%d",byte.bits.b2);
        printf("%d",byte.bits.b1);
        printf("%d\n",byte.bits.b0);
    }

}

int trie_insert(Trie *t, void *item, int sz){
    uint8_t *byte = (uint8_t*) item;
    union eight_bit_value *curr = (union eight_bit_value*) byte;
    int i; //loop counter
    TrieNode *currNode = NULL; //for work besides the root node
    //printf("insert: byte 0 has value %d\n", curr->whole);
    //deal with the first byte
    if(t->children[curr->whole] == NULL){
        t->children[curr->whole] = make_trie_node(curr->whole);
        //printf("insert: making new node at bits.b0 with value %u\n", curr->bits.b0);
    }
    currNode = t->children[curr->whole];

    if(sz == 1) { 
        if(currNode->endpoint){ return 0; } //value already in trie.
        currNode->endpoint = 1; 
        return 1; 
    } //one byte long -> done now.

    for(i = 1; i < sz; i++) { //iterate over rest of bytes in input
        curr = (union eight_bit_value*) &(byte[i]);
        //printf("byte %d has value %d\n", i, curr->whole);
        if(currNode->children[curr->whole] == NULL){
            currNode->children[curr->whole] = make_trie_node(curr->whole);
            //printf("insert: making new node at whole with value %u\n", curr->whole);
        }
        currNode = currNode->children[curr->whole];
    }
    if(currNode->endpoint){ return 0; } //value already in trie
    currNode->endpoint = 1;
    return 1;
}

int trie_traverse(Trie *t, void *item, int sz, enum trie_action ta){
    uint8_t *byte = (uint8_t*) item;
    union eight_bit_value *curr = (union eight_bit_value*) byte;
    int i; //loop counter
    TrieNode *currNode = NULL; //for work besides the root node
    //printf("traverse: curr 0 has value %d\n", curr->whole);
    //deal with the first curr
    if(t->children[curr->whole] == NULL){
        //printf("traverse: did not find wanted value %u at whole\n", curr->whole);
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
        //printf("traverse: byte %d has value %d\n", i, curr->whole);
        if(currNode->children[curr->whole] == NULL){
            //printf("traverse: did not find wanted value %u at whole\n", curr->whole);
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
}

int trie_delete(Trie *t, void *item, int sz){
    return trie_traverse(t, item, sz, DELETE);
}

int trie_search(Trie *t, void *item, int sz){
    return trie_traverse(t, item, sz, SEARCH);
}

int main(){
    Trie* t = make_trie();
    void *vptr = NULL;
    int len = 0;
    uint32_t a = 93847542;
    char * str = "this is a test string";
    vptr = (void*) str;
    len = sizeof(char) * strlen(str);
    int insert_rc, search_rc, delete_rc, second_delete_rc, after_search_rc;
    insert_rc = trie_insert(t, vptr, len);
    search_rc = trie_search(t, vptr, len);
    delete_rc = trie_delete(t, vptr, len);
    second_delete_rc = trie_delete(t, vptr, len);
    after_search_rc = trie_search(t, vptr, len);
    printf("insert %d; search %d; delete %d, second delete %d, second search %d\n", insert_rc, search_rc, delete_rc, second_delete_rc,after_search_rc);
    srand(time(NULL));
    int i;
    uint64_t r;
    len = sizeof(r);
    int FD = open("/dev/urandom",O_RDONLY);
    for(i = 0; i < 10000; i++){
        //r = rand();
        read(FD, (void*) &r, len);
//        printf("random number r is %llu\n", r);
        insert_rc = trie_insert(t, (void*) &r, len);
        search_rc = trie_search(t, (void*) &r, len);
        delete_rc = trie_delete(t, (void*) &r, len);
        second_delete_rc = trie_delete(t, (void*) &r, len);
        after_search_rc = trie_search(t, (void*) &r, len);
        if((insert_rc != 1) || (search_rc != 1) || (delete_rc != 1) ||
           (second_delete_rc != 0) || (after_search_rc != 0)){
            printf("ERROR: r = %d; insert %d, search %d, delete %d, second delete %d; second search %d\n", r, insert_rc, search_rc, delete_rc, second_delete_rc,after_search_rc);
    
        }
    }
    close(FD);
    return 0;
}
