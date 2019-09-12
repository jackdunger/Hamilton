#include <LeapFrog.h>
#include <Random.h>
#include <algorithm>
#include <cmath>

namespace hamilton{
    
template <typename Grad_t>
void
Proposer<Grad_t>::Next(const std::vector<double>& currentStep_,
                       std::vector<double>& currentMomenta_,   // output
                       std::vector<double>& newStep_,          // output
                       std::vector<double>& newMomenta_        // output
                       ){
    if(!fMasses.size())
        SetMasses(std::vector<double>(currentStep_.size(), 1));
    
    // Step 1. make up some momenta
    currentMomenta_ = Random::Momenta(fRootMasses);

    // start the trajectory at the correct point
    newStep_    = currentStep_;
    newMomenta_ = currentMomenta_;

    // Step 2. simulate hamiltonian dynamics with or without reflection monitoring
    if(fDoReflect)
        LeapFrog::Step(newStep_, newMomenta_, fMasses, fEpsilon, fGradient, fNsteps, fMinima, fMaxima);
    else
        LeapFrog::Step(newStep_, newMomenta_, fMasses, fEpsilon, fGradient, fNsteps);

    // currentMomenta_, newMomenta_ and newStep_ have been left in the final point in the trajectory
}

template<typename Grad_t>
void
Proposer<Grad_t>::SetMasses(const std::vector<double>& masses_){
    fMasses = masses_;
    fRootMasses.clear();
    for(size_t i = 0; i < fMasses.size(); i++)
        fRootMasses.push_back(std::sqrt(masses_.at(i)));
}

template<typename Grad_t>
const std::vector<double>&
Proposer<Grad_t>::GetMasses() const{
    return fMasses;
}

template<typename Grad_t>
void
Proposer<Grad_t>::SetRange(const std::vector<double>& minima_, const std::vector<double> maxima_){
    fMaxima = maxima_;
    fMinima = minima_;

    fDoReflect = (fMaxima.size()) && (fMinima.size());
}

template<typename Grad_t>
void
Proposer<Grad_t>::GetRange(std::vector<double>& minima_, std::vector<double> maxima_){
    maxima_ = fMaxima;
    minima_ = fMinima;
}

template<typename Grad_t>
int
Proposer<Grad_t>::GetNsteps() const{
    return fNsteps;
}

template<typename Grad_t>
void
Proposer<Grad_t>::SetNsteps(int nSteps_){
    fNsteps = nSteps_;
}

}
