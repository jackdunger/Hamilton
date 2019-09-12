#ifndef __HAMILTON_PROPOSER__
#define __HAMILTON_PROPOSER__
#include <vector>

namespace hamilton{

template<typename Grad_t>
class Proposer{
 public:
 Proposer(Grad_t g_, double epsilon_, int nSteps_)
     : fGradient(g_), fEpsilon(epsilon_), fNsteps(nSteps_) {}
    
 void Next(const std::vector<double>& currentStep_,
           std::vector<double>& currentMomenta_,
           std::vector<double>& newStep_,
           std::vector<double>& newMomenta_);
 
 // boilerplate
 void SetMasses(const std::vector<double>& masses_);
 const std::vector<double>& GetMasses() const;
 
 double GetEpsilon() const;
 void   SetEpsilon(double);
 
 int  GetNsteps() const;
 void SetNsteps(int);
 
 void SetRange(const std::vector<double>& minima_, const std::vector<double> maxima_);
 void GetRange(std::vector<double>& minima_, std::vector<double> maxima_);
 
    
 private:

 Grad_t fGradient;
 
 double fEpsilon;
 int    fNsteps;
 
 std::vector<double> fMasses;
 std::vector<double> fRootMasses;
 
 // if these are set we are modelling reflections. Without reflections it is important to *propose* steps
 // outside the sample range even though they will always be rejected.
 std::vector<double> fMinima;
 std::vector<double> fMaxima;
 bool fDoReflect;
 
};

} //namespace hamilton
#include <Proposer.hpp>
#endif
