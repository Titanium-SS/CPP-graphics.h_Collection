#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#define DETECT 0

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

enum {
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	LIGHTGRAY = 6,
	DARKGRAY = 7,
	YELLOW = 8,
	WHITE = 9,
	CRIMSON = 10,
	ORANGE = 11,
	TEAL = 12,
	PURPLE = 13,
	VIOLET = 14,
	PINK = 15,
	MAXCOLORS = 15
};

uint32_t bgi_palette[1 + MAXCOLORS] = {
	// Includes extra custom colors and removed some colors 
	// RGBA
	0x000000ff,	 // BLACK
	0x0000ffff,	 // BLUE
	0x00ff00ff,	 // GREEN
	0x00ffffff,	 // CYAN
	0xff0000ff,	 // RED
	0xff00ffff,	 // MAGENTA
	0xd3d3d3ff,	 // LIGHTGRAY
	0xa9a9a9ff,	 // DARKGRAY
	0xffff00ff,	 // YELLOW
	0xffffffff,	 // WHITE
    0xdc143cff,    // CRIMSON
    0xffa500ff,    // ORANGE
    0x008080ff,    // TEAL
    0x800080ff,    // PURPLE
    0xee82eeff,    // VIOLET
    0xffc0cbff     // PINK
};

// representation of required bitmap font
int font8x8[10][8] = {
	{0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00},  // U+0030 (0)
	{0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00},  // U+0031 (1)
	{0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00},  // U+0032 (2)
	{0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00},  // U+0033 (3)
	{0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00},  // U+0034 (4)
	{0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00},  // U+0035 (5)
	{0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00},  // U+0036 (6)
	{0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00},  // U+0037 (7)
	{0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00},  // U+0038 (8)
	{0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00},  // U+0039 (9)
};

int currentColor = WHITE;

Uint32** pixels;

int maxX = 0;
int maxY = 0;

int offset = 35;

int side = 640;   // Width and height of screen. Change as per need
int innerSide = 21;  // No of pixel boxes to be displayed. Change as per need

int windowWidth = side + offset + 4;
int windowHeight = side + offset + 8;
int pixelgrid = side;

void graphs(void);

/// @brief Returns the maximum value of x-coordinate.
/// @return Maximum value of x-coordinate.
int getmaxx() {
	return maxX;
}

/// @brief Returns the maximum value of y-coordinate.
/// @return Maximum value of y-coordinate.
int getmaxy() {
	return maxY;
}

/// @brief Creates a delay, thereby halting the program for the given duration.
/// @param ms The duration(in ms).
void delay(uint32_t ms) {
	SDL_Delay(ms);
}

/// @brief Sets the default color.
/// @param color One of the valid colors.
void setColor(int color) {
	SDL_SetRenderDrawColor(renderer, ((bgi_palette[color] >> 24) & 0xFF),
						   ((bgi_palette[color] >> 16) & 0xFF),
						   ((bgi_palette[color] >> 8) & 0xFF),
						   ((bgi_palette[color] >> 0) & 0xFF));
}

/// @brief Initializes the window.
/// @param width Width of the graph to plot.
/// @param height Height of the graph to plot.
void initwindow(int width, int height) {
	// variables

	bool quit = false;
	SDL_Event event;

	// init SDL

	SDL_VideoInit(NULL);
	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, 0);
	maxX = width;
	maxY = height;

	pixels = new Uint32*[maxX];
	for (int i = 0; i < width; i++) {
		pixels[i] = new Uint32[maxY];
		for (int j = 0; j < height; j++)
			pixels[i][j] = 0;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 
							((bgi_palette[WHITE] >> 24) & 0xFF),
						   	((bgi_palette[WHITE] >> 16) & 0xFF),
						   	((bgi_palette[WHITE] >> 8) & 0xFF),
						   	((bgi_palette[WHITE] >> 0) & 0xFF));
	SDL_RenderPresent(renderer);
}

/// @brief Updates the graph.
void update() {
    int px = (pixelgrid / maxX);
    for (int x = 0; x < maxX; x++)
        for (int y = 0; y < maxY; y++) {
            auto color = pixels[x][y];
            auto xc = x * px + offset;
            auto yc = (maxY - y - 1) * px + offset;  // Change this line
            auto rect = new SDL_Rect{xc + 1, yc + 1, px - 1, px - 1};
            SDL_SetRenderDrawColor(renderer,
                                   ((bgi_palette[color] >> 24) & 0xFF),
                                   ((bgi_palette[color] >> 16) & 0xFF),
                                   ((bgi_palette[color] >> 8) & 0xFF),
                                   ((bgi_palette[color] >> 0) & 0xFF));
            SDL_RenderFillRect(renderer, rect);
            delete rect;
        }

    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 
							((bgi_palette[currentColor] >> 24) & 0xFF),
                           	((bgi_palette[currentColor] >> 16) & 0xFF),
                           	((bgi_palette[currentColor] >> 8) & 0xFF),
                           	((bgi_palette[currentColor] >> 0) & 0xFF));
}

/// @brief Sets the background color. Also clears the graph.
/// @param color The new background color.
void setbkcolor(int color) {
    if (color == BLACK) {
        SDL_SetRenderDrawColor(renderer, 
                                ((bgi_palette[WHITE] >> 24) & 0xFF),
                                ((bgi_palette[WHITE] >> 16) & 0xFF),
                                ((bgi_palette[WHITE] >> 8) & 0xFF),
                                ((bgi_palette[WHITE] >> 0) & 0xFF));
        currentColor = WHITE;
    }
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,
                            ((bgi_palette[color] >> 24) & 0xFF),
                            ((bgi_palette[color] >> 16) & 0xFF),
                            ((bgi_palette[color] >> 8) & 0xFF),
                            ((bgi_palette[color] >> 0) & 0xFF));
    for (int x = maxX-1; x >= 0; x--)
        for (int y = maxY-1; y >= 0; y--)
            pixels[x][y] = color;
}

/// @brief Fills the pixel at (x, y) with the given color.
/// @param x x-coordinate of the pixel.
/// @param y y-coordinate of the pixel.
/// @param color Color to fill the pixel.
void putpixel(int x, int y, int color = WHITE) {
	// std::cout << x << ", " << y << std::endl;
	if (x >= maxX || y >= maxY || x < 0 || y < 0)
		return;
	pixels[x][y] = color;
	update();
}


/// @brief Gets the color of the given pixel.
/// @param x x-coordinate of the pixel.
/// @param y y-coordinate of the pixel.
/// @return The color of the given pixel.
int getpixel(int x, int y) {
    // Check if the coordinates are within the valid range.
    if (x >= maxX || y >= maxY || x < 0 || y < 0)
        return -1; // Return an error code or throw an exception.

    // Return the color of the pixel at (x, y).
    return pixels[x][y];
}


void initgraph(int* graphdriver, int* graphmode, char* pathtodriver) {
	initwindow(innerSide, innerSide);
}


/// @brief Renders the given number as text.
/// @param x x-coordinate of the top-left corner of the text.
/// @param y y-coordinate of the top-left corner of the text.
/// @param num The number to draw.
void renderText(int x, int y, int num) {
	auto bitmap = font8x8[num];
	int set;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			set = bitmap[i] & 1 << j;
			if (set) {
				SDL_RenderDrawPoint(renderer, x + j, y + i);
			}
		}
	}
}

/// @brief Draws the graph grid and axes lines.
void graphs() {
    int px = (pixelgrid / maxX);
    for (int i = 0; i < maxX; i++) {
        if (i <= 9) {
            renderText(offset + i * px + px / 2, windowHeight - offset + 25, i); 
        } else {
            renderText(offset + (i * px + px / 2) - 7, windowHeight - offset + 25, (i) / 10); 
            renderText(offset + i * px + px / 2 - 1, windowHeight - offset + 25, (i) % 10); 
        }
        int y = maxY - i - 1;
        if (y <= 9) {
            renderText(16, offset + (maxY - y - 1) * px + px / 2, y);
        } else {
            renderText(9, offset + (maxY - y - 1) * px + px / 2, (y) / 10);
            renderText(15, offset + (maxY - y - 1) * px + px / 2, (y) % 10);
        }
    }

    for (int x = 0; x < maxX; x++)
        for (int y = 0; y < maxY; y++) {
            auto xc = x * px + offset;
            auto yc = (maxY - y - 1) * px + offset;
            auto rect = new SDL_Rect{xc + 1, yc + 1, px - 1, px - 1};
            SDL_RenderDrawRect(renderer, rect);
            delete rect;
        }
    SDL_RenderPresent(renderer);
}

/// @brief Closes the graphics system.
void closegraph() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_VideoQuit();
	SDL_Quit();
}

/// @brief keeps the graphics window running until close button is pressed.
int getch(void) {
	graphs();
	SDL_Event event;

	while (1) {
		while (SDL_WaitEvent(&event))
			if (event.type == SDL_QUIT)
				return event.type;
	}
}


/// @brief makes a custom polygon. Similar approach as Midpoint Circle Algorithm. 
/// @param xc x-coordinate of the center of the polygon.
/// @param yc y-coordinate of the center of the polygon.
/// @param x x-coordinate to put the pixel.
/// @param y y-coordinate to put the pixel.
/// @param color color of the plotted pixel.
void draw_polygon(int xc, int yc, int x, int y, int color) {
    putpixel(xc+x, yc+y, color);
    putpixel(xc+x, yc-y, color);
    putpixel(xc-x, yc+y, color);
    putpixel(xc-x, yc-y, color);
    putpixel(xc+y, yc+x, color);
    putpixel(xc+y, yc-x, color);
    putpixel(xc-y, yc+x, color);
    putpixel(xc-y, yc-x, color);
}

/// @brief makes a custom polygon
/// @param xc x-coordinate of the center of the polygon.
/// @param yc y-coordinate of the center of the polygon.
/// @param n distance from the center.
/// @param color color of the plotted pixel.
void POLYGON(int xc, int yc, int n, int color) {
    int x = 0;
    int y = n;

    draw_polygon(xc, yc, x, y, color);

    while(x<y) {
        x++;
        if (x%2 == 0){
            y++;
        }
        draw_polygon(xc, yc, x, y, color);
    }
}

/// @brief makes a boundary in the grid. 
/// @param xc x-coordinate of the center of the polygon.
/// @param yc y-coordinate of the center of the polygon.
/// @param m distance from the center.
/// @param color color of the plotted pixel.
void BOUNDARY(int xc, int yc, int m, char color) {
    int x = 0;
    int y = m;

    draw_polygon(xc, yc, x, y, color);

    while(x<y) {
        x++;
        draw_polygon(xc, yc, x, y, color);
    }
}

// Made by Madhur Saini and Shailendra Singh
// Uses the SDL2 library (zlib license)
// Uses some code from the SDL_bgi Library (zlib license) 
