#ifndef __HAMILTON_RANDOM__
#define __HAMILTON_RANDOM__

#include <random>

namespace hamilton{

class Random{
 public:
    // generate random numbers acording to a Gaussian distribution
    static double Gaus(double mean_, double sigma_);

    // uniform on [0, 1]
    static double Uniform(double min_ = 0, double max_ = 1);

    // generate momenta according to the mass distributions
    static std::vector<double> Momenta(const std::vector<double>& masses_);
    
};  

}// namespace hamilton
#endif
