#ifndef __HAMILTON__LEAP_FROG__
#define __HAMILTON__LEAP_FROG__
#include <vector>

namespace hamilton{
    
class LeapFrog{
public:

    // no reflections
    template<typename G>
    static void Step(std::vector<double>& qs_,
                     std::vector<double>& ps_,
                     const std::vector<double>& masses_,
                     double epsilon_, G&, int nSteps_);
        
    //  with reflections
    template<typename G>
    static void Step(std::vector<double>& qs_,
                     std::vector<double>& ps_,
                     const std::vector<double>& masses_,
                     double epsilon_, G&, int nSteps_,
                     const std::vector<double>& minima_,
                     const std::vector<double>& maxima_);

    // calculate the kinetic energy
    static double KineticEnergy(const std::vector<double>& momenta_,
                                const std::vector<double>& masses_
                                );
    
 private:
    // look for reflections
    static double IntersectionTime(double wall_, double intPos_, double vel_);

    static void FirstIntersectionTime(const std::vector<double>& initPos_,
                                      const std::vector<double>& momenta_,
                                      const std::vector<double>& masses_,
                                      const std::vector<double>& minima_,
                                      const std::vector<double>& maxima_,
                                      double epsilon_,
                                      size_t& dim_, double& time_
                                      );
};

}// namespace hamilton

#include <LeapFrog.hpp> // implementation
#endif
