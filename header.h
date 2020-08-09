typedef struct poly{
    double coef;
    int deg;
    struct poly *next, *prev;
}poly;

poly* get_number_input();

void print_poly(poly* num);

poly* poly_div(poly *a_node, poly *b_node);

