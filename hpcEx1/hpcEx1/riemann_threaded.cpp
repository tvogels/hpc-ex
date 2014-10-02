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
#include <vector>
#include "timer.hpp"
#include "result.h"


// define some shorthands
typedef std::function<long double(long double)> r2r;
typedef std::lock_guard<std::mutex> guard;

// the Riemann function
// it adds the sum to result pair (double, mutex)
void riemann(std::pair<long double, std::mutex> &result, r2r f, long double a, long double b, std::size_t n) {
    long double subtotal = 0;
    
    const long double dx = (b-a) / n;
    
    for (std::size_t ii = 0; ii < n; ++ii) {
        subtotal += f(a + dx*(ii+.5))*dx;
    }
    
    guard l (result.second);
    result.first += subtotal;
}

result compute(int steps) {
    
    timer t;
    t.start();
    
    std::pair<long double, std::mutex> result;
    result.first = 0;
    
    auto const f = [](long double x){ return sqrtl(x)*logl(x);};
    const long double a = 1.;
    const long double b = 4.;
    const std::size_t N = steps;
    
    // determine the number of threads
    const std::size_t nThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(nThreads);
    
    // and some consequences of that
    const std::size_t NperThread = N/nThreads;
    
    // spawn the threads
    long double dx = (b-a)/nThreads;
    long double left = a;
    long double right = 0.0;
    for (std::size_t ii = 0; ii < nThreads; ii++) {
        right = left + dx;
        threads[ii] = std::thread(riemann, std::ref(result), f, left, right, NperThread);
        left = right;
    }
    
    for (std::thread &t : threads) {
        t.join();
    }
    
    t.stop();
    
    struct result myRes;
    myRes.time = t.get_timing();
    myRes.threads = nThreads;
    myRes.result = result.first;
    myRes.steps = N;

    return myRes;
}

int main(int argc, const char * argv[]) {
    // Initialize

    for (unsigned ii = 0; ii < 10; ii++) {
        result r = compute(pow(10, ii));
        std::cout << std::setprecision(18) << r.result << "," << r.time << "," << r.steps << "," << r.threads << std::endl;
    }
    
    return 0;
}
