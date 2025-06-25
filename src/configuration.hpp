#pragma once
#include "formulas.hpp"


// data set Constants
#define EULER       2.71828
#define ALPHA       0.0001
#define EPSILON     0.001
#define THRESHOLD   0.0001 // LIMIT till which gradient descent is done

// data set array constants
#define SIZE 		20 // data set size m
#define PARAMS 		10

// SFML window constants
#define WIDTH	   	550
#define HEIGHT	   	550

// graph constants
#define EDGE 		100


extern float para[PARAMS];
extern float LOSS;

