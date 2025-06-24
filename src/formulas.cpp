#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define EULER       2.71828
#define ALPHA       0.0001
#define EPSILON     0.001
#define THRESHOLD   0.0001 // LIMIT till which gradient descent is done


#define SIZE 20 // data set size m
#define PARAMS 10

// global var to prevent redundant calculations

float Loss = 0;

typedef struct
{
    float x,y;
} pair;


float hypothesis(float x, float para[]){

    // to prevent log 10 from having a nan
    float log_arg = 1 + para[5] * (pow(x, 2));

    // Safeguard to prevent log10 from failing
    if (log_arg <= 0) {
        log_arg = 1e-9; // Set to a tiny positive number to avoid nan
    }

    return 
    para[0]*sin(para[1]*x) + 
    para[2]*pow(EULER,(-para[3]*pow(x,2))) + 
    para[4]*log10(log_arg) + 
    para[6]*pow(x,3) + 
    para[7]*pow(x,2) + 
    para[8]*x + 
    para[9];
}

float loss_func(float para[], pair data[]){

    float sum = 0;

    for (size_t i = 0; i < SIZE; i++)
    {
        sum += pow(hypothesis(data[i].x,para)-data[i].y,2);
    }
    sum /=SIZE;
    Loss = sum;
    return sum;

}

// parameter index to which's respective the loss function is derivated
// partial J / partial ti
// J is loss function
// ti is theta i
float loss_gradient(float para[], pair data[],int index){

    // in the original function J(t1,t2,...,ti+e,...,)
    // hence that index is increased by epsilon
    // new array to handle the incremented para, data is copied
    float greater_para[PARAMS];
    for (int i = 0; i < PARAMS; ++i) {
        greater_para[i] = para[i];
    }


    greater_para[index] += EPSILON;

    return ((loss_func(greater_para,data) - loss_func(para,data)) / EPSILON);

}

// threshold function, will return 1 when two num are same to 2 significant figures
int threshold(float num1,float num2){
     return fabs(num1 - num2) < THRESHOLD;
}

// sum of all nums in an array

float sum(float arr[],int n){
    int sum = 0;
    for (size_t i = 0; i < n; i++)
    {
        sum+=arr[i];
    }
    return sum;
}



void batch_gradient_descent(float para[],pair data[]){

    float new_para = 0;
    int steps = 1000;
    int print = 0;

    float gradient_vector[PARAMS];

    while (
        /* !threshold(new_para, para[index])  &&*/ 
        steps++ < 500000 ||
        Loss>0.1 
        //  new_para<20
    )
    {
        if(print >1000){
            printf("\nloss: %f",loss_func(para,data));
            print = 0;
        }
        print++;

        
        for (size_t index = 0; index < PARAMS; index++){
            gradient_vector[index] = loss_gradient(para,data,index);
        }
        
        for (size_t index = 0; index < PARAMS; index++){
            para[index] -= ALPHA*gradient_vector[index];
        }
    }
}



float rand_range(int min, int max){
    return rand() % (max - min + 1) + min;
}

/* int main(){
    srand(time(NULL));


    pair data[SIZE] = {
        
        

        { -5.0, -1.50 },
        { -4.5,  0.01 },
        { -4.0,  0.55 },
        { -3.5,  1.20 },
        { -3.0,  1.85 },
        { -2.5,  2.30 },
        { -2.0,  2.70 },
        { -1.5,  3.00 },
        { -1.0,  3.20 },
        { -0.5,  3.30 },
        {  0.0,  3.35 },
        {  0.5,  3.30 },
        {  1.0,  3.20 },
        {  1.5,  3.00 },
        {  2.0,  2.70 },
        {  2.5,  2.30 },
        {  3.0,  1.85 },
        {  3.5,  1.20 },
        {  4.0,  0.55 },
        {  4.5,  0.01 }

    };

    

    
    float para[PARAMS] = {
        10,
        10,
        10,
        10,
        10,
        10,
        10,
        10,
        10,
        3.4
    };

    printf("choosing rand parameters ... \n");
    // choose random initial parameters until loss<0.1
    while (loss_func(para,data)>10)
    {
        printf("loss: %f\n",Loss);
        for (size_t i = 0; i < PARAMS; i++)
        {
            para[i] = rand_range(0,2);
        }
    }
    

    printf("initial parameters:\n\n");
    printf("[");
    for (size_t i = 0; i < PARAMS; i++)
    {
        printf("%f,",para[i]);
    }
    
    printf("]\n");
    
    
    batch_gradient_descent(para,data);
    
    
    printf("\nfinal parameters:\n\n");
    printf("[");
    for (size_t i = 0; i < PARAMS; i++)
    {
        printf("%f,",para[i]);
    }
    
    printf("]\n");
    


}
 */