namespace hamilton{

template<typename Target_t, typename Grad_t>
void
Sampler<Target_t, Grad_t>::Draw(int nDraws_){

    // starting position, for now its just zeros
    std::vector<double> currentPos(fNparams, 0);
    std::vector<double> currentMomenta(fNparams, 0);
    std::vector<double> newPos(fNparams, 0);
    std::vector<double> newMomenta(fNparams, 0);

    // main loop
    for(int i = 0; i < nDraws_; i++){

        // propose a new step
        fProposer.Next(currentPos,  // input
                       currentMomenta, newPos, newMomenta // outputs
                       );

        // accept or reject
        if(fAcceptor.StepAccepted(currentPos, currentMomenta, newPos, newMomenta))
            currentPos = newPos;

        // no need to update the current momenta, they are randomly assigned by the proposer
        for(size_t j = 0; j < currentPos.size(); j++)
            std::cout << currentPos.at(j) << "\t";
        std::cout << std::endl;
    }
}

template<typename Target_t, typename Grad_t>
void
Sampler<Target_t, Grad_t>::SetRange(const std::vector<double>& minima_, const std::vector<double>& maxima_,
                                    bool reflect){
    fAcceptor.SetRange(minima_, maxima_);
    if(reflect)
        fProposer.SetRange(minima_, maxima_);
}

template<typename Target_t, typename Grad_t>
void
Sampler<Target_t, Grad_t>::GetRange(const std::vector<double>& minima_, const std::vector<double>& maxima_,
                                    bool& reflect_){
    fAcceptor.GetRange(minima_, maxima_);

    std::vector<double> testVec;
    std::vector<double> testVec2;
    fProposer.GetRange(testVec, testVec2);
    reflect_ = testVec.size() || testVec2.size();

}


///////////////////////////////////////////////////////
// Free convienience functions for creating samplers //
///////////////////////////////////////////////////////

// uses numerical gradient
template<typename Target_t>
Sampler<Target_t, Gradient<Target_t> >
MakeSampler(Target_t& t_, double epsilon_, int nSteps_){
    return Sampler<Target_t>(t_, epsilon_, nSteps_);
}

// uses custom gradient
template<typename Target_t, typename Gradient_t>
Sampler<Target_t, Gradient_t>
MakeSampler(Target_t& t_, Gradient_t& g_, double epsilon_, int nSteps_){
    return Sampler<Target_t, Gradient_t>(t_, g_, epsilon_, nSteps_);
}

    
}// namespace hamilton
