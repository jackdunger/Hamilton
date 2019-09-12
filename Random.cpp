#include "Random.h"
#include <iostream>

namespace hamilton{

double
Random::Gaus(double mean_, double sigma_){
    std::random_device rd{};
    std::mt19937 gen{rd()};

    std::normal_distribution<> dist{mean_, sigma_};
    return dist(gen);
}

double
Random::Uniform(double min_, double max_){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(min_, max_);
    return dist(gen);
}

std::vector<double>
Random::Momenta(const std::vector<double>& rootMasses_){
    std::vector<double> momenta;
    momenta.reserve(rootMasses_.size());

    for(size_t i = 0; i < rootMasses_.size(); i++){
        momenta.push_back(Gaus(0, rootMasses_.at(i)));
    }

    return momenta;
}


}

