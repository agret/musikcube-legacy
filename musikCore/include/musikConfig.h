///////////////////////////////////////////////////
//
// License Agreement:
//
// The following are Copyright � 2002-2006, Casey Langen
//
// Sources and Binaries of: musikCore musikCube musikBox
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright 
//      notice, this list of conditions and the following disclaimer in the 
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the author nor the names of other contributors may 
//      be used to endorse or promote products derived from this software 
//      without specific prior written permission. 
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE. 
//
///////////////////////////////////////////////////

#ifndef MUSIKEXPORT
#if defined(WIN32) /*&& !defined(__MINGW32__)*/
#define MUSIKEXPORT __declspec(dllexport)
#else
#define MUSIKEXPORT 
#endif
#endif

#if !defined(UNICODE) && !defined(_UNICODE)
#define UNICODE
#define _UNICODE
#endif

#if !defined(WIN32) && !defined(__MINGW32__)

//
// linux
//

#include "unicode.h"
#define USE_XINE 1

#if defined (USE_XINE)
#undef USE_FMOD
#else
#define USE_FMOD 
#endif

#else

//
// windows
//

#undef USE_XINE
#undef USE_FMOD
#define USE_BASS

#endif

#if defined (WIN32) && !defined(__MINGW32__)
#pragma warning (disable : 4311)
#pragma warning (disable : 4267)
#pragma warning (disable : 4244)
#pragma warning (disable : 4251)    // export warnings
#pragma warning (disable : 4275)    // export warnings
#endif

///////////////////////////////////////////////////

#ifndef MUSIK_CONFIG_H
#define MUSIK_CONFIG_H

///////////////////////////////////////////////////

#include "StdString.h"

#include <sstream>
#include <vector>

#include "../src/unicode.h"

using namespace std;
namespace musikCore {

///////////////////////////////////////////////////

typedef CStdString String;    
typedef std::vector<String> StringArray;
typedef std::vector<int> IntArray;

///////////////////////////////////////////////////

// stuff that windows uses but 
// may not be exactly the same
// with gcc

#ifdef WIN32
#ifndef assert
#define assert(x) ASSERT(x)
#endif
#endif

#if !defined(WIN32) || defined(__MINGW32__)

#if !defined(__MINGW32__)
#include <unistd.h>
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#if !defined(UNICODE) && !defined(_UNICODE)
#define _T(x) x
#else
#if !defined(_T)
#define _T(x) L ## x
#endif
#endif

#ifndef __MINGW32__
#ifndef Sleep
#define Sleep(x) usleep(x * 1000)
#endif
#endif

#ifndef ASSERT
#define ASSERT(x) assert(x)
#endif

#endif

///////////////////////////////////////////////////

inline String IntToString(int n)
{
    ostringstream aStream;
    aStream << n << "\0";

    string str = aStream.str().c_str();
    return str;
}

///////////////////////////////////////////////////

inline int StringToInt(string str)
{
    int ret;

    istringstream aStream;
    aStream.str(str);
    aStream >> ret;

    return ret;
}

///////////////////////////////////////////////////

// modified versions of TagLib::String::to8Bit

inline std::wstring utf8to16(const std::string& src)
{
    int bufferSize = src.size() + 1;
    musikUnicode::UTF8  *sourceBuffer = new musikUnicode::UTF8[bufferSize];
    musikUnicode::UTF16 *targetBuffer = new musikUnicode::UTF16[bufferSize];

    size_t i = 0;
    for(; i < src.size(); i++)
      sourceBuffer[i] = musikUnicode::UTF8(src[i]);
    sourceBuffer[i] = 0;

    const musikUnicode::UTF8 *source = sourceBuffer;
    musikUnicode::UTF16 *target = targetBuffer;

    musikUnicode::ConversionResult result =
      musikUnicode::ConvertUTF8toUTF16(&source, sourceBuffer + bufferSize,
                                  &target, targetBuffer + bufferSize,
                                  musikUnicode::lenientConversion);

    if(result != musikUnicode::conversionOK)
      printf("String::prepare() - Unicode conversion error.");


    int newSize = target != targetBuffer ? target - targetBuffer - 1 : 0;

    std::wstring ret;
    ret.resize(newSize);

    for(i = 0; i < (unsigned int)newSize; i++)
      ret[i] = targetBuffer[i];

    delete [] sourceBuffer;
    delete [] targetBuffer;

    return ret;
}

inline std::string utf16to8(const String& src, bool unicode = true)
{
    std::string ret;
    ret.resize(src.size());

    if(!unicode) 
    {
        for (size_t i = 0; i < src.size(); i++)
            ret[i] = (char)src[i];

        return ret;
    }

    const int outputBufferSize = src.size() * 3 + 1;

    musikUnicode::UTF16 *sourceBuffer = new musikUnicode::UTF16[src.size() + 1];
    musikUnicode::UTF8  *targetBuffer = new musikUnicode::UTF8[outputBufferSize];

    // take the wstring and build a valid UTF16
    for(unsigned int i = 0; i < src.size(); i++)
        sourceBuffer[i] = musikUnicode::UTF16(src[i]);

    const musikUnicode::UTF16 *source = sourceBuffer;
    musikUnicode::UTF8 *target = targetBuffer;

    musikUnicode::ConversionResult result =
        musikUnicode::ConvertUTF16toUTF8(&source, sourceBuffer + src.size(),
                                     &target, targetBuffer + outputBufferSize,
                                     musikUnicode::lenientConversion);

    if(result != musikUnicode::conversionOK)
        printf("utf16to8() failled\n");

    int newSize = target - targetBuffer;
    ret.resize(newSize);
    targetBuffer[newSize] = 0;

    ret = (char *) targetBuffer;

    delete [] sourceBuffer;
    delete [] targetBuffer;

    return ret;
}

///////////////////////////////////////////////////

inline String q_str(String src)
{
    src.Replace(_T("'"), _T("''"));
    return src;
}

///////////////////////////////////////////////////


// modified versions of TagLib::String::to8Bit

inline int utf16toint(const String& src)
{
    std::string ret;
    ret.resize(src.size());

    for (size_t i = 0; i < src.size(); i++)
        ret[i] = (char)src[i];

    return atoi(ret.c_str());
}

///////////////////////////////////////////////////

inline int StringToInt(const wstring& str)
{
   return utf16toint(str); 
}

///////////////////////////////////////////////////

inline float StringToFloat(const wstring& src)
{
    std::string ret;
    ret.resize(src.size());

    for (size_t i = 0; i < src.size(); i++)
        ret[i] = (char)src[i];

    return atof(ret.c_str());
}

///////////////////////////////////////////////////

} // namespace

///////////////////////////////////////////////////

#endif

///////////////////////////////////////////////////
