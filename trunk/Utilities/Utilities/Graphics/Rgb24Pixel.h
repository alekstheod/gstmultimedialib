/*
 * Rgb24Pixel.h
 *
 *  Created on: May 15, 2010
 *      Author: m1cro
 */

#ifndef RGB24PIXEL_H_
#define RGB24PIXEL_H_
#include <Utilities/Graphics/IPixel.h>

namespace utils {

class Rgb24Pixel: public IPixel {
private:
	unsigned char _red;
	unsigned char _green;
	unsigned char _blue;

public:
	static const unsigned int CONST_BITS_PER_PIXEL;

public:
	Rgb24Pixel();
	Rgb24Pixel(unsigned char red, unsigned char green, unsigned char blue);
	Rgb24Pixel(const Rgb24Pixel& pixel);
	const Rgb24Pixel & operator +=(const Rgb24Pixel& pixel);
	const Rgb24Pixel & operator -=(const Rgb24Pixel& pixel);
	const Rgb24Pixel operator -(const Rgb24Pixel& pixel) const;
	const Rgb24Pixel operator +(const Rgb24Pixel& pixel) const;
	const Rgb24Pixel & operator =(const Rgb24Pixel& pixel);
	bool operator ==(const Rgb24Pixel& pixel) const;
	unsigned int getBitsPerPixel(void) const;
	bool getPixelData(std::vector<unsigned char>& data) const;
	unsigned int getPixelDataSize(void) const;
	virtual ~Rgb24Pixel();
};

}

#endif /* RGB24PIXEL_H_ */
