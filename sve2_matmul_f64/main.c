//-----------------------------------------------------------------------------------------
// Copyright (c) 2019-2021 Arm Limited (or its affiliates). All rights reserved.
// Use, modification and redistribution of this file is subject to your possession of a
// valid End User License Agreement for the Arm Product of which these examples are part of
// and your compliance with all applicable terms and conditions of such licence agreement.
//-----------------------------------------------------------------------------------------

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matmul.h"

#define M 128
#define K 128
#define N 128

#define ERROR_TOLERANCE 0.01

// Disable all SVE and SIMD traps by setting CPTR_EL3.EZ bit [8] and clearing CPTR_EL3.TFP bit [10]
void disable_sve_traps(void)
{
    __asm volatile (
    "MRS x0, CPTR_EL3\n"
    "BIC x0, x0, #(1<<10)\n"
    "ORR x0, x0, #(1<<8)\n"
    "MSR CPTR_EL3, x0\n"
    "ISB\n"
    );
}

int main()
{
    float64_t input_left[M*K];
    float64_t input_right[K*N];

    float64_t output_ref[M*N] = {0};
    float64_t output_opt[M*N] = {0};

    printf("\nSVE2 Matrix Multiply Float64 example\n");

    disable_sve_traps();

    srand((unsigned int)time(0));

    for(int64_t x = 0; x < (M * K); ++x)
    {
        input_left[x] = ((double)(rand() % 2000000) / 100.f) - 10000.0;
    }
    for(int64_t x = 0; x < (K * N); ++x)
    {
        input_right[x] = ((double)(rand() % 2000000) / 100.f) - 10000.0;
    }

    calc_matmul_ref(M, K, N, input_left, input_right, output_ref);
    calc_matmul_opt(M, K, N, input_left, input_right, output_opt);

    printf("ERROR TOLERANCE = %f%%\n", (float)ERROR_TOLERANCE);
    uint32_t error = 0;
    for(int64_t i = 0; i < (M * N); ++i)
    {
        if((fabs((output_ref[i] - output_opt[i]) / output_ref[i]) * 100.0) > ERROR_TOLERANCE)
        {
            error++;
        }
    }

    if(!error)
    {
        printf("TEST PASSED\n");
    }
    else
    {
        printf("TEST FAILED\n");
        printf("NUMBER OF ERRORS: %d\n", error);
    }

    return 0;
}
