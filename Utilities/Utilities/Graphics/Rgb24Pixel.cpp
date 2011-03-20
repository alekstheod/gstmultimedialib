/*
 * Rgb24Pixel.cpp
 *
 *  Created on: May 15, 2010
 *      Author: m1cro
 */

#include "Rgb24Pixel.h"

namespace utils {

    const unsigned int Rgb24Pixel::CONST_BITS_PER_PIXEL = 24;

    Rgb24Pixel::Rgb24Pixel() {
        _red = 0;
        _green = 0;
        _blue = 0;

    }

    Rgb24Pixel::Rgb24Pixel(const Rgb24Pixel& pixel) {
        _red = pixel._red;
        _green = pixel._green;
        _blue = pixel._blue;
    }

    Rgb24Pixel::Rgb24Pixel(unsigned char red, unsigned char green, unsigned char blue) {
        _red = red;
        _green = green;
        _blue = blue;
    }

    const Rgb24Pixel& Rgb24Pixel::operator +=(const Rgb24Pixel& pixel) {
        unsigned char red = 0xff;
        unsigned char green = 0xff;
        unsigned char blue = 0xff;

        int sum = _red + pixel._red;
        if (sum < 255) {
            red = sum;
        }

        sum = _green + pixel._green;
        if (sum < 255) {
            green = sum;
        }

        sum = _blue + pixel._blue;
        if (sum < 255) {
            blue = sum;
        }
        _red = red;
        _green = green;
        _blue = blue;
        return *this;
    }

    const Rgb24Pixel& Rgb24Pixel::operator -=(const Rgb24Pixel& pixel) {
        unsigned char red = 0;
        unsigned char green = 0;
        unsigned char blue = 0;

        if (pixel._red < _red) {
            red = _red - pixel._red;
        }

        if (pixel._green < _green) {
            green = _green - pixel._green;
        }

        if (pixel._blue < _blue) {
            blue = _blue - pixel._blue;
        }
        _red = red;
        _green = green;
        _blue = blue;
        return *this;
    }

    const Rgb24Pixel Rgb24Pixel::operator -(const Rgb24Pixel& pixel)const {
        unsigned char red = 0;
        unsigned char green = 0;
        unsigned char blue = 0;

        if (pixel._red < _red) {
            red = _red - pixel._red;
        }

        if (pixel._green < _green) {
            green = _green - pixel._green;
        }

        if (pixel._blue < _blue) {
            blue = _blue - pixel._blue;
        }
        Rgb24Pixel newPixel(red, green, blue);
        return newPixel;
    }

    const Rgb24Pixel Rgb24Pixel::operator +(const Rgb24Pixel& pixel)const {
        unsigned char red = 0xff;
        unsigned char green = 0xff;
        unsigned char blue = 0xff;

        int sum = _red + pixel._red;
        if (sum < 0xff) {
            red = sum;
        }

        sum = _green + pixel._green;
        if (sum < 0xff) {
            green = sum;
        }

        sum = _blue + pixel._blue;
        if (sum < 0xff) {
            blue = sum;
        }
        Rgb24Pixel newPixel(red, green, blue);
        return newPixel;
    }

    const Rgb24Pixel& Rgb24Pixel::operator =(const Rgb24Pixel& pixel) {
        _red = pixel._red;
        _green = pixel._green;
        _blue = pixel._blue;
        return *this;
    }

    bool Rgb24Pixel::operator ==(const Rgb24Pixel& pixel)const {
        return (pixel._red == _red && pixel._green == _green && pixel._blue == _blue);
    }

    unsigned int Rgb24Pixel::getBitsPerPixel(void)const {
        return CONST_BITS_PER_PIXEL;
    }

    bool Rgb24Pixel::getPixelData(std::vector<unsigned char>& data)const {
        if (data.size() != CONST_BITS_PER_PIXEL) {
            return false;
        }

        data[0] = _red;
        data[1] = _green;
        data[2] = _blue;
        return true;
    }

    unsigned int Rgb24Pixel::getPixelDataSize(void)const {
        return CONST_BITS_PER_PIXEL;
    }

    Rgb24Pixel::~Rgb24Pixel() {
    }

}
