#ifndef __HAMILTON_CALLBACK__
#define __HAMILTON_CALLBACK__

namespace hamilton{

class Callback{
 public:
    virtual void OnSample(int nSample_, bool accepted_,
                          const std::vector<double>& sample_) {}
};

}
#endif
