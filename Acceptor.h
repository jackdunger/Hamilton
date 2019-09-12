#ifndef __HAMILTON_ACCEPTOR__
#define __HAMILTON_ACCEPTOR__

namespace hamilton{

template<typename Target_t>
class Acceptor{
 public:

 Acceptor(Target_t& t_)
  : fTarget(t_), fMasses(std::vector<double>(t_.GetNparams(), 1)) {}

 Acceptor(Target_t& t_, const std::vector<double>& masses_)
  : fTarget(t_), fMasses(masses_) {}

 bool StepAccepted(const std::vector<double>& currentPositions_,
                   const std::vector<double>& currentMomenta_,
                   const std::vector<double>& proposedPositions_,
                   const std::vector<double>& proposedMomenta_);

 void SetRange(const std::vector<double>& minima_, const std::vector<double>& maxima_);
 void GetRange(std::vector<double>& minima_, std::vector<double>& maxima_);
 
 private:

 bool InRange(const std::vector<double>& positions_);
 
 Target_t& fTarget;
 std::vector<double> fMasses;
 std::vector<double> fMinima;
 std::vector<double> fMaxima;
};

}

#include <Acceptor.hpp>
#endif
