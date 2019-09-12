#include <LeapFrog.h>

namespace hamilton{
    
double
LeapFrog::IntersectionTime(double wall_, double initPos_, double vel_){
    return (wall_ - initPos_)/vel_;
}


void
LeapFrog::FirstIntersectionTime(const std::vector<double>& initPos_,
                                const std::vector<double>& momenta_,
                                const std::vector<double>& masses_,
                                const std::vector<double>& minima_,
                                const std::vector<double>& maxima_,
                                double epsilon_,
                                size_t& dim_, double& crossTime_
                                ){
    crossTime_ = -1;
    dim_ = -1;
    for(size_t i = 0; i < initPos_.size(); i++){
        double vel = momenta_.at(i)/masses_.at(i);
        double mintime = IntersectionTime(minima_.at(i), initPos_.at(i), vel);
        double maxtime = IntersectionTime(maxima_.at(i), initPos_.at(i), vel);

        // only pick up crosses in the right direction
        // the other way shouldn't happen, but round off error can make it so
        bool mincrossed  = (mintime > 0 && mintime < epsilon_ && (initPos_.at(i) > minima_.at(i)));
        bool maxcrossed  = (maxtime > 0 && maxtime < epsilon_ && (initPos_.at(i) < maxima_.at(i)));
        
        if(!mincrossed && !maxcrossed)
            continue;
        
        double time;
        if(mincrossed)
            time = mintime;
        else if(maxcrossed)
            time = maxtime;


        if(crossTime_ == -1 || time < crossTime_){
            crossTime_ = time;
            dim_ = i;
        }
        
    }
}

double
LeapFrog::KineticEnergy(const std::vector<double>& momenta_,
                        const std::vector<double>& masses_
                        ){
    double kinEnergy = 0;
    for(size_t i = 0; i < momenta_.size(); i++){
        kinEnergy += momenta_.at(i) * momenta_.at(i)/2/masses_.at(i);
    }
    return kinEnergy;
}
    
}// namespace hamilton
