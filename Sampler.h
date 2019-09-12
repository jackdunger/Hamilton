#ifndef __HAMILTON_SAMPLER__
#define __HAMILTON_SAMPLER__
#include <Proposer.h>
#include <Acceptor.h>
#include <Gradient.h>
#include <Callback.h>

namespace hamilton{

template<typename Target_t, typename Grad_t = Gradient<Target_t> >
class Sampler{

 public:
 
 Sampler(Target_t& t_, Grad_t g_, double epsilon_, int nSteps_)
  : fProposer(g_, epsilon_, nSteps_), fAcceptor(t_), fNparams(t_.GetNparams()) {}

 Sampler(Target_t& t_, double epsilon_, int nSteps_)
  : fProposer(Grad_t(t_, epsilon_), epsilon_, nSteps_), fAcceptor(t_), fNparams(t_.GetNparams()) {}

 
 void Draw(int nDraws_);
 void SetRange(const std::vector<double>& minima_, const std::vector<double>& maxima_, bool reflect_ = true);
 void GetRange(const std::vector<double>& minima_, const std::vector<double>& maxima_, bool& reflect_);

 
 private:
 
 Proposer<Grad_t>   fProposer;
 Acceptor<Target_t> fAcceptor;
 int fNparams;
 
};

// uses numerical gradient
template<typename Target_t>
Sampler<Target_t, Gradient<Target_t> >
MakeSampler(Target_t& t_, double epsilon_, int nSteps_);

// uses custom gradient
template<typename Target_t, typename Gradient_t>
Sampler<Target_t, Gradient_t>
MakeSampler(Target_t& t_, Gradient_t& g_, double epsilon_, int nSteps_);

}// namespace hamilton

#include <Sampler.hpp>
#endif
