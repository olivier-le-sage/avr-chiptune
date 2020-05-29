/*
 * OCR0A values for different frequencies/notes.
 * The formula used is: OCR0A = CPU_f / frequency / prescale - 1
 *      assuming CPU_f = 1MHz and prescale = 64
 *
 * NB: This prescaling scheme can represent frequencies up to ~600Hz.
 */

#define REST     0   /* empty note */
#define NOTE_B0  503 /* 31Hz */
#define NOTE_C1  472 /* 33Hz */
#define NOTE_CS1 445 /* 35Hz */
#define NOTE_D1  421 /* 37Hz */
#define NOTE_DS1 400 /* 39Hz */
#define NOTE_E1  380 /* 41Hz */
#define NOTE_F1  354 /* 44Hz */
#define NOTE_FS1 339 /* 46Hz */
#define NOTE_G1  318 /* 49Hz */
#define NOTE_GS1 299 /* 52Hz */
#define NOTE_A1  283 /* 55Hz */
#define NOTE_AS1 268 /* 58Hz */
#define NOTE_B1  251 /* 62Hz */
#define NOTE_C2  239 /* 65Hz */
#define NOTE_CS2 225 /* 69Hz */
#define NOTE_D2  213 /* 73Hz */
#define NOTE_DS2 199 /* 78Hz */
#define NOTE_E2  190 /* 82Hz */
#define NOTE_F2  179 /* 87Hz */
#define NOTE_FS2 167 /* 93Hz */
#define NOTE_G2  158 /* 98Hz */
#define NOTE_GS2 149 /* 104Hz */
#define NOTE_A2  141 /* 110Hz */
#define NOTE_AS2 133 /* 117Hz */
#define NOTE_B2  126 /* 123Hz */
#define NOTE_C3  118 /* 131Hz */
#define NOTE_CS3 111 /* 139Hz */
#define NOTE_D3  105 /* 147Hz */
#define NOTE_DS3 99 /* 156Hz */
#define NOTE_E3  94 /* 165Hz */
#define NOTE_F3  88 /* 175Hz */
#define NOTE_FS3 83 /* 185Hz */
#define NOTE_G3  79 /* 196Hz */
#define NOTE_GS3 74 /* 208Hz */
#define NOTE_A3  70 /* 220Hz */
#define NOTE_AS3 66 /* 233Hz */
#define NOTE_B3  62 /* 247Hz */
#define NOTE_C4  59 /* 262Hz */
#define NOTE_CS4 55 /* 277Hz */
#define NOTE_D4  52 /* 294Hz */
#define NOTE_DS4 49 /* 311Hz */
#define NOTE_E4  46 /* 330Hz */
#define NOTE_F4  44 /* 349Hz */
#define NOTE_FS4 41 /* 370Hz */
#define NOTE_G4  39 /* 392Hz */
#define NOTE_GS4 37 /* 415Hz */
#define NOTE_A4  35 /* 440Hz */
#define NOTE_AS4 33 /* 466Hz */
#define NOTE_B4  31 /* 494Hz */
#define NOTE_C5  29 /* 523Hz */
#define NOTE_CS5 27 /* 554Hz */
#define NOTE_D5  26 /* 587Hz */
#define NOTE_DS5 24 /* 622Hz */
#define NOTE_E5  23 /* 659Hz */
#define NOTE_F5  21 /* 698Hz */
#define NOTE_FS5 20 /* 740Hz */
#define NOTE_G5  19 /* 784Hz */
#define NOTE_GS5 18 /* 831Hz */
#define NOTE_A5  17 /* 880Hz */
#define NOTE_AS5 16 /* 932Hz */
#define NOTE_B5  15 /* 988Hz */
#define NOTE_C6  14 /* 1047Hz */
#define NOTE_CS6 13 /* 1109Hz */
#define NOTE_D6  12 /* 1175Hz */
#define NOTE_DS6 12 /* 1245Hz */
#define NOTE_E6   /* 1319Hz */
#define NOTE_F6   /* 1397Hz */
#define NOTE_FS6  /* 1480Hz */
#define NOTE_G6   /* 1568Hz */
#define NOTE_GS6  /* 1661Hz */
#define NOTE_A6   /* 1760Hz */
#define NOTE_AS6  /* 1865Hz */
#define NOTE_B6   /* 1976Hz */
#define NOTE_C7   /* 2093Hz */
#define NOTE_CS7  /* 2217Hz */
#define NOTE_D7   /* 2349Hz */
#define NOTE_DS7  /* 2489Hz */
#define NOTE_E7   /* 2637Hz */
#define NOTE_F7   /* 2794Hz */
#define NOTE_FS7  /* 2960Hz */
#define NOTE_G7   /* 3136Hz */
#define NOTE_GS7  /* 3322Hz */
#define NOTE_A7   /* 3520Hz */
#define NOTE_AS7  /* 3729Hz */
#define NOTE_B7   /* 3951Hz */
#define NOTE_C8   /* 4186Hz */
#define NOTE_CS8  /* 4435Hz */
#define NOTE_D8   /* 4699Hz */
#define NOTE_DS8  /* 4978Hz */
