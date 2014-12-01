#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

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

int main(){
    uint8_t value = 1;
    union eight_bit_value ebv;
    while(value > 0){
        ebv.whole = value;
        /*
        printf("value: %d\n", value);
        printf("b0: %d; db0: %d; n0: %d\n", ebv.bits.b0, ebv.dblbits.db0, ebv.nibbles.n0);
        printf("b1: %d; db1: %d; n1: %d\n", ebv.bits.b1, ebv.dblbits.db1, ebv.nibbles.n1);
        printf("b2: %d; db2: %d\n", ebv.bits.b2, ebv.dblbits.db2);
        printf("b3: %d; db3: %d\n", ebv.bits.b3, ebv.dblbits.db3);
        printf("b4: %d\n", ebv.bits.b4);
        printf("b5: %d\n", ebv.bits.b5);
        printf("b6: %d\n", ebv.bits.b6);
        printf("b7: %d\n", ebv.bits.b7);
        */
        printf("%d -> %d%d%d%d%d%d%d%d\n", 
                value, 
                ebv.bits.b7, 
                ebv.bits.b6, 
                ebv.bits.b5,
                ebv.bits.b4, 
                ebv.bits.b3, 
                ebv.bits.b2, 
                ebv.bits.b1, 
                ebv.bits.b0);
        value += 1;
        sleep(0.1);
    }

    return 0;
}
