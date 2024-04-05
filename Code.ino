#define          character_shifting_time        500
#define          display_conflict_time          32000
#define          all_bytes                      82
#define          eight_led_columns              8


int main(){
  
    volatile char *dirf, *dirk, *outf, *outk, *dira, *outa, *dirc, *outc, *dirl, *outl;
    char led_column;


    dirf=0x30;      *dirf=0xff;     outf=0x31;    // PORTF set as output
    dirk=0x107;     *dirk=0xff;     outk=0x108;   // PORTK set as output
    dira=0x21;      *dira=0xff;     outa=0x22;    // PORTA set as output 
    dirc=0x27;      *dirc=0xff;     outc=0x28;    // PORTC set as output
    dirl=0x10a;     *dirl=0xff;     outl=0x10b;   // PORTL set as output


  volatile char arr[] = {
    0, 0, 0, 0, 0, 0, 0, 0,   // These 32 byte zeros for the initial display blank
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,

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
    //0b00000000,
    //0b00000000,
    0b01111111,
    0b11111111,
    0b10000000,
    //0b00000000,
    //0b00000000, // l

    0b00000000,
    0b01110000,
    0b11111000,
    0b10001000,
    0b10011000,
    0b10011000,
    //0b00000000,
    //0b00000000, // c

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

    0, 0, 0, 0, 0, 0, 0, 0,   // These 32 byte zeros for the final display blank
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
  };


while(1){
  for(char array_byte = 0; array_byte < all_bytes; array_byte++){ 

    for(volatile long a = 0; a < character_shifting_time; a++){      // this is the each character shifting time


/* The following loop displays only the 1st columns to 8th columns of the 8*32 LED Matrix Display */
        for(led_column = 0; led_column < eight_led_columns; led_column++){
            *outf = 128 >> led_column;                  // this selects each column (1-8) of the led matrix at a time
            *outk = ~(arr[array_byte + led_column]);    // this selects each byte of the array at a time
            *outk = 0xff;                               // put 5v to all leds -ve pin
            *outf = 0;                                  // put 0v to all leds +ve pin
          }


/* The following loop displays only the 9th columns to 16th columns of the 8*32 LED Matrix Display */
        for(led_column = 0; led_column < eight_led_columns; led_column++){
            *outa = 128 >> led_column;                    // this selects each column (9-16) of the led matrix at a time
            *outk = ~(arr[array_byte + led_column + 8]);  // this selects each byte of the array at a time (but not 1st 8 bytes)
            *outk = 0xff;                                 // put 5v to all leds -ve pin
            *outa = 0;                                    // put 0v to all leds +ve pin
          }


/* The following loop displays only the 17th columns to 24th columns of the 8*32 LED Matrix Display */
        for(led_column = 0; led_column < eight_led_columns; led_column++){
            *outc = 128 >> led_column;                     // this selects each column (17-24) of the led matrix at a time
            *outk = ~(arr[array_byte + led_column + 16]);  // this selects each byte of the array at a time (but not 1st 16 bytes)
            *outk = 0xff;                                  // put 5v to all leds -ve pin
            *outc = 0;                                     // put 0v to all leds +ve pin
          }


/* The following loop displays only the 25th columns to 32th columns of the 8*32 LED Matrix Display */
        for(led_column = 0; led_column < eight_led_columns; led_column++){
            *outl = 128 >> led_column;                     // this selects each column (25-32) of the led matrix at a time
            *outk = ~(arr[array_byte + led_column + 24]);  // this selects each byte of the array at a time (but not 1st 24 bytes)
            *outk = 0xff;                                  // put 5v to all leds -ve pin
            *outl = 0;                                     // put 0v to all leds +ve pin
          }
       }
      for(volatile long b = 0; b < display_conflict_time; b++);  // This delay avoid conflicts between two adjacent displaying contents on the matrix dispaly 
     }
  }
}