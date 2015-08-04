/*============================================================================
 * FONT.CPP
 *
 * DISPLAYS FONTS
 *
 *===========================================================================*/


#include "shape.h"


class Font : public Shape  
{
   protected:
  
//Variaveis do Calculo de FrameRate
int   fpsTotal;
int   fpsFrame;
int   fpsTempo;
int   fpsTempoBase;
float FPS;
char  fpsString[30];



   public:
      Font();
      ~Font();

      void draw();
      void write();
      void DefaultHelpMenu();
      char* mFPS ();

   private:
      void putstring (char* s, float x, float y);
};



