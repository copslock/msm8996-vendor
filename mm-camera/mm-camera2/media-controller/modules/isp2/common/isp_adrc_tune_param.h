/*============================================================================

 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.

============================================================================*/
// ADRC Knee Gain LUT
6, /* number of knees in knee gain array, max 8 knee,
        must match the data itself.
        array will have num_knee +2 entries,
        including two endpoints.*/
{
  // 1 : x1.000
  {
    { 1.0000,   1.0000,     1.0000,     1.0000,     1.0000,     1.0000}, //Knee gain[]
    { 0,        14,         26,         39,         51,         64}, //knee index[]
  },
  // 2 : x1.030
  {
    { 1.0300,   1.0292,     1.0197,     1.0131,     1.0072,     1.0000}, //Knee gain[]
    { 0,        13,         26,         39,         51,         64}, //knee index[]
  },
  // 3 : x1.061
  {
    { 1.0609,   1.0581,     1.0393,     1.0263,     1.0144,     1.0000}, //Knee gain[]
    { 0,        13,         26,         39,         51,         64}, //knee index[]
  },
  // 4 : x1.093
  {
    { 1.0927,   1.0869,     1.0588,     1.0414,     1.0217,     1.0000}, //Knee gain[]
    { 0,        13,         26,         38,         51,         64}, //knee index[]
  },
  // 5 : x1.126
  {
    { 1.1255,   1.1213,     1.0812,     1.0552,     1.0290,     1.0000}, //Knee gain[]
    { 0,        12,         25,         38,         51,         64}, //knee index[]
  },
  // 6 : x1.159
  {
    { 1.1593,   1.1511,     1.1012,     1.0691,     1.0365,     1.0000}, //Knee gain[]
    { 0,        12,         25,         38,         51,         64}, //knee index[]
  },
  // 7 : x1.194
  {
    { 1.1941,   1.1808,     1.1213,     1.0830,     1.0439,     1.0000}, //Knee gain[]
    { 0,        12,         25,         38,         51,         64}, //knee index[]
  },
  // 8 : x1.230
  {
    { 1.2299,   1.2220,     1.1413,     1.0970,     1.0515,     1.0000}, //Knee gain[]
    { 0,        11,         25,         38,         51,         64}, //knee index[]
  },
  // 9 : x1.267
  {
    { 1.2668,   1.2529,     1.1671,     1.1111,     1.0592,     1.0000}, //Knee gain[]
    { 0,        11,         24,         38,         51,         64}, //knee index[]
  },
  // 10: x1.305
  {
    { 1.3048,   1.2837,     1.1878,     1.1313,     1.0669,     1.0000}, //Knee gain[]
    { 0,        11,         24,         37,         51,         64}, //knee index[]
  },
  // 11: x1.344
  {
    { 1.3439,   1.3145,     1.2085,     1.1462,     1.0748,     1.0000}, //Knee gain[]
    { 0,        11,         24,         37,         51,         64}, //knee index[]
  },
  // 12: x1.384
  {
    { 1.3842,   1.3657,     1.2292,     1.1613,     1.0828,     1.0000}, //Knee gain[]
    { 0,        10,         24,         37,         51,         64}, //knee index[]
  },
  // 13: x1.426
  {
    { 1.4258,   1.3979,     1.2588,     1.1765,     1.0987,     1.0000}, //Knee gain[]
    { 0,        10,         23,         37,         50,         64}, //knee index[]
  },
  // 14: x1.469
  {
    { 1.4685,   1.4300,     1.2802,     1.1919,     1.1080,     1.0000}, //Knee gain[]
    { 0,        10,         23,         37,         50,         64}, //knee index[]
  },
  // 15: x1.513
  {
    { 1.5126,   1.4929,     1.3018,     1.2074,     1.1174,     1.0000}, //Knee gain[]
    { 0,        9,          23,         37,         50,         64}, //knee index[]
  },
  // 16: x1.558
  {
    { 1.5580,   1.5267,     1.3234,     1.2231,     1.1271,     1.0000}, //Knee gain[]
    { 0,        9,          23,         37,         50,         64}, //knee index[]
  },
  // 17: x1.605
  {
    { 1.6047,   1.5605,     1.3451,     1.2499,     1.1369,     1.0000}, //Knee gain[]
    { 0,        9,          23,         36,         50,         64}, //knee index[]
  },
  // 18: x1.653
  {
    { 1.6528,   1.5942,     1.3670,     1.2667,     1.1465,     1.0000}, //Knee gain[]
    { 0,        9,          23,         36,         50,         64}, //knee index[]
  },
  // 19: x1.702
  {
    { 1.7024,   1.6279,     1.4021,     1.2837,     1.1564,     1.0000}, //Knee gain[]
    { 0,        9,          22,         36,         50,         64}, //knee index[]
  },
  // 20: x1.754
  {
    { 1.7535,   1.7108,     1.4247,     1.3009,     1.1664,     1.0000}, //Knee gain[]
    { 0,        8,          22,         36,         50,         64}, //knee index[]
  },
  // 21: x1.806
  {
    { 1.8061,   1.7465,     1.4476,     1.3184,     1.1767,     1.0000}, //Knee gain[]
    { 0,        8,          22,         36,         50,         64}, //knee index[]
  },
  // 22: x1.860
  {
    { 1.8603,   1.7821,     1.4706,     1.3361,     1.1872,     1.0000}, //Knee gain[]
    {0,         8,          22,         36,         50,         64}, //knee index[]
  },
  // 23: x1.916
  {
    { 1.9161,   1.8171,     1.4907,     1.3496,     1.1942,     1.0000}, //Knee gain[]
    { 0,         8,         22,         36,         50,         64}, //knee index[]
  },
  // 24: x1.974
  {
    { 1.9736,   1.9257,     1.5057,     1.3557,     1.1956,     1.0000}, //Knee gain[]
    { 0,        7,          22,         36,         50,         64}, //knee index[]
  },
  // 25: x2.033
  {
    { 2.0328,   1.9621,     1.5387,     1.3617,     1.1970,     1.0000}, //Knee gain[]
    { 0,        7,          21,         36,         50,         64}, //knee index[]
  },
  // 26: x2.094
  {
    { 2.0938,   1.9979,     1.5540,     1.3677,     1.1983,     1.0000}, //Knee gain[]
    { 0,        7,          21,         36,         50,         64}, //knee index[]
  },
  // 27: x2.157
  {
    { 2.1566,   2.0331,     1.5690,     1.3907,     1.1996,     1.0000}, //Knee gain[]
    { 0,        7,          21,         35,         50,         64}, //knee index[]
  },
  // 28: x2.221
  {
    { 2.2213,   2.0676,     1.5837,     1.3967,     1.2009,     1.0000}, //Knee gain[]
    { 0,        7,          21,         35,         50,         64}, //knee index[]
  },
  // 29: x2.288
  {
    { 2.2879,   2.1016,     1.5981,     1.4027,     1.2022,     1.0000}, //Knee gain[]
    { 0,        7,          21,         35,         50,         64}, //knee index[]
  },
  // 30: x2.357
  {
    { 2.3566,   2.2627,     1.6123,     1.4086,     1.2035,     1.0000}, //Knee gain[]
    { 0,        6,          21,         35,         50,         64}, //knee index[]
  },
  // 31: x2.427
  {
    { 2.4273,   2.2997,     1.6261,     1.4144,     1.2047,     1.0000}, //Knee gain[]
    { 0,        6,          21,         35,         50,         64}, //knee index[]
  },
  // 32: x2.500
  {
    { 2.5001,   2.3360,     1.6397,     1.4200,     1.2060,     1.0000}, //Knee gain[]
    { 0,        6 ,         21,         35,         50,         64}, //knee index[]
  },
  // 33: x2.575
  {
    { 2.5751,   2.3716,     1.6808,     1.4256,     1.2243,     1.0000}, //Knee gain[]
    { 0,        6,          20,         35,         49,         64}, //knee index[]
  },
  // 34: x2.652
  {
    { 2.6523,   2.4066,     1.6948,     1.4310,     1.2260,     1.0000}, //Knee gain[]
    { 0,        6 ,         20,         35,         49,         64}, //knee index[]
  },
  // 35: x2.732
  {
    { 2.7319,   2.4410,     1.7084,     1.4364,     1.2276,     1.0000}, //Knee gain[]
    { 0,        6,          20,         35,         49,         64}, //knee index[]
  },
  // 36: x2.814
  {
    { 2.8139,   2.4748,     1.7219,     1.4416,     1.2292,     1.0000}, //Knee gain[]
    { 0,        6,          20,         35,         49,         64}, //knee index[]
  },
  // 37: x2.898
  {
    { 2.8983,   2.7255,     1.7350,     1.4468,     1.2308,     1.0000}, //Knee gain[]
    { 0,        5,          20,         35,         49,         64}, //knee index[]
  },
  // 38: x2.985
  {
    { 2.9852,   2.7631,     1.7479,     1.4518,     1.2323,     1.0000}, //Knee gain[]
    { 0,        5,          20,         35,         49,         64}, //knee index[]
  },
  // 39: x3.075
  {
    { 3.0748,   2.8000,     1.7606,     1.4568,     1.2338,     1.0000}, //Knee gain[]
    { 0,        5,          20,         35,         49,         64}, //knee index[]
  },
  // 40: x3.167
  {
    { 3.1670,   2.8362,     1.7730,     1.4617,     1.2352,     1.0000}, //Knee gain[]
    { 0,        5,          20,         35,         49,        64}, //knee index[]
  },
  // 41: x3.262
  {
    { 3.2620,   2.8717,     1.7852,     1.4901,     1.2364,     1.0000}, //Knee gain[]
    { 0,        5,          20,         34,         49,         64}, //knee index[]
  },
  // 42: x3.360
  {
    { 3.3599,   2.9066,     1.7972,     1.4952,     1.2376,     1.0000}, //Knee gain[]
    { 0,        5,          20,         34,         49,      64}, //knee index[]
  },
  // 43: x3.461
  {
    { 3.4607,   2.9408,     1.8089,     1.5001,     1.2387,     1.0000}, //Knee gain[]
    { 0,         5,         20,         34,         49,         64}, //knee index[]
  },
  // 44: x3.565
  {
    { 3.5645,   2.9744,     1.8604,     1.5050,     1.2398,     1.0000}, //Knee gain[]
    { 0,        5,          19,         34,         49,         64}, //knee index[]
  },
  // 45: x3.671
  {
    { 3.6715,   3.3894,     1.8725,     1.5098,     1.2409,     1.0000}, //Knee gain[]
    { 0,        4,          19,         34,         49,         64}, //knee index[]
  },
  // 46: x3.782
  {
    { 3.7816,   3.4281,     1.8843,     1.5144,     1.2420,     1.0000}, //Knee gain[]
    { 0,        4,          19,         34,         49,         64}, //knee index[]
  },
  // 47: x3.895
  {
    { 3.8950,   3.4659,     1.8958,     1.5190,     1.2431,     1.0000}, //Knee gain[]
    { 0,        4,          19,         34,         49,         64}, //knee index[]
  },
},
