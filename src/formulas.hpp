#pragma once

// ALWAYS DEFINE TEMPLATES IN HPPs NOT CPPs
template <typename T>
class Pair
{
public:
    T x,y;
	Pair(T x=0, T y=0) : x(x), y(y) {}
};


void load_data_from_file(const char* filename, Pair<float> data[], int size);

namespace ML{

    float hypothesis(float x, float para[]);
    float loss_func(float para[], Pair<float> data[]);
    float loss_gradient(float para[], Pair<float> data[],int index);
    void batch_gradient_descent_step(float para[], Pair<float> data[]);
    float sum(float arr[],int n);
}

namespace DS{

    // since the data points are of type Pair<float>, we can use a template function to find the max value
    template <typename T>
    Pair <T> findMax(const Pair<T> arr[], int size) {
        
        Pair <T> max(arr[0].x, arr[0].y);
        for(int i = 1; i < size; ++i) {
            if(arr[i].x > max.x) max.x = arr[i].x;
            if(arr[i].y > max.y) max.y = arr[i].y;
        }
        return max;
    }

    template <typename T>
    Pair <T> findMin(const Pair<T> arr[], int size) {
        
        Pair <T> min(arr[0].x, arr[0].y); 
        for(int i = 1; i < size; ++i) {
            if(arr[i].x < min.x) min.x = arr[i].x;
            if(arr[i].y < min.y) min.y = arr[i].y;
        }
        return min;
    }
}