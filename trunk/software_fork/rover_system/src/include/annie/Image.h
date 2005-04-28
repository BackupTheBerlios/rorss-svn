#ifndef P_EXAMPLES_H
#define P_EXAMPLES_H

#include <stdint.h>
#include "defines.h" //Vector
#include "Exception.h"
#include <iostream>
#include <string>

struct SDL_Surface;
namespace annie	{
/**
 * represents one image
 * (actually a SDL_Context wrapper ..)
 *
 * Unless you force it by to* functions, you can assume nothing about pixel format of the image!
 * Typical use would therefore be: 
   <pre>
   Image *raw = Image::fromFile(...); if(!raw) ...
   Image *rgb_img = raw->toRGBA();
   delete(raw);
   if(!rgb_img) ...
   rgb_img-toVector(...)
   delete(rgb_img);
   </pre>
 * 
 * NOTE: some const functions may in theory change state of the Image because they lock the surface
 * Image uses window coordinates where 0,0 is top-left
 *
 * @todo use exceptions instead of NULL ?
 */
class Image	{
public:
	/**
	 * the color components should be in [0, 1]
	 * */
	struct Color	{
		real r, g, b;
		real gray() const { return (r + g + b)/3.; }
		Color(real r, real g, real b) : r(r), g(g), b(b) {}
	};


	/// new image of undefined content in default RGBA pixel format
	Image(unsigned xs, unsigned ys);
	void resize(unsigned xs, unsigned ys);
	~Image();

	/**
	 * @return NULL on failure
	 */
	static Image *fromFile(const std::string &fileName);

	/**
	 * Save image to file (BMP)
	 * */
	void toFile(const std::string &fileName);

	/**
	 * Creates an image from a vector of [0,1] reals. The real images are mapped into color component bytes (R,G,B or Y,Y,Y (graY))
	 * 
	 * @param width x-size of the created image
	 * @param gray if true, only one value will be used for the three color components (--> resulting in grayscale)
	 * else each pixel has three components
	 */
	static Image *fromVector(const Vector &v, unsigned width, bool gray);

	/**
	 * Create a sub-image of the original. Resulting image has the same pixel format.
	 * @return NULL on failure
	 */
	Image *subImage(unsigned width, unsigned height, unsigned xOffset=0, unsigned yOffset=0) const;

	/**
	 * Copy contents of image from the src image to given offset.
	 * The source image can be smaller, but not larger
	 */
	void setSubImage(const Image &src, unsigned xo=0, unsigned yo=0);

	/**
	 * @param out	- [3] vector for color components - will be \in [0,1]
	 */
	Color getAverageColor() const throw(Exception);


#ifdef HAVE_OPENGL
	/**
	 * Worx on every type of the surface. The resulting surface will have the same format as the input surface.
	 */
#if 0
	Image *scale(uint width, uint height) const throw(Exception);
#endif
#endif

	/**
	 * Image pixel format will be converted to RGBA (one pixel = one byte)
	 * Unless you know the input image format, you should convert image with this function before making training examples from a loaded image.
	 */
	Image *toRGBA() const;

	/// copy this image (the result is independent)
	Image *clone() const;

	/** flip image
	 * @return the flipped clone
	 */
	Image *upsideDown() const;

	/**
	 * Image will be converted to 32-RGBA (one pixel = four bytes). But all three RGB components are equal,
	 * so the image is grayscale-only.
	 * TODO: could we use one-byte SDL surface? We'd probably need to use palleted surface so the displayed image would be correct.
	 */
	Image *toGray() const;

	unsigned getWidth()	const;
	unsigned getHeight() const;
	unsigned getBPP() const;

	/**
	 * Converts the image to vector. Each choosen byte is mapped into [0,1] real (0=black)
	 * @param bytes_mask. Sets the bytes you want from each pixel (system-dependent-endian) - e.g. 0x2 | 0x8 means you want 0x00FF0000 and 0x000000FF XXX
	 *
	 * Note: you have to make sure the image is in proper pixel format - this function just blindly reads given bytes
	 */
	enum { GRAY_MASK = 1 };
	Vector toVector(uint8_t bytes_mask) const;

	/**
	 * display to the video window (offsets are relative to win coords)
	 * if !gl, the video surface is flipped automatically (so far) - under GL you have to do it yourself
	 * (in GL mode, the offset is passed directly to glRasterPos --> it's up to caller to give it sense
	 */ 
	void display(unsigned xo=0, unsigned yo=0) const;
	//	void saveAs

	void clear();
	void rect(const Color &c, uint x1, uint y1, uint x2, uint y2);

	/**
	 * Use get/put stuff with care - it's amazingly slow :)
	 */
	///draw a pixel
	///TODO: avoid frequent locking???
	void putPixel(const Color &c, uint x, uint y);

	///get a pixel
	Color getPixel(uint x, uint y) const;

	///return the pixel as [0,1] gray
	real getPixelGray(uint x, uint y) const;

protected:
	/**
	 * Create image wrapping the given surface. The created image owns the surface and will free in destructor.
	 */
	Image(SDL_Surface *i)	{ surface = i; }
	int glFormat() const;
	void setGlPixelStore(bool unpack) const;
	
	/// create void surface with the same flags as this
	SDL_Surface *createSameSurface(uint width, uint height) const;
	SDL_Surface *createSameSurface() const;

	/// direct GL draw (assuming rasterPosition is set)
	void glDraw() const;

	/**
	 * Average the color components. The surface must have 4-bytes-per-pixel.
	 * The result is a grayscale-looking surface (but it is still RGBA!)
	 */
	void colorless();
	uint32_t color2SDL(const Color &c) const;
	uint32_t getPixelRaw(uint x, uint y)	const;
	Color sdl2color(uint32_t p) const;
	SDL_Surface *surface;
};

inline std::ostream & operator<<(std::ostream &o, const Image &i)	{ o << "Image: " << i.getWidth() << " x " << i.getHeight() << ", " << i.getBPP() << " bytes per pixel"; return o;}
inline std::ostream & operator<<(std::ostream &o, const Image::Color &c)	{ o << "Color: " << c.r << "," << c.g << "," << c.b; return o;}

}	//annie
#endif //H
