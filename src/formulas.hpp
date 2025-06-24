#pragma once




float hypothesis(float x, float para[]);
float loss_func(float para[], pair data[]);
float loss_gradient(float para[], pair data[],int index);
float sum(float arr[],int n);
void batch_gradient_descent(float para[],pair data[]);

