#include <iostream>
#include <math.h>
#include "configuration.hpp"
#include "formulas.hpp"
#include <fstream>
#include <sstream>
#include <iostream>



void load_data_from_file(const char* filename, Pair<float> data[], int size) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Could not open data file: " << filename << std::endl;
        return;
    }
    std::string line;
    int i = 0;
    while (std::getline(infile, line) && i < size) {
        std::istringstream iss(line);
        float x, y;
        char comma;
        if (iss >> x >> comma >> y) {
            data[i++] = Pair<float>(x, y);
        }
    }
    if (i < size) {
        std::cerr << "Warning: Only " << i << " data points loaded, expected " << size << std::endl;
    }
}


namespace ML{

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

    float loss_func(float para[], Pair<float> data[]){

        float sum = 0;

        for (size_t i = 0; i < SIZE; i++)
        {
            sum += pow(hypothesis(data[i].x,para)-data[i].y,2);
        }
        sum /=SIZE;
        LOSS = sum;
        return sum;

    }

    // parameter index to which's respective the loss function is differentiated
    // partial J / partial ti
    // J is loss function
    // ti is theta i
    float loss_gradient(float para[], Pair<float> data[],int index){

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

    // performs a single step, on the parameters
    void batch_gradient_descent_step(float para[], Pair<float> data[]) {
        
        float gradient_vector[PARAMS];
        for (size_t index = 0; index < PARAMS; index++){
                gradient_vector[index] = ML::loss_gradient(para,data,index);
        }
        for (size_t index = 0; index < PARAMS; index++){
            para[index] -= ALPHA*gradient_vector[index];
        }
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
}