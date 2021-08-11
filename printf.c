#include "uart.h"
#include "main.h"

extern volatile unsigned char _end;

unsigned int vsprintf(char *dst, char* fmt, __builtin_va_list args){
    s64 arg;
    int len, sign, i,lf;
    char *p, *orig=dst, tmpstr[30];

    if(dst==(void*)0 || fmt==(void*)0)
        return 0;
    arg = 0;
    lf = 0;
    while(*fmt) {
        if(*fmt=='%') {
            fmt++;
            if(*fmt=='%')
                goto put;
            len=0;
            while(*fmt >='0' && *fmt<='9') {
                len *= 10;
                len += *fmt-'0';
                fmt++;
            }
            if(*fmt=='l'){
                fmt++;
                lf++;
            }
            if(*fmt=='c') {
                arg = __builtin_va_arg(args, int);
                *dst++ = (char)arg;
                fmt++;
                continue;
            }
            else if(*fmt=='d' || *fmt=='u') {
				if(lf == 0){
					arg = __builtin_va_arg(args, int);
					i=18;
					if(arg > 99999999999999999L)
						arg = 99999999999999999L;
				}
				else{
					arg = __builtin_va_arg(args, s64);
					i=29;
				}
				sign=0;
				if(*fmt=='d' && (int)arg < 0) {
					arg *= -1;
					sign++;
				}
                tmpstr[i]=0;
                do {
					s64 l = __div(arg,10);
                    tmpstr[--i]= '0' + (arg - (l*10));
                    arg = l;
                } while(arg != 0 && i > 0);
                if(sign)
                    tmpstr[--i]='-';
                if(len > 0 && len < sizeof(tmpstr)) {
                    while(i > sizeof(tmpstr)-len)
                        tmpstr[--i]=' ';
                }
                p = &tmpstr[i];
                goto copystring;
            }
            else if(*fmt=='x') {
                arg = __builtin_va_arg(args, s64);
                i=16;
                tmpstr[i]=0;
                do {
                    char n = arg & 0xf;
                    tmpstr[--i]= n + (n > 9 ? 0x37:0x30);
                    arg>>=4;
                } while(arg!=0 && i>0);
                if(len>0 && len<=16) {
                    while(i>16-len)
                        tmpstr[--i]='0';
                }
                p=&tmpstr[i];
                goto copystring;
            }
            else  if(*fmt=='s') {
                p = __builtin_va_arg(args, char*);
copystring:
                lf=0;
				if(p==(void*)0)
                    p="(null)";
                while(*p)
                    *dst++ = *p++;
            }
        }
        else {
put:
			*dst++ = *fmt;
        }
        fmt++;
    }
    *dst=0;
    return dst-orig;
}

unsigned int sprintf(char *dst, char* fmt, ...){
    __builtin_va_list args;
    __builtin_va_start(args, fmt);
    return vsprintf(dst,fmt,args);
}

void printf(char *fmt, ...) {
	__builtin_va_list args;
    __builtin_va_start(args, fmt);
    char *s = (char*)&_end;
    vsprintf(s,fmt,args);
    while(*s) {
        if(*s=='\n')
            rk_uart_sendbyte('\r');
        rk_uart_sendbyte(*s++);
    }
}