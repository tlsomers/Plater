#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "Part.h"

using namespace std;

namespace Plater
{
    Part::Part()
        : bmp(NULL)
    {
    }

    Part::~Part()
    {
        if (bmp != NULL) {
            for (int i=0; i<bmps; i++) {
                delete bmp[i];
            }
            delete[] bmp;
        }
    }

    int Part::load(std::string filename_, float precision_, float deltaR_, float spacing,
            string orientation, float plateWidth, float plateHeight)
    {
        precision = precision_;
        deltaR = deltaR_;
        bmps = ceil((M_PI*2)/deltaR);
        filename = filename_;

        model = loadModelFromFile(filename.c_str());
        model = model.putFaceOnPlate(orientation);
        bmp = new Bitmap*[bmps];
        bmp[0] = model.pixelize(precision, spacing);
        surface = bmp[0]->width * bmp[0]->height;

        Point3 minP = model.min();
        Point3 maxP = model.max();
        width = maxP.x-minP.x + 2*spacing;
        height = maxP.y-minP.y + 2*spacing;
        int correct = 0;

        for (int k=0; k<bmps; k++) {
            if (k > 0) {
                Bitmap *rotated = Bitmap::rotate(bmp[0], k*deltaR);
                bmp[k] = Bitmap::trim(rotated);
                delete rotated;
            }
        }

        for (int k=0; k<bmps; k++) {
            // Will this fit on the plate ?
            if (bmp[k]->width*precision < plateWidth && bmp[k]->height*precision < plateHeight) {
                correct++;
            } else {
                delete bmp[k];
                bmp[k] = NULL;
            }
        }

        return correct;
    }
            
    float Part::getSurface() const
    {
        return surface;
    }

    std::string Part::getFilename()
    {
        return filename;
    }
            
    Bitmap *Part::getBmp(int index) const
    {
        return bmp[index];
    }
            
    float Part::getDensity(int index) const
    {
        Bitmap *bmp = getBmp(index);
        return bmp->pixels/(bmp->width*bmp->height);
    }
}
