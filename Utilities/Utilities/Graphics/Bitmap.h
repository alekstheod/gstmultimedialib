/*
 * Bitmap.h
 *
 *  Created on: May 15, 2010
 *      Author: m1cro
 */

#ifndef BITMAP_H_
#define BITMAP_H_

#include <vector>
#include <map>
#include <Utilities/Graphics/IPixel.h>
#include <string.h>


namespace utils {

#ifndef tagBITMAPINFOHEADER
#define tagBITMAPINFOHEADER

    typedef struct tagBITMAPINFOHEADER {
        unsigned int biSize;
        unsigned int biWidth;
        unsigned int biHeight;
        unsigned short biPlanes;
        unsigned short biBitCount;
        unsigned int biCompression;
        unsigned int biSizeImage;
        unsigned int biXPelsPerMeter;
        unsigned int biYPelsPerMeter;
        unsigned int biClrUsed;
        unsigned int biClrImportant;
    } BITMAPINFOHEADER;

#endif

    template<class T>
    class Bitmap {
    private:
        typename std::map<unsigned int, typename std::vector<T> > _bmp;
        BITMAPINFOHEADER _bmpInfo;

    public:
        Bitmap(unsigned int width, unsigned int height);
        unsigned int GetWidth(void)const;
        unsigned int GetHeight(void)const;
        bool SetWidth(unsigned int width);
        bool SetHeight(unsigned int height);
        std::vector<unsigned char> GetBitmapAsRawData(void)const;
        std::vector<unsigned char> GetBitmapAsFileRawData(void)const;
        T * operator[] (unsigned int row);
        ~Bitmap()throw ();
    };

    template<class T>
    Bitmap<T>::Bitmap(unsigned int width, unsigned int height) {
        T newPixel;
        IPixel* pixel = static_cast<IPixel*> (&newPixel);
        if (width == 0) {
            width = 1;
        }

        if (height == 0) {
            height = 1;
        }

        for (unsigned int i = 0; i < height; i++) {
            std::vector<T> row;
            row.resize(width, T());
            std::pair<unsigned int, std::vector<T> > newEntry(i, row);
            if (_bmp.insert(newEntry).second == false) {
                _bmp.clear();
                return;
            }
        }

        memset((void*) &_bmpInfo, sizeof (_bmpInfo), 0);
        _bmpInfo.biPlanes = 1;
        _bmpInfo.biCompression = 0;
        _bmpInfo.biBitCount = pixel->GetBitsPerPixel();
        _bmpInfo.biWidth = width;
        _bmpInfo.biHeight = height;
    }

    template<class T>
    unsigned int Bitmap<T>::GetWidth(void)const {
        return _bmpInfo.biWidth;
    }

    template<class T>
    unsigned int Bitmap<T>::GetHeight(void)const {
        return _bmpInfo.biHeight;
    }

    template<class T>
    T* Bitmap<T>::operator[] (unsigned int row) {
        if (_bmp.find(row) == _bmp.end()) {
            return &(_bmp[0].at(0));
        }
        return &(_bmp[row].at(0));
    }

    template<class T>
    bool Bitmap<T>::SetWidth(unsigned int width) {
        if (width == 0) {
            width = 1;
        }
        for (unsigned int i = 0; i <= _bmpInfo.biHeight; i++) {
            _bmp[i].resize(width, T());
            if (_bmp[i].size() != width) {
                _bmp.clear();
                return false;
            }
        }
        _bmpInfo.biWidth = width;
        return true;
    }

    template<class T>
    bool Bitmap<T>::SetHeight(unsigned int height) {
        if (height == 0) {
            height = 1;
        }
        if (_bmpInfo.biHeight <= height) {
            std::vector<T> newRow = _bmp[_bmpInfo.biHeight - 1];
            for (unsigned int i = height - _bmpInfo.biHeight; i < _bmpInfo.biHeight; i++) {
                if (_bmp.insert(newRow).second == false) {
                    _bmp.clear();
                    return false;
                }
            }
        } else {
            for (unsigned int i = _bmpInfo.biHeight; i > _bmpInfo.biHeight; i--) {
                _bmp.erase(i);
            }
        }
        _bmpInfo.biHeight = height;
        return true;
    }

    template<class T>
    std::vector<unsigned char> Bitmap<T>::GetBitmapAsRawData(void)const {
        std::vector<unsigned char> result;
        T p;
        IPixel* tmpPixel = static_cast<IPixel*> (&p);
        unsigned int pad = (4 - _bmpInfo.biWidth * (tmpPixel->GetPixelDataSize()) % 4);

        std::vector<unsigned char> padData;
        padData.resize(pad, 0);
        for (unsigned int i = 0; i < _bmpInfo.biHeight; i++) {
            typename std::map<unsigned int, typename std::vector<T> >::const_iterator currentRow;
            currentRow = _bmp.find(i);
            if (currentRow != _bmp.end()) {
                for (unsigned int j = 0; j < _bmpInfo.biWidth; j++) {
                    T pxl = currentRow->second.at(j);
                    IPixel* pixel = static_cast<IPixel*> (&pxl);
                    std::vector<unsigned char> pixelData;
                    pixelData.resize(pixel->GetPixelDataSize(), 0);
                    pixel->GetPixelData(pixelData);
                    result.insert(result.end(), pixelData.begin(), pixelData.end());
                }
                result.insert(result.end(), padData.begin(), padData.end());
            }
        }
        return result;
    }

    template<class T>
    std::vector<unsigned char> Bitmap<T>::GetBitmapAsFileRawData(void)const {
        std::vector<unsigned char> result;
        result.resize(sizeof (_bmpInfo), 0);
        memcpy(&result.at(0), &_bmpInfo, sizeof (_bmpInfo));
        T p;
        IPixel* tmpPixel = static_cast<IPixel*> (&p);
        unsigned int pad = (4 - _bmpInfo.biWidth * (tmpPixel->GetPixelDataSize()) % 4);

        std::vector<unsigned char> padData;
        padData.resize(pad, 0);
        for (unsigned int i = 0; i < _bmpInfo.biHeight; i++) {
            typename std::map<unsigned int, typename std::vector<T> >::const_iterator currentRow;
            currentRow = _bmp.find(i);
            if (currentRow != _bmp.end()) {
                for (unsigned int j = 0; j < _bmpInfo.biWidth; j++) {
                    T pxl = currentRow->second.at(j);
                    IPixel* pixel = static_cast<IPixel*> (&pxl);
                    std::vector<unsigned char> pixelData;
                    pixelData.resize(pixel->GetPixelDataSize(), 0);
                    pixel->GetPixelData(pixelData);
                    result.insert(result.end(), pixelData.begin(), pixelData.end());
                }
                result.insert(result.end(), padData.begin(), padData.end());
            }
        }
        return result;
    }

    template<class T>
    Bitmap<T>::~Bitmap()throw () {
    }

}

#endif /* BITMAP_H_ */
