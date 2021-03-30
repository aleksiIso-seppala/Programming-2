// Note that there is no need for "using namespace std",
// since no C++ standard libraries are used.

double addition(double left, double right) {
    return left + right;
}


double subtraction(double left, double right) {
    return left - right;
}


double multiplication(double left, double right) {
    return left * right;
}


double division(double left, double right) {
    return left / right;
}

double exponent(double left, double right){
    double calculate = left;
    while (right > 1){
        calculate = calculate * left;
        right--;
    }
    return calculate;
}
