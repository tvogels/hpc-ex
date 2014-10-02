//
//  result.h
//  hpcEx1
//
//  Created by Thijs Vogels on 2-10-2014.
//  Copyright (c) 2014 Vit. All rights reserved.
//

#ifndef __hpcEx1__result__
#define __hpcEx1__result__

#include <stdio.h>

struct result {
    double time;
    std::size_t steps;
    long double result;
    std::size_t threads;
};

#endif /* defined(__hpcEx1__result__) */
