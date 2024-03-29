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

#include "Arduino.h"
#include "privdetails.h"
#include "Shim_CharacterOLEDSPI2.h"
#include "SPI.h"


void Shim_CharacterOLEDSPI2::shim_setup( int _chipSelect )
{
    chipSelect = _chipSelect;
}

void Shim_CharacterOLEDSPI2::mirror_reply()
{
}

void Shim_CharacterOLEDSPI2::sendByte( byte b )
{
    SPI.transfer( b );

    // at div16 removing...
    delayMicroseconds(250); 
//    delay(1);
}


void Shim_CharacterOLEDSPI2::meth_impl( int m, int extrasz )
{
    static int callcount = 0;
    
//  Serial.print("meth() called top");

    callcount++;
    if( callcount == 4 )
    {
        // mirror_reply();
        callcount=0;
//        delay(20);
    }
    
    
#if 0
    //
    // Basic flow control. Every so often,
    // send a ping and wait for the reply.
    //
    callcount++;
    if( callcount == 16 )
    {
        // mirror_reply();
        callcount=0;
        ss->write('m');
        ss->write( (char)(2+0) );
        ss->write( (char)METH_internal_ping );
//        Serial.println("going to wait for reply (v3) ");

        while( 1 )
        {
            if( ss->available() )
            { 
                char c = ss->read();
//                Serial.print("ping reply from attiny: ");
//                Serial.print( (int)c );
//                Serial.print(" ");
                break;
            }
            delayMicroseconds(25); 
        }
    }
#endif

    selectChip();
    sendByte( 'm' );
    sendByte( (char)(2+extrasz) );
    sendByte( (char)m );
}

void Shim_CharacterOLEDSPI2::meth_flush()
{
    unselectChip();
}

void Shim_CharacterOLEDSPI2::selectChip()
{
    if( !chipSelectCount )
    {
          SPI.setDataMode(SPI_MODE0);
          SPI.setClockDivider(SPI_CLOCK_DIV16);
          SPI.setBitOrder( MSBFIRST );
  
          digitalWrite( chipSelect, LOW );

        // Give the slave some time in order to come to life
//        delayMicroseconds(1000); 
          delayMicroseconds(500);
    }
    chipSelectCount++;
}

void Shim_CharacterOLEDSPI2::unselectChip()
{
    chipSelectCount--;
    if( !chipSelectCount )
    {
        digitalWrite( chipSelect, HIGH );
//        delayMicroseconds(1000); 
        delayMicroseconds(250);
    }
}



void Shim_CharacterOLEDSPI2::meth( int m )
{
    meth_impl( m, 0 );
    meth_flush();
}

void Shim_CharacterOLEDSPI2::meth( int m, uint8_t a )
{
    meth_impl( m, 1 );
    sendByte( a );
    meth_flush();
}

void Shim_CharacterOLEDSPI2::meth( int m, uint8_t a, uint8_t b )
{
    meth_impl( m, 2 );
    sendByte( a );
    sendByte( b );
    meth_flush();
}


Shim_CharacterOLEDSPI2::Shim_CharacterOLEDSPI2( uint8_t rs, uint8_t rw, uint8_t enable,
                                              uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
    :
    chipSelectCount( 0 )
{
}

        
void Shim_CharacterOLEDSPI2::init( uint8_t rs, uint8_t rw, uint8_t enable,
                                  uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
    chipSelectCount = 0;
}


void Shim_CharacterOLEDSPI2::begin(uint8_t cols, uint8_t rows)
{
    meth( METH_begin, cols, rows );
}


void Shim_CharacterOLEDSPI2::clear()
{
    meth( METH_clear );
}

void Shim_CharacterOLEDSPI2::home()
{
    meth( METH_home );
}

void Shim_CharacterOLEDSPI2::noDisplay()
{
    meth( METH_noDisplay );
}
void Shim_CharacterOLEDSPI2::display()
{
    meth( METH_display );
}
void Shim_CharacterOLEDSPI2::noBlink()
{
    meth( METH_noBlink );
}
void Shim_CharacterOLEDSPI2::blink()
{
    meth( METH_blink );
}
void Shim_CharacterOLEDSPI2::noCursor()
{
    meth( METH_noCursor );
}
void Shim_CharacterOLEDSPI2::cursor()
{
    meth( METH_cursor );
}
void Shim_CharacterOLEDSPI2::scrollDisplayLeft()
{
    meth( METH_scrollDisplayLeft );
}
void Shim_CharacterOLEDSPI2::scrollDisplayRight()
{
    meth( METH_scrollDisplayRight );
}
void Shim_CharacterOLEDSPI2::leftToRight()
{
    meth( METH_leftToRight );
}
void Shim_CharacterOLEDSPI2::rightToLeft()
{
    meth( METH_rightToLeft );
}
void Shim_CharacterOLEDSPI2::autoscroll()
{
    meth( METH_autoscroll );
}
void Shim_CharacterOLEDSPI2::noAutoscroll()
{
    meth( METH_noAutoscroll );
}

void Shim_CharacterOLEDSPI2::setCursor(uint8_t a, uint8_t b) 
{
    meth( METH_setCursor, a, b );
}
size_t Shim_CharacterOLEDSPI2::write(uint8_t a)
{
    meth( METH_write, a );
}
void Shim_CharacterOLEDSPI2::command(uint8_t a)
{
    meth( METH_command, a );
}
  


ChipSelectionRAII::ChipSelectionRAII( ChipSelectable* _cs )
    :
    cs( _cs )
{
    cs->selectChip();
}

ChipSelectionRAII::~ChipSelectionRAII()
{
    cs->unselectChip();
}


