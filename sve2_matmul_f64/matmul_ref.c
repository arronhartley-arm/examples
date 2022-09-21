//-----------------------------------------------------------------------------------------
// Copyright (c) 2019-2021 Arm Limited (or its affiliates). All rights reserved.
// Use, modification and redistribution of this file is subject to your possession of a
// valid End User License Agreement for the Arm Product of which these examples are part of
// and your compliance with all applicable terms and conditions of such licence agreement.
//-----------------------------------------------------------------------------------------

#include "matmul.h"

void calc_matmul_ref(uint64_t M, uint64_t K, uint64_t N, float64_t* input_left, float64_t* input_right, float64_t* output)
{
    for(uint64_t x = 0; x < M; ++x)
    {
        for(uint64_t y = 0; y < N; ++y)
        {
            float64_t acc = 0.0;

            for(uint64_t z = 0; z < K; ++z)
            {
                acc += input_left[(x*K)+z] * input_right[(z*N)+y];
            }

            output[(x*N)+y] = acc;
        }
    }
}
