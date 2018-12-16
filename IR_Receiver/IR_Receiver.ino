#define IR_OUT 2 // INT0
#define IR_GND 3
#define IR_VCC 4

#define IR_DEBUG 1

enum { IR_IDLE, IR_HEAD, IR_CODE, IR_DONE };

#define IR_CODE_NAME(code,name) { code, #name }

typedef struct { word code; const char* name; } TIrCodeName;


TIrCodeName gIrKey24[] =
{
    IR_CODE_NAME( 0xc03f, ON ),
    IR_CODE_NAME( 0x40bf, OFF ),
    IR_CODE_NAME( 0x807f, DN ),
    IR_CODE_NAME( 0x00ff, UP ),
    IR_CODE_NAME( 0xe01f, W ),
    IR_CODE_NAME( 0x609f, B ),
    IR_CODE_NAME( 0xa05f, G ),
    IR_CODE_NAME( 0x20df, R ),
    IR_CODE_NAME( 0xd02f, FLASH ),
    IR_CODE_NAME( 0xf00f, STROBE ),
    IR_CODE_NAME( 0xc837, FADE ),
    IR_CODE_NAME( 0xe817, SMOOTH ),
    IR_CODE_NAME( 0x10ef, R1 ),
    IR_CODE_NAME( 0x30cf, R2 ),
    IR_CODE_NAME( 0x08f7, R3 ),
    IR_CODE_NAME( 0x28d7, R4 ),
    IR_CODE_NAME( 0x906f, G1 ),
    IR_CODE_NAME( 0xb04f, G2 ),
    IR_CODE_NAME( 0x8877, G3 ),
    IR_CODE_NAME( 0xa857, G4 ),
    IR_CODE_NAME( 0x50af, B1 ),
    IR_CODE_NAME( 0x708f, B2 ),
    IR_CODE_NAME( 0x48b7, B3 ),
    IR_CODE_NAME( 0x6897, B4 )
};

TIrCodeName gIrKey44[] =
{
    IR_CODE_NAME( 0x02FD, ON ),
    IR_CODE_NAME( 0x827D, PLAY ),
    IR_CODE_NAME( 0xBA45, DN ),
    IR_CODE_NAME( 0x3AC5, UP ),
    IR_CODE_NAME( 0x22DD, W ),
    IR_CODE_NAME( 0xA25D, B ),
    IR_CODE_NAME( 0x9A65, G ),
    IR_CODE_NAME( 0x1AE5, R ),
    IR_CODE_NAME( 0x2AD5, R1 ),
    IR_CODE_NAME( 0x0AF5, R2 ),
    IR_CODE_NAME( 0x38C7, R3 ),
    IR_CODE_NAME( 0x18E7, R4 ),
    IR_CODE_NAME( 0xAA55, G1 ),
    IR_CODE_NAME( 0x8A75, G2 ),
    IR_CODE_NAME( 0xB847, G3 ),
    IR_CODE_NAME( 0x9867, G4 ),
    IR_CODE_NAME( 0x926D, B1 ),
    IR_CODE_NAME( 0xB24D, B2 ),
    IR_CODE_NAME( 0x7887, B3 ),
    IR_CODE_NAME( 0x58A7, B4 ),
    IR_CODE_NAME( 0x12ED, W1 ),
    IR_CODE_NAME( 0x32CD, W2 ),
    IR_CODE_NAME( 0xF807, W3 ),
    IR_CODE_NAME( 0xD827, W4 ),
    IR_CODE_NAME( 0xE817, QUICK ),
    IR_CODE_NAME( 0xC837, SLOW ),
    IR_CODE_NAME( 0xF00F, AUTO ),
    IR_CODE_NAME( 0xD02F, FLASH ),
    IR_CODE_NAME( 0xE01F, FADE7 ),
    IR_CODE_NAME( 0x30CF, DIY1 ),
    IR_CODE_NAME( 0xB04F, DIY2 ),
    IR_CODE_NAME( 0x708F, DIY3 ),
    IR_CODE_NAME( 0x10EF, DIY4 ),
    IR_CODE_NAME( 0x906F, DIY5 ),
    IR_CODE_NAME( 0x50AF, DIY6 ),
    IR_CODE_NAME( 0x20DF, JUMP3 ),
    IR_CODE_NAME( 0xA05F, JUMP7 ),
    IR_CODE_NAME( 0x609F, FADE3 ),
    IR_CODE_NAME( 0x28D7, R_UP ),
    IR_CODE_NAME( 0x08F7, R_DN ),
    IR_CODE_NAME( 0xA857, G_UP ),
    IR_CODE_NAME( 0x8877, G_DN ),
    IR_CODE_NAME( 0x6897, B_UP ),
    IR_CODE_NAME( 0x48B7, B_DN )
};

TIrCodeName gIrChanghongTV[] =
{
    IR_CODE_NAME( 0x08F7, MUTE ),

    IR_CODE_NAME( 0x48B7, POWER ),
    IR_CODE_NAME( 0xC837, TV ),
    IR_CODE_NAME( 0x1AE5, AV ),
    IR_CODE_NAME( 0x30CF, HDMI ),
    IR_CODE_NAME( 0xBA45, USB ),
    IR_CODE_NAME( 0x52AD, RW ),
    IR_CODE_NAME( 0xD22D, FW ),
    IR_CODE_NAME( 0x32CD, BEGIN ),
    IR_CODE_NAME( 0xB24D, END ),
    IR_CODE_NAME( 0x42BD, HEART ),
    IR_CODE_NAME( 0x38C7, MTS ),
    IR_CODE_NAME( 0xEA15, CC ),
    IR_CODE_NAME( 0x2AD5, STILL ),
    IR_CODE_NAME( 0x18E7, CHLIST ),
    IR_CODE_NAME( 0x6897, INFO ),
    IR_CODE_NAME( 0xA25D, STRETCH ),
    IR_CODE_NAME( 0xFA05, HOME ),
    IR_CODE_NAME( 0xDA25, MENU ),
    IR_CODE_NAME( 0x28D7, WHAT ),
    IR_CODE_NAME( 0x22DD, EXIT ),
    IR_CODE_NAME( 0x02FD, RECALL ),
    IR_CODE_NAME( 0x9867, UP ),
    IR_CODE_NAME( 0xB847, DOWN ),
    IR_CODE_NAME( 0xE21D, RIGHT ),
    IR_CODE_NAME( 0x629D, LEFT ),
    IR_CODE_NAME( 0x50AF, ENTER ),
    IR_CODE_NAME( 0x58A7, VOL_UP ),
    IR_CODE_NAME( 0x7887, VOL_DN ),
    IR_CODE_NAME( 0xD827, CH_UP ),
    IR_CODE_NAME( 0xF807, CH_DN ),
    IR_CODE_NAME( 0x5AA5, SOUND ),
    IR_CODE_NAME( 0x8877, PICTURE ),
    IR_CODE_NAME( 0x807F, KEY1 ),
    IR_CODE_NAME( 0x40BF, KEY2 ),
    IR_CODE_NAME( 0xC03F, KEY3 ),
    IR_CODE_NAME( 0x20DF, KEY4 ),
    IR_CODE_NAME( 0xA05F, KEY5 ),
    IR_CODE_NAME( 0x609F, KEY6 ),
    IR_CODE_NAME( 0xE01F, KEY7 ),
    IR_CODE_NAME( 0x10EF, KEY8 ),
    IR_CODE_NAME( 0x906F, KEY9 ),
    IR_CODE_NAME( 0x708F, MINUS ),
    IR_CODE_NAME( 0x00FF, KEY0 ),
    IR_CODE_NAME( 0xB04F, SLEEP )
};

const struct { const char *name; word mfg; TIrCodeName *defs; byte num; } gIrDefs[] =
{
    { "LED-24Key", 0x00f7, gIrKey24, sizeof(gIrKey24)/sizeof(TIrCodeName) }, // 24 Key LED Controller (0x00f7)
//    { "LED-44Key", 0x00ff, gIrKey44, sizeof(gIrKey44)/sizeof(TIrCodeName) }, // 44 Key LED Controller (0x00ff)
    { "Changhong", 0x02fd, gIrChanghongTV, sizeof(gIrChanghongTV)/sizeof(TIrCodeName) } // Changhong TV Remote
};


byte gIrStatus = IR_IDLE;
uint32_t gIrEdgeUs = 0;
union { uint32_t u32; word u16[2]; } gIrCode;

#if IR_DEBUG
word gIrPulseOn = 0, gIrPulseOff = 0, gIrPulseCount = 0;
#endif
 

void setup() 
{
    pinMode(IR_VCC, OUTPUT);
    pinMode(IR_GND, OUTPUT);
    pinMode(IR_OUT, INPUT);

    digitalWrite(IR_GND, LOW); // power up the sensor
    digitalWrite(IR_VCC, HIGH);

    attachInterrupt(0, irInt0, CHANGE);

#if IR_DEBUG
    Serial.begin(115200);
    Serial.println("Testing IR Receiver 38kHz ...");
#endif    
}


void irInt0 ()
{
    uint32_t now = micros();
    uint32_t pulse = now - gIrEdgeUs;
    gIrEdgeUs = now;
#if IR_DEBUG
    word wpulse = pulse > 0xffff ? 0xffff : pulse;
#endif
    byte pulse8 = ((word)pulse>>8) & 0xff;

    if(PIND & B100) 
    {
        // ON: was LOW now HIGH
#if IR_DEBUG
        gIrPulseOn = wpulse;
#endif
        if(pulse8 > 20) // usually 8ms
            gIrStatus = IR_HEAD;
//        else
//        if(gIrStatus == IR_IDLE && pulse8 > 9) // PS2
//            gIrStatus = IR_CODE;
    }
    else
    {
        // OFF: was HIGH now LOW
#if IR_DEBUG
        gIrPulseOff = wpulse;
#endif
        if(gIrStatus == IR_HEAD) {
            gIrCode.u32 = pulse8 < 12 ? 1 : 0; // 2.2ms repeat, 4.4ms code
            gIrStatus = IR_CODE;
        } else
        if(gIrStatus == IR_CODE) {
            if(pulse8 > 16)
                gIrStatus = IR_DONE;
            else
                gIrCode.u32 = (gIrCode.u32 << 1) | (pulse8 > 4 ? 1 : 0);
        }
    }

#if IR_DEBUG
    gIrPulseCount ++;
#endif
}


bool irHasCode ()
{

    if(gIrStatus == IR_DONE) {
        gIrStatus = IR_IDLE;
        return true;
    }

    if(gIrStatus == IR_CODE) {
        uint32_t pulse = micros() - gIrEdgeUs;
        if(pulse < 0xffff0000L && pulse > 100000L) {
            gIrStatus = IR_IDLE;
            return true;
        }
    }
    
    return false;
}


#if IR_DEBUG

#include <stdarg.h>
#define printf PRINTF
void PRINTF(char *fmt, ... )
{
    char buf[128]; // resulting string limited to 128 chars
    va_list args;
    va_start (args, fmt );
    vsnprintf(buf, 128, fmt, args);
    va_end (args);
    Serial.print(buf);
}

byte ir_learn = 0;
word ir_all[128];
byte ir_dist[8];
byte ir_num = 0;
uint32_t xx = 0;

void irDebugRemoteControl ()
{
    char tmp[16];
    uint32_t pause = micros() - gIrEdgeUs;
    if(pause > 0xffff0000) // seems like micros() can go back
        pause = 0;

    switch(ir_learn)
    {
        case 0:
            Serial.println("Press any key on the remote ...");
            ir_learn = 1;
            gIrPulseOn = 0;
            gIrPulseCount = 0;
            break;
        case 1:
            if(ir_num>8 && pause > 3000000L) {
                ir_learn = 2;
                xx = pause;
                return;
            }
            if(gIrPulseOn) {
                sprintf(tmp, "%s%u,%u", gIrPulseCount>0?" ":"", gIrPulseOff, gIrPulseOn);
                Serial.print(tmp);
                if(gIrPulseCount % 16 == 0)
                    Serial.println();
                if(ir_num < sizeof(ir_all)/sizeof(ir_all[0])) {
                    ir_all[ir_num] = gIrPulseOff;
                    ir_all[ir_num+1] = gIrPulseOn;
                    ir_num += 2;
                }
                gIrPulseOn = 0;
            }
            break;
            
        case 2:
            word onlo=0xffff, onhi=0, offlo=0xffff, offhi=0;
            for(int i=0; i<ir_num; i+=2) {
                if(ir_all[i] != 0xffff && ir_all[i] > offhi)
                    offhi = ir_all[i];
                if(ir_all[i] < offlo)
                    offlo = ir_all[i];
                if(ir_all[i+1] > onhi)
                    onhi = ir_all[i+1];
                if(ir_all[i+1] < onlo)
                    onlo = ir_all[i+1];
            }
            printf("\n\noff low: %u", offlo);
            printf("\noff hi:  %u", offhi);
            printf("\non min:  %u", onlo);
            printf("\non max:  %u", onhi);

            word lo = (offlo > onlo ? onlo : offlo)/2, hi;
            uint32_t total; byte num;
            for(word hi=lo*3; hi<0x7fff; lo=hi,hi*=2) {
                printf("\n\nBucket %d - %d [us]:", lo, hi);
                num = 0;
                total = 0;
                for(int i=0; i<ir_num; i+=2)
                    if(ir_all[i] > lo && ir_all[i] <=hi) {
                        total += ir_all[i];
                        num++;
                    }
                if(num)
                    printf("\nOFF: %d (%d)", num, total/num);
                num = 0;
                total = 0;
                for(int i=1; i<ir_num; i+=2)
                    if(ir_all[i] > lo && ir_all[i] <=hi) {
                        total += ir_all[i];
                        num++;
                    }
                if(num)
                    printf("\nON:  %d (%d)", num, total/num);
            }
            
            ir_learn = 3;
            break;
    }

}

#endif // #if IR_DEBUG

void loop() 
{
//    return irDebugRemoteControl();
    
    bool hasCode = irHasCode();
    if(hasCode) {
#if IR_DEBUG
        if(gIrCode.u32 == 1)
            printf(" HOLD");
        else
        {
            for(byte m=0; m<sizeof(gIrDefs)/sizeof(gIrDefs[0]); m++) if(gIrDefs[m].mfg == gIrCode.u16[1])
                for(byte i=0; i<gIrDefs[m].num; i++)
                    if(gIrDefs[m].defs[i].code == gIrCode.u16[0]) {
                        printf("\n%s %s", gIrDefs[m].name, gIrDefs[m].defs[i].name);
                        hasCode = false;
                    }
            if(hasCode)
                printf("\n0x%08lX", gIrCode);
        }
#endif    
        gIrStatus = IR_IDLE;
    } 
}


