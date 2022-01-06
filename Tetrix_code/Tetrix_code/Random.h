#include<random>
int random(int nMin, int nMax)
{
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(nMin, nMax);

    auto num = uni(rng);
    return num;
}