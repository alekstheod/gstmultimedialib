#ifndef IPLAYBIN_H
#define IPLAYBIN_H

namespace multimedia
{

class IPlaybin
{

public:
    IPlaybin(){};
    virtual bool play()=0;
    virtual bool stop()=0;
    virtual bool rewind()=0;
    virtual ~IPlaybin(){};
};

}

#endif // IPLAYBIN_H
