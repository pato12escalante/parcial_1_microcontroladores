/*
 * File:   main.c
 * Author: Patricio Escalante
 *
 * Created on 21 de septiembre de 2021, 03:50 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "configbits.h"

#define _XTAL_FREQ 4000000

#define modo1standby 0
#define modo1cuenta 1
#define modo1pausa 2
#define modo2standby 3
#define modo2cuenta 4
#define modo2pausa 5
#define reset 6

#define boton_start PORTBbits.RB0
#define boton_modo PORTBbits.RB1
#define boton_reset PORTBbits.RB2


#define datos LATDbits.LATD0
#define clock LATDbits.LATD1

#define digit0enable LATDbits.LATD7
#define digit1enable LATDbits.LATD6
#define digit2enable LATDbits.LATD5
#define digit3enable LATDbits.LATD4
#define digit4enable LATDbits.LATD3
#define digit5enable LATDbits.LATD2


/*
 * 
 */

signed char millis=0, decenas_millis=0, segundos=0, decenas=0, minutos=0, decenas_minuto=0;
char estado=0;
char entrada=0;
char flag=0, flag2=0;
int contador=0;
char digitos[10]={0b01111110, 0b00110000, 0b01101101, 0b01111001, 0b00110011, 0b01011011, 0b01011111, 0b01110000, 0b011111111, 0b01110011};


void buzzer1500(){
    LATBbits.LATB3 = 1;
    __delay_ms(80);
    LATBbits.LATB3 = 0;
    return;
}
void buzzer2000(){
    LATBbits.LATB4 = 1;
    __delay_ms(300);
    LATBbits.LATB4  = 0;
    return;
}

void showdigit0(){
    digit0enable=1;
    digit1enable=0;
    digit2enable=0;
    digit3enable=0;
    digit4enable=0;
    digit5enable=0;
    
    for (char k=0;k<7;k++){
        char x=digitos[millis];
        x=x>>k;
        x=x&0b00000001;
        LATD=LATD & 0b11111110;
        LATD=LATD | x;
        
        __delay_us(10);
        clock=1;
        __delay_us(10);
        clock=0;
    }
}

void showdigit1(){
    digit0enable=0;
    digit1enable=1;
    digit2enable=0;
    digit3enable=0;
    digit4enable=0;
    digit5enable=0;
    
    for (char k=0;k<7;k++){
        char x=digitos[decenas_millis];
        x=x>>k;
        x=x&0b00000001;
        LATD=LATD & 0b11111110;
        LATD=LATD | x;
        
        __delay_us(10);
        clock=1;
        __delay_us(10);
        clock=0;
    }
}

void showdigit2(){
    digit0enable=0;
    digit1enable=0;
    digit2enable=1;
    digit3enable=0;
    digit4enable=0;
    digit5enable=0;
    
    for (char k=0;k<7;k++){
        char x=digitos[segundos];
        x=x>>k;
        x=x&0b00000001;
        LATD=LATD & 0b11111110;
        LATD=LATD | x;
        
        __delay_us(10);
        clock=1;
        __delay_us(10);
        clock=0;
    }
}

void showdigit3(){
    digit0enable=0;
    digit1enable=0;
    digit2enable=0;
    digit3enable=1;
    digit4enable=0;
    digit5enable=0;
    
    for (char k=0;k<7;k++){
        char x=digitos[decenas];
        x=x>>k;
        x=x&0b00000001;
        LATD=LATD & 0b11111110;
        LATD=LATD | x;
        
        __delay_us(10);
        clock=1;
        __delay_us(10);
        clock=0;
    }
}

void showdigit4(){
    digit0enable=0;
    digit1enable=0;
    digit2enable=0;
    digit3enable=0;
    digit4enable=1;
    digit5enable=0;
    
    for (char k=0;k<7;k++){
        char x=digitos[minutos];
        x=x>>k;
        x=x&0b00000001;
        LATD=LATD & 0b11111110;
        LATD=LATD | x;
        
        __delay_us(10);
        clock=1;
        __delay_us(10);
        clock=0;
    }
}

void showdigit5(){
    digit0enable=0;
    digit1enable=0;
    digit2enable=0;
    digit3enable=0;
    digit4enable=0;
    digit5enable=1;
    
    for (char k=0;k<7;k++){
        char x=digitos[decenas_minuto];
        x=x>>k;
        x=x&0b00000001;
        LATD=LATD & 0b11111110;
        LATD=LATD | x;
        
        __delay_us(10);
        clock=1;
        __delay_us(10);
        clock=0;
    }
}


void conteo(){

    __delay_ms(10);
        millis++;
        showdigit0();
        if(millis==10){
            millis=0;
            decenas_millis++;
            showdigit0();
            showdigit0();
            showdigit1();
            showdigit2();
            showdigit3();
            showdigit4();
            showdigit5();
            
            if(decenas_millis==10){
                decenas_millis=0;
                segundos++;
 
                showdigit0();
                showdigit1();
                showdigit2();
                showdigit3();
                showdigit4();
                showdigit5();
                
                if(segundos==10){
                    segundos=0;
                    decenas++;
   
                    showdigit0();
                    showdigit1();
                    showdigit2();
                    showdigit3();
                    showdigit4();
                    showdigit5();
                
                    if(decenas==6){
                        decenas=0;
                        minutos++;
  
                        showdigit0();
                        showdigit1();
                        showdigit2();
                        showdigit3();
                        showdigit4();
                        showdigit5();
                
                            if(minutos==10){
                                minutos=0;
                                decenas_minuto++;

                                showdigit0();
                                showdigit1();
                                showdigit2();
                                showdigit3();
                                showdigit4();
                                showdigit5();
                
                                    if(decenas_minuto==6){
                                        decenas_minuto=0;
                                            showdigit0();
                                            showdigit0();
                                            showdigit1();
                                            showdigit2();
                                            showdigit3();
                                            showdigit4();
                                            showdigit5();
                                            }
                                }
                        }
                }
            }
        }
}


void conteo2(){
    
    if(millis>0 || decenas_millis>0 || segundos>0|| decenas>0 || minutos>0 || decenas_minuto>0){
    __delay_ms(10);
        millis--;
        showdigit0();
        if(millis<0){
            millis=9;
            decenas_millis--;
            showdigit0();
            showdigit1();
            showdigit2();
            showdigit3();
            
            if(decenas_millis<0){
                decenas_millis=9;
                segundos--;
 
                showdigit0();
                showdigit1();
                showdigit2();
                showdigit3();
    
                
                if(segundos<0){
                    segundos=9;
                    decenas--;
   
                    showdigit0();
                    showdigit1();
                    showdigit2();
                    showdigit3();
                
                    if(decenas<0){
                        decenas=2;
                        
  
                        showdigit0();
                        showdigit1();
                        showdigit2();
                        showdigit3();
                        
                        
                        
                        }
                }
                
            }
        }
}else{
        buzzer2000();
        estado=modo1standby;
        
}
}

void main() {
    TRISD=0;
    TRISBbits.RB0=1;
    TRISBbits.RB1=1;
    TRISBbits.RB2=1;
    TRISBbits.RB3=0;
    TRISBbits.RB4=0;
    
   

    
    char input_mode=0, input_start=0, input_reset=0;
    
//    tmr0init();
    
    showdigit0();
    showdigit1();
    showdigit2();
    showdigit3();
    showdigit4();
    showdigit5();
    
    
    while(1){

        input_start=boton_start;
        input_mode=boton_modo;
        input_reset=boton_reset;
        if(input_start==0 && input_mode==0 && input_reset==0){
            flag=0;
            flag2=0;
        }
        
        input_start=boton_start;
        if(input_start==1 && flag==0 && estado==modo1standby){
            flag=1;
            estado=modo1cuenta;
          
        }
        
        input_start=boton_start;
        if(input_start==1 && flag==0 && estado==modo1pausa){
            flag=1;
            estado=modo1cuenta;
        }
        
        input_reset=boton_reset;
        if(input_reset==1 && flag==0 && estado==modo1pausa){
            flag=1;
            estado=modo1standby;
            
            millis=0, decenas_millis=0, segundos=0, decenas=0, minutos=0, decenas_minuto=0;
               showdigit0();
                showdigit1();
                showdigit2();
                showdigit3();
                showdigit4();
                showdigit5();
    
        }
        
        input_start=boton_start;
        if(input_start==1 && estado==modo1cuenta && flag==0){
            flag=1;
            estado=modo1pausa;
        }
        
        
        
        //-----MODO 2----
        input_mode=boton_modo;
        if(input_mode==1 && estado==modo1standby && flag==0){
            flag=1;
            millis=0, decenas_millis=0, segundos=0, decenas=3, minutos=0, decenas_minuto=0;
               showdigit0();
                showdigit1();
                showdigit2();
                showdigit3();
                showdigit4();
                showdigit5();
            estado=modo2standby;
        }
        
        input_mode=boton_modo;
        if(input_mode==1 && estado==modo1pausa && flag==0){
            flag=1;
            millis=0, decenas_millis=0, segundos=0, decenas=3, minutos=0, decenas_minuto=0;
               showdigit0();
                showdigit1();
                showdigit2();
                showdigit3();
                showdigit4();
                showdigit5();
            estado=modo2standby;
        }
        
        input_start=boton_start;
        if(input_start==1 && estado==modo2cuenta && flag==0){
            flag=1;
            estado=modo2pausa;
        }
        
        input_start=boton_start;
        if(input_start==1 && estado==modo2pausa && flag==0){
            flag=1;
            estado=modo2cuenta;
        }
        
        
        input_start=boton_start;
        if(input_start==1 && estado==modo2standby && flag==0){
            flag=1;
            millis=9, decenas_millis=9, segundos=9, decenas=2, minutos=0, decenas_minuto=0;
               showdigit0();
                showdigit1();
                showdigit2();
                showdigit3();
                showdigit4();
                showdigit5();
            estado=modo2cuenta;
        }
        
        input_mode=boton_modo;
        if(input_mode==1 && estado==modo2pausa && flag==0){
            flag=1;
            millis=0, decenas_millis=0, segundos=0, decenas=0, minutos=0, decenas_minuto=0;
               showdigit0();
                showdigit1();
                showdigit2();
                showdigit3();
                showdigit4();
                showdigit5();
            estado=modo1standby;
        }
        
        input_mode=boton_modo;
        if(input_mode==1 && estado==modo2standby && flag==0){
            flag=1;
            millis=0, decenas_millis=0, segundos=0, decenas=0, minutos=0, decenas_minuto=0;
               showdigit0();
                showdigit1();
                showdigit2();
                showdigit3();
                showdigit4();
                showdigit5();
            estado=modo1standby;
        }
        
        input_reset=boton_reset;
        if(input_reset==1 && flag==0 && estado==modo2pausa){
            flag=1;
            estado=modo2standby;
            
            millis=0, decenas_millis=0, segundos=0, decenas=3, minutos=0, decenas_minuto=0;
               showdigit0();
                showdigit1();
                showdigit2();
                showdigit3();
                showdigit4();
                showdigit5();
    
        }
        
        
        
        
        
        if(estado==modo1cuenta){
            conteo();
        }
        if(estado==modo2cuenta){
            conteo2();
        }
        
        
        
        
        input_start=boton_start;
        if(boton_start==1 && flag2==0){
            buzzer1500();
            flag2=1;
        }
        
        input_reset=boton_reset;

        if(boton_reset==1 && flag2==0){
            buzzer1500();
            flag2=1;
        }
        

        input_mode=boton_modo;
        if(boton_modo==1 && flag2==0){
            buzzer1500();
            flag2=1;
        }

        
       
    }
    
    
    
    
}
