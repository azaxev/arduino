#include "FastLED.h"

// FastLED.r = blue
// FastLED.g = red
// FastLED.b = green

// How many leds in your strip?
#define NUM_LEDS1 84
#define NUM_LEDS2 36
#define NUM_LEDS (NUM_LEDS1+NUM_LEDS2)
#define S2(i) (NUM_LEDS1*2-1-i)

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS1+NUM_LEDS2];


//
// this routine exists to normalize colors for this strip
//
CRGB strip_fix_color (CRGB color, byte brightness=0xff)
{
    CRGB tmp;
    tmp.g = (word)color.r * brightness / 0x100;
    tmp.b = (word)color.g * brightness / 0x100; // green is too dominant?
    tmp.r = (word)color.b * brightness / 0x100;
    return tmp;
}

//
// animate LEDs forward
//
void strip_fw ()
{
    CRGB tmp = leds[NUM_LEDS1-1];
    for(byte i=NUM_LEDS1-1; i>0; i--) {
        leds[i] = leds[i-1];
		if(S2(i) < NUM_LEDS)
			leds[S2(i)] = leds[i];
	}
    leds[0] = tmp;
}

//
// animate LEDs backward
//
void strip_bw ()
{
    CRGB tmp = leds[0];
    for(byte i=1; i<NUM_LEDS1; i++) {
        leds[i-1] = leds[i];
		if(S2(i-1) < NUM_LEDS)
			leds[S2(i-1)] = leds[i];
	}
    leds[NUM_LEDS1-1] = tmp;
    leds[NUM_LEDS1] = tmp;
}

//
// setup
//

void setup() { 
      // Uncomment/edit one of the following lines for your leds arrangement.
      // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS1);
      // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS1);
      // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS1);
     FastLED.addLeds<WS2811, DATA_PIN, RGB>((CRGB*)leds, NUM_LEDS);
      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS1);
      // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS1);
//  	  FastLED.addLeds<NEOPIXEL, DATA_PIN, RGB>(leds, NUM_LEDS1);
      // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS1);

      // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS1);
      // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS1);
      // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS1);

      // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS1);
      // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS1);
      // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS1);
    memset(leds, 0, NUM_LEDS1*3);
}

void animate_random ()
{
    for(int d=0; d<100; d++) {
        for(int i=0; i<NUM_LEDS1; i++) {
            leds[i] = strip_fix_color(random(0xffffff), random(0xff));
			if(S2(i) < NUM_LEDS)
				leds[S2(i)] = leds[i];
		}
        FastLED.show();
        delay(200);
    }
}

void animate_single_color ()
{
    memset(leds, 0, NUM_LEDS1*3);
    for(int d=0; d<256; d++) {
        for(int i=0; i<NUM_LEDS1; i++) {
            int x = d*10+i*3*256/NUM_LEDS1;
            byte val = x % 256;
            byte col = (x/256) % 3;
            val = val>=128 ? (255-val) : val;
            val = val<64 ? 0 : val-64;
            leds[i] = 0;
            switch(col) {
                case 0: leds[i].r = val; break;
                case 1: leds[i].g = val; break;
                case 2: leds[i].b = val; break;
            }
			if(S2(i) < NUM_LEDS)
				leds[S2(i)] = leds[i];
        }
        FastLED.show();
        delay(50);
    }
}

void animate_larson (CRGB color, byte count=NUM_LEDS1/4, byte speed=30)
{
    memset(leds, 0, NUM_LEDS1*3);
    byte frac = NUM_LEDS1 / count;
    byte both = count * 2;

    // go forward
    for(byte i=0; i<NUM_LEDS1+count; i++) {
        strip_fw();
        if(i<both)
            leds[0] = strip_fix_color(color, (i<=count) ? (0xff * frac * i / NUM_LEDS1) : (0xff - 0xff * frac * i / NUM_LEDS1));
        else
            leds[0] = 0;
        FastLED.show();
        delay(speed);
    }
    
    // go backward
    for(byte i=0; i<NUM_LEDS1+NUM_LEDS1/8; i++) {
        strip_bw();
        if(i<count)
            leds[NUM_LEDS1-1] = strip_fix_color(color, 0xff - 0xff * frac * i / NUM_LEDS1);
        else
            leds[NUM_LEDS1-1] = 0;
        FastLED.show();
        delay(speed);
    }
}

void animate_test ()
{
//    memset(leds, 0, NUM_LEDS1*3);
    for(int d=0; d<256; d++) {
        strip_bw();
        leds[NUM_LEDS1-1] = random(0xffffff);
        word bright1 = (word)leds[NUM_LEDS1-2].r + leds[NUM_LEDS1-2].g + leds[NUM_LEDS1-2].b;
        word bright0 = (word)leds[NUM_LEDS1-1].r + leds[NUM_LEDS1-1].g + leds[NUM_LEDS1-2].b;
        if(bright1 >= 0xff*3/2 && bright0 > 0xff*3/2) {
            leds[NUM_LEDS1-1].r >>= 4;
            leds[NUM_LEDS1-1].g >>= 4;
            leds[NUM_LEDS1-1].b >>= 4;
        }
        FastLED.show();
        delay(100);
    }
}

void strip_fade ()
{
    for(byte i=0; i<NUM_LEDS1+NUM_LEDS2; i++) {
        if(leds[i].r)
            leds[i].r --;
        if(leds[i].g)
            leds[i].g --;
        if(leds[i].b)
            leds[i].b --;
		if(S2(i) < NUM_LEDS)
			leds[S2(i)] = leds[i];
    } 
}

void animate_stars (CRGB color)
{
    for(byte i=0; i<100; i++) {
        byte star = random(NUM_LEDS1);
        if(leds[star])
            leds[star] = 0;
        else
            leds[star] = strip_fix_color(color, (i%8)*32+16);
		if(S2(star) < NUM_LEDS)
			leds[S2(star)] = leds[star];
        FastLED.show();
        delay(50);
    }
    
    for(byte i=0; i<255; i++) {
        strip_fade();
        FastLED.show();
        delay(10);
    }
}

void animate_rainbow ()
{
    byte third = NUM_LEDS1/3;
    for(int dim=7; dim>=0; dim--) 
    {
        for(byte i=0; i<third; i++) {
            byte val1 = i * 0xff/third;
            byte val2 = 0xff - val1;
            leds[i].r = (val2/2)>>dim;
            leds[i].g = val1>>dim;
            if(S2(i) < NUM_LEDS)
                leds[S2(i)] = leds[i];
            leds[i+third].g = val2>>dim;
            leds[i+third].b = (val1/2)>>dim;
            if(S2(i+third) < NUM_LEDS)
    	        leds[S2(i+third)] = leds[i+third];
            leds[i+2*third].b = (val2/2)>>dim;
            leds[i+2*third].r = (val1/2)>>dim;
            if(S2(i+2*third) < NUM_LEDS)
    	        leds[S2(i+2*third)] = leds[i+2*third];
        }
        for(byte i=3*third; i<NUM_LEDS1; i++) {
            leds[i] = leds[i-1];
            if(S2(i) < NUM_LEDS)
    	        leds[S2(i)] = leds[i];
    	}

        FastLED.show();
        delay(100);
    }

    for(int i=0; i<NUM_LEDS1; i++) {
        strip_fw();
        FastLED.show();
        delay(50);
    }
    for(int i=0; i<NUM_LEDS1; i++) {
        strip_fw();
        strip_fade();
        FastLED.show();
        delay(50);
    }
    memset(leds, 0, NUM_LEDS1*3);
}

void loop() { 
//    leds[0] = strip_fix_color(CRGB::Yellow);
//    FastLED.show();
//    animate_single_color();
    animate_rainbow();
    animate_stars(CRGB::Red);
    animate_larson(CRGB::Red, 10, 20);
    animate_rainbow();
    animate_stars(CRGB::Green);
    animate_larson(CRGB::Green, 10, 20);
    animate_rainbow();
    animate_stars(CRGB::Blue);
    animate_larson(CRGB::Blue, 10, 20);
    animate_rainbow();
    animate_stars(CRGB::Yellow);
    animate_larson(CRGB::Yellow, 10, 20);
    animate_rainbow();
    animate_stars(CRGB::Purple);
    animate_larson(CRGB::Purple, 10, 20);
    animate_rainbow();
    animate_stars(CRGB::White);
    animate_larson(CRGB::White, 10, 20);
}
