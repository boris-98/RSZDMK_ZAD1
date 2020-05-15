#include <LiquidCrystal.h>
#include <util/delay.h>
#include <stdlib.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

byte niz[4][8] = {
  {B00000,
   B01010,
   B11111,
   B11111,  //herc
   B01110,
   B00100,
   B00000},

  {B00100,
   B01110,
   B11111,
   B11111,  //karo
   B01110,
   B00100,
   B00000},

  {B00100,
   B01110,
   B11111,
   B11111,  //pik
   B01110,
   B01110,
   B11111},

  {B00100,
   B01110,
   B10101,
   B11111,  //tref
   B10101,
   B01110,
   B11111}
};

char ocitaj_taster()
{
  char taster = 0;
  unsigned char row;

  MCUCR &= ~0x10;
  PORTD = 0x0f;

  for(row = 0x80; row != 0x08; row >>= 1)
  {
    DDRD = row;
	_delay_ms(2);

    switch(row | ((~PIND) & 0x0f))
    {
      case 0x88:
      	taster = '1'; break;
      case 0x84:
      	taster = '2'; break;
      case 0x82:
      	taster = '3'; break;
      case 0x81:
      	taster = 'A'; break;

	  case 0x48:
      	taster = '4'; break;
      case 0x44:
      	taster = '5'; break;
      case 0x42:
      	taster = '6'; break;
      case 0x41:
      	taster = 'B'; break;

	  case 0x28:
      	taster = '7'; break;
      case 0x24:
      	taster = '8'; break;
      case 0x22:
      	taster = '9'; break;
      case 0x21:
      	taster = 'C'; break;

	  case 0x18:
      	taster = '*'; break;
      case 0x14:
      	taster = '0'; break;
      case 0x12:
      	taster = '#'; break;
      case 0x11:
      	taster = 'D'; break;
    }
  }

  return taster;
}

int main()
{
  	lcd.begin(16, 2);
    lcd.print("Pritisnite *");

	while(1)
    {
     	char taster = ocitaj_taster();
    	while(taster != '*'){
    		taster = ocitaj_taster();
        }

      	lcd.clear();

      	int j;
  		for(int i = 0; i < 4; i++){
          	uint32_t seed = 0;
          	seed++;
          	randomSeed(seed);

            j = rand() %3 + 0;

            lcd.createChar(0, niz[j]);
          	lcd.setCursor(i, 0);
            lcd.write(byte(0));
        }
      	_delay_ms(2000);
      	lcd.clear();

      	lcd.print("____");
        int n = 0, m = 0, k = 0;
      	lcd.setCursor(n, m);
      	lcd.cursor();

      	byte pokusaj[4][8];

      	while(taster != '5'){
      		taster = ocitaj_taster();
          	if(taster != 0 && taster == '4'){
              	if(n==0){
              		n = 0;
                } else {
              		n--;
                }
              	lcd.setCursor(n, m);

              	while(taster==ocitaj_taster());
            } else if (taster != 0 && taster == '6'){
            	if(n==3){
              		n = 3;
                } else {
              		n++;
                }
              	lcd.setCursor(n, m);

              	while(taster==ocitaj_taster());
            } else if (taster != 0 && taster == '2'){
            	if(k==3){
              		k = 3;
                } else {
              		k++;
                }
             	for(int i = 0; i < 8; i++){
              		pokusaj[k][i] = niz[k][i];
              	}
              	lcd.createChar(0, pokusaj[n]);
              	lcd.setCursor(n, m);
              	lcd.write(byte(0));

                while(taster==ocitaj_taster());
            } else if (taster != 0 && taster == '8'){
            	if(k==0){
              		k = 0;
                } else {
              		k--;
                }
              	for(int i = 0; i < 8; i++){
              		pokusaj[k][i] = niz[k][i];
              	}
              	lcd.createChar(0, pokusaj[n]);
              	lcd.setCursor(n, m);
              	lcd.write(byte(0));

              	while(taster==ocitaj_taster());
            }
      	}
	  	for(int i = 0; i < 4; i++){
            lcd.createChar(0, niz[i]);
          	lcd.setCursor(i, 1);
            lcd.write(byte(0));
        }
      	lcd.print("KRAJ");
    }

  	return 0;
}
