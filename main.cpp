#include "mbed.h"
#include "QEI.h"
#include "PS3.h"

Thread th1;
Thread th2;
int thread1();
int thread2();

I2C i2c(D14,D15); // D14 = PB_8, D15 = PB_9
PS3 ps3( A0, A1); // PA_0, PA_1

DigitalIn sw1(PC_4);
DigitalIn sw2(PB_15);
DigitalIn sw3(PB_12);
DigitalIn sw4(PB_15);
DigitalIn sw5(PC_8);

DigitalOut led1(PA_9);  //  PA_9 = D8
DigitalOut led2(PA_8);  //  PA_8 = D7
DigitalOut led3(PB_10); // PB_10 = D6
DigitalOut led4(PB_4);  //  PB_4 = D5
DigitalOut led5(PB_5);  //  PB_5 = D4

QEI rori1(  PD_2, PC_11, NC, 2048, QEI::X2_ENCODING);
QEI rori2( PC_10, PC_12, NC, 2048, QEI::X2_ENCODING);
QEI rori3( PA_13, PA_14, NC, 2048, QEI::X2_ENCODING);
QEI rori4( PA_15,  PB_7, NC, 2048, QEI::X2_ENCODING);
QEI rori5(  PC_1,  PC_0, NC, 2048, QEI::X2_ENCODING);
QEI rori6(  PC_3,  PA_4, NC, 2048, QEI::X2_ENCODING);

int pulse1, pulse2, pulse3, pulse4, pulse5, pulse6;
float angle1, angle2, angle3, angle4, angle5, angle6;

int main (void){

    th1.start(thread1);
    th2.start(thread2);

    rori1.reset();
    rori2.reset();
    rori3.reset();
    rori4.reset();
    rori5.reset();
    rori6.reset();

    while (true){
        if ( sw1 == 1 || ps3.getButtonState(PS3::maru)){
            led1 = 1;
        } else {
            led1 = 0;
        }

        if ( sw2 == 1 || ps3.getButtonState(PS3::sikaku)){
            led2 = 1;
        } else {
            led2 = 0;
        }

        if ( sw3 == 1 || ps3.getButtonState(PS3::sankaku)){
            led3 = 1;
        } else {
            led3 = 0;
        }

        if ( sw4 == 1 || ps3.getButtonState(PS3::batu)){
            led4 = 1;
        } else {
            led4 = 0;
        }

        if ( sw5 == 1 || ps3.getButtonState(PS3::batu)){
            led5 = 1;
        } else {
            led5 = 0;
        }
        
    }

}

int thread1 (void){
    while (true){
        printf("p1:%6d p2:%6d p3:%6d p4:%6d p5:%6d p6:%6d\n", pulse1, pulse2, pulse3, pulse4, pulse5, pulse6);
        ThisThread::sleep_for(100ms);
    }
}

int thread2 (void){
    while (true){
        pulse1 = rori1.getPulses();
        pulse2 = rori2.getPulses();
        pulse3 = rori3.getPulses();
        pulse4 = rori4.getPulses();
        pulse5 = rori5.getPulses();
        pulse6 = rori6.getPulses();
        
        angle1 = ( 360*(float)pulse1 / (2048*2) );
        angle2 = ( 360*(float)pulse2 / (2048*2) );
        angle3 = ( 360*(float)pulse3 / (2048*2) );
        angle4 = ( 360*(float)pulse4 / (2048*2) );
        angle5 = ( 360*(float)pulse5 / (2048*2) );
        angle6 = ( 360*(float)pulse6 / (2048*2) );
    }
}