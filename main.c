#include <stdio.h>
#include <math.h>
#include <assert.h>

enum NUM_ROOTS {
    NO_ROOTS  = 0,
    ONE_ROOT  = 1,
    TWO_ROOTS = 2,
    INF_ROOTS = -1
};

struct coeff {
    double a;
    double b;
    double c;
};

int SolveQuadr(struct coeff *pointer, double *px1, double *px2);
void Bufer_Clean(void);
void Interface(struct coeff *pointer);
int Show_Results(int nRoots, double x1, double x2);

int main(void) {

    struct coeff quadr;
    struct coeff *quadr_pointer = &quadr;
    
    Interface(quadr_pointer);
    
    double x1 = 0, x2 = 0;
    
    int nRoots = SolveQuadr(quadr_pointer, &x1, &x2);
    
    Show_Results(nRoots, x1, x2);
}


int SolveQuadr(struct coeff *pointer, double *px1, double *px2) {
    
    double a= pointer->a, b = pointer->b, c=pointer->c;
    
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    
    assert(px1 != NULL);
    assert(px2 != NULL);
    assert(px1 != px2);
    
    if (a != 0) {
        
        double d = b * b - 4 * a * c;
        
        if(d > 0) {
            
            double sqrt_d = sqrt(d);
            
            *px1 = (sqrt_d - b) / (2 * a);
            *px2 = -(sqrt_d + b)/(2 * a);
            
            return TWO_ROOTS;
        }
        if(d == 0) {
            
            *px1 = -b / (2 * a);
            
            return ONE_ROOT;
        }
        return NO_ROOTS;
    }
    
    if(b != 0) {
        
        *px1 = -c / b;
        
        return ONE_ROOT;
    }
    
    if (c == 0) {
        return INF_ROOTS;
    }
    
    return NO_ROOTS;
}

void Bufer_Clean(void){
    
    char a = 0;
    
    do {
        a = getchar();
    }
    while (a != EOF && a != '\n');
}

void Interface(struct coeff *pointer) {
    
    printf("quadratic equation solver \n");
    
    int flag = 0;
   
    do {
        printf("Enter a, b, c \n");
        flag = scanf("%lg %lg %lg", &((*pointer).a), &((*pointer).b) , &((*pointer).c));
        Bufer_Clean();
    } while(flag != 3);
}

int Show_Results(int nRoots, double x1, double x2){
    
    switch(nRoots) {
        case NO_ROOTS: printf("No roots! \n");
                break;
        case ONE_ROOT: printf("x1 = %.2lf \n", x1);
                break;
        case TWO_ROOTS: printf("x1 = %.2lf, x2 = %.2lf \n", x1, x2);
                break;
        case INF_ROOTS: printf("Any number \n");
                        break;
        default: printf("ERROR nRoots = %d \n", nRoots);
                 return 1;
    }
    
    return 0;
}
