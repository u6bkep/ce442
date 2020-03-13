 /*
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "Arduino.h"
#include "Arduino.h"
#include "FastPID.h"

#ifndef Motor_h
#define Motor_h

#define CORE_NUM_INTERRUPT  6 //hardcode for mega2560
#define ENCODER_USE_INTERRUPTS
#define ENCODER_ARGLIST_SIZE CORE_NUM_INTERRUPT
#define CORE_INT0_PIN    2
#define CORE_INT1_PIN   3
#define CORE_INT2_PIN   21
#define CORE_INT3_PIN   20
#define CORE_INT4_PIN   19
#define CORE_INT5_PIN   18

#define KP 254
#define KI 10
#define KD 20

       typedef struct {
      volatile int counter;
      int aPin;
      int bPin;
      int reversed;
    } Encoder_internal_state_t;

class motorPID
{
  public:

  volatile int encoderCounter;
   //settup PID controller
   // FastPID myPID(KP, KI, KD, 10, 8, true);

   static Encoder_internal_state_t * interruptArgs[ENCODER_ARGLIST_SIZE];
  
    motorPID(int dirPin1,int dirPin2,int spdPin,
            int encoderAPin,int encoderBPin, int reversed)
  {
    this->dirPin1     = dirPin1    ;
    this->dirPin2     = dirPin2    ;
    this->spdPin      = spdPin     ;
    this->encoderAPin = encoderAPin;
    this->encoderBPin = encoderBPin;
    this->reversed    = reversed   ;
      //settup pins
    pinMode(this->dirPin1,OUTPUT);
    pinMode(this->dirPin2,OUTPUT);
    pinMode(this->spdPin,OUTPUT);
    pinMode(this->encoderAPin,INPUT);
    pinMode(this->encoderBPin,INPUT);
    
    //register encoder interupt
    Encoder_internal_state_t state1;
    state1.counter = 0;
    state1.aPin = this->encoderAPin;
    state1.bPin = this->encoderBPin;
    state1.reversed = this->reversed;
    attach_interrupt(this->encoderAPin, &state1);

    Encoder_internal_state_t state2;
    state2.aPin = this->encoderAPin;
    state2.bPin = this->encoderBPin;
    state2.reversed = this->reversed;
    attach_interrupt(this->encoderBPin, &state2);
    
    
    
    if (myPID.err()) 
      Serial1.println("There is a configuration error!");
  
    encoderCounter = 0;
  }
 

            
    void drive(int speed);
    
    

    static void update(Encoder_internal_state_t *arg) 
    {
      //Serial1.print("ISR triggered for pin: ");
      Serial1.println(arg->aPin);
      switch(arg->reversed)
      {
        case 0:
          if((digitalRead(arg->bPin) == digitalRead(arg->aPin)))
          {
            arg->counter --;
          }
          else
          {
            arg->counter ++;
          }
          break;
        case 1:
          if((digitalRead(arg->bPin) == digitalRead(arg->aPin)))
          {
            arg->counter ++;
          }
          else
          {
            arg->counter --;
          }
      }
    }

  private:
    int dirPin1;
    int dirPin2;
    int spdPin;
    int encoderAPin;
    int encoderBPin;
    int reversed;
    
    FastPID myPID;
    void motorEncoderISR();


// I want to thank Paul Stoffregen on github for this next bit of code for handling interupts
// https://github.com/PaulStoffregen/Encoder/blob/master/Encoder.h


#ifdef ENCODER_USE_INTERRUPTS
  // this giant function is an unfortunate consequence of Arduino's
  // attachInterrupt function not supporting any way to pass a pointer
  // or other context to the attached function.
  static uint8_t attach_interrupt(uint8_t pin, Encoder_internal_state_t *state) {
    switch (pin) {
    #ifdef CORE_INT0_PIN
      case CORE_INT0_PIN:
        interruptArgs[0] = state;
        attachInterrupt(0, isr0, CHANGE);
        break;
    #endif
    #ifdef CORE_INT1_PIN
      case CORE_INT1_PIN:
        interruptArgs[1] = state;
        attachInterrupt(1, isr1, CHANGE);
        break;
    #endif
    #ifdef CORE_INT2_PIN
      case CORE_INT2_PIN:
        interruptArgs[2] = state;
        attachInterrupt(2, isr2, CHANGE);
        break;
    #endif
    #ifdef CORE_INT3_PIN
      case CORE_INT3_PIN:
        interruptArgs[3] = state;
        attachInterrupt(3, isr3, CHANGE);
        break;
    #endif
    #ifdef CORE_INT4_PIN
      case CORE_INT4_PIN:
        interruptArgs[4] = state;
        attachInterrupt(4, isr4, CHANGE);
        break;
    #endif
    #ifdef CORE_INT5_PIN
      case CORE_INT5_PIN:
        interruptArgs[5] = state;
        attachInterrupt(5, isr5, CHANGE);
        break;
    #endif
    #ifdef CORE_INT6_PIN
      case CORE_INT6_PIN:
        interruptArgs[6] = state;
        attachInterrupt(6, isr6, CHANGE);
        break;
    #endif
    #ifdef CORE_INT7_PIN
      case CORE_INT7_PIN:
        interruptArgs[7] = state;
        attachInterrupt(7, isr7, CHANGE);
        break;
    #endif
    #ifdef CORE_INT8_PIN
      case CORE_INT8_PIN:
        interruptArgs[8] = state;
        attachInterrupt(8, isr8, CHANGE);
        break;
    #endif
    #ifdef CORE_INT9_PIN
      case CORE_INT9_PIN:
        interruptArgs[9] = state;
        attachInterrupt(9, isr9, CHANGE);
        break;
    #endif
    #ifdef CORE_INT10_PIN
      case CORE_INT10_PIN:
        interruptArgs[10] = state;
        attachInterrupt(10, isr10, CHANGE);
        break;
    #endif
    #ifdef CORE_INT11_PIN
      case CORE_INT11_PIN:
        interruptArgs[11] = state;
        attachInterrupt(11, isr11, CHANGE);
        break;
    #endif
    #ifdef CORE_INT12_PIN
      case CORE_INT12_PIN:
        interruptArgs[12] = state;
        attachInterrupt(12, isr12, CHANGE);
        break;
    #endif
    #ifdef CORE_INT13_PIN
      case CORE_INT13_PIN:
        interruptArgs[13] = state;
        attachInterrupt(13, isr13, CHANGE);
        break;
    #endif
    #ifdef CORE_INT14_PIN
      case CORE_INT14_PIN:
        interruptArgs[14] = state;
        attachInterrupt(14, isr14, CHANGE);
        break;
    #endif
    #ifdef CORE_INT15_PIN
      case CORE_INT15_PIN:
        interruptArgs[15] = state;
        attachInterrupt(15, isr15, CHANGE);
        break;
    #endif
    #ifdef CORE_INT16_PIN
      case CORE_INT16_PIN:
        interruptArgs[16] = state;
        attachInterrupt(16, isr16, CHANGE);
        break;
    #endif
    #ifdef CORE_INT17_PIN
      case CORE_INT17_PIN:
        interruptArgs[17] = state;
        attachInterrupt(17, isr17, CHANGE);
        break;
    #endif
    #ifdef CORE_INT18_PIN
      case CORE_INT18_PIN:
        interruptArgs[18] = state;
        attachInterrupt(18, isr18, CHANGE);
        break;
    #endif
    #ifdef CORE_INT19_PIN
      case CORE_INT19_PIN:
        interruptArgs[19] = state;
        attachInterrupt(19, isr19, CHANGE);
        break;
    #endif
    #ifdef CORE_INT20_PIN
      case CORE_INT20_PIN:
        interruptArgs[20] = state;
        attachInterrupt(20, isr20, CHANGE);
        break;
    #endif
    #ifdef CORE_INT21_PIN
      case CORE_INT21_PIN:
        interruptArgs[21] = state;
        attachInterrupt(21, isr21, CHANGE);
        break;
    #endif
    #ifdef CORE_INT22_PIN
      case CORE_INT22_PIN:
        interruptArgs[22] = state;
        attachInterrupt(22, isr22, CHANGE);
        break;
    #endif
    #ifdef CORE_INT23_PIN
      case CORE_INT23_PIN:
        interruptArgs[23] = state;
        attachInterrupt(23, isr23, CHANGE);
        break;
    #endif
    #ifdef CORE_INT24_PIN
      case CORE_INT24_PIN:
        interruptArgs[24] = state;
        attachInterrupt(24, isr24, CHANGE);
        break;
    #endif
    #ifdef CORE_INT25_PIN
      case CORE_INT25_PIN:
        interruptArgs[25] = state;
        attachInterrupt(25, isr25, CHANGE);
        break;
    #endif
    #ifdef CORE_INT26_PIN
      case CORE_INT26_PIN:
        interruptArgs[26] = state;
        attachInterrupt(26, isr26, CHANGE);
        break;
    #endif
    #ifdef CORE_INT27_PIN
      case CORE_INT27_PIN:
        interruptArgs[27] = state;
        attachInterrupt(27, isr27, CHANGE);
        break;
    #endif
    #ifdef CORE_INT28_PIN
      case CORE_INT28_PIN:
        interruptArgs[28] = state;
        attachInterrupt(28, isr28, CHANGE);
        break;
    #endif
    #ifdef CORE_INT29_PIN
      case CORE_INT29_PIN:
        interruptArgs[29] = state;
        attachInterrupt(29, isr29, CHANGE);
        break;
    #endif

    #ifdef CORE_INT30_PIN
      case CORE_INT30_PIN:
        interruptArgs[30] = state;
        attachInterrupt(30, isr30, CHANGE);
        break;
    #endif
    #ifdef CORE_INT31_PIN
      case CORE_INT31_PIN:
        interruptArgs[31] = state;
        attachInterrupt(31, isr31, CHANGE);
        break;
    #endif
    #ifdef CORE_INT32_PIN
      case CORE_INT32_PIN:
        interruptArgs[32] = state;
        attachInterrupt(32, isr32, CHANGE);
        break;
    #endif
    #ifdef CORE_INT33_PIN
      case CORE_INT33_PIN:
        interruptArgs[33] = state;
        attachInterrupt(33, isr33, CHANGE);
        break;
    #endif
    #ifdef CORE_INT34_PIN
      case CORE_INT34_PIN:
        interruptArgs[34] = state;
        attachInterrupt(34, isr34, CHANGE);
        break;
    #endif
    #ifdef CORE_INT35_PIN
      case CORE_INT35_PIN:
        interruptArgs[35] = state;
        attachInterrupt(35, isr35, CHANGE);
        break;
    #endif
    #ifdef CORE_INT36_PIN
      case CORE_INT36_PIN:
        interruptArgs[36] = state;
        attachInterrupt(36, isr36, CHANGE);
        break;
    #endif
    #ifdef CORE_INT37_PIN
      case CORE_INT37_PIN:
        interruptArgs[37] = state;
        attachInterrupt(37, isr37, CHANGE);
        break;
    #endif
    #ifdef CORE_INT38_PIN
      case CORE_INT38_PIN:
        interruptArgs[38] = state;
        attachInterrupt(38, isr38, CHANGE);
        break;
    #endif
    #ifdef CORE_INT39_PIN
      case CORE_INT39_PIN:
        interruptArgs[39] = state;
        attachInterrupt(39, isr39, CHANGE);
        break;
    #endif
    #ifdef CORE_INT40_PIN
      case CORE_INT40_PIN:
        interruptArgs[40] = state;
        attachInterrupt(40, isr40, CHANGE);
        break;
    #endif
    #ifdef CORE_INT41_PIN
      case CORE_INT41_PIN:
        interruptArgs[41] = state;
        attachInterrupt(41, isr41, CHANGE);
        break;
    #endif
    #ifdef CORE_INT42_PIN
      case CORE_INT42_PIN:
        interruptArgs[42] = state;
        attachInterrupt(42, isr42, CHANGE);
        break;
    #endif
    #ifdef CORE_INT43_PIN
      case CORE_INT43_PIN:
        interruptArgs[43] = state;
        attachInterrupt(43, isr43, CHANGE);
        break;
    #endif
    #ifdef CORE_INT44_PIN
      case CORE_INT44_PIN:
        interruptArgs[44] = state;
        attachInterrupt(44, isr44, CHANGE);
        break;
    #endif
    #ifdef CORE_INT45_PIN
      case CORE_INT45_PIN:
        interruptArgs[45] = state;
        attachInterrupt(45, isr45, CHANGE);
        break;
    #endif
    #ifdef CORE_INT46_PIN
      case CORE_INT46_PIN:
        interruptArgs[46] = state;
        attachInterrupt(46, isr46, CHANGE);
        break;
    #endif
    #ifdef CORE_INT47_PIN
      case CORE_INT47_PIN:
        interruptArgs[47] = state;
        attachInterrupt(47, isr47, CHANGE);
        break;
    #endif
    #ifdef CORE_INT48_PIN
      case CORE_INT48_PIN:
        interruptArgs[48] = state;
        attachInterrupt(48, isr48, CHANGE);
        break;
    #endif
    #ifdef CORE_INT49_PIN
      case CORE_INT49_PIN:
        interruptArgs[49] = state;
        attachInterrupt(49, isr49, CHANGE);
        break;
    #endif
    #ifdef CORE_INT50_PIN
      case CORE_INT50_PIN:
        interruptArgs[50] = state;
        attachInterrupt(50, isr50, CHANGE);
        break;
    #endif
    #ifdef CORE_INT51_PIN
      case CORE_INT51_PIN:
        interruptArgs[51] = state;
        attachInterrupt(51, isr51, CHANGE);
        break;
    #endif
    #ifdef CORE_INT52_PIN
      case CORE_INT52_PIN:
        interruptArgs[52] = state;
        attachInterrupt(52, isr52, CHANGE);
        break;
    #endif
    #ifdef CORE_INT53_PIN
      case CORE_INT53_PIN:
        interruptArgs[53] = state;
        attachInterrupt(53, isr53, CHANGE);
        break;
    #endif
    #ifdef CORE_INT54_PIN
      case CORE_INT54_PIN:
        interruptArgs[54] = state;
        attachInterrupt(54, isr54, CHANGE);
        break;
    #endif
    #ifdef CORE_INT55_PIN
      case CORE_INT55_PIN:
        interruptArgs[55] = state;
        attachInterrupt(55, isr55, CHANGE);
        break;
    #endif
    #ifdef CORE_INT56_PIN
      case CORE_INT56_PIN:
        interruptArgs[56] = state;
        attachInterrupt(56, isr56, CHANGE);
        break;
    #endif
    #ifdef CORE_INT57_PIN
      case CORE_INT57_PIN:
        interruptArgs[57] = state;
        attachInterrupt(57, isr57, CHANGE);
        break;
    #endif
    #ifdef CORE_INT58_PIN
      case CORE_INT58_PIN:
        interruptArgs[58] = state;
        attachInterrupt(58, isr58, CHANGE);
        break;
    #endif
    #ifdef CORE_INT59_PIN
      case CORE_INT59_PIN:
        interruptArgs[59] = state;
        attachInterrupt(59, isr59, CHANGE);
        break;
    #endif
      default:
        return 0;
    }
    return 1;
  }
#endif // ENCODER_USE_INTERRUPTS


#if defined(ENCODER_USE_INTERRUPTS) && !defined(ENCODER_OPTIMIZE_INTERRUPTS)
  #ifdef CORE_INT0_PIN
  static void isr0(void) { update(interruptArgs[0]); }
  #endif
  #ifdef CORE_INT1_PIN
  static void isr1(void) { update(interruptArgs[1]); }
  #endif
  #ifdef CORE_INT2_PIN
  static void isr2(void) { update(interruptArgs[2]); }
  #endif
  #ifdef CORE_INT3_PIN
  static void isr3(void) { update(interruptArgs[3]); }
  #endif
  #ifdef CORE_INT4_PIN
  static void isr4(void) { update(interruptArgs[4]); }
  #endif
  #ifdef CORE_INT5_PIN
  static void isr5(void) { update(interruptArgs[5]); }
  #endif
  #ifdef CORE_INT6_PIN
  static void isr6(void) { update(interruptArgs[6]); }
  #endif
  #ifdef CORE_INT7_PIN
  static void isr7(void) { update(interruptArgs[7]); }
  #endif
  #ifdef CORE_INT8_PIN
  static void isr8(void) { update(interruptArgs[8]); }
  #endif
  #ifdef CORE_INT9_PIN
  static void isr9(void) { update(interruptArgs[9]); }
  #endif
  #ifdef CORE_INT10_PIN
  static void isr10(void) { update(interruptArgs[10]); }
  #endif
  #ifdef CORE_INT11_PIN
  static void isr11(void) { update(interruptArgs[11]); }
  #endif
  #ifdef CORE_INT12_PIN
  static void isr12(void) { update(interruptArgs[12]); }
  #endif
  #ifdef CORE_INT13_PIN
  static void isr13(void) { update(interruptArgs[13]); }
  #endif
  #ifdef CORE_INT14_PIN
  static void isr14(void) { update(interruptArgs[14]); }
  #endif
  #ifdef CORE_INT15_PIN
  static void isr15(void) { update(interruptArgs[15]); }
  #endif
  #ifdef CORE_INT16_PIN
  static void isr16(void) { update(interruptArgs[16]); }
  #endif
  #ifdef CORE_INT17_PIN
  static void isr17(void) { update(interruptArgs[17]); }
  #endif
  #ifdef CORE_INT18_PIN
  static void isr18(void) { update(interruptArgs[18]); }
  #endif
  #ifdef CORE_INT19_PIN
  static void isr19(void) { update(interruptArgs[19]); }
  #endif
  #ifdef CORE_INT20_PIN
  static void isr20(void) { update(interruptArgs[20]); }
  #endif
  #ifdef CORE_INT21_PIN
  static void isr21(void) { update(interruptArgs[21]); }
  #endif
  #ifdef CORE_INT22_PIN
  static void isr22(void) { update(interruptArgs[22]); }
  #endif
  #ifdef CORE_INT23_PIN
  static void isr23(void) { update(interruptArgs[23]); }
  #endif
  #ifdef CORE_INT24_PIN
  static void isr24(void) { update(interruptArgs[24]); }
  #endif
  #ifdef CORE_INT25_PIN
  static void isr25(void) { update(interruptArgs[25]); }
  #endif
  #ifdef CORE_INT26_PIN
  static void isr26(void) { update(interruptArgs[26]); }
  #endif
  #ifdef CORE_INT27_PIN
  static void isr27(void) { update(interruptArgs[27]); }
  #endif
  #ifdef CORE_INT28_PIN
  static void isr28(void) { update(interruptArgs[28]); }
  #endif
  #ifdef CORE_INT29_PIN
  static void isr29(void) { update(interruptArgs[29]); }
  #endif
  #ifdef CORE_INT30_PIN
  static void isr30(void) { update(interruptArgs[30]); }
  #endif
  #ifdef CORE_INT31_PIN
  static void isr31(void) { update(interruptArgs[31]); }
  #endif
  #ifdef CORE_INT32_PIN
  static void isr32(void) { update(interruptArgs[32]); }
  #endif
  #ifdef CORE_INT33_PIN
  static void isr33(void) { update(interruptArgs[33]); }
  #endif
  #ifdef CORE_INT34_PIN
  static void isr34(void) { update(interruptArgs[34]); }
  #endif
  #ifdef CORE_INT35_PIN
  static void isr35(void) { update(interruptArgs[35]); }
  #endif
  #ifdef CORE_INT36_PIN
  static void isr36(void) { update(interruptArgs[36]); }
  #endif
  #ifdef CORE_INT37_PIN
  static void isr37(void) { update(interruptArgs[37]); }
  #endif
  #ifdef CORE_INT38_PIN
  static void isr38(void) { update(interruptArgs[38]); }
  #endif
  #ifdef CORE_INT39_PIN
  static void isr39(void) { update(interruptArgs[39]); }
  #endif
  #ifdef CORE_INT40_PIN
  static void isr40(void) { update(interruptArgs[40]); }
  #endif
  #ifdef CORE_INT41_PIN
  static void isr41(void) { update(interruptArgs[41]); }
  #endif
  #ifdef CORE_INT42_PIN
  static void isr42(void) { update(interruptArgs[42]); }
  #endif
  #ifdef CORE_INT43_PIN
  static void isr43(void) { update(interruptArgs[43]); }
  #endif
  #ifdef CORE_INT44_PIN
  static void isr44(void) { update(interruptArgs[44]); }
  #endif
  #ifdef CORE_INT45_PIN
  static void isr45(void) { update(interruptArgs[45]); }
  #endif
  #ifdef CORE_INT46_PIN
  static void isr46(void) { update(interruptArgs[46]); }
  #endif
  #ifdef CORE_INT47_PIN
  static void isr47(void) { update(interruptArgs[47]); }
  #endif
  #ifdef CORE_INT48_PIN
  static void isr48(void) { update(interruptArgs[48]); }
  #endif
  #ifdef CORE_INT49_PIN
  static void isr49(void) { update(interruptArgs[49]); }
  #endif
  #ifdef CORE_INT50_PIN
  static void isr50(void) { update(interruptArgs[50]); }
  #endif
  #ifdef CORE_INT51_PIN
  static void isr51(void) { update(interruptArgs[51]); }
  #endif
  #ifdef CORE_INT52_PIN
  static void isr52(void) { update(interruptArgs[52]); }
  #endif
  #ifdef CORE_INT53_PIN
  static void isr53(void) { update(interruptArgs[53]); }
  #endif
  #ifdef CORE_INT54_PIN
  static void isr54(void) { update(interruptArgs[54]); }
  #endif
  #ifdef CORE_INT55_PIN
  static void isr55(void) { update(interruptArgs[55]); }
  #endif
  #ifdef CORE_INT56_PIN
  static void isr56(void) { update(interruptArgs[56]); }
  #endif
  #ifdef CORE_INT57_PIN
  static void isr57(void) { update(interruptArgs[57]); }
  #endif
  #ifdef CORE_INT58_PIN
  static void isr58(void) { update(interruptArgs[58]); }
  #endif
  #ifdef CORE_INT59_PIN
  static void isr59(void) { update(interruptArgs[59]); }
  #endif
#endif





};


#endif
