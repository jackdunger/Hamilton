#ifndef __HAMILTON_GRADIENT__
#define __HAMILTON_GRADIENT__

namespace hamilton{
    
template<typename Stat>
class Gradient{
 public:
    Gradient(Stat& st_, double epsilon_) : fStat(st_), fEpsilon(epsilon_){}
    std::vector<double> operator()(const std::vector<double>& x0_);

 private:
    Stat& fStat;
    double fEpsilon;
};

}

#include <Gradient.hpp>
#endif
