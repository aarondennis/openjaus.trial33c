/*****************************************************************************
 *  Copyright (c) 2009, OpenJAUS.com
 *  All rights reserved.
 *
 *  This file is part of OpenJAUS.  OpenJAUS is distributed under the BSD
 *  license.  See the LICENSE file for details.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of the University of Florida nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/
// File Name: jausEndianness.h
//
// Written By: Rob Meyers (rjmeyers81 AT gmail DOT com)
//
// Version: 3.3.0b
//
// Date: 09/07/10
//
// Description: This file defines jaus endianness system and should only be used by jaus functions

#include "type/jausEndianness.h"


void jausEndianSafeCopy(void* dst, void* src, const JausInteger len)
{
  unsigned char* destination = (unsigned char*)dst;
  unsigned char* source = (unsigned char*)src;

  if(jausDetectEndianness() == _JAUS_BIG_ENDIAN)
  { // it is little endian, switch to network byte order for serialization
    unsigned int i = 0;

    for(i=0; i < len; ++i)
    {
      destination[i] = source[len - i - 1];
    }
  }
  else
  {
    memcpy(destination, source, len);
  }
}

JausEndianness jausDetectEndianness()
{
  static JausEndianness detectedEndianness = JAUS_UNKNOWN_ENDIAN;

  if(detectedEndianness == JAUS_UNKNOWN_ENDIAN)
  {
    unsigned char testStr[2] = {1,0};
    short testShort;

    testShort = *(short *)testStr;

    if(testShort == 0x100)
    {
      detectedEndianness = _JAUS_BIG_ENDIAN;
    }
    else if(testShort == 0x01)
    {
      detectedEndianness = _JAUS_LITTLE_ENDIAN;
    }
    else
    {
      detectedEndianness = JAUS_UNKNOWN_ENDIAN;
    }

    if(detectedEndianness == _JAUS_BIG_ENDIAN)
      {
        printf("Big endian system\n");
      }
    else if (detectedEndianness == _JAUS_LITTLE_ENDIAN)
      {
        printf("Little endian system\n");
      }
    else
      {
        printf("Unknown endian system\n");
      }

  }

  return detectedEndianness;
}

