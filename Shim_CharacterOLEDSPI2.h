#ifndef Shim_CharacterOLEDSPI2_h
#define Shim_CharacterOLEDSPI2_h

#include <inttypes.h>
#include "Print.h"

class Shim_CharacterOLEDSPI2 : public Print {

    int chipSelect;
    void meth_impl( int m, int extrasz  );
    void meth_flush();
    void meth( int m );
    void meth( int m, uint8_t a );
    void meth( int m, uint8_t a, uint8_t b );

    void sendByte( byte b );
    
    
public:
    void shim_setup( int _chipSelect );
    void mirror_reply();

  Shim_CharacterOLEDSPI2(uint8_t rs, uint8_t rw, uint8_t enable,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
  void init(uint8_t rs, uint8_t rw, uint8_t enable,
	    uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

  
  void begin(uint8_t cols, uint8_t rows);

  void clear();
  void home();

  void noDisplay();
  void display();
  void noBlink();
  void blink();
  void noCursor();
  void cursor();
  void scrollDisplayLeft();
  void scrollDisplayRight();
  void leftToRight();
  void rightToLeft();
  void autoscroll();
  void noAutoscroll();

//  void createChar(uint8_t, uint8_t[]);
  void setCursor(uint8_t, uint8_t); 
  virtual size_t write(uint8_t);
  void command(uint8_t);
  
};

#endif
