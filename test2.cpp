#include <SamplerFactory.h>
#include <cmath>
#include <Gradient.h>

// this should be -logP = -log(exp(-x**2/2)) = +(x**2)/2
class Energy{
public:
    Energy(){
        sigmax = 1;
        sigmay = 1;
        corr   = 0.8;
        norm = -1./2/(1 - corr * corr);
    }
    double operator()(const std::vector<double>& in_) {

        double exponent = in_.at(0) * in_.at(0)/sigmax/sigmax;
        exponent += in_.at(1) * in_.at(1)/sigmay/sigmay;
        exponent -= 2 * corr * in_.at(0) * in_.at(1)/sigmax/sigmay;
        exponent *= norm;

        return -exponent;
    }
    int GetNparams() const {return 2;}

private:
    double sigmax;
    double sigmay;
    double corr;

    double norm;
};

typedef hamilton::Gradient<Energy> NumGrad;

int main(){
    Energy e;
    NumGrad g(e, 0.01);
    
    std::vector<double> masses = {1, 1};
    auto sampler = hamilton::MakeSampler(e, g, 1, 10);
    sampler.SetRange({-10000, 0}, {10000, 10000});
    sampler.Draw(1000000);
    
    return 0;
}
