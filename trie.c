#include "trie.h"

Trie* make_trie(){
    Trie *ret = malloc(sizeof(Trie));
    ret->children[0] = NULL;
    ret->children[1] = NULL;
    return ret;
}

TrieNode* make_trie_node(uint8_t value){
    TrieNode* ret = malloc(sizeof(TrieNode));
    ret->value = value;
    ret->children[0] = NULL;
    ret->children[1] = NULL;
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
    if(t->children[curr->bits.b0] == NULL){
        t->children[curr->bits.b0] = make_trie_node(curr->bits.b0);
        //printf("insert: making new node at bits.b0 with value %u\n", curr->bits.b0);
    }
    currNode = t->children[curr->bits.b0];
    if(currNode->children[curr->bits.b1] == NULL){
        currNode->children[curr->bits.b1] = make_trie_node(curr->bits.b1);
        //printf("insert: making new node at bits.b1 with value %u\n", curr->bits.b1);
    }
    currNode = currNode->children[curr->bits.b1];
    if(currNode->children[curr->bits.b2] == NULL){
        currNode->children[curr->bits.b2] = make_trie_node(curr->bits.b2);
        //printf("insert: making new node at bits.b2 with value %u\n", curr->bits.b2);
    }
    currNode = currNode->children[curr->bits.b2];
    if(currNode->children[curr->bits.b3] == NULL){
        currNode->children[curr->bits.b3] = make_trie_node(curr->bits.b3);
        //printf("insert: making new node at bits.b3 with value %u\n", curr->bits.b3);
    }
    currNode = currNode->children[curr->bits.b3];
    if(currNode->children[curr->bits.b4] == NULL){
        currNode->children[curr->bits.b4] = make_trie_node(curr->bits.b4);
        //printf("insert: making new node at bits.b4 with value %u\n", curr->bits.b4);
    }
    currNode = currNode->children[curr->bits.b4];
    if(currNode->children[curr->bits.b5] == NULL){
        currNode->children[curr->bits.b5] = make_trie_node(curr->bits.b5);
        //printf("insert: making new node at bits.b5 with value %u\n", curr->bits.b5);
    }
    currNode = currNode->children[curr->bits.b5];
    if(currNode->children[curr->bits.b6] == NULL){
        currNode->children[curr->bits.b6] = make_trie_node(curr->bits.b6);
        //printf("insert: making new node at bits.b6 with value %u\n", curr->bits.b6);
    }
    currNode = currNode->children[curr->bits.b6];
    if(currNode->children[curr->bits.b7] == NULL){
        currNode->children[curr->bits.b7] = make_trie_node(curr->bits.b7);
        //printf("insert: making new node at bits.b7 with value %u\n", curr->bits.b7);
    }
    currNode = currNode->children[curr->bits.b7];

    if(sz == 1) { 
        if(currNode->endpoint){ return 0; } //value already in trie.
        currNode->endpoint = 1; 
        return 1; 
    } //one byte long -> done now.

    for(i = 1; i < sz; i++) { //iterate over rest of bytes in input
        curr = (union eight_bit_value*) &(byte[i]);
        //printf("byte %d has value %d\n", i, curr->whole);
        if(currNode->children[curr->bits.b0] == NULL){
            currNode->children[curr->bits.b0] = make_trie_node(curr->bits.b0);
            //printf("insert: making new node at bits.b0 with value %u\n", curr->bits.b0);
        }
        currNode = currNode->children[curr->bits.b0];
        if(currNode->children[curr->bits.b1] == NULL){
            currNode->children[curr->bits.b1] = make_trie_node(curr->bits.b1);
            //printf("insert: making new node at bits.b1 with value %u\n", curr->bits.b1);
        }
        currNode = currNode->children[curr->bits.b1];
        if(currNode->children[curr->bits.b2] == NULL){
            currNode->children[curr->bits.b2] = make_trie_node(curr->bits.b2);
            //printf("insert: making new node at bits.b2 with value %u\n", curr->bits.b2);
        }
        currNode = currNode->children[curr->bits.b2];
        if(currNode->children[curr->bits.b3] == NULL){
            currNode->children[curr->bits.b3] = make_trie_node(curr->bits.b3);
            //printf("insert: making new node at bits.b3 with value %u\n", curr->bits.b3);
        }
        currNode = currNode->children[curr->bits.b3];
        if(currNode->children[curr->bits.b4] == NULL){
            currNode->children[curr->bits.b4] = make_trie_node(curr->bits.b4);
            //printf("insert: making new node at bits.b4 with value %u\n", curr->bits.b4);
        }
        currNode = currNode->children[curr->bits.b4];
        if(currNode->children[curr->bits.b5] == NULL){
            currNode->children[curr->bits.b5] = make_trie_node(curr->bits.b5);
            //printf("insert: making new node at bits.b5 with value %u\n", curr->bits.b5);
        }
        currNode = currNode->children[curr->bits.b5];
        if(currNode->children[curr->bits.b6] == NULL){
            currNode->children[curr->bits.b6] = make_trie_node(curr->bits.b6);
            //printf("insert: making new node at bits.b6 with value %u\n", curr->bits.b6);
        }
        currNode = currNode->children[curr->bits.b6];
        if(currNode->children[curr->bits.b7] == NULL){
            currNode->children[curr->bits.b7] = make_trie_node(curr->bits.b7);
            //printf("insert: making new node at bits.b7 with value %u\n", curr->bits.b7);
        }
        currNode = currNode->children[curr->bits.b7];
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
    if(t->children[curr->bits.b0] == NULL){
        //printf("traverse: did not find wanted value %u at bits.b0\n", curr->bits.b0);
        return 0;
    }
    currNode = t->children[curr->bits.b0];
    if(currNode->children[curr->bits.b1] == NULL){
        //printf("traverse: did not find wanted value %u at bits.b1\n", curr->bits.b1);
        return 0;
    }
    currNode = currNode->children[curr->bits.b1];
    if(currNode->children[curr->bits.b2] == NULL){
        //printf("traverse: did not find wanted value %u at bits.b2\n", curr->bits.b2);
        return 0;
    }
    currNode = currNode->children[curr->bits.b2];
    if(currNode->children[curr->bits.b3] == NULL){
        //printf("traverse: did not find wanted value %u at bits.b3\n", curr->bits.b3);
        return 0;
    }
    currNode = currNode->children[curr->bits.b3];
    if(currNode->children[curr->bits.b4] == NULL){
        //printf("traverse: did not find wanted value %u at bits.b4\n", curr->bits.b4);
        return 0;
    }
    currNode = currNode->children[curr->bits.b4];
    if(currNode->children[curr->bits.b5] == NULL){
        //printf("traverse: did not find wanted value %u at bits.b5\n", curr->bits.b5);
        return 0;
    }
    currNode = currNode->children[curr->bits.b5];
    if(currNode->children[curr->bits.b6] == NULL){
        //printf("traverse: did not find wanted value %u at bits.b6\n", curr->bits.b6);
        return 0;
    }
    currNode = currNode->children[curr->bits.b6];
    if(currNode->children[curr->bits.b7] == NULL){
        //printf("traverse: did not find wanted value %u at bits.b7\n", curr->bits.b7);
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
        //printf("traverse: byte %d has value %d\n", i, curr->whole);
        if(currNode->children[curr->bits.b0] == NULL){
            //printf("traverse: did not find wanted value %u at bits.b0\n", curr->bits.b0);
            return 0;
        }
        currNode = currNode->children[curr->bits.b0];
        if(currNode->children[curr->bits.b1] == NULL){
            //printf("traverse: did not find wanted value %u at bits.b1\n", curr->bits.b1);
            return 0;
        }
        currNode = currNode->children[curr->bits.b1];
        if(currNode->children[curr->bits.b2] == NULL){
            //printf("traverse: did not find wanted value %u at bits.b2\n", curr->bits.b2);
            return 0;
        }
        currNode = currNode->children[curr->bits.b2];
        if(currNode->children[curr->bits.b3] == NULL){
            //printf("traverse: did not find wanted value %u at bits.b3\n", curr->bits.b3);
            return 0;
        }
        currNode = currNode->children[curr->bits.b3];
        if(currNode->children[curr->bits.b4] == NULL){
            //printf("traverse: did not find wanted value %u at bits.b4\n", curr->bits.b4);
            return 0;
        }
        currNode = currNode->children[curr->bits.b4];
        if(currNode->children[curr->bits.b5] == NULL){
            //printf("traverse: did not find wanted value %u at bits.b5\n", curr->bits.b5);
            return 0;
        }
        currNode = currNode->children[curr->bits.b5];
        if(currNode->children[curr->bits.b6] == NULL){
            //printf("traverse: did not find wanted value %u at bits.b6\n", curr->bits.b6);
            return 0;
        }
        currNode = currNode->children[curr->bits.b6];
        if(currNode->children[curr->bits.b7] == NULL){
            //printf("traverse: did not find wanted value %u at bits.b7\n", curr->bits.b7);
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
    int insert_rc, search_rc, delete_rc, after_search_rc;
    insert_rc = trie_insert(t, vptr, len);
    search_rc = trie_search(t, vptr, len);
    delete_rc = trie_delete(t, vptr, len);
    after_search_rc = trie_search(t, vptr, len);
    printf("insert %d; search %d; delete %d, second search %d\n", insert_rc, search_rc, delete_rc, after_search_rc);
    return 0;
}
