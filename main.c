#include<stdio.h>
#include "2_header.h"

void main(){
    poly *a_head = NULL, *b_head  = NULL, *num;
    unsigned int dig;
    char ch=',', op = ' ';
    while(ch != EOF){
        printf("First polynomial \n");
        a_head = get_number_input();
        printf("Second polynomial \n");
        b_head = get_number_input();
        poly_div(a_head, b_head);
        printf("Repeat again ? Enter N to discontinue: \n");
        scanf("%c", &ch);
        if(ch == 'N' || ch=='n')
            break;
		while(ch!=10)
		scanf("%c", &ch);
    }
}
