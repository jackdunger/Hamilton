#include <SamplerFactory.h>
#include <cmath>
#include <Gradient.h>

// this should be -logP = -log(exp(-x**2/2)) = +(x**2)/2
class Energy{
public:
    double operator()(const std::vector<double>& in_) {return 0.5 * in_.at(0) * in_.at(0);}
    int GetNparams() const {return 1;}
};

class AnalyGradient{
public:
    std::vector<double> operator()(const std::vector<double> in_){return  {in_.at(0)};}
    int GetNparams() const {return 1;}
};

typedef hamilton::Gradient<Energy> NumGrad;

int main(){
    Energy e;
    AnalyGradient g;
    NumGrad g2(e, 0.1);
    
    std::vector<double> masses = {1};
    auto sampler = hamilton::MakeSampler(e, g, 1, 10);
    sampler.SetRange({0}, {20}, true);

    sampler.Draw(1000000);
    
    return 0;
}
