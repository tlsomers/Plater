#ifndef _PLATER_PART_H
#define _PLATER_PART_H

#include <iostream>
#include "stl/StlFactory.h"


namespace Plater
{
    class Part
    {
        public:
            Part();
            virtual ~Part();

            int load(std::string filename, float precision, float deltaR, float spacing, string orientation,
                float plateWidth, float plateHeight);
            std::string getFilename();

            Model model;

            Bitmap *getBmp(int index) const;
            float getSurface() const;
            float getDensity(int index) const;

            float precision;
            float deltaR;

            float width;
            float height;
            float surface;

            int bmps;
            Bitmap **bmp;
        
        protected:
            std::string filename;
    };
}

#endif
