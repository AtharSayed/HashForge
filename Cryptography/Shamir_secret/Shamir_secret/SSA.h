#pragma once
#ifndef SSA_H
#define SSA_H

#include <iostream>
#include <vector>
#include <cmath>
#include "InfInt.h"

class SSA {
private:
    InfInt S;
    int N, K;
    std::vector<std::pair<int, InfInt>> points;

    InfInt calculate_Y(int x, std::vector<InfInt>& poly);

    void secret_sharing();

public:
    InfInt Generate_Secret(InfInt x[], InfInt y[], int M);

    SSA(std::string s, int n, int k);

    void operation();
};

#endif
