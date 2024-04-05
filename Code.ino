#define          character_shifting_time        3000
#define          display_conflict_time          32000
#define          all_byte                       62
#define          eight_led_column               8



int main(){
volatile char *dirf, *dirk, *outf, *outk;

dirf=0x30;      *dirf=0xff;     outf=0x31;    // PORTF set as output
dirk=0x107;     *dirk=0xff;     outk=0x108;   // PORTK set as output

volatile char arr[] = {
 0, 0, 0, 0, 0, 0, 0, 0,   // for the initial display blank

0b11111111,
0b11111111,
0b01100000,
0b00110000,
0b00110000,
0b01100000,
0b11111111,
0b11111111, // W

0b00000000,
0b01110000,
0b11111000,
0b10101000,
0b10101000,
0b10111000,
0b00110000,
0b00000000, // e

//0b00000000,
0b00000000,
0b00000000,
0b01111111,
0b11111111,
0b10000000,
//0b00000000,
0b00000000, // l

0b00000000,
0b01110000,
0b11111000,
0b10001000,
0b10011000,
0b10011000,
//0b00000000,
0b00000000, // c

0b00000000,
0b01110000,
0b11111000,
0b10001000,
0b10001000,
0b11111000,
0b01110000,
0b00000000, // o

0b11110000,
0b11111000,
0b00001000,
0b11111000,
0b11110000,
0b00001000,
0b11111000,
0b11110000, // m

0b00000000,
0b01110000,
0b11111000,
0b10101000,
0b10101000,
0b10111000,
0b00110000,
0b00000000, // e

0, 0, 0, 0, 0, 0, 0, 0,   // for the final display blank
};


while(1){
 for(char array_byte = 0; array_byte < all_byte; array_byte++){ 
 for(volatile long a = 0; a < character_shifting_time; a++){              // this is the each character shifting time
 for(char led_column = 0; led_column < eight_led_column; led_column++){
 *outf = 128 >> led_column;                // this select each column of the led matrix at a time
 *outk = ~(arr[array_byte + led_column]);  // this select each byte of the array at a time
 *outk = 0xff;                             // put 5v to all leds -ve pin
 *outf = 0;                                // put 0v to all leds +ve pin
  }
 }
 for(volatile long b = 0; b < display_conflict_time; b++);  // This delay avoid conflicts between two adjacent displaying contents on the matrix dispaly 
 }
}
}
