#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

int my_printf_putchar(char p1){
    write(1,&p1,1);
    return 1;
}

int length(char* p1){
    int count = 0;

    for(int i = 0; p1[i]; i++){
        count++;
    }

    return count;
}

int my_printf_putstr(char* p1){
    int str_len = 0;

    for(int i = 0; p1[i]; i++){
        my_printf_putchar(p1[i]);
        str_len++;
    }
    return str_len;
}

char* int_to_str(int p1){
    char* str = malloc(sizeof(char)* 10);
    int num = p1;
    int x = 0;
    int point = 0;
    if(p1 == 0){
        return "0";
    }
    if(num < 0){
        num = num * -1;
        point++;
    }

    for(int i = 0; num != 0; i++){
        str[i] = num % 10 + '0';
        num = num / 10;
    }

    char* rev_str = malloc(sizeof(char)* length(str));

    for(int i = length(str) -1; i >= 0 ; i--){
        if(point == 1){
            rev_str[x] = '-';
            point--;
            x++;
        }
        rev_str[x] = str[i];
        x++;
    }
    return rev_str;
}


int dec_to_octa(int p1){
    int dec = p1;
    int count = 0;
    
    int octa = 0, temp = 1;

    while (dec != 0)
    {
        octa = octa + (dec % 8) * temp;
        dec = dec / 8;
        temp = temp * 10;
    }
    char* str_octa = int_to_str(octa);
    count += my_printf_putstr(str_octa);

    return count;
}

int dec_to_hex(int p1){
    int dec = p1;
    int i = 1, j, temp;
    int count = 0;
    char hexa[100];
    
    while (dec != 0) {
        temp = dec % 16;
        if (temp < 10){
            temp = temp + 48;
        }
        else{
            temp = temp + 55;
        }
        hexa[i++] = temp;
        dec = dec / 16;
    }

    for ( j = i - 1; j > 0; j--){
        count += my_printf_putchar(hexa[j]);
    }

    return count;
}

int dec_to_hex_un(long p1){
    long dec = p1;
    int i = 1, j, temp;
    int count = 0;
    int hexa[100];
    while (dec != 0) {
        temp = dec % 16;
        if (temp < 10){
            temp = temp + 48;
        }
        else{
            temp = temp + 87;
        }
        hexa[i++] = temp;
        dec = dec / 16;
    }
    my_printf_putstr("0x");
    for ( j = i - 1; j > 0; j--){
        count += my_printf_putchar(hexa[j]);
    }
    count +=2;
    return count;
}

int dec_unsigned(int p1){
    int count = 0;
    if(p1 < 0){
        p1 = p1 * -1;
    }
    char* un_str = int_to_str(p1);
    count += my_printf_putstr(un_str);
    return count;
}

int my_printf(char * p1, ...){
    va_list page;
    va_start(page,p1);
    int p1_len = 0;
    int i = 0;

    while(p1[i]){
        if(p1[i] == '%' && p1[i+1] == 'c'){
            i+=2;
            char ch = va_arg(page, int);
            p1_len = p1_len + my_printf_putchar(ch);
        }
        else if(p1[i] == '%' && p1[i+1] == 's'){
            i+=2;
            char* str = va_arg(page, char*);
            if(str == NULL){
                str = "(null)";
            }
            p1_len = p1_len + my_printf_putstr(str);
        }
        else if(p1[i] == '%' && p1[i+1] == 'd'){
            i+=2;
            int dec = va_arg(page, int);
            char* char_dec = int_to_str(dec);
            p1_len = p1_len + my_printf_putstr(char_dec);
        }
        else if(p1[i] == '%' && p1[i+1] == 'x'){
            i+=2;
            int hex = va_arg(page, int);
            p1_len = p1_len + dec_to_hex(hex);
        }
        else if(p1[i] == '%' && p1[i+1] == 'o'){
            i+=2;
            int octa = va_arg(page, int);
            p1_len = p1_len + dec_to_octa(octa);
        }
        else if(p1[i] == '%' && p1[i+1] == 'u'){
            i+=2;
            int un_dec = va_arg(page, int);
            p1_len = p1_len + dec_unsigned(un_dec);
        }
        else if(p1[i] == '%' && p1[i+1] == 'p'){
            i+=2;
            unsigned long d = (unsigned long) va_arg(page, void*);
            p1_len = p1_len + dec_to_hex_un(d);
        }
        else {
            my_printf_putchar(p1[i]);
            p1_len++;
            i++;
        }
    }

    return p1_len;
}

// int main(){
//     // char s[] = "Allo";
//     // char c = '!';
//     // int d = -122;
//     printf("%p\n", "asd");
//     // int len1 = my_printf("NULL STRING (null)!\n");
//     // printf("len printf %d\n", len);
//     // my_printf("len my_printf %d\n", len1);
//     int num = my_printf("%p\n", "asd");
//     printf("%d\n",num);
//     return 0;
// }