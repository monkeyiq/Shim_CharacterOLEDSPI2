/**
 *   Copyright (C) 2013 Ben Martin
 *
 *   Code for doing interesting things on Arduino.
 *
 *   This arduino code is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   libferris is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with libferris.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   For more details see the COPYING file in the root directory of this
 *   distribution.
 *
 ********************************************************************
 *
 */
#ifndef Shim_CharacterOLEDSPI2_h
#define Shim_CharacterOLEDSPI2_h

#include <inttypes.h>
#include "Print.h"

class ChipSelectable
{
  public:
    virtual void selectChip() = 0;
    virtual void unselectChip() = 0;
};


class ChipSelectionRAII 
{
    ChipSelectable* cs;
  public:
    ChipSelectionRAII( ChipSelectable* cs );
    ~ChipSelectionRAII();
};


class Shim_CharacterOLEDSPI2 : public Print, public ChipSelectable {

    int chipSelectCount;
    int chipSelect;
    void meth_impl( int m, int extrasz  );
    void meth_flush();
    void meth( int m );
    void meth( int m, uint8_t a );
    void meth( int m, uint8_t a, uint8_t b );

    void sendByte( byte b );

    void selectChip();
    void unselectChip();
    
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
