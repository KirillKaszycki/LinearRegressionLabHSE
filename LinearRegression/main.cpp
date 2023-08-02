#include <iostream>
#include <cmath>

float X[8] = {45.0, 58.0, 54.0, 62.0, 56.0, 47.0, 55.0, 51.0};
float y[8] = {65.0, 59.0, 59.0, 52.0, 55.0, 57.0, 49.0, 61.0};

// initialize the errors class
class Errors final{
    public:
    static float r2_score(float r){
        float r2score = pow(r, 2);
        return r2score;
    }
};



// average counting function
float average(const float value[], int size){
    float sum = 0;
    for(int i=0; i<size; i++){
        sum += value[i];
    }
    return sum / size;
}

float sum(const float value[], int size){
    float sum = 0;
    for(int i=0; i<size; i++){
        sum += value[i];
    }
    return sum;
}

// regression model
float regression_model(float Features[], float target[]){
    float X_mean = average(Features, 8);
    float y_mean = average(target, 8);

    float X_sum = sum(Features, 8);
    float y_sum = sum(target, 8);

    float XY[8];
    for (size_t i = 0; i < sizeof(X) / sizeof(float); ++i) {
        XY[i] = X[i] * y[i];
    }

    float XY_mean = average(XY, 8);
    float XY_sum = sum(XY, 8);

    float X_square[8];
    for(int i=0; i<sizeof(X); ++i){
        X_square[i] = pow(i, 2);
    }
    float y_square[8];
    for(int i=0; i< sizeof(y); ++i){
        y_square[i] = pow(i, 2);
    }

    float X_square_sum = sum(X_square, 8);
    float y_square_sum = sum(y_square, 8);

    float X_square_mean = average(X_square, 8);
    float y_square_mean = average(y_square, 8);

    float X_mean_square = pow(X_mean, 2);
    float y_mean_square = pow(y_mean, 2);

    // take the linear regression coefficients
    float b = (XY_mean - X_mean * y_mean) / (X_square_mean - X_mean_square);
    float a = y_mean - b * X_mean;

    std::cout << "b coefficient is "<< b << std::endl;
    std::cout << "a coefficient is " << a <<  std::endl;

    // take the correlation coefficient
    float sigma_x = X_square_mean - X_mean_square;
    float sigma_y = y_square_mean - y_mean_square;
    float R_xy = b * sigma_x / sigma_y;

    std::cout << "___________________________________" << std::endl;
    std::cout << "R_xy = " << R_xy << std::endl;

    float r2_score =  Errors::r2_score(R_xy);
    std::cout << "R2_score = " << r2_score << std::endl;

    // initialize the prediction with X_new = 105% of X_mean
    float X_new = X_mean * 1.05;
    float y_new = a + b * X_new;
    std::cout << "___________________________________" << std::endl;
    std::cout << "X = 105% is " << X_new << std::endl;
    std::cout << "Predicted y with X = 105% is " << y_new << std::endl;

    return 0;
}

int main(){
    std::cout << "Mean X = " << average(reinterpret_cast<float *>(X), 8) << std::endl;
    std::cout << "Mean y = " << average(reinterpret_cast<float *>(y), 8) << std::endl;
    std::cout << "___________________________________" << std::endl;
    std::cout << regression_model(X, y);
    return 0;
}
