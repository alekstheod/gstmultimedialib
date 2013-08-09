#ifndef IPLAYBIN_H
#define IPLAYBIN_H
#include <Multimedia/FilterGraph/Signal.h>

namespace multimedia
{

class IPlaybin
{

public:
    IPlaybin(){};
    virtual bool sendSignal( const Signal& signal )=0;
    virtual ~IPlaybin(){};
};

}

#endif // IPLAYBIN_H
