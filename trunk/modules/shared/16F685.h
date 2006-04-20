//////// Standard Header file for the PIC16F685 device ////////////////
#device PIC16F685
#nolist
//////// Program memory: 4096x14  Data RAM: 256  Stack: 8
//////// I/O: 18   Analog Pins: 12
//////// Data EEPROM: 256
//////// C Scratch area: 20   ID Location: 2000
//////// Fuses: LP,XT,HS,EC_IO,INTRC_IO,INTRC,RC_IO,RC,PROTECT,NOPROTECT
//////// Fuses: NOBROWNOUT,BROWNOUT,MCLR,NOMCLR,CPD,NOCPD,WDT,NOWDT,PUT
//////// Fuses: NOPUT,IESO,NOIESO,FCMEN,NOFCMEN,BROWNOUT_SW,BROWNOUT_NOSL
//////// 
////////////////////////////////////////////////////////////////// I/O
// Discrete I/O Functions: SET_TRIS_x(), OUTPUT_x(), INPUT_x(),
//                         PORT_B_PULLUPS(), INPUT(),
//                         OUTPUT_LOW(), OUTPUT_HIGH(),
//                         OUTPUT_FLOAT(), OUTPUT_BIT()
// Constants used to identify pins in the above are:

#define PIN_A0  40
#define PIN_A1  41
#define PIN_A2  42
#define PIN_A3  43
#define PIN_A4  44
#define PIN_A5  45

#define PIN_B4  52
#define PIN_B5  53
#define PIN_B6  54
#define PIN_B7  55

#define PIN_C0  56
#define PIN_C1  57
#define PIN_C2  58
#define PIN_C3  59
#define PIN_C4  60
#define PIN_C5  61
#define PIN_C6  62
#define PIN_C7  63

////////////////////////////////////////////////////////////////// Useful defines
#define FALSE 0
#define TRUE 1

#define BYTE int
#define BOOLEAN short int

#define getc getch
#define fgetc getch
#define getchar getch
#define putc putchar
#define fputc putchar
#define fgets gets
#define fputs puts

////////////////////////////////////////////////////////////////// Control
// Control Functions:  RESET_CPU(), SLEEP(), RESTART_CAUSE()
// Constants returned from RESTART_CAUSE() are:
#define WDT_FROM_SLEEP  0     
#define WDT_TIMEOUT     8     
#define MCLR_FROM_SLEEP 16    
#define NORMAL_POWER_UP 24    


////////////////////////////////////////////////////////////////// Timer 0
// Timer 0 (AKA RTCC)Functions: SETUP_COUNTERS() or SETUP_TIMER_0(),
//                              SET_TIMER0() or SET_RTCC(),
//                              GET_TIMER0() or GET_RTCC()
// Constants used for SETUP_TIMER_0() are:
#define RTCC_INTERNAL   0
#define RTCC_EXT_L_TO_H 32
#define RTCC_EXT_H_TO_L 48

#define RTCC_DIV_1      8
#define RTCC_DIV_2      0
#define RTCC_DIV_4      1
#define RTCC_DIV_8      2
#define RTCC_DIV_16     3
#define RTCC_DIV_32     4
#define RTCC_DIV_64     5
#define RTCC_DIV_128    6
#define RTCC_DIV_256    7


#define RTCC_8_BIT      0     

// Constants used for SETUP_COUNTERS() are the above
// constants for the 1st param and the following for
// the 2nd param:

////////////////////////////////////////////////////////////////// WDT
// Watch Dog Timer Functions: SETUP_WDT() or SETUP_COUNTERS() (see above)
//                            RESTART_WDT()
//
#define WDT_ON          1
#define WDT_OFF         0

#define WDT_DIV_32      1
#define WDT_DIV_64      3
#define WDT_DIV_128     5
#define WDT_DIV_256     7
#define WDT_DIV_512     9
#define WDT_DIV_1024    11
#define WDT_DIV_2048    13
#define WDT_DIV_4096    15
#define WDT_DIV_8192    17
#define WDT_DIV_16394   19
#define WDT_DIV_32768   21
#define WDT_DIV_65536   23

////////////////////////////////////////////////////////////////// Timer 1
// Timer 1 Functions: SETUP_TIMER_1, GET_TIMER1, SET_TIMER1
// Constants used for SETUP_TIMER_1() are:
//      (or (via |) together constants from each group)
#define T1_DISABLED         0
#define T1_INTERNAL         0x85
#define T1_EXTERNAL         0x87
#define T1_EXTERNAL_SYNC    0x83

#define T1_CLK_OUT          8

#define T1_DIV_BY_1         0
#define T1_DIV_BY_2         0x10
#define T1_DIV_BY_4         0x20
#define T1_DIV_BY_8         0x30

// You may Or (with |) the above with one of:
#define T1_GATE           0x40
#define T1_GATE_INVERTED  0xC0

////////////////////////////////////////////////////////////////// Timer 2
// Timer 2 Functions: SETUP_TIMER_2, GET_TIMER2, SET_TIMER2
// Constants used for SETUP_TIMER_2() are:
#define T2_DISABLED         0
#define T2_DIV_BY_1         4
#define T2_DIV_BY_4         5
#define T2_DIV_BY_16        6

////////////////////////////////////////////////////////////////// CCP
// CCP Functions: SETUP_CCPx, SET_PWMx_DUTY
// CCP Variables: CCP_x, CCP_x_LOW, CCP_x_HIGH
// Constants used for SETUP_CCPx() are:
#define CCP_OFF                         0
#define CCP_CAPTURE_FE                  4
#define CCP_CAPTURE_RE                  5
#define CCP_CAPTURE_DIV_4               6
#define CCP_CAPTURE_DIV_16              7
#define CCP_COMPARE_SET_ON_MATCH        8
#define CCP_COMPARE_CLR_ON_MATCH        9
#define CCP_COMPARE_INT                 0xA
#define CCP_COMPARE_RESET_TIMER         0xB
#define CCP_PWM                         0xC
#define CCP_PWM_PLUS_1                  0x1c
#define CCP_PWM_PLUS_2                  0x2c
#define CCP_PWM_PLUS_3                  0x3c
long CCP_1;
#byte   CCP_1    =                      0x15          
#byte   CCP_1_LOW=                      0x15          
#byte   CCP_1_HIGH=                     0x16          
// The following should be used with the ECCP unit only (or these in)
#define CCP_PWM_H_H                     0x0c
#define CCP_PWM_H_L                     0x0d
#define CCP_PWM_L_H                     0x0e
#define CCP_PWM_L_L                     0x0f

#define CCP_PWM_FULL_BRIDGE             0x40
#define CCP_PWM_FULL_BRIDGE_REV         0xC0
#define CCP_PWM_HALF_BRIDGE             0x80

#define CCP_SHUTDOWN_ON_COMP1           0x100000
#define CCP_SHUTDOWN_ON_COMP2           0x200000
#define CCP_SHUTDOWN_ON_COMP            0x300000
#define CCP_SHUTDOWN_ON_INT0            0x400000
#define CCP_SHUTDOWN_ON_COMP1_INT0      0x500000
#define CCP_SHUTDOWN_ON_COMP2_INT0      0x600000
#define CCP_SHUTDOWN_ON_COMP_INT0       0x700000

#define CCP_SHUTDOWN_AC_L               0x000000
#define CCP_SHUTDOWN_AC_H               0x040000
#define CCP_SHUTDOWN_AC_F               0x080000

#define CCP_SHUTDOWN_BD_L               0x000000
#define CCP_SHUTDOWN_BD_H               0x010000
#define CCP_SHUTDOWN_BD_F               0x020000

#define CCP_SHUTDOWN_RESTART            0x80000000
#define CCP_DELAY                       0x1000000  // Multiply this by the delay count

////////////////////////////////////////////////////////////////// COMP
// Comparator Variables: C1OUT, C2OUT
// Constants used in setup_comparator() are:
//
#define NC_NC_NC_NC  0x00

#define CP1_A1_A0  0x80
#define CP1_C1_A0  0x81
#define CP1_C2_A0  0x82
#define CP1_C3_A0  0x83
#define CP1_A1_VR  0x84
#define CP1_C1_VR  0x85
#define CP1_C2_VR  0x86
#define CP1_C3_VR  0x87
#define CP1_OUT_ON_A2  0x20
#define CP1_INVERT  0x10
// Or the following with the above
#define CP2_A1_C0  0x8000
#define CP2_C1_C0  0x8100
#define CP2_C2_C0  0x8200
#define CP2_C3_C0  0x8300
#define CP2_A1_VR  0x8400
#define CP2_C1_VR  0x8500
#define CP2_C2_VR  0x8600
#define CP2_C3_VR  0x8700
#define CP2_OUT_ON_C4  0x2000
#define CP2_INVERT  0x1000
// Optionaly Or the following with the above
#define COMP_C1_LATCHED        0x300000
#define COMP_T1_SYNC          0x1000000
#define COMP_T1_GATE          0x2000000

#bit C1OUT = 0x11B.7
#bit C2OUT = 0x11B.6

////////////////////////////////////////////////////////////////// VREF
// Constants used in setup_vref() are:
//

#define VR_ENABLE      0x0800  //1.2V bandgap reference
#define VR_UNBUFFERED  0x1000  //Buffered by default
#define VREF_OUT_VR    0x0C00  //1.2V reference appears on A1
#define VREF_OUT_CVREF 0x0200  //CVREF ladder output appears on A1

#define VREF_C1_LOW    0xA0
#define VREF_C1_HIGH   0x80
#define VREF_C2_LOW    0x60
#define VREF_C2_HIGH   0x40
// OR both _LOWs or both _HIGHs together to turn on both comparators
// OR (with |) the above with a number 0-15


////////////////////////////////////////////////////////////////// INTERNAL RC
// Constants used in setup_oscillator() are:
#define OSC_31KHZ   1
#define OSC_125KHZ  0x11
#define OSC_250KHZ  0x21
#define OSC_500KHZ  0x31
#define OSC_1MHZ    0x41
#define OSC_2MHZ    0x51
#define OSC_4MHZ    0x61
#define OSC_8MHZ    0x71
#define OSC_INTRC   1
#define OSC_NORMAL  0
// Result may be (ignore all other bits)
#define OSC_STATE_STABLE 4
#define OSC_31KHZ_STABLE 2



////////////////////////////////////////////////////////////////// ADC
// ADC Functions: SETUP_ADC(), SETUP_ADC_PORTS() (aka SETUP_PORT_A),
//                SET_ADC_CHANNEL(), READ_ADC()
// Constants used for SETUP_ADC() are:
#define ADC_OFF                0              // ADC Off
#define ADC_CLOCK_DIV_2    0x100
#define ADC_CLOCK_DIV_4     0x40
#define ADC_CLOCK_DIV_8     0x10
#define ADC_CLOCK_DIV_32    0x20
#define ADC_CLOCK_DIV_16    0x50
#define ADC_CLOCK_DIV_64    0x60
#define ADC_CLOCK_INTERNAL  0x30              // Internal 2-6us

// Constants used in SETUP_ADC_PORTS() are:
#define sAN0            1       //| A0
#define sAN1            2       //| A1
#define sAN2            4       //| A2
#define sAN3            8       //| A4
#define sAN4            16      //| C0
#define sAN5            32      //| C1
#define sAN6            64      //| C2
#define sAN7            128     //| C3
#define sAN8         0x10000    //| C6
#define sAN9         0x20000    //| C7
#define sAN10        0x40000    //| B4
#define sAN11        0x80000    //| B5
#define NO_ANALOGS      0       // None
#define ALL_ANALOG   0xF00FF    // A0 A1 A2 A4 C0 C1 C2 C3 C6 C7 B4 B5

// One of the following may be OR'ed in with the above using |
#define VSS_VDD              0x0000        //| Range 0-Vdd
#define VSS_VREF             0x4000        //| Range 0-Vref



// Constants used in READ_ADC() are:
#define ADC_START_AND_READ     7   // This is the default if nothing is specified
#define ADC_START_ONLY         1
#define ADC_READ_ONLY          6



////////////////////////////////////////////////////////////////// INT
// Interrupt Functions: ENABLE_INTERRUPTS(), DISABLE_INTERRUPTS(),
//                      EXT_INT_EDGE()
//
// Constants used in EXT_INT_EDGE() are:
#define L_TO_H              0x40
#define H_TO_L                 0
// Constants used in ENABLE/DISABLE_INTERRUPTS() are:
#define GLOBAL                    0x0BC0
#define INT_RTCC                  0x0B20
#define INT_EXT                   0x0B10
#define INT_AD                    0x8C40
#define INT_TIMER1                0x8C01
#define INT_TIMER2                0x8C02
#define INT_CCP1                  0x8C04
#define INT_EEPROM                0x8D10
#define INT_TIMER0                0x0B20
#define INT_RA                    0x0B08
#define INT_OSC_FAIL              0x8D80
#define INT_COMP                  0x8D20
#define INT_COMP2                 0x8D40
#define INT_RA0                   0x010B08
#define INT_RA1                   0x020B08
#define INT_RA2                   0x040B08
#define INT_RA3                   0x080B08
#define INT_RA4                   0x100B08
#define INT_RA5                   0x200B08
#define INT_RB4                   0x100B08
#define INT_RB5                   0x200B08
#define INT_RB6                   0x400B08
#define INT_RB7                   0x800B08

#list
