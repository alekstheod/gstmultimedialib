/*
 * IPixel.h
 *
 *  Created on: May 30, 2010
 *      Author: m1cro
 */

#ifndef IPIXEL_H_
#define IPIXEL_H_
#include <vector>

namespace utils {

    class IPixel {
    public:
        virtual unsigned int GetBitsPerPixel(void)const = 0;
        virtual bool GetPixelData(std::vector<unsigned char>& data)const = 0;
        virtual unsigned int GetPixelDataSize(void)const = 0;

        virtual ~IPixel() {
        };
    };

}
#endif /* IPIXEL_H_ */
