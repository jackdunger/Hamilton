#include <iostream>
#include <LeapFrog.h>

namespace hamilton{
    
template<typename G>
void
LeapFrog::Step(std::vector<double>& qs_,
               std::vector<double>& ps_,
               const std::vector<double>& masses_,
               double epsilon_, G& differ_, int nSteps_){

    // step 1 take a half step in momentum
    std::vector<double> grad = differ_(qs_);    
    for(size_t i = 0; i < ps_.size(); i++)
        ps_[i] -= epsilon_/2 * grad.at(i);

    // step 2 alternate full steps for position and momentum
    for(int i = 0; i < nSteps_; i++){
        // Full step for position
        for(size_t j = 0; j < qs_.size(); j++)
            qs_[j] += epsilon_ * ps_.at(j)/masses_.at(j);
        
        // Full step for momentum, unless this is the last step
        if(i != nSteps_ -1){
            grad = differ_(qs_);
            for(size_t j = 0; j < ps_.size(); j++)
                ps_[j] -= epsilon_ * grad.at(j);
        }   
    }

    // step 3 make a half step for momentum
    grad = differ_(qs_);
    for(int i = 0; i < ps_.size(); i++)
        ps_[i] -= epsilon_/2 * grad.at(i);
}



template<typename G>
void
LeapFrog::Step(std::vector<double>& qs_, std::vector<double>& ps_,
               const std::vector<double>& masses_,
               double epsilon_, G& differ_, int nSteps_,
               const std::vector<double>& minima_,
               const std::vector<double>& maxima_
               ){
    /// https://papers.nips.cc/paper/5801-reflection-refraction-and-hamiltonian-monte-carlo.pdf
    /// pg4 - simplified for only 1d constant boundaries and no refraction (= hard boundaries with delta U = inf)


    for(int i = 0; i < nSteps_; i++){
        // step 1 take a half step in momentum
        std::vector<double> grad = differ_(qs_);
        for(size_t i = 0; i < ps_.size(); i++)
            ps_[i] -= epsilon_/2 * grad.at(i);

        
        // step 2 alternate full steps for position and momentum
        // monitor boundary crosses
        size_t reflectDim;
        double reflectTime;
        double t0 = 0;

        // reflectDim is set to "" if none exists
        FirstIntersectionTime(qs_, ps_, masses_, minima_, maxima_,
                              epsilon_ - t0, reflectDim, reflectTime);
        while(reflectDim != -1){
            // use up the time to get to the boundary
            t0 += reflectTime;
            
            // get to this boundary
            for(size_t j = 0; j < qs_.size(); j++)
                qs_[j] += reflectTime * ps_.at(j)/masses_.at(j);
            
            // flip the offending momentum
            ps_[reflectDim] *= -1;


            // on to the next reflection if there is one
            FirstIntersectionTime(qs_, ps_, masses_, minima_, maxima_,
                                  epsilon_ - t0, reflectDim, reflectTime);
        }
        
        // finally advance the remaining time knowing there are no futher reflections

        double remainingTime = epsilon_ - t0;
        for(size_t j = 0; j < qs_.size(); j++)
            qs_[j] += remainingTime * ps_.at(j)/masses_.at(j);
        
        // step 3 make a half step for momentum
        grad = differ_(qs_);
        for(int i = 0; i < ps_.size(); i++)
            ps_[i] -= epsilon_/2 * grad.at(i);

    }
}

}// namespace hamilton
