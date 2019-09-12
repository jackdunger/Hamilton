#include <Random.h>
#include <LeapFrog.h>
#include <cmath>

namespace hamilton{

template<typename Target_t>
bool
Acceptor<Target_t>::StepAccepted(const std::vector<double>& currentPositions_,
                                 const std::vector<double>& currentMomenta_,
                                 const std::vector<double>& proposedPositions_,
                                 const std::vector<double>& proposedMomenta_){

    // don't accept steps outside the specified range if there is one specified
    // should sort circuit
    if(fMinima.size() && !InRange(proposedPositions_))
        return false;


    // conditionally accept inside range
    double energyChange = std::exp(LeapFrog::KineticEnergy(currentMomenta_, fMasses) + fTarget(currentPositions_) \
                                   - LeapFrog::KineticEnergy(proposedMomenta_, fMasses) - fTarget(proposedPositions_));
    
    double draw = Random::Uniform();
    return (energyChange > 1) || (energyChange > draw); 
}

template<typename Target_t>
void
Acceptor<Target_t>::SetRange(const std::vector<double>& minima_, const std::vector<double>& maxima_){
    fMinima = minima_;
    fMaxima = maxima_;
}


template<typename Target_t>
void
Acceptor<Target_t>::GetRange(std::vector<double>& minima_, std::vector<double>& maxima_){
    minima_ =  fMinima;
    maxima_ =  fMaxima;
}

template<typename Target_t>
bool
Acceptor<Target_t>::InRange(const std::vector<double>& positions_){
    for(size_t i = 0; i < positions_.size(); i++)
        if(positions_.at(i) > fMaxima.at(i) || positions_.at(i) < fMinima.at(i))
            return false;

    return true;
}

}

