//
//  main.cpp
//  hpcEx1
//
//  Created by Thijs Vogels on 27-9-2014.
//  Copyright (c) 2014 Vit. All rights reserved.
//

#include <iostream>
#include <thread>
#include <cmath>
#include <iomanip>

typedef std::function<double(double)> r2r;

double riemann(r2r f, double a, double b, std::size_t n) {
    double result = 0;
    double dx = (b-a) / double(n);
    double xim1 = a;
    for (std::size_t ii = 0; ii < n; ++ii) {
        double xi = xim1 + dx;
        result += f((xi + xim1)/2)*dx;
        xim1 = xi;
    }
    return result;
}

//int main(int argc, const char * argv[]) {
//    // insert code here...
//    std::cout << std::setprecision(18) << riemann([](double x){ return sqrt(x)*log(x);}, 1,4,100000) << std::endl;
//    return 0;
//}
