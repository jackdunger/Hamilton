#include <LeapFrog.h>
#include <fstream>

using namespace hamilton;

class Gradient1D{
public:
    std::vector<double>
    operator()(const std::vector<double>& qs_){
        return {qs_.at(0)};
    }
};

class Gradient2D{
public:
    std::vector<double>
    operator()(const std::vector<double>& qs_){
        return {0, 0};
    }
};

int main(){

    // config
    double epsilon = 0.0001;
    int    steps   = 100;
    
    // simple harmonic motion start at extremum
    std::vector<double> qs = {10};
    std::vector<double> ps = {0};
    std::vector<double> masses = {1};
    std::vector<double> minima = {0};
    std::vector<double> maxima = {20};
    
    // energy gradient
    Gradient1D g;

    // no reflection
    std::ofstream out("unreflected.dat");
    for(int i = 0; i < 1000; i++){
        LeapFrog::Step(qs, ps, masses, epsilon, g, steps);
        out << qs.at(0) << "\t" << ps.at(0) << "\n";
    }
    out.close();

    // with reflection
    qs = {10};
    ps = {0};
    
    std::ofstream out2("reflected.dat");
    for(int i = 0; i < 1000; i++){
        LeapFrog::Step(qs, ps, masses, epsilon, g, steps, minima, maxima);
        out2 << qs.at(0) << "\t" << ps.at(0) << "\n";
    }
    out2.close();


    // one bounce
    Gradient2D g2;
    qs = {-10, -10};
    ps = {1, 1};
    masses = {1, 1};
    minima = {-20, -20};
    maxima = {0, 1000};
    
    std::ofstream out3("onebounce.dat");
    for(int i = 0; i < 10000; i++){
        LeapFrog::Step(qs, ps, masses, epsilon, g2, steps, minima, maxima);
        out3 << qs.at(0) << "\t" << qs.at(1) << "\n";
    }
    out3.close();
    
    
    return 0;
}
