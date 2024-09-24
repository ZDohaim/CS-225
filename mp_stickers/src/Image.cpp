#include "Image.h"
#include <iostream>
#include <string>
#include <cmath>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace std;
    /**
     * Lighten an Image by increasing the luminance of every pixel by 0.1.
     * This function ensures that the luminance remains in the range [0, 1].
    **/
    
    void Image::lighten() {

        lighten(0.1);//will go to double since it's a double
      }
    /**
     * Lighten an Image by increasing the luminance of every pixel by `amount`.
     * This function ensures that the luminance remains in the range [0, 1].
     *
     * @param amount The desired increase in luminance.
    **/
    void Image::lighten(double amount){
     //change to double to simply call the other function
    
 for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            cs225::HSLAPixel &pixel = getPixel(i,j); 
            
            pixel.l += amount; 

            
                if (pixel.l < 0.0) {
                    pixel.l = 0;
                } else if (pixel.l > 1.0) {
                    pixel.l = 1;
            }
        }
    }
}
    /**
     * Darken an Image by decreasing the luminance of every pixel by 0.1.
     * This function ensures that the luminance remains in the range [0, 1].
    **/
    void Image::darken(){
     darken (0.1);
    }
    /**
     * Darkens an Image by decreasing the luminance of every pixel by `amount`.
     * This function ensures that the luminance remains in the range [0, 1].
     *
     * @param amount The desired decrease in luminance.
    **/
    void Image::darken(double amount){
    lighten(-amount);
    }

    /**
     * Saturates an Image by increasing the saturation of every pixel by 0.1.
     * This function ensures that the saturation remains in the range [0, 1].
    **/
    void Image::saturate(){
        saturate(0.1);
    }

    /**
     * Saturates an Image by increasing the saturation of every pixel by `amount`.
     * This function ensures that the saturation remains in the range [0, 1].
     *
     * @param amount The desired increase in saturation.
    **/
    void Image::saturate(double amount){ 
   
 for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            cs225::HSLAPixel &pixel = getPixel(i, j); 
            pixel.s += amount; 

                if (pixel.s < 0.0) {
                    pixel.s = 0;
                } else if (pixel.s > 1.0) {
                    pixel.s = 1;
            }
        }
    }
    }

    /**
     * Desaturates an Image by decreasing the saturation of every pixel by 0.1.
     * This function ensures that the saturation remains in the range [0, 1].
    **/
    void Image::desaturate(){
        desaturate(0.1);
    }

    /**
     * Desaturates an Image by decreasing the saturation of every pixel by `amount`.
     * This function ensures that the saturation remains in the range [0, 1].
     *
     * @param amount The desired decrease in saturation.
    **/
    void Image::desaturate(double amount){
        saturate(-amount);
    }

    /**
     * Turns the image grayscale.
    **/
    void Image::grayscale(){
    
      
 for (unsigned int i = 0; i <width() ; i++) {
        for (unsigned int j = 0; j < height(); j++) {
            cs225::HSLAPixel &pixel = getPixel(i, j); 
            //takes into account previous luminace
            pixel.s =  0;

        }
     }
}

    /**
     * Rotates the color wheel by `degrees`. Rotating in a positive direction increases the degree of the hue.
     * This function ensures that the hue remains in the range [0, 360].
     *
     * @param degrees The desired amount of rotation.
    **/
void Image::rotateColor(double degrees){

      
 for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            cs225::HSLAPixel &pixel = getPixel(i, j); 
            //takes into account previous luminace
            pixel.h += degrees;
            while(pixel.h < 0){
            pixel.h += 360; 
           }

           while(pixel.h > 360){
            pixel.h -= 360;
            }
        }
    }
}

  /**
     * Illinify the image.
    **/
    void Image::illinify(){
    

    int orange = 11;
    int blue = 216;
      

 for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            cs225::HSLAPixel &pixel = getPixel(i, j);

            int distanceOrange = min(abs(pixel.h - orange), 360 - abs(pixel.h - orange));
            int distanceBlue = min(abs(pixel.h - blue), 360 - abs(pixel.h - blue));

                if (distanceBlue > distanceOrange) {
                    pixel.h = orange;
                } else 
                    pixel.h = blue;
            }
        }
    }
    
    


    /**
     * Scale the Image by a given `factor`.
     *
     * For example:
     * - A `factor` of 1.0 does not change the image.
     * - A `factor` of 0.5 results in an image with half the width and half the height.
     * - A `factor` of 2 results in an image with twice the width and twice the height.
     *
     * This function both resizes the Image and scales the contents.
     *
     * @param factor Scale factor.
    **/
    void Image::scale(double factor){
      if (factor == 1) return;

    
    int scaledWidth = width() * factor; 
    int scaledHeight = height() * factor; 

    Image scaledImage;
    scaledImage.resize(scaledWidth, scaledHeight);

    for (int i = 0; i < scaledHeight; i++) {
        for (int j = 0; j < scaledWidth; j++) {
            scaledImage.getPixel(j, i) = getPixel(j / factor, i / factor);
        }
    }

    *this = scaledImage;
}
  
    

    /**
     * Scales the image to fit within the size (`w` x `h`).  This function preserves
     * the aspect ratio of the image, so the result will always be an image of width
     * `w` or of height `h` (not necessarily both).
     *
     * For example, if the Image is currently (10, 20) and we want to scale to
     * (100, 100), then this should scale the Image to (50, 100). Note that scaling
     * the image to (100, 200) does not fit within the (100,100) dimensions given
     * and is therefore incorrect.
     *
     * This function both resizes the Image and scales the contents.
     *
     * @param w Desired width of the scaled Image
     * @param h Desired height of the scaled Image
    **/
    
    void Image::scale(unsigned w, unsigned h){
    double currentAspectRatio = double(width()) / height();
    double targetAspectRatio = double(w) / h;
    
    double scaleFactor;
        if (currentAspectRatio > targetAspectRatio) {
        scaleFactor = w / double(width());
    } else {
        scaleFactor = h / double(height());
    }
    
    this->scale(scaleFactor);
}
        

