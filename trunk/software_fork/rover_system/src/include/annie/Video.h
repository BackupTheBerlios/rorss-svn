#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>
#include <string>
#include <list>
#include <SDL/SDL.h>

struct SDL_Surface;
namespace annie	{

/**
 * Video (and input) system maintaince. You must create this class before using <code>Image</image>. There 
 * Problem: if you want to visualise, you can only have one window. So if you need more, the only way is to fork() and have two videos..
 */
class Video	{
public:
	///inits Video on first call
	static Video &getInstance();

	///deinits video. Should be called before exit.
	static void deinit();

	/**
	 * sets the size of video window. On the first call, the window will be created.
	 * @param  redrawThread if video && event thread is running.
	 * @param openGL whether to create an OpenGL context
	 */ 
	void setWindow(unsigned x, unsigned y, bool redrawThread=false, bool openGL=false);
	unsigned getWindowWidth()	const;
	unsigned getWindowHeight() const;

	/// User redraw class. draw() will be called from the video thread
	/*abstract*/ class Redrawer	{
	  public:
		///default ctor - sets viewport to whole actual window
		Redrawer()	{  setFullViewport(); }
		virtual ~Redrawer()	{}
		Redrawer(uint ox, uint oy, uint sx, uint sy) { offsetX = ox; offsetY = oy;  sizeX = sx;  sizeY = sy; }
		void doRedraw();

		/**
		 * @todo we could store the viewport in normalized values so it would be independent of window size ..
		 */
		void setViewport(uint ox, uint oy, uint sx, uint sy)	{ offsetX = ox; offsetY = oy;  sizeX = sx;  sizeY = sy; }

		/// sets viewport to full current window
		void setFullViewport();
	  protected:
		
		/**
		 * actual draw - to be implemented in childs
		 * Shouldn't do clearing or glFinish
		 * the viewport is set to redrawer's range and X-form matrix is set to default 2D ortho (0,0,sizeX,sizeY)
		 */
		virtual void draw()=0;

	  private:
		/// actual drawing viewport
		uint offsetX, offsetY, sizeX, sizeY;
	};



	/** 
	 * Adds the user redraw function called from redraw() - the surface is cleared and and flipped automatically.
	 * warning: Video only stores reference -> you must call removeRedraw() before the object becomes invalid!
	 */
	void addRedraw(Redrawer *r);
	
	/// remove previously added Redrawer
	void removeRedraw(Redrawer *r);
	
	///redraws if possible. Should only be called from the video (GL) thread !
	void redraw();

	void waitForKey();

	bool gl()	{ return usesGL; }

	//flip buffers(if supported)
	void flip();
protected:
	typedef std::list<Redrawer *> Painters;
	Painters painters;
	SDL_Surface *screen;
	
	Video();
	~Video();
private:
	bool redrawThread;
	bool usesGL;
};

/// the only format of surface we create
extern SDL_PixelFormat defaultRGBformat;
}
#endif
