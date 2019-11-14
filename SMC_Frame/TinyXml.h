/*
www.sourceforge.net/projects/tinyxml
Original code (2.0 and earlier )copyright (c) 2000-2002 Lee Thomason (www.grinninglizard.com)

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


#ifndef TINYXML_INCLUDED
#define TINYXML_INCLUDED

#ifdef _MSC_VER
#pragma warning( disable : 4530 )
#pragma warning( disable : 4786 )
#pragma warning( disable : 4996 )  
#endif

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TIXML_USE_STL

// Help out windows:
#if defined( _DEBUG ) && !defined( DEBUG )
#define DEBUG
#endif

#if defined( DEBUG ) && defined( _MSC_VER )
#include <windows.h>
#define TIXML_LOG OutputDebugString
#else
#define TIXML_LOG printf
#endif

#ifdef TIXML_USE_STL
	#include <string>
 	#include <iostream>
	#define TIXML_STRING	std::string
	#define TIXML_ISTREAM	std::istream
	#define TIXML_OSTREAM	std::ostream
#else
	#include "tinystr.h"
	#define TIXML_STRING	TiXmlString
	#define TIXML_OSTREAM	TiXmlOutStream
#endif

class TiXmlDocument;
class TiXmlElement;
class TiXmlComment;
class TiXmlUnknown;
class TiXmlAttribute;
class TiXmlText;
class TiXmlDeclaration;
class TiXmlParsingData;

const int TIXML_MAJOR_VERSION = 2;
const int TIXML_MINOR_VERSION = 3;
const int TIXML_PATCH_VERSION = 4;

/*	Internal structure for tracking location of items 
	in the XML file.
*/
//##ModelId=4309ADEC028A
struct TiXmlCursor
{
	//##ModelId=4309ADEC0293
	TiXmlCursor()		{ Clear(); }
	//##ModelId=4309ADEC029C
	void Clear()		{ row = col = -1; }

	//##ModelId=4309ADEC02D8
	int row;	// 0 based.
	//##ModelId=4309ADEC02D9
	int col;	// 0 based.
};


// Only used by Attribute::Query functions
enum 
{ 
	TIXML_SUCCESS,
	TIXML_NO_ATTRIBUTE,
	TIXML_WRONG_TYPE
};


// Used by the parsing routines.
//##ModelId=4309ADEC0314
enum TiXmlEncoding
{
	//##ModelId=4309ADEC0328
	TIXML_ENCODING_UNKNOWN,
	//##ModelId=4309ADEC0329
	TIXML_ENCODING_UTF8,
	//##ModelId=4309ADEC0332
	TIXML_ENCODING_LEGACY
};

const TiXmlEncoding TIXML_DEFAULT_ENCODING = TIXML_ENCODING_UNKNOWN;

/** TiXmlBase is a base class for every class in TinyXml.
	It does little except to establish that TinyXml classes
	can be printed and provide some utility functions.

	In XML, the document and elements can contain
	other elements and other types of nodes.

	@verbatim
	A Document can contain:	Element	(container or leaf)
							Comment (leaf)
							Unknown (leaf)
							Declaration( leaf )

	An Element can contain:	Element (container or leaf)
							Text	(leaf)
							Attributes (not on tree)
							Comment (leaf)
							Unknown (leaf)

	A Decleration contains: Attributes (not on tree)
	@endverbatim
*/
//##ModelId=4309ADED0135
class TiXmlBase
{
	friend class TiXmlNode;
	friend class TiXmlElement;
	friend class TiXmlDocument;

public:
	//##ModelId=4309ADED0149
	TiXmlBase()	:	userData(0) {}
	//##ModelId=4309ADED014A
	virtual ~TiXmlBase()					{}

	/**	All TinyXml classes can print themselves to a filestream.
		This is a formatted print, and will insert tabs and newlines.
		
		(For an unformatted stream, use the << operator.)
	*/
	//##ModelId=4309ADED014C
	virtual void Print( FILE* cfile, int depth ) const = 0;

	/**	The world does not agree on whether white space should be kept or
		not. In order to make everyone happy, these global, static functions
		are provided to set whether or not TinyXml will condense all white space
		into a single space or not. The default is to condense. Note changing this
		values is not thread safe.
	*/
	//##ModelId=4309ADED0153
	static void SetCondenseWhiteSpace( bool condense )		{ condenseWhiteSpace = condense; }

	/// Return the current white space setting.
	//##ModelId=4309ADED0156
	static bool IsWhiteSpaceCondensed()						{ return condenseWhiteSpace; }

	/** Return the position, in the original source file, of this node or attribute.
		The row and column are 1-based. (That is the first row and first column is
		1,1). If the returns values are 0 or less, then the parser does not have
		a row and column value.

		Generally, the row and column value will be set when the TiXmlDocument::Load(),
		TiXmlDocument::LoadFile(), or any TiXmlNode::Parse() is called. It will NOT be set
		when the DOM was created from operator>>.

		The values reflect the initial load. Once the DOM is modified programmatically
		(by adding or changing nodes and attributes) the new values will NOT update to
		reflect changes in the document.

		There is a minor performance cost to computing the row and column. Computation
		can be disabled if TiXmlDocument::SetTabSize() is called with 0 as the value.

		@sa TiXmlDocument::SetTabSize()
	*/
	//##ModelId=4309ADED0158
	int Row() const			{ return location.row + 1; }
	//##ModelId=4309ADED015D
	int Column() const		{ return location.col + 1; }	///< See Row()

	//##ModelId=4309ADED015F
	void  SetUserData( void* user )			{ userData = user; }
	//##ModelId=4309ADED0161
	void* GetUserData()						{ return userData; }

	// Table that returs, for a given lead byte, the total number of bytes
	// in the UTF-8 sequence.
	//##ModelId=4309ADED0162
	static const int utf8ByteTable[256];

	//##ModelId=4309ADED0167
	virtual const char* Parse(	const char* p, 
								TiXmlParsingData* data, 
								TiXmlEncoding encoding /*= TIXML_ENCODING_UNKNOWN */ ) = 0;

	enum
	{
		TIXML_NO_ERROR = 0,
		TIXML_ERROR,
		TIXML_ERROR_OPENING_FILE,
		TIXML_ERROR_OUT_OF_MEMORY,
		TIXML_ERROR_PARSING_ELEMENT,
		TIXML_ERROR_FAILED_TO_READ_ELEMENT_NAME,
		TIXML_ERROR_READING_ELEMENT_VALUE,
		TIXML_ERROR_READING_ATTRIBUTES,
		TIXML_ERROR_PARSING_EMPTY,
		TIXML_ERROR_READING_END_TAG,
		TIXML_ERROR_PARSING_UNKNOWN,
		TIXML_ERROR_PARSING_COMMENT,
		TIXML_ERROR_PARSING_DECLARATION,
		TIXML_ERROR_DOCUMENT_EMPTY,
		TIXML_ERROR_EMBEDDED_NULL,

		TIXML_ERROR_STRING_COUNT
	};

protected:

	// See STL_STRING_BUG
	// Utility class to overcome a bug.
	//##ModelId=4309AF6E002A
	class StringToBuffer
	{
	  public:
		//##ModelId=4309AF6E003E
		StringToBuffer( const TIXML_STRING& str );
		//##ModelId=4309AF6E0040
		~StringToBuffer();
		//##ModelId=4309AF6E0048
		char* buffer;
	};

	//##ModelId=4309ADED0173
	static const char*	SkipWhiteSpace( const char*, TiXmlEncoding encoding );
	//##ModelId=4309ADED017B
	inline static bool	IsWhiteSpace( char c )		
	{ 
		return ( isspace( (unsigned char) c ) || c == '\n' || c == '\r' ); 
	}

	//##ModelId=4309ADED017E
	virtual void StreamOut (TIXML_OSTREAM *) const = 0;

	#ifdef TIXML_USE_STL
	//##ModelId=4309ADED0185
	    static bool	StreamWhiteSpace( TIXML_ISTREAM * in, TIXML_STRING * tag );
	//##ModelId=4309ADED0189
	    static bool StreamTo( TIXML_ISTREAM * in, int character, TIXML_STRING * tag );
	#endif

	/*	Reads an XML name into the string provided. Returns
		a pointer just past the last character of the name,
		or 0 if the function has an error.
	*/
	//##ModelId=4309ADED0192
	static const char* ReadName( const char* p, TIXML_STRING* name, TiXmlEncoding encoding );

	/*	Reads text. Returns a pointer past the given end tag.
		Wickedly complex options, but it keeps the (sensitive) code in one place.
	*/
	//##ModelId=4309ADED019B
	static const char* ReadText(	const char* in,				// where to start
									TIXML_STRING* text,			// the string read
									bool ignoreWhiteSpace,		// whether to keep the white space
									const char* endTag,			// what ends this text
									bool ignoreCase,			// whether to ignore case in the end tag
									TiXmlEncoding encoding );	// the current encoding

	// If an entity has been found, transform it into a character.
	//##ModelId=4309ADED01A7
	static const char* GetEntity( const char* in, char* value, int* length, TiXmlEncoding encoding );

	// Get a character, while interpreting entities.
	// The length can be from 0 to 4 bytes.
	//##ModelId=4309ADED01B1
	inline static const char* GetChar( const char* p, char* _value, int* length, TiXmlEncoding encoding )
	{
		assert( p );
		if ( encoding == TIXML_ENCODING_UTF8 )
		{
			*length = utf8ByteTable[ *((unsigned char*)p) ];
			assert( *length >= 0 && *length < 5 );
		}
		else
		{
			*length = 1;
		}

		if ( *length == 1 )
		{
			if ( *p == '&' )
				return GetEntity( p, _value, length, encoding );
			*_value = *p;
			return p+1;
		}
		else if ( *length )
		{
			strncpy( _value, p, *length );
			return p + (*length);
		}
		else
		{
			// Not valid text.
			return 0;
		}
	}

	// Puts a string to a stream, expanding entities as it goes.
	// Note this should not contian the '<', '>', etc, or they will be transformed into entities!
	//##ModelId=4309ADED01C2
	static void PutString( const TIXML_STRING& str, TIXML_OSTREAM* out );

	//##ModelId=4309ADED01C6
	static void PutString( const TIXML_STRING& str, TIXML_STRING* out );

	// Return true if the next characters in the stream are any of the endTag sequences.
	// Ignore case only works for english, and should only be relied on when comparing
	// to Engilish words: StringEqual( p, "version", true ) is fine.
	//##ModelId=4309ADED01CE
	static bool StringEqual(	const char* p,
								const char* endTag,
								bool ignoreCase,
								TiXmlEncoding encoding );

	//##ModelId=4309ADED01D8
	static const char* errorString[ TIXML_ERROR_STRING_COUNT ];

	//##ModelId=4309AF6E000D
	TiXmlCursor location;

    /// Field containing a generic user pointer
	//##ModelId=4309ADED01F3
	void*			userData;
	
	// None of these methods are reliable for any language except English.
	// Good for approximation, not great for accuracy.
	//##ModelId=4309ADED01F4
	static int IsAlpha( unsigned char anyByte, TiXmlEncoding encoding );
	//##ModelId=4309ADED0200
	static int IsAlphaNum( unsigned char anyByte, TiXmlEncoding encoding );
	//##ModelId=4309ADED0208
	inline static int ToLower( int v, TiXmlEncoding encoding )
	{
		if ( encoding == TIXML_ENCODING_UTF8 )
		{
			if ( v < 128 ) return tolower( v );
			return v;
		}
		else
		{
			return tolower( v );
		}
	}
	//##ModelId=4309ADED020C
	static void ConvertUTF32ToUTF8( unsigned long input, char* output, int* length );

private:
	//##ModelId=4309ADED0215
	TiXmlBase( const TiXmlBase& );				// not implemented.
	//##ModelId=4309ADED021C
	void operator=( const TiXmlBase& base );	// not allowed.

	//##ModelId=4309AF6E0052
	struct Entity
	{
		//##ModelId=4309AF6E0066
		const char*     str;
		//##ModelId=4309AF6E0070
		unsigned int	strLength;
		//##ModelId=4309AF6E0071
		char		    chr;
	};
	enum
	{
		NUM_ENTITY = 5,
		MAX_ENTITY_LENGTH = 6

	};
	//##ModelId=4309AF6E0021
	static Entity entity[ NUM_ENTITY ];
	//##ModelId=4309ADED0225
	static bool condenseWhiteSpace;
};


/** The parent class for everything in the Document Object Model.
	(Except for attributes).
	Nodes have siblings, a parent, and children. A node can be
	in a document, or stand on its own. The type of a TiXmlNode
	can be queried, and it can be cast to its more defined type.
*/
//##ModelId=4309ADEE033F
class TiXmlNode : public TiXmlBase
{
	friend class TiXmlDocument;
	friend class TiXmlElement;

public:
	#ifdef TIXML_USE_STL	

	    /** An input stream operator, for every class. Tolerant of newlines and
		    formatting, but doesn't expect them.
	    */
	//##ModelId=4309ADEF00B6
	    friend std::istream& operator >> (std::istream& in, TiXmlNode& base);

	    /** An output stream operator, for every class. Note that this outputs
		    without any newlines or formatting, as opposed to Print(), which
		    includes tabs and new lines.

		    The operator<< and operator>> are not completely symmetric. Writing
		    a node to a stream is very well defined. You'll get a nice stream
		    of output, without any extra whitespace or newlines.
		    
		    But reading is not as well defined. (As it always is.) If you create
		    a TiXmlElement (for example) and read that from an input stream,
		    the text needs to define an element or junk will result. This is
		    true of all input streams, but it's worth keeping in mind.

		    A TiXmlDocument will read nodes until it reads a root element, and
			all the children of that root element.
	    */	
	//##ModelId=4309ADEF00C0
	    friend std::ostream& operator<< (std::ostream& out, const TiXmlNode& base);

		/// Appends the XML node or attribute to a std::string.
	//##ModelId=4309ADEF00C4
		friend std::string& operator<< (std::string& out, const TiXmlNode& base );

	#else
	    // Used internally, not part of the public API.
	    friend TIXML_OSTREAM& operator<< (TIXML_OSTREAM& out, const TiXmlNode& base);
	#endif

	/** The types of XML nodes supported by TinyXml. (All the
			unsupported types are picked up by UNKNOWN.)
	*/
	//##ModelId=4309AF6E02DD
	enum NodeType
	{
		//##ModelId=4309AF6E02F2
		DOCUMENT,
		//##ModelId=4309AF6E02FB
		ELEMENT,
		//##ModelId=4309AF6E0305
		COMMENT,
		//##ModelId=4309AF6E0306
		UNKNOWN,
		//##ModelId=4309AF6E030F
		TEXT,
		//##ModelId=4309AF6E0310
		DECLARATION,
		//##ModelId=4309AF6E0319
		TYPECOUNT
	};

	//##ModelId=4309ADEE0354
	virtual ~TiXmlNode();

	/** The meaning of 'value' changes for the specific type of
		TiXmlNode.
		@verbatim
		Document:	filename of the xml file
		Element:	name of the element
		Comment:	the comment text
		Unknown:	the tag contents
		Text:		the text string
		@endverbatim

		The subclasses will wrap this function.
	*/
	//##ModelId=4309ADEE0356
	const char * Value() const { return value.c_str (); }

	/** Changes the value of the node. Defined as:
		@verbatim
		Document:	filename of the xml file
		Element:	name of the element
		Comment:	the comment text
		Unknown:	the tag contents
		Text:		the text string
		@endverbatim
	*/
	//##ModelId=4309ADEE0358
	void SetValue(const char * _value) { value = _value;}

    #ifdef TIXML_USE_STL
	/// STL std::string form.
	//##ModelId=4309ADEE035E
	void SetValue( const std::string& _value )    
	{	  
		StringToBuffer buf( _value );
		SetValue( buf.buffer ? buf.buffer : "" );    	
	}	
	#endif

	/// Delete all the children of this node. Does not affect 'this'.
	//##ModelId=4309ADEE0360
	void Clear();

	/// One step up the DOM.
	//##ModelId=4309ADEE0361
	TiXmlNode* Parent()							{ return parent; }
	//##ModelId=4309ADEE0367
	const TiXmlNode* Parent() const				{ return parent; }

	//##ModelId=4309ADEE0369
	const TiXmlNode* FirstChild()	const	{ return firstChild; }		///< The first child of this node. Will be null if there are no children.
	//##ModelId=4309ADEE036B
	TiXmlNode* FirstChild()					{ return firstChild; }
	//##ModelId=4309ADEE036C
	const TiXmlNode* FirstChild( const char * value ) const;			///< The first child of this node with the matching 'value'. Will be null if none found.
	//##ModelId=4309ADEE0372
	TiXmlNode* FirstChild( const char * value );						///< The first child of this node with the matching 'value'. Will be null if none found.

	//##ModelId=4309ADEE0374
	const TiXmlNode* LastChild() const	{ return lastChild; }		/// The last child of this node. Will be null if there are no children.
	//##ModelId=4309ADEE0376
	TiXmlNode* LastChild()	{ return lastChild; }
	//##ModelId=4309ADEE037B
	const TiXmlNode* LastChild( const char * value ) const;			/// The last child of this node matching 'value'. Will be null if there are no children.
	//##ModelId=4309ADEE037E
	TiXmlNode* LastChild( const char * value );	

    #ifdef TIXML_USE_STL
	//##ModelId=4309ADEE0380
	const TiXmlNode* FirstChild( const std::string& _value ) const	{	return FirstChild (_value.c_str ());	}	///< STL std::string form.
	//##ModelId=4309ADEE0387
	TiXmlNode* FirstChild( const std::string& _value )				{	return FirstChild (_value.c_str ());	}	///< STL std::string form.
	//##ModelId=4309ADEE0389
	const TiXmlNode* LastChild( const std::string& _value ) const	{	return LastChild (_value.c_str ());	}	///< STL std::string form.
	//##ModelId=4309ADEE0390
	TiXmlNode* LastChild( const std::string& _value )				{	return LastChild (_value.c_str ());	}	///< STL std::string form.
	#endif

	/** An alternate way to walk the children of a node.
		One way to iterate over nodes is:
		@verbatim
			for( child = parent->FirstChild(); child; child = child->NextSibling() )
		@endverbatim

		IterateChildren does the same thing with the syntax:
		@verbatim
			child = 0;
			while( child = parent->IterateChildren( child ) )
		@endverbatim

		IterateChildren takes the previous child as input and finds
		the next one. If the previous child is null, it returns the
		first. IterateChildren will return null when done.
	*/
	//##ModelId=4309ADEE0392
	const TiXmlNode* IterateChildren( const TiXmlNode* previous ) const;
	//##ModelId=4309ADEE0399
	TiXmlNode* IterateChildren( TiXmlNode* previous );

	/// This flavor of IterateChildren searches for children with a particular 'value'
	//##ModelId=4309ADEE039B
	const TiXmlNode* IterateChildren( const char * value, const TiXmlNode* previous ) const;
	//##ModelId=4309ADEE039F
	TiXmlNode* IterateChildren( const char * value, TiXmlNode* previous );

    #ifdef TIXML_USE_STL
	//##ModelId=4309ADEE03A5
	const TiXmlNode* IterateChildren( const std::string& _value, const TiXmlNode* previous ) const	{	return IterateChildren (_value.c_str (), previous);	}	///< STL std::string form.
	//##ModelId=4309ADEE03A9
	TiXmlNode* IterateChildren( const std::string& _value, TiXmlNode* previous ) {	return IterateChildren (_value.c_str (), previous);	}	///< STL std::string form.
	#endif

	/** Add a new node related to this. Adds a child past the LastChild.
		Returns a pointer to the new object or NULL if an error occured.
	*/
	//##ModelId=4309ADEE03AF
	TiXmlNode* InsertEndChild( const TiXmlNode& addThis );


	/** Add a new node related to this. Adds a child past the LastChild.

		NOTE: the node to be added is passed by pointer, and will be
		henceforth owned (and deleted) by tinyXml. This method is efficient
		and avoids an extra copy, but should be used with care as it
		uses a different memory model than the other insert functions.

		@sa InsertEndChild
	*/
	//##ModelId=4309ADEE03B1
	TiXmlNode* LinkEndChild( TiXmlNode* addThis );

	/** Add a new node related to this. Adds a child before the specified child.
		Returns a pointer to the new object or NULL if an error occured.
	*/
	//##ModelId=4309ADEE03B8
	TiXmlNode* InsertBeforeChild( TiXmlNode* beforeThis, const TiXmlNode& addThis );

	/** Add a new node related to this. Adds a child after the specified child.
		Returns a pointer to the new object or NULL if an error occured.
	*/
	//##ModelId=4309ADEE03BB
	TiXmlNode* InsertAfterChild(  TiXmlNode* afterThis, const TiXmlNode& addThis );

	/** Replace a child of this node.
		Returns a pointer to the new object or NULL if an error occured.
	*/
	//##ModelId=4309ADEE03C3
	TiXmlNode* ReplaceChild( TiXmlNode* replaceThis, const TiXmlNode& withThis );

	/// Delete a child of this node.
	//##ModelId=4309ADEE03C6
	bool RemoveChild( TiXmlNode* removeThis );

	/// Navigate to a sibling node.
	//##ModelId=4309ADEE03CC
	const TiXmlNode* PreviousSibling() const			{ return prev; }
	//##ModelId=4309ADEE03CE
	TiXmlNode* PreviousSibling()						{ return prev; }

	/// Navigate to a sibling node.
	//##ModelId=4309ADEE03CF
	const TiXmlNode* PreviousSibling( const char * ) const;
	//##ModelId=4309ADEE03D5
	TiXmlNode* PreviousSibling( const char * );

    #ifdef TIXML_USE_STL
	//##ModelId=4309ADEE03D7
	const TiXmlNode* PreviousSibling( const std::string& _value ) const	{	return PreviousSibling (_value.c_str ());	}	///< STL std::string form.
	//##ModelId=4309ADEE03DA
	TiXmlNode* PreviousSibling( const std::string& _value ) 			{	return PreviousSibling (_value.c_str ());	}	///< STL std::string form.
	//##ModelId=4309ADEE03E0
	const TiXmlNode* NextSibling( const std::string& _value) const		{	return NextSibling (_value.c_str ());	}	///< STL std::string form.
	//##ModelId=4309ADEE03E3
	TiXmlNode* NextSibling( const std::string& _value) 					{	return NextSibling (_value.c_str ());	}	///< STL std::string form.
	#endif

	/// Navigate to a sibling node.
	//##ModelId=4309ADEF0001
	const TiXmlNode* NextSibling() const				{ return next; }
	//##ModelId=4309ADEF0003
	TiXmlNode* NextSibling()							{ return next; }

	/// Navigate to a sibling node with the given 'value'.
	//##ModelId=4309ADEF0004
	const TiXmlNode* NextSibling( const char * ) const;
	//##ModelId=4309ADEF000B
	TiXmlNode* NextSibling( const char * );

	/** Convenience function to get through elements.
		Calls NextSibling and ToElement. Will skip all non-Element
		nodes. Returns 0 if there is not another element.
	*/
	//##ModelId=4309ADEF000D
	const TiXmlElement* NextSiblingElement() const;
	//##ModelId=4309ADEF000F
	TiXmlElement* NextSiblingElement();

	/** Convenience function to get through elements.
		Calls NextSibling and ToElement. Will skip all non-Element
		nodes. Returns 0 if there is not another element.
	*/
	//##ModelId=4309ADEF0010
	const TiXmlElement* NextSiblingElement( const char * ) const;
	//##ModelId=4309ADEF0018
	TiXmlElement* NextSiblingElement( const char * );

    #ifdef TIXML_USE_STL
	//##ModelId=4309ADEF001A
	const TiXmlElement* NextSiblingElement( const std::string& _value) const	{	return NextSiblingElement (_value.c_str ());	}	///< STL std::string form.
	//##ModelId=4309ADEF0020
	TiXmlElement* NextSiblingElement( const std::string& _value)				{	return NextSiblingElement (_value.c_str ());	}	///< STL std::string form.
	#endif

	/// Convenience function to get through elements.
	//##ModelId=4309ADEF0022
	const TiXmlElement* FirstChildElement()	const;
	//##ModelId=4309ADEF0024
	TiXmlElement* FirstChildElement();

	/// Convenience function to get through elements.
	//##ModelId=4309ADEF0025
	const TiXmlElement* FirstChildElement( const char * value ) const;
	//##ModelId=4309ADEF002C
	TiXmlElement* FirstChildElement( const char * value );

    #ifdef TIXML_USE_STL
	//##ModelId=4309ADEF002E
	const TiXmlElement* FirstChildElement( const std::string& _value ) const	{	return FirstChildElement (_value.c_str ());	}	///< STL std::string form.
	//##ModelId=4309ADEF0035
	TiXmlElement* FirstChildElement( const std::string& _value )				{	return FirstChildElement (_value.c_str ());	}	///< STL std::string form.
	#endif

	/** Query the type (as an enumerated value, above) of this node.
		The possible types are: DOCUMENT, ELEMENT, COMMENT,
								UNKNOWN, TEXT, and DECLARATION.
	*/
	//##ModelId=4309ADEF0037
	virtual int Type() const	{ return type; }

	/** Return a pointer to the Document this node lives in.
		Returns null if not in a document.
	*/
	//##ModelId=4309ADEF0039
	const TiXmlDocument* GetDocument() const;
	//##ModelId=4309ADEF003E
	TiXmlDocument* GetDocument();

	/// Returns true if this node has no children.
	//##ModelId=4309ADEF003F
	bool NoChildren() const						{ return !firstChild; }

	//##ModelId=4309ADEF0041
	const TiXmlDocument* ToDocument()	const		{ return ( this && type == DOCUMENT ) ? (const TiXmlDocument*) this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4309ADEF0043
	const TiXmlElement*  ToElement() const			{ return ( this && type == ELEMENT  ) ? (const TiXmlElement*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4309ADEF0049
	const TiXmlComment*  ToComment() const			{ return ( this && type == COMMENT  ) ? (const TiXmlComment*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4309ADEF004B
	const TiXmlUnknown*  ToUnknown() const			{ return ( this && type == UNKNOWN  ) ? (const TiXmlUnknown*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4309ADEF004D
	const TiXmlText*	   ToText()    const		{ return ( this && type == TEXT     ) ? (const TiXmlText*)     this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4309ADEF0052
	const TiXmlDeclaration* ToDeclaration() const	{ return ( this && type == DECLARATION ) ? (const TiXmlDeclaration*) this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.

	//##ModelId=4309ADEF0054
	TiXmlDocument* ToDocument()			{ return ( this && type == DOCUMENT ) ? (TiXmlDocument*) this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4309ADEF0055
	TiXmlElement*  ToElement()			{ return ( this && type == ELEMENT  ) ? (TiXmlElement*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4309ADEF0056
	TiXmlComment*  ToComment()			{ return ( this && type == COMMENT  ) ? (TiXmlComment*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4309ADEF005C
	TiXmlUnknown*  ToUnknown()			{ return ( this && type == UNKNOWN  ) ? (TiXmlUnknown*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4309ADEF005D
	TiXmlText*	   ToText()   			{ return ( this && type == TEXT     ) ? (TiXmlText*)     this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4309ADEF005E
	TiXmlDeclaration* ToDeclaration()	{ return ( this && type == DECLARATION ) ? (TiXmlDeclaration*) this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.

	/** Create an exact duplicate of this node and return it. The memory must be deleted
		by the caller. 
	*/
	//##ModelId=4309ADEF005F
	virtual TiXmlNode* Clone() const = 0;

protected:
	//##ModelId=4309ADEF0066
	TiXmlNode( NodeType _type );

	// Copy to the allocated object. Shared functionality between Clone, Copy constructor,
	// and the assignment operator.
	//##ModelId=4309ADEF0068
	void CopyTo( TiXmlNode* target ) const;

	#ifdef TIXML_USE_STL
	    // The real work of the input operator.
	//##ModelId=4309ADEF006B
	    virtual void StreamIn( TIXML_ISTREAM* in, TIXML_STRING* tag ) = 0;
	#endif

	// Figure out what is at *p, and parse it. Returns null if it is not an xml node.
	//##ModelId=4309ADEF0073
	TiXmlNode* Identify( const char* start, TiXmlEncoding encoding );

	// Internal Value function returning a TIXML_STRING
	//##ModelId=4309ADEF007B
	const TIXML_STRING& SValue() const	{ return value ; }

	//##ModelId=4309AF6E0286
	TiXmlNode*		parent;
	//##ModelId=4309AF6E028E
	NodeType		type;

	//##ModelId=4309AF6E029A
	TiXmlNode*		firstChild;
	//##ModelId=4309AF6E02A4
	TiXmlNode*		lastChild;

	//##ModelId=4309AF6E02AC
	TIXML_STRING	value;

	//##ModelId=4309AF6E02B8
	TiXmlNode*		prev;
	//##ModelId=4309AF6E02C2
	TiXmlNode*		next;

private:
	//##ModelId=4309ADEF00AC
	TiXmlNode( const TiXmlNode& );				// not implemented.
	//##ModelId=4309ADEF00AE
	void operator=( const TiXmlNode& base );	// not allowed.
};


/** An attribute is a name-value pair. Elements have an arbitrary
	number of attributes, each with a unique name.

	@note The attributes are not TiXmlNodes, since they are not
		  part of the tinyXML document object model. There are other
		  suggested ways to look at this problem.
*/
//##ModelId=4309ADEF02C8
class TiXmlAttribute : public TiXmlBase
{
	friend class TiXmlAttributeSet;

public:
	/// Construct an empty attribute.
	//##ModelId=4309ADEF02DE
	TiXmlAttribute() : TiXmlBase()
	{
		document = 0;
		prev = next = 0;
	}

	#ifdef TIXML_USE_STL
	/// std::string constructor.
	//##ModelId=4309ADEF02DF
	TiXmlAttribute( const std::string& _name, const std::string& _value )
	{
		name = _name;
		value = _value;
		document = 0;
		prev = next = 0;
	}
	#endif

	/// Construct an attribute with a name and value.
	//##ModelId=4309ADEF02E2
	TiXmlAttribute( const char * _name, const char * _value )
	{
		name = _name;
		value = _value;
		document = 0;
		prev = next = 0;
	}

	//##ModelId=4309ADEF02E9
	const char*		Name()  const		{ return name.c_str (); }		///< Return the name of this attribute.
	//##ModelId=4309ADEF02EB
	const char*		Value() const		{ return value.c_str (); }		///< Return the value of this attribute.
	//##ModelId=4309ADEF02ED
	const int       IntValue() const;									///< Return the value of this attribute, converted to an integer.
	//##ModelId=4309ADEF02F2
	const double	DoubleValue() const;								///< Return the value of this attribute, converted to a double.

	/** QueryIntValue examines the value string. It is an alternative to the
		IntValue() method with richer error checking.
		If the value is an integer, it is stored in 'value' and 
		the call returns TIXML_SUCCESS. If it is not
		an integer, it returns TIXML_WRONG_TYPE.

		A specialized but useful call. Note that for success it returns 0,
		which is the opposite of almost all other TinyXml calls.
	*/
	//##ModelId=4309ADEF02F4
	int QueryIntValue( int* value ) const;
	/// QueryDoubleValue examines the value string. See QueryIntValue().
	//##ModelId=4309ADEF02FB
	int QueryDoubleValue( double* value ) const;

	//##ModelId=4309ADEF02FE
	void SetName( const char* _name )	{ name = _name; }				///< Set the name of this attribute.
	//##ModelId=4309ADEF0300
	void SetValue( const char* _value )	{ value = _value; }				///< Set the value.

	//##ModelId=4309ADEF0306
	void SetIntValue( int value );										///< Set the value from an integer.
	//##ModelId=4309ADEF0308
	void SetDoubleValue( double value );								///< Set the value from a double.

    #ifdef TIXML_USE_STL
	/// STL std::string form.
	//##ModelId=4309ADEF030A
	void SetName( const std::string& _name )	
	{	
		StringToBuffer buf( _name );
		SetName ( buf.buffer ? buf.buffer : "error" );	
	}
	/// STL std::string form.	
	//##ModelId=4309ADEF0310
	void SetValue( const std::string& _value )	
	{	
		StringToBuffer buf( _value );
		SetValue( buf.buffer ? buf.buffer : "error" );	
	}
	#endif

	/// Get the next sibling attribute in the DOM. Returns null at end.
	//##ModelId=4309ADEF0312
	const TiXmlAttribute* Next() const;
	//##ModelId=4309ADEF0319
	TiXmlAttribute* Next();
	/// Get the previous sibling attribute in the DOM. Returns null at beginning.
	//##ModelId=4309ADEF031A
	const TiXmlAttribute* Previous() const;
	//##ModelId=4309ADEF031C
	TiXmlAttribute* Previous();

	//##ModelId=4309ADEF031D
	bool operator==( const TiXmlAttribute& rhs ) const { return rhs.name == name; }
	//##ModelId=4309ADEF0323
	bool operator<( const TiXmlAttribute& rhs )	 const { return name < rhs.name; }
	//##ModelId=4309ADEF0326
	bool operator>( const TiXmlAttribute& rhs )  const { return name > rhs.name; }

	/*	Attribute parsing starts: first letter of the name
						 returns: the next char after the value end quote
	*/
	//##ModelId=4309ADEF0329
	virtual const char* Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding );

	// Prints this Attribute to a FILE stream.
	//##ModelId=4309ADEF0330
	virtual void Print( FILE* cfile, int depth ) const;

	//##ModelId=4309ADEF0337
	virtual void StreamOut( TIXML_OSTREAM * out ) const;
	// [internal use]
	// Set the document pointer so the attribute can report errors.
	//##ModelId=4309ADEF033A
	void SetDocument( TiXmlDocument* doc )	{ document = doc; }

private:
	//##ModelId=4309ADEF033C
	TiXmlAttribute( const TiXmlAttribute& );				// not implemented.
	//##ModelId=4309ADEF0342
	void operator=( const TiXmlAttribute& base );	// not allowed.

	//##ModelId=4309AF6F004B
	TiXmlDocument*	document;	// A pointer back to a document, for error reporting.
	//##ModelId=4309AF6F0050
	TIXML_STRING name;
	//##ModelId=4309AF6F0055
	TIXML_STRING value;
	//##ModelId=4309AF6F0061
	TiXmlAttribute*	prev;
	//##ModelId=4309AF6F006B
	TiXmlAttribute*	next;
};


/*	A class used to manage a group of attributes.
	It is only used internally, both by the ELEMENT and the DECLARATION.
	
	The set can be changed transparent to the Element and Declaration
	classes that use it, but NOT transparent to the Attribute
	which has to implement a next() and previous() method. Which makes
	it a bit problematic and prevents the use of STL.

	This version is implemented with circular lists because:
		- I like circular lists
		- it demonstrates some independence from the (typical) doubly linked list.
*/
//##ModelId=4309ADF00035
class TiXmlAttributeSet
{
public:
	//##ModelId=4309ADF0003F
	TiXmlAttributeSet();
	//##ModelId=4309ADF00040
	~TiXmlAttributeSet();

	//##ModelId=4309ADF00049
	void Add( TiXmlAttribute* attribute );
	//##ModelId=4309ADF0004B
	void Remove( TiXmlAttribute* attribute );

	//##ModelId=4309ADF0004D
	const TiXmlAttribute* First()	const	{ return ( sentinel.next == &sentinel ) ? 0 : sentinel.next; }
	//##ModelId=4309ADF0004F
	TiXmlAttribute* First()					{ return ( sentinel.next == &sentinel ) ? 0 : sentinel.next; }
	//##ModelId=4309ADF00053
	const TiXmlAttribute* Last() const		{ return ( sentinel.prev == &sentinel ) ? 0 : sentinel.prev; }
	//##ModelId=4309ADF00055
	TiXmlAttribute* Last()					{ return ( sentinel.prev == &sentinel ) ? 0 : sentinel.prev; }

	//##ModelId=4309ADF00056
	const TiXmlAttribute*	Find( const char * name ) const;
	//##ModelId=4309ADF0005D
	TiXmlAttribute*	Find( const char * name );

private:
	//*ME:	Because of hidden/disabled copy-construktor in TiXmlAttribute (sentinel-element),
	//*ME:	this class must be also use a hidden/disabled copy-constructor !!!
	//##ModelId=4309ADF0005F
	TiXmlAttributeSet( const TiXmlAttributeSet& );	// not allowed
	//##ModelId=4309ADF00061
	void operator=( const TiXmlAttributeSet& );	// not allowed (as TiXmlAttribute)

	//##ModelId=4309AF6F00EB
	TiXmlAttribute sentinel;
};


/** The element is a container class. It has a value, the element name,
	and can contain other elements, text, comments, and unknowns.
	Elements also contain an arbitrary number of attributes.
*/
//##ModelId=4309ADF0023E
class TiXmlElement : public TiXmlNode
{
public:
	/// Construct an element.
	//##ModelId=4309ADF00252
	TiXmlElement (const char * in_value);

	#ifdef TIXML_USE_STL
	/// std::string constructor.
	//##ModelId=4309ADF00254
	TiXmlElement( const std::string& _value );
	#endif

	//##ModelId=4309ADF00256
	TiXmlElement( const TiXmlElement& );

	//##ModelId=4309ADF0025C
	void operator=( const TiXmlElement& base );

	//##ModelId=4309ADF0025E
	virtual ~TiXmlElement();

	/** Given an attribute name, Attribute() returns the value
		for the attribute of that name, or null if none exists.
	*/
	//##ModelId=4309ADF00260
	const char* Attribute( const char* name ) const;

	/** Given an attribute name, Attribute() returns the value
		for the attribute of that name, or null if none exists.
		If the attribute exists and can be converted to an integer,
		the integer value will be put in the return 'i', if 'i'
		is non-null.
	*/
	//##ModelId=4309ADF00266
	const char* Attribute( const char* name, int* i ) const;

	/** Given an attribute name, Attribute() returns the value
		for the attribute of that name, or null if none exists.
		If the attribute exists and can be converted to an double,
		the double value will be put in the return 'd', if 'd'
		is non-null.
	*/
	//##ModelId=4309ADF0026A
	const char* Attribute( const char* name, double* d ) const;

	/** QueryIntAttribute examines the attribute - it is an alternative to the
		Attribute() method with richer error checking.
		If the attribute is an integer, it is stored in 'value' and 
		the call returns TIXML_SUCCESS. If it is not
		an integer, it returns TIXML_WRONG_TYPE. If the attribute
		does not exist, then TIXML_NO_ATTRIBUTE is returned.
	*/	
	//##ModelId=4309ADF00271
	int QueryIntAttribute( const char* name, int* value ) const;
	/// QueryDoubleAttribute examines the attribute - see QueryIntAttribute().
	//##ModelId=4309ADF00275
	int QueryDoubleAttribute( const char* name, double* value ) const;
	/// QueryFloatAttribute examines the attribute - see QueryIntAttribute().
	//##ModelId=4309ADF0027C
	int QueryDoubleAttribute( const char* name, float* value ) const {
		double d;
		int result = QueryDoubleAttribute( name, &d );
		*value = (float)d;
		return result;
	}

	/** Sets an attribute of name to a given value. The attribute
		will be created if it does not exist, or changed if it does.
	*/
	//##ModelId=4309ADF00280
	void SetAttribute( const char* name, const char * value );

    #ifdef TIXML_USE_STL
	//##ModelId=4309ADF00286
	const char* Attribute( const std::string& name ) const				{ return Attribute( name.c_str() ); }
	//##ModelId=4309ADF00289
	const char* Attribute( const std::string& name, int* i ) const		{ return Attribute( name.c_str(), i ); }
	//##ModelId=4309ADF00290
	const char* Attribute( const std::string& name, double* d ) const	{ return Attribute( name.c_str(), d ); }
	//##ModelId=4309ADF00294
	int QueryIntAttribute( const std::string& name, int* value ) const	{ return QueryIntAttribute( name.c_str(), value ); }
	//##ModelId=4309ADF0029A
	int QueryDoubleAttribute( const std::string& name, double* value ) const { return QueryDoubleAttribute( name.c_str(), value ); }

	/// STL std::string form.
	//##ModelId=4309ADF0029E
	void SetAttribute( const std::string& name, const std::string& _value )	
	{	
		StringToBuffer n( name );
		StringToBuffer v( _value );
		if ( n.buffer && v.buffer )
			SetAttribute (n.buffer, v.buffer );	
	}	
	///< STL std::string form.
	//##ModelId=4309ADF002A4
	void SetAttribute( const std::string& name, int _value )	
	{	
		StringToBuffer n( name );
		if ( n.buffer )
			SetAttribute (n.buffer, _value);	
	}	
	#endif

	/** Sets an attribute of name to a given value. The attribute
		will be created if it does not exist, or changed if it does.
	*/
	//##ModelId=4309ADF002A7
	void SetAttribute( const char * name, int value );

	/** Sets an attribute of name to a given value. The attribute
		will be created if it does not exist, or changed if it does.
	*/
	//##ModelId=4309ADF002AE
	void SetDoubleAttribute( const char * name, double value );

	/** Deletes an attribute with the given name.
	*/
	//##ModelId=4309ADF002B1
	void RemoveAttribute( const char * name );
    #ifdef TIXML_USE_STL
	//##ModelId=4309ADF002B7
	void RemoveAttribute( const std::string& name )	{	RemoveAttribute (name.c_str ());	}	///< STL std::string form.
	#endif

	//##ModelId=4309ADF002B9
	const TiXmlAttribute* FirstAttribute() const	{ return attributeSet.First(); }		///< Access the first attribute in this element.
	//##ModelId=4309ADF002BB
	TiXmlAttribute* FirstAttribute() 				{ return attributeSet.First(); }
	//##ModelId=4309ADF002C0
	const TiXmlAttribute* LastAttribute()	const 	{ return attributeSet.Last(); }		///< Access the last attribute in this element.
	//##ModelId=4309ADF002C2
	TiXmlAttribute* LastAttribute()					{ return attributeSet.Last(); }

	/// Creates a new Element and returns it - the returned element is a copy.
	//##ModelId=4309ADF002C3
	virtual TiXmlNode* Clone() const;
	// Print the Element to a FILE stream.
	//##ModelId=4309ADF002C5
	virtual void Print( FILE* cfile, int depth ) const;

	/*	Attribtue parsing starts: next char past '<'
						 returns: next char past '>'
	*/
	//##ModelId=4309ADF002CC
	virtual const char* Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding );

protected:

	//##ModelId=4309ADF002D4
	void CopyTo( TiXmlElement* target ) const;
	//##ModelId=4309ADF002D7
	void ClearThis();	// like clear, but initializes 'this' object as well

	// Used to be public [internal use]
	#ifdef TIXML_USE_STL
	//##ModelId=4309ADF002D8
	    virtual void StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag );
	#endif
	//##ModelId=4309ADF002E1
	virtual void StreamOut( TIXML_OSTREAM * out ) const;

	/*	[internal use]
		Reads the "value" of the element -- another element, or text.
		This should terminate with the current end tag.
	*/
	//##ModelId=4309ADF002E4
	const char* ReadValue( const char* in, TiXmlParsingData* prevData, TiXmlEncoding encoding );

private:

	//##ModelId=4309AF6F0253
	TiXmlAttributeSet attributeSet;
};


/**	An XML comment.
*/
//##ModelId=4309ADF00388
class TiXmlComment : public TiXmlNode
{
public:
	/// Constructs an empty comment.
	//##ModelId=4309ADF00393
	TiXmlComment() : TiXmlNode( TiXmlNode::COMMENT ) {}
	//##ModelId=4309ADF00394
	TiXmlComment( const TiXmlComment& );
	//##ModelId=4309ADF0039C
	void operator=( const TiXmlComment& base );

	//##ModelId=4309ADF0039E
	virtual ~TiXmlComment()	{}

	/// Returns a copy of this Comment.
	//##ModelId=4309ADF003A0
	virtual TiXmlNode* Clone() const;
	/// Write this Comment to a FILE stream.
	//##ModelId=4309ADF003A2
	virtual void Print( FILE* cfile, int depth ) const;

	/*	Attribtue parsing starts: at the ! of the !--
						 returns: next char past '>'
	*/
	//##ModelId=4309ADF003A8
	virtual const char* Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding );

protected:
	//##ModelId=4309ADF003B0
	void CopyTo( TiXmlComment* target ) const;

	// used to be public
	#ifdef TIXML_USE_STL
	//##ModelId=4309ADF003B3
	    virtual void StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag );
	#endif
	//##ModelId=4309ADF003BD
	virtual void StreamOut( TIXML_OSTREAM * out ) const;

private:

};


/** XML text. Contained in an element.
*/
//##ModelId=4309ADF1007D
class TiXmlText : public TiXmlNode
{
	friend class TiXmlElement;
public:
	/// Constructor.
	//##ModelId=4309ADF10092
	TiXmlText (const char * initValue) : TiXmlNode (TiXmlNode::TEXT)
	{
		SetValue( initValue );
	}
	//##ModelId=4309ADF10094
	virtual ~TiXmlText() {}

	#ifdef TIXML_USE_STL
	/// Constructor.
	//##ModelId=4309ADF10096
	TiXmlText( const std::string& initValue ) : TiXmlNode (TiXmlNode::TEXT)
	{
		SetValue( initValue );
	}
	#endif

	//##ModelId=4309ADF1009B
	TiXmlText( const TiXmlText& copy ) : TiXmlNode( TiXmlNode::TEXT )	{ copy.CopyTo( this ); }
	//##ModelId=4309ADF1009D
	void operator=( const TiXmlText& base )							 	{ base.CopyTo( this ); }

	/// Write this text object to a FILE stream.
	//##ModelId=4309ADF1009F
	virtual void Print( FILE* cfile, int depth ) const;

	//##ModelId=4309ADF100A6
	virtual const char* Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding );

protected :
	///  [internal use] Creates a new Element and returns it.
	//##ModelId=4309ADF100B3
	virtual TiXmlNode* Clone() const;
	//##ModelId=4309ADF100B5
	void CopyTo( TiXmlText* target ) const;

	//##ModelId=4309ADF100BB
	virtual void StreamOut ( TIXML_OSTREAM * out ) const;
	//##ModelId=4309ADF100BE
	bool Blank() const;	// returns true if all white space and new lines
	// [internal use]
	#ifdef TIXML_USE_STL
	//##ModelId=4309ADF100C3
	    virtual void StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag );
	#endif

private:
};


/** In correct XML the declaration is the first entry in the file.
	@verbatim
		<?xml version="1.0" standalone="yes"?>
	@endverbatim

	TinyXml will happily read or write files without a declaration,
	however. There are 3 possible attributes to the declaration:
	version, encoding, and standalone.

	Note: In this version of the code, the attributes are
	handled as special cases, not generic attributes, simply
	because there can only be at most 3 and they are always the same.
*/
//##ModelId=4309ADF101BD
class TiXmlDeclaration : public TiXmlNode
{
public:
	/// Construct an empty declaration.
	//##ModelId=4309ADF101D2
	TiXmlDeclaration()   : TiXmlNode( TiXmlNode::DECLARATION ) {}

#ifdef TIXML_USE_STL
	/// Constructor.
	//##ModelId=4309ADF101D3
	TiXmlDeclaration(	const std::string& _version,
						const std::string& _encoding,
						const std::string& _standalone );
#endif

	/// Construct.
	//##ModelId=4309ADF101DC
	TiXmlDeclaration(	const char* _version,
						const char* _encoding,
						const char* _standalone );

	//##ModelId=4309ADF101E0
	TiXmlDeclaration( const TiXmlDeclaration& copy );
	//##ModelId=4309ADF101E5
	void operator=( const TiXmlDeclaration& copy );

	//##ModelId=4309ADF101E7
	virtual ~TiXmlDeclaration()	{}

	/// Version. Will return an empty string if none was found.
	//##ModelId=4309ADF101E9
	const char *Version() const			{ return version.c_str (); }
	/// Encoding. Will return an empty string if none was found.
	//##ModelId=4309ADF101EB
	const char *Encoding() const		{ return encoding.c_str (); }
	/// Is this a standalone document?
	//##ModelId=4309ADF101EF
	const char *Standalone() const		{ return standalone.c_str (); }

	/// Creates a copy of this Declaration and returns it.
	//##ModelId=4309ADF101F1
	virtual TiXmlNode* Clone() const;
	/// Print this declaration to a FILE stream.
	//##ModelId=4309ADF101F3
	virtual void Print( FILE* cfile, int depth ) const;

	//##ModelId=4309ADF101FA
	virtual const char* Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding );

protected:
	//##ModelId=4309ADF101FF
	void CopyTo( TiXmlDeclaration* target ) const;
	// used to be public
	#ifdef TIXML_USE_STL
	//##ModelId=4309ADF10205
	    virtual void StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag );
	#endif
	//##ModelId=4309ADF10209
	virtual void StreamOut ( TIXML_OSTREAM * out) const;

private:

	//##ModelId=4309AF70004C
	TIXML_STRING version;
	//##ModelId=4309AF700056
	TIXML_STRING encoding;
	//##ModelId=4309AF700060
	TIXML_STRING standalone;
};


/** Any tag that tinyXml doesn't recognize is saved as an
	unknown. It is a tag of text, but should not be modified.
	It will be written back to the XML, unchanged, when the file
	is saved.

	DTD tags get thrown into TiXmlUnknowns.
*/
//##ModelId=4309ADF102AD
class TiXmlUnknown : public TiXmlNode
{
public:
	//##ModelId=4309ADF102B8
	TiXmlUnknown() : TiXmlNode( TiXmlNode::UNKNOWN )	{}
	//##ModelId=4309ADF102C1
	virtual ~TiXmlUnknown() {}

	//##ModelId=4309ADF102C3
	TiXmlUnknown( const TiXmlUnknown& copy ) : TiXmlNode( TiXmlNode::UNKNOWN )		{ copy.CopyTo( this ); }
	//##ModelId=4309ADF102C5
	void operator=( const TiXmlUnknown& copy )										{ copy.CopyTo( this ); }

	/// Creates a copy of this Unknown and returns it.
	//##ModelId=4309ADF102C7
	virtual TiXmlNode* Clone() const;
	/// Print this Unknown to a FILE stream.
	//##ModelId=4309ADF102CC
	virtual void Print( FILE* cfile, int depth ) const;

	//##ModelId=4309ADF102D0
	virtual const char* Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding );

protected:
	//##ModelId=4309ADF102D7
	void CopyTo( TiXmlUnknown* target ) const;

	#ifdef TIXML_USE_STL
	//##ModelId=4309ADF102DA
	    virtual void StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag );
	#endif
	//##ModelId=4309ADF102E1
	virtual void StreamOut ( TIXML_OSTREAM * out ) const;

private:

};


/** Always the top level node. A document binds together all the
	XML pieces. It can be saved, loaded, and printed to the screen.
	The 'value' of a document node is the xml file name.
*/
//##ModelId=4309ADF200A6
class TiXmlDocument : public TiXmlNode
{
public:
	/// Create an empty document, that has no name.
	//##ModelId=4309ADF200B1
	TiXmlDocument();
	/// Create a document with a name. The name of the document is also the filename of the xml.
	//##ModelId=4309ADF200BA
	TiXmlDocument( const char * documentName );

	#ifdef TIXML_USE_STL
	/// Constructor.
	//##ModelId=4309ADF200BC
	TiXmlDocument( const std::string& documentName );
	#endif

	//##ModelId=4309ADF200BE
	TiXmlDocument( const TiXmlDocument& copy );
	//##ModelId=4309ADF200C4
	void operator=( const TiXmlDocument& copy );

	//##ModelId=4309ADF200C6
	virtual ~TiXmlDocument() {}

	/** Load a file using the current document value.
		Returns true if successful. Will delete any existing
		document data before loading.
	*/
	//##ModelId=4309ADF200C8
	bool LoadFile( TiXmlEncoding encoding = TIXML_DEFAULT_ENCODING );
	/// Save a file using the current document value. Returns true if successful.
	//##ModelId=4309ADF200CA
	bool SaveFile() const;
	/// Load a file using the given filename. Returns true if successful.
	//##ModelId=4309ADF200CF
	bool LoadFile( const char * filename, TiXmlEncoding encoding = TIXML_DEFAULT_ENCODING );
	/// Save a file using the given filename. Returns true if successful.
	//##ModelId=4309ADF200D2
	bool SaveFile( const char * filename ) const;

	#ifdef TIXML_USE_STL
	//##ModelId=4309ADF200D8
	bool LoadFile( const std::string& filename, TiXmlEncoding encoding = TIXML_DEFAULT_ENCODING )			///< STL std::string version.
	{
		StringToBuffer f( filename );
		return ( f.buffer && LoadFile( f.buffer, encoding ));
	}
	//##ModelId=4309ADF200DB
	bool SaveFile( const std::string& filename ) const		///< STL std::string version.
	{
		StringToBuffer f( filename );
		return ( f.buffer && SaveFile( f.buffer ));
	}
	#endif

	/** Parse the given null terminated block of xml data. Passing in an encoding to this
		method (either TIXML_ENCODING_LEGACY or TIXML_ENCODING_UTF8 will force TinyXml
		to use that encoding, regardless of what TinyXml might otherwise try to detect.
	*/
	//##ModelId=4309ADF200E2
	virtual const char* Parse( const char* p, TiXmlParsingData* data = 0, TiXmlEncoding encoding = TIXML_DEFAULT_ENCODING );

	/** Get the root element -- the only top level element -- of the document.
		In well formed XML, there should only be one. TinyXml is tolerant of
		multiple elements at the document level.
	*/
	//##ModelId=4309ADF200E7
	const TiXmlElement* RootElement() const		{ return FirstChildElement(); }
	//##ModelId=4309ADF200EC
	TiXmlElement* RootElement()					{ return FirstChildElement(); }

	/** If an error occurs, Error will be set to true. Also,
		- The ErrorId() will contain the integer identifier of the error (not generally useful)
		- The ErrorDesc() method will return the name of the error. (very useful)
		- The ErrorRow() and ErrorCol() will return the location of the error (if known)
	*/	
	//##ModelId=4309ADF200ED
	bool Error() const						{ return error; }

	/// Contains a textual (english) description of the error if one occurs.
	//##ModelId=4309ADF200EF
	const char * ErrorDesc() const	{ return errorDesc.c_str (); }

	/** Generally, you probably want the error string ( ErrorDesc() ). But if you
		prefer the ErrorId, this function will fetch it.
	*/
	//##ModelId=4309ADF200F1
	const int ErrorId()	const				{ return errorId; }

	/** Returns the location (if known) of the error. The first column is column 1, 
		and the first row is row 1. A value of 0 means the row and column wasn't applicable
		(memory errors, for example, have no row/column) or the parser lost the error. (An
		error in the error reporting, in that case.)

		@sa SetTabSize, Row, Column
	*/
	//##ModelId=4309ADF200F3
	int ErrorRow()	{ return errorLocation.row+1; }
	//##ModelId=4309ADF200F6
	int ErrorCol()	{ return errorLocation.col+1; }	///< The column where the error occured. See ErrorRow()

	/** By calling this method, with a tab size
		greater than 0, the row and column of each node and attribute is stored
		when the file is loaded. Very useful for tracking the DOM back in to
		the source file.

		The tab size is required for calculating the location of nodes. If not
		set, the default of 4 is used. The tabsize is set per document. Setting
		the tabsize to 0 disables row/column tracking.

		Note that row and column tracking is not supported when using operator>>.

		The tab size needs to be enabled before the parse or load. Correct usage:
		@verbatim
		TiXmlDocument doc;
		doc.SetTabSize( 8 );
		doc.Load( "myfile.xml" );
		@endverbatim

		@sa Row, Column
	*/
	//##ModelId=4309ADF200F7
	void SetTabSize( int _tabsize )		{ tabsize = _tabsize; }

	//##ModelId=4309ADF200F9
	int TabSize() const	{ return tabsize; }

	/** If you have handled the error, it can be reset with this call. The error
		state is automatically cleared if you Parse a new XML block.
	*/
	//##ModelId=4309ADF20100
	void ClearError()						{	error = false; 
												errorId = 0; 
												errorDesc = ""; 
												errorLocation.row = errorLocation.col = 0; 
												//errorLocation.last = 0; 
											}

	/** Dump the document to standard out. */
	//##ModelId=4309ADF20101
	void Print() const						{ Print( stdout, 0 ); }

	/// Print this Document to a FILE stream.
	//##ModelId=4309ADF20103
	virtual void Print( FILE* cfile, int depth = 0 ) const;
	// [internal use]
	//##ModelId=4309ADF2010A
	void SetError( int err, const char* errorLocation, TiXmlParsingData* prevData, TiXmlEncoding encoding );

protected :
	//##ModelId=4309ADF2010F
	virtual void StreamOut ( TIXML_OSTREAM * out) const;
	// [internal use]
	//##ModelId=4309ADF20116
	virtual TiXmlNode* Clone() const;
	#ifdef TIXML_USE_STL
	//##ModelId=4309ADF20118
	    virtual void StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag );
	#endif

private:
	//##ModelId=4309ADF20120
	void CopyTo( TiXmlDocument* target ) const;

	//##ModelId=4309ADF20123
	bool error;
	//##ModelId=4309ADF20128
	int  errorId;
	//##ModelId=4309AF700287
	TIXML_STRING errorDesc;
	//##ModelId=4309ADF20137
	int tabsize;
	//##ModelId=4309AF700291
	TiXmlCursor errorLocation;
};


/**
	A TiXmlHandle is a class that wraps a node pointer with null checks; this is
	an incredibly useful thing. Note that TiXmlHandle is not part of the TinyXml
	DOM structure. It is a separate utility class.

	Take an example:
	@verbatim
	<Document>
		<Element attributeA = "valueA">
			<Child attributeB = "value1" />
			<Child attributeB = "value2" />
		</Element>
	<Document>
	@endverbatim

	Assuming you want the value of "attributeB" in the 2nd "Child" element, it's very 
	easy to write a *lot* of code that looks like:

	@verbatim
	TiXmlElement* root = document.FirstChildElement( "Document" );
	if ( root )
	{
		TiXmlElement* element = root->FirstChildElement( "Element" );
		if ( element )
		{
			TiXmlElement* child = element->FirstChildElement( "Child" );
			if ( child )
			{
				TiXmlElement* child2 = child->NextSiblingElement( "Child" );
				if ( child2 )
				{
					// Finally do something useful.
	@endverbatim

	And that doesn't even cover "else" cases. TiXmlHandle addresses the verbosity
	of such code. A TiXmlHandle checks for null	pointers so it is perfectly safe 
	and correct to use:

	@verbatim
	TiXmlHandle docHandle( &document );
	TiXmlElement* child2 = docHandle.FirstChild( "Document" ).FirstChild( "Element" ).Child( "Child", 1 ).Element();
	if ( child2 )
	{
		// do something useful
	@endverbatim

	Which is MUCH more concise and useful.

	It is also safe to copy handles - internally they are nothing more than node pointers.
	@verbatim
	TiXmlHandle handleCopy = handle;
	@endverbatim

	What they should not be used for is iteration:

	@verbatim
	int i=0; 
	while ( true )
	{
		TiXmlElement* child = docHandle.FirstChild( "Document" ).FirstChild( "Element" ).Child( "Child", i ).Element();
		if ( !child )
			break;
		// do something
		++i;
	}
	@endverbatim

	It seems reasonable, but it is in fact two embedded while loops. The Child method is 
	a linear walk to find the element, so this code would iterate much more than it needs 
	to. Instead, prefer:

	@verbatim
	TiXmlElement* child = docHandle.FirstChild( "Document" ).FirstChild( "Element" ).FirstChild( "Child" ).Element();

	for( child; child; child=child->NextSiblingElement() )
	{
		// do something
	}
	@endverbatim
*/
//##ModelId=4309ADF20241
class TiXmlHandle
{
public:
	/// Create a handle from any node (at any depth of the tree.) This can be a null pointer.
	//##ModelId=4309ADF2024B
	TiXmlHandle( TiXmlNode* node )					{ this->node = node; }
	/// Copy constructor
	//##ModelId=4309ADF2024D
	TiXmlHandle( const TiXmlHandle& ref )			{ this->node = ref.node; }
	//##ModelId=4309ADF20256
	TiXmlHandle operator=( const TiXmlHandle& ref ) { this->node = ref.node; return *this; }

	/// Return a handle to the first child node.
	//##ModelId=4309ADF20258
	TiXmlHandle FirstChild() const;
	/// Return a handle to the first child node with the given name.
	//##ModelId=4309ADF2025A
	TiXmlHandle FirstChild( const char * value ) const;
	/// Return a handle to the first child element.
	//##ModelId=4309ADF20260
	TiXmlHandle FirstChildElement() const;
	/// Return a handle to the first child element with the given name.
	//##ModelId=4309ADF20262
	TiXmlHandle FirstChildElement( const char * value ) const;

	/** Return a handle to the "index" child with the given name. 
		The first child is 0, the second 1, etc.
	*/
	//##ModelId=4309ADF20265
	TiXmlHandle Child( const char* value, int index ) const;
	/** Return a handle to the "index" child. 
		The first child is 0, the second 1, etc.
	*/
	//##ModelId=4309ADF2026B
	TiXmlHandle Child( int index ) const;
	/** Return a handle to the "index" child element with the given name. 
		The first child element is 0, the second 1, etc. Note that only TiXmlElements
		are indexed: other types are not counted.
	*/
	//##ModelId=4309ADF2026E
	TiXmlHandle ChildElement( const char* value, int index ) const;
	/** Return a handle to the "index" child element. 
		The first child element is 0, the second 1, etc. Note that only TiXmlElements
		are indexed: other types are not counted.
	*/
	//##ModelId=4309ADF20275
	TiXmlHandle ChildElement( int index ) const;

	#ifdef TIXML_USE_STL
	//##ModelId=4309ADF20278
	TiXmlHandle FirstChild( const std::string& _value ) const				{ return FirstChild( _value.c_str() ); }
	//##ModelId=4309ADF2027D
	TiXmlHandle FirstChildElement( const std::string& _value ) const		{ return FirstChildElement( _value.c_str() ); }

	//##ModelId=4309ADF20280
	TiXmlHandle Child( const std::string& _value, int index ) const			{ return Child( _value.c_str(), index ); }
	//##ModelId=4309ADF20284
	TiXmlHandle ChildElement( const std::string& _value, int index ) const	{ return ChildElement( _value.c_str(), index ); }
	#endif

	/// Return the handle as a TiXmlNode. This may return null.
	//##ModelId=4309ADF2028A
	TiXmlNode* Node() const			{ return node; } 
	/// Return the handle as a TiXmlElement. This may return null.
	//##ModelId=4309ADF2028C
	TiXmlElement* Element() const	{ return ( ( node && node->ToElement() ) ? node->ToElement() : 0 ); }
	/// Return the handle as a TiXmlText. This may return null.
	//##ModelId=4309ADF2028E
	TiXmlText* Text() const			{ return ( ( node && node->ToText() ) ? node->ToText() : 0 ); }
	/// Return the handle as a TiXmlUnknown. This may return null;
	//##ModelId=4309ADF20292
	TiXmlUnknown* Unknown() const			{ return ( ( node && node->ToUnknown() ) ? node->ToUnknown() : 0 ); }

private:
	//##ModelId=4309AF7003B3
	TiXmlNode* node;
};

#ifdef _MSC_VER
#pragma warning( default : 4530 )
#pragma warning( default : 4786 )
#endif

#endif

