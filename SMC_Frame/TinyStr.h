/*
www.sourceforge.net/projects/tinyxml
Original file by Yves Berquin.

This software is provided 'as-is', without any express or implied 
warranty. In no event will the authors be held liable for any 
damages arising from the use of this software.

Permission is granted to anyone to use this software for any 
purpose, including commercial applications, and to alter it and 
redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must 
not claim that you wrote the original software. If you use this 
software in a product, an acknowledgment in the product documentation 
would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and
must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source 
distribution.
*/

#include "tinyxml.h"


#ifndef TIXML_USE_STL

#ifndef TIXML_STRING_INCLUDED
#define TIXML_STRING_INCLUDED

#ifdef _MSC_VER
#pragma warning( disable : 4530 )
#pragma warning( disable : 4786 )
#endif

#include <assert.h>

/*
   TiXmlString is an emulation of the std::string template.
   Its purpose is to allow compiling TinyXML on compilers with no or poor STL support.
   Only the member functions relevant to the TinyXML project have been implemented.
   The buffer allocation is made by a simplistic power of 2 like mechanism : if we increase
   a string and there's no more room, we allocate a buffer twice as big as we need.
*/
//##ModelId=4309ADF202CD
class TiXmlString
{
  public :
    // TiXmlString constructor, based on a string, mark explicit to force
	// us to find unnecessary casting.
	//##ModelId=4309ADF202E1
    explicit TiXmlString (const char * instring);

    // TiXmlString empty constructor
	//##ModelId=4309ADF202E3
    TiXmlString ()
    {
        allocated = 0;
        cstring = NULL;
        current_length = 0;
    }

    // TiXmlString copy constructor
	//##ModelId=4309ADF202E4
    explicit TiXmlString (const TiXmlString& copy);

    // TiXmlString destructor
	//##ModelId=4309ADF202EC
    ~ TiXmlString ()
    {
        empty_it ();
    }

    // Convert a TiXmlString into a classical char *
	//##ModelId=4309ADF202ED
    const char * c_str () const
    {
        if (allocated)
            return cstring;
        return "";
    }

    // Return the length of a TiXmlString
	//##ModelId=4309ADF202EF
    size_t length () const
	{
		return ( allocated ) ? current_length : 0;
	}

    // TiXmlString = operator
	//##ModelId=4309ADF202F1
    void operator = (const char * content);

    // = operator
	//##ModelId=4309ADF202F6
    void operator = (const TiXmlString & copy);

    // += operator. Maps to append
	//##ModelId=4309ADF202F8
    TiXmlString& operator += (const char * suffix)
    {
        append (suffix);
		return *this;
    }

    // += operator. Maps to append
	//##ModelId=4309ADF202FF
    TiXmlString& operator += (char single)
    {
        append (single);
		return *this;
    }

    // += operator. Maps to append
	//##ModelId=4309ADF20301
    TiXmlString& operator += (TiXmlString & suffix)
    {
        append (suffix);
		return *this;
    }
	//##ModelId=4309ADF20303
    bool operator == (const TiXmlString & compare) const;
	//##ModelId=4309ADF2030A
    bool operator == (const char* compare) const;
	//##ModelId=4309ADF2030D
    bool operator < (const TiXmlString & compare) const;
	//##ModelId=4309ADF20310
    bool operator > (const TiXmlString & compare) const;

    // Checks if a TiXmlString is empty
	//##ModelId=4309ADF20315
    bool empty () const
    {
        return length () ? false : true;
    }

    // single char extraction
	//##ModelId=4309ADF20317
    const char& at (unsigned index) const
    {
        assert( index < length ());
        return cstring [index];
    }

    // find a char in a string. Return TiXmlString::notfound if not found
	//##ModelId=4309ADF2031A
    unsigned find (char lookup) const
    {
        return find (lookup, 0);
    }

    // find a char in a string from an offset. Return TiXmlString::notfound if not found
	//##ModelId=4309ADF2031F
    unsigned find (char tofind, unsigned offset) const;

    /*	Function to reserve a big amount of data when we know we'll need it. Be aware that this
		function clears the content of the TiXmlString if any exists.
    */
	//##ModelId=4309ADF20323
    void reserve (unsigned size)
    {
        empty_it ();
        if (size)
        {
            allocated = size;
            cstring = new char [size];
            cstring [0] = 0;
            current_length = 0;
        }
    }

    // [] operator 
	//##ModelId=4309ADF20328
    char& operator [] (unsigned index) const
    {
        assert( index < length ());
        return cstring [index];
    }

    // Error value for find primitive 
    enum {	notfound = 0xffffffff,
            npos = notfound };

	//##ModelId=4309ADF2032B
    void append (const char *str, size_t len );

  protected :

    // The base string
	//##ModelId=4309ADF20331
    char * cstring;
    // Number of chars allocated
	//##ModelId=4309ADF20332
    size_t allocated;
    // Current string size
	//##ModelId=4309ADF2033B
    size_t current_length;

    // New size computation. It is simplistic right now : it returns twice the amount
    // we need
	//##ModelId=4309ADF20345
    size_t assign_new_size (size_t minimum_to_allocate)
    {
        return minimum_to_allocate * 2;
    }

    // Internal function that clears the content of a TiXmlString
	//##ModelId=4309ADF20347
    void empty_it ()
    {
        if (cstring)
            delete [] cstring;
        cstring = NULL;
        allocated = 0;
        current_length = 0;
    }

	//##ModelId=4309ADF20348
    void append (const char *suffix );

    // append function for another TiXmlString
	//##ModelId=4309ADF20350
    void append (const TiXmlString & suffix)
    {
        append (suffix . c_str ());
    }

    // append for a single char.
	//##ModelId=4309ADF20352
    void append (char single)
    {
        if ( cstring && current_length < (allocated-1) )
		{
			cstring[ current_length ] = single;
			++current_length;
			cstring[ current_length ] = 0;
		}
		else
		{
			char smallstr [2];
			smallstr [0] = single;
			smallstr [1] = 0;
			append (smallstr);
		}
    }

} ;

/* 
   TiXmlOutStream is an emulation of std::ostream. It is based on TiXmlString.
   Only the operators that we need for TinyXML have been developped.
*/
//##ModelId=4309ADF2035A
class TiXmlOutStream : public TiXmlString
{
public :
	//##ModelId=4309ADF2036E
    TiXmlOutStream () : TiXmlString () {}

    // TiXmlOutStream << operator. Maps to TiXmlString::append
	//##ModelId=4309ADF2036F
    TiXmlOutStream & operator << (const char * in)
    {
        append (in);
        return (* this);
    }

    // TiXmlOutStream << operator. Maps to TiXmlString::append
	//##ModelId=4309ADF20371
    TiXmlOutStream & operator << (const TiXmlString & in)
    {
        append (in . c_str ());
        return (* this);
    }
} ;

#ifdef _MSC_VER
#pragma warning( default : 4530 )
#pragma warning( default : 4786 )
#endif

#endif	// TIXML_STRING_INCLUDED
#endif	// TIXML_USE_STL
