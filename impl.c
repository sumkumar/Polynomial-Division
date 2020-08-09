#include<stdio.h>
#include<stdlib.h>
#include "2_header.h"

int is_zero(double d){
    if(d>0.000001f || d<-0.000001f)
        return 0;
    return 1;
}

void print_node(poly* node){
    if(node->next == NULL){
            if(node->deg != 0)
                printf("%lfx^%d\n", node->coef, node->deg);
            else
                printf("%lf\n", node->coef);
        return ;
    }
    if(node->next->coef >= 0)
    printf("%lfx^%d + ", node->coef, node->deg);
    else
    printf("%lfx^%d ", node->coef, node->deg);
    print_node(node->next);
}

void print_poly(poly* num){
    if(num != NULL)
    print_node(num);
    else
        printf("0\n");
}

poly* add_node(poly* head, int deg, double coef){
    poly* new_node = (poly*) malloc(sizeof(poly));
    new_node->coef = coef;
    new_node->deg = deg;
    new_node->next = head->next;
    if(new_node->next != NULL){
        new_node->next->prev = new_node;
    }
    new_node->prev = head;
    head->next = new_node;
    return new_node;
}

poly* update_poly(poly* head, int deg, double coef){
    poly *p=head, *temp;
    while(p->deg>deg){
        p=p->next;
    }
    if(p->deg == deg){
        p->coef += coef;
    }
    else{
        if(p->prev != NULL){
            add_node(p->prev, deg, coef);
        }
        else{
            poly* new_node = (poly*) malloc(sizeof(poly));
            new_node->coef = coef;
            new_node->deg = deg;
            new_node->next = p;
            new_node->prev = NULL;
            head = new_node;
        }
    }
    return head;
}

poly* get_number_input(){
    double coef;
    int deg;
    poly *head = NULL, *p;
    printf("Enter your polynomial: ");
    char ch=' ';
    ch=' ';
    while(ch==' ')
    scanf("%c", &ch);
	if(ch == '(')
    scanf("%d,%lf)", &deg, &coef);
	else{
		printf("Please Enter valid input\n");
		exit(-1);
	}
    if(is_zero(coef) == 1){
        printf("Please enter proper input\n");
        exit(0);
    }
    head = (poly*) malloc(sizeof(poly));
    head->next = NULL;
    head->prev = NULL;
    head->coef = coef;
    head->deg = deg;
    p=head;
    ch=' ';
    while(ch==' ')
    scanf("%c", &ch);
    while(ch==','){
        scanf("(%d,%lf)", &deg, &coef);
        if((is_zero(coef) == 1) || p->deg <= deg ){
            printf("Please enter proper input\n");
            exit(-1);
        }
        add_node(p, deg, coef);
        p=p->next;
        ch=' ';
        while(ch==' ')
        scanf("%c", &ch);
        if(ch == ',')
            continue;
        else if(ch=='\n' || ch == EOF)
            break;
    }
	while(ch!=10)
	scanf("%c", &ch);
    return head;
}

poly* get_div_val(poly *a_node,poly *b_node){
    poly *temp, *p, *q;
    while(a_node != NULL && b_node !=NULL){
        if(a_node->deg >= b_node->deg){
            temp = (poly*) malloc(sizeof(poly));
            temp->deg = a_node->deg - b_node->deg;
            temp->coef = a_node->coef / b_node->coef;
            p=a_node;
            q=b_node;
            while(p!=NULL && q!=NULL){
                if(p->deg == (q->deg + temp->deg)){
                    p->coef -= (q->coef * temp->coef);
                    p=p->next;
                    q=q->next;
                    continue;
                }
                else if(p->deg < (q->deg + temp->deg)){
                    temp = p->prev;
                    if(temp != NULL){
                        add_node(temp, q->deg+temp->deg, temp->coef*-1);
                        q=q->next;
                    }
                    else
                        break;
                }
            }
            temp->next = NULL;
            temp->prev = NULL;
        }
        else
            break;
    }
    return a_node;
}

poly* remove_zero_coef(poly *a_head){
    poly *temp, *p;
    while(is_zero(a_head->coef) == 1){
        temp = a_head->next;
        if(temp != NULL){
            temp->prev = NULL;
        }
        free(a_head);
        a_head = temp;
        if(a_head == NULL)
        return a_head;
    }
    p=a_head->next;
    while(p!= NULL){
        if(is_zero(p->coef) == 1){
            temp = p->next;
            if(temp != NULL){
                temp->prev = p->prev;
            }
            p->prev->next = temp;
            free(p);
            p=temp;
        }
        else
            p=p->next;
    }
    return a_head;
}

poly* poly_div(poly *a_node, poly *b_node){
    poly *quotient = NULL, *rem = NULL, *temp, *q_temp, *p_node, *q, *head = a_node, *p;

    while(a_node != NULL && b_node !=NULL){
        if(is_zero(a_node->coef) == 1)
            a_node = a_node->next;
        if(a_node->deg >= b_node->deg){
            temp = (poly*) malloc(sizeof(poly));
            temp->deg = a_node->deg - b_node->deg;
            temp->coef = a_node->coef / b_node->coef;
            temp->next = NULL;
            temp->prev = NULL;
            if(quotient == NULL){
                quotient = temp;
                p_node=temp;
            }
            else{
                p_node->next = temp;
                temp->prev = p_node;
                p_node=p_node->next;
            }
            p=a_node;
            q=b_node;
            while(p!=NULL && q!=NULL){
                if(p->deg == (q->deg + temp->deg)){
                    p->coef -= (q->coef * temp->coef);
                    p=p->next;
                    q=q->next;
                    continue;
                }
                else if(p->deg < (q->deg + temp->deg)){
                    if(temp != NULL){
                        update_poly(p->prev, q->deg+temp->deg, temp->coef*-1);
                        q=q->next;
                    }
                    else
                        break;
                }
                else{
                    p=p->next;
                }
            }
            a_node=a_node->next;
        }
        else
            break;
    }
    printf("\nQuotient : \n");
    print_poly(quotient);
    printf("\nRemainder : \n");
    a_node = remove_zero_coef(head);
    print_poly(a_node);
}

