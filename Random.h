#pragma once
#include <random>


class Random{

    static std::mt19937 random;
public:
    static int mineAmount(int min, int max);
    static float floatMineAmt(float min, float max);


};