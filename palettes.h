CRGB black = CRGB::Black;
CRGB white = CRGB::White;

CRGB red = CHSV( HUE_RED, 255, 255);
CRGB orange  = CHSV( HUE_ORANGE, 255, 255);
CRGB yellow  = CHSV( HUE_YELLOW, 255, 255);
CRGB green = CHSV( HUE_GREEN, 255, 255);
CRGB aqua = CHSV( HUE_AQUA, 255, 255);
CRGB blue  = CHSV( HUE_BLUE, 255, 255);
CRGB purple = CHSV( HUE_PURPLE, 255, 255);
CRGB pink  = CHSV( HUE_PINK, 255, 255);

CRGB amethyst = CRGB::Amethyst;
CRGB cyan = CRGB::Cyan;
CRGB darkMagenta = CRGB::DarkMagenta;
CRGB darkGray = CRGB::DarkGray;
CRGB darkGreen = CRGB::DarkGreen;
CRGB darkOrange = CRGB::DarkOrange;
CRGB darkRed = CRGB::DarkRed;
CRGB darkSalmon = CRGB::DarkSalmon;
CRGB darkSlateBlue = CRGB::DarkSlateBlue;
CRGB darkSeaGreen = CRGB::DarkSeaGreen;
CRGB gray = CRGB::Gray;
CRGB gold = CRGB::Gold;
CRGB darkTurquoise = CRGB::DarkTurquoise;
CRGB darkViolet = CRGB::DarkViolet;
CRGB deepPink = CRGB::DeepPink;
CRGB dodgerBlue = CRGB::DodgerBlue;
CRGB greenYellow = CRGB::GreenYellow;
CRGB hotPink = CRGB::HotPink;
CRGB indianRed = CRGB::IndianRed;
CRGB indigo = CRGB::Indigo;
CRGB magenta = CRGB::Magenta;
CRGB mediumPurple = CRGB::MediumPurple;
CRGB midnightBlue = CRGB::MidnightBlue;
CRGB vibrantPurple = 0x7600ad;
CRGB vibrantBlue = 0x000263;

CRGB light_green = CHSV(85, 255, 255);


CRGBPalette16 Random_p()
{
  return CRGBPalette16(
                      CHSV( random8(), 255, 32),
                      CHSV( random8(), 255, 255),
                      CHSV( random8(), 128, 255),
                      CHSV( random8(), 255, 255));
}

CRGBPalette16 PurpleAndGreen_p = CRGBPalette16(
    green,  green,  black,  black,
    purple, purple, black,  black,
    green,  green,  black,  black,
    purple, purple, black,  black );

CRGBPalette16 AyaanColor_p = CRGBPalette16(
    pink,  pink,  white,  white,
    light_green, light_green, white,  white,
    pink,  pink,  white,  white,
    light_green, light_green, white,  white);

CRGBPalette16 RedAndBlue_p = CRGBPalette16(
    red, blue, red, blue);

CRGBPalette16 GoldAndPurple_p = CRGBPalette16(
    gold, 0x4800ff);
   
CRGBPalette16 TahaColor_p = CRGBPalette16(
    darkViolet, blue, deepPink, orange);

CRGBPalette16 WagnerColor_p = CRGBPalette16(
    black, indigo, white, pink);
CRGBPalette16 AyaanColorTwo_p = CRGBPalette16(
  yellow, orange, red, black);

CRGBPalette16 AyaanColorThree_p = CRGBPalette16(
  vibrantBlue, vibrantPurple, vibrantBlue, vibrantPurple);

CRGBPalette16 MaxColor_p = CRGBPalette16(
  cyan, purple, indianRed, gold);

CRGBPalette16 AidanColor_p = CRGBPalette16(
  red, green, blue, black);
 
CRGBPalette16 TurquoiseAndYellow_p = CRGBPalette16(
    yellow, darkTurquoise, white, darkTurquoise,
    yellow, darkTurquoise, white, darkTurquoise,
    yellow, darkTurquoise, white, darkTurquoise,
    yellow, darkTurquoise, white, darkTurquoise);




CRGBPalette16 currPal_p = AidanColor_p;

uint16_t speedPal = 15;
uint16_t scalePal = 20;
uint8_t colorLoopPal = 1;
