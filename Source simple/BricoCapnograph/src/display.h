#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>

// Display config
#define DISPLAY_CS_PIN  5  // define chip select pin
#define DISPLAY_DC_PIN  2  // define data/command pin
#define DISPLAY_RST_PIN 4  // define reset pin
#define DISPLAY_X_SIZE 240
#define DISPLAY_Y_SIZE 240


// Some ready-made 16-bit ('565') color settings
// TODO: Move to a FColor struct
#define COLOR_BLACK   0x0000
#define COLOR_WHITE   0xFFFF
#define COLOR_RED     0xF800
#define COLOR_GREEN   0x07E0
#define COLOR_BLUE    0x001F
#define COLOR_CYAN    0x07FF
#define COLOR_MAGENTA 0xF81F
#define COLOR_YELLOW  0xFFE0
#define COLOR_ORANGE  0xFC00

extern unsigned int samplesPerPixel;
extern Adafruit_ST7789 display;

void setupDisplay(void);
void printGraph(void);
void setupGraph(void);

void printBPM(unsigned int bpm); // belongs to display actually
void printEtCO2(long bpm); // belongs to display actually
void printState(const char *state); // belongs to display actually

#endif