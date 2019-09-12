#include <iostream>

namespace hamilton{
    
template<typename Stat>
std::vector<double>
Gradient<Stat>::operator()(const std::vector<double>& x0_){
    std::vector<double> grad;
    grad.reserve(x0_.size());

    for(size_t i = 0; i < x0_.size(); i++){
        // step forward
        std::vector<double> high = x0_;
        high.at(i) += fEpsilon/10;

        double highVal = fStat(high);

        // step back
        std::vector<double> low = x0_;        
        low.at(i) -= fEpsilon/10;

        // take the difference
        double lowVal = fStat(low);
        grad.push_back((highVal - lowVal)/2/fEpsilon);
    }

    return grad;
}
}
