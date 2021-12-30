// filename: utf8validator.c
#include <stdio.h>
int main (){
    int ch, codepoint, cntASCII, multibytes, temp;
    cntASCII = 0;
    multibytes = 0;
    while ((ch = getchar()) != EOF){
        temp = ch;
        if ((ch & 0x80) == 0){// prota eksetazoume an einai xaraktiras tou 1-byte
            codepoint = ch;
            cntASCII++;
        }
        else{
            if ((ch & 0xE0) == 0xC0){ //an oxi tote eksezatoume an einai xaraktiras ton 2-byte
                codepoint = ch & 0x1F;
                if ((ch = getchar()) == EOF){
                    printf("unexpected EOF\n");
                    return 1;
                }
                if ((ch & 0xC0) != 0x80){
                    printf("Invalid UTF-8 tail byte: 0x%02X\n", ch);
                    return 2;
                }
                codepoint <<= 6;
                codepoint += (ch & 0x3F);
                if (codepoint < 0x0080){//eksetazoume an o xaraktiras xrisimopoiei perissotera byte apoti provlepei i utf-8 kodikopoiisi
                    printf("Oversized UTF-8 code point: U+%04X\n", codepoint);
                    return 3;
                }
            }
            if ((ch & 0xF0) == 0xE0){ //an oxi tote eksezatoume an einai xaraktiras ton 3-byte
                codepoint = ch & 0x0F;
                if ((ch = getchar()) == EOF){
                    printf("unexpected EOF\n");
                    return 1;
                }
                if ((ch & 0xC0) != 0x80){
                    printf("Invalid UTF-8 tail byte: 0x%02X\n", ch);
                    return 2;
                }
                codepoint <<= 6;
                codepoint += (ch & 0x3F);
                if ((ch = getchar()) == EOF){
                    printf("unexpected EOF\n");
                    return 1;
                }
                if ((ch & 0xC0) != 0x80){
                    printf("Invalid UTF-8 tail byte: 0x%02X\n", ch);
                    return 2;
                }
                codepoint <<= 6;
                codepoint += (ch & 0x3F);
                if ((codepoint >= 0xD800) && (codepoint <= 0xDFFF)){
                   printf("Invalid UTF-8 code point: U+%04X\n", codepoint);
                    return 3;
                }
                if (codepoint < 0x0800){//eksetazoume an o xaraktiras xrisimopoiei perissotera byte apoti provlepei i utf-8 kodikopoiisi
                    printf("Oversized UTF-8 code point: U+%04X\n", codepoint);
                    return 4;
                }
            }
            if ((ch & 0xF8) == 0xF0){ //an oxi tote eksezatoume an einai xaraktiras ton 4-byte
                codepoint = ch & 0x07;
                if ((ch = getchar()) == EOF){
                    printf("unexpected EOF\n");
                    return 1;
                }
                if ((ch & 0xC0) != 0x80){
                    printf("Invalid UTF-8 tail byte: 0x%02X\n", ch);
                    return 2;
                }
                codepoint <<= 6;
                codepoint += (ch & 0x3F);
                if ((ch = getchar()) == EOF){
                    printf("unexpected EOF\n");
                    return 1;
                }
                if ((ch & 0xC0) != 0x80){
                    printf("Invalid UTF-8 tail byte: 0x%02X\n", ch);
                    return 2;
                }
                codepoint <<= 6;
                codepoint += (ch & 0x3F);
                if ((ch = getchar()) == EOF){
                    printf("unexpected EOF\n");
                    return 1;
                }
                if ((ch & 0xC0) != 0x80){
                    printf("Invalid UTF-8 tail byte: 0x%02X\n", ch);
                    return 2;
                }
                codepoint <<= 6;
                codepoint += (ch & 0x3F);
                if (codepoint < 0x010000){//eksetazoume an o xaraktiras xrisimopoiei perissotera byte apoti provlepei i utf-8 kodikopoiisi
                    printf("Oversized UTF-8 code point: U+%04X\n", codepoint);
                    return 4;
                }
            }
        }
        if (codepoint > 0x10FFFF){//eksetazoume ean ksepernaei to codepoint gia to opoio isxieii i utf-8 kodikopoiisi
            printf("Invalid UTF-8 codepoint: U+%04X\n", codepoint);
            return 3;
        }
        //printf("U+%04X\n", codepoint);
        if (((temp & 0xE0) != 0xC0) && ((temp & 0xF0) != 0xE0) && ((temp & 0xF1) != 0xF0) && ((temp & 0x80) != 0)){//eksetazoume an to header byte plirei tis proipotheseis ton header-byte stin utf-8 kodikopoiisi
            printf("Invalid UTF-8 header byte: 0x%02X\n", temp);
            return 5;
        }
        if (((temp & 0xE0) == 0xC0) || ((temp & 0xF0) == 0xE0) || ((temp & 0xF1) == 0xF0)){
            multibytes++;//an to header byte plirei tis proipotheseis ton header-byte stin utf-8 kodikopoiisi auksanoume kata ena tin metavliti pou mas deixnei tous multibytes xaraktires
        }
    }
    printf("Found %d ASCII and %d multibyte UTF-8 characters\n", cntASCII, multibytes);
    return 0;
}

