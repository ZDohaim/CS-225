/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include "cs225/PNG.h"

/**
* A subclass of PNG with more member functions for modifying the image.
*/
class Image : public cs225::PNG {
  public:
    /**
      * Creates an empty Image.
      */
    Image() : PNG(){};

    /**s
      * Creates an Image of the specified dimensions.
      * @param width Width of the new image.
      * @param height Height of the new image.
      */
    Image(unsigned int width, unsigned int height) : PNG(width, height){};

    /**
     * Lighten an Image by increasing the luminance of every pixel by 0.1.
     * This function ensures that the luminance remains in the range [0, 1].
    **/
    void lighten();

    /**
     * Lighten an Image by increasing the luminance of every pixel by `amount`.
     * This function ensures that the luminance remains in the range [0, 1].
     *
     * @param amount The desired increase in luminance.
    **/
    void lighten(double amount);

    /**
     * Darken an Image by decreasing the luminance of every pixel by 0.1.
     * This function ensures that the luminance remains in the range [0, 1].
    **/
    void darken();

    /**
     * Darkens an Image by decreasing the luminance of every pixel by `amount`.
     * This function ensures that the luminance remains in the range [0, 1].
     *
     * @param amount The desired decrease in luminance.
    **/
    void darken(double amount);


    /**
     * Saturates an Image by increasing the saturation of every pixel by 0.1.
     * This function ensures that the saturation remains in the range [0, 1].
    **/
    void saturate();

    /**
     * Saturates an Image by increasing the saturation of every pixel by `amount`.
     * This function ensures that the saturation remains in the range [0, 1].
     *
     * @param amount The desired increase in saturation.
    **/
    void saturate(double amount);

    /**
     * Desaturates an Image by decreasing the saturation of every pixel by 0.1.
     * This function ensures that the saturation remains in the range [0, 1].
    **/
    void desaturate();

    /**
     * Desaturates an Image by decreasing the saturation of every pixel by `amount`.
     * This function ensures that the saturation remains in the range [0, 1].
     *
     * @param amount The desired decrease in saturation.
    **/
    void desaturate(double amount);

    /**
     * Turns the image grayscale.
    **/
    void grayscale();


    /**
     * Rotates the color wheel by `degrees`. Rotating in a positive direction increases the degree of the hue.
     * This function ensures that the hue remains in the range [0, 360].
     *
     * @param degrees The desired amount of rotation.
    **/
    void rotateColor(double degrees);

    /**
     * Illinify the image.
    **/
    void illinify();


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
    void scale(double factor);

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
    void scale(unsigned w, unsigned h);
};