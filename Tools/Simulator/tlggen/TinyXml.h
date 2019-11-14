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
//##ModelId=4370A02A0383
struct TiXmlCursor
{
	//##ModelId=4370A02A038E
	TiXmlCursor()		{ Clear(); }
	//##ModelId=4370A02A038F
	void Clear()		{ row = col = -1; }

	//##ModelId=4370A02A0397
	int row;	// 0 based.
	//##ModelId=4370A02A0398
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
//##ModelId=4370A02A03D4
enum TiXmlEncoding
{
	//##ModelId=4370A02A03DF
	TIXML_ENCODING_UNKNOWN,
	//##ModelId=4370A02B0000
	TIXML_ENCODING_UTF8,
	//##ModelId=4370A02B0001
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
//##ModelId=4370A02B0264
class TiXmlBase
{
	friend class TiXmlNode;
	friend class TiXmlElement;
	friend class TiXmlDocument;

public:
	//##ModelId=4370A02B0265
	TiXmlBase()	:	userData(0) {}
	//##ModelId=4370A02B026E
	virtual ~TiXmlBase()					{}

	/**	All TinyXml classes can print themselves to a filestream.
		This is a formatted print, and will insert tabs and newlines.
		
		(For an unformatted stream, use the << operator.)
	*/
	//##ModelId=4370A02B0270
	virtual void Print( FILE* cfile, int depth ) const = 0;

	/**	The world does not agree on whether white space should be kept or
		not. In order to make everyone happy, these global, static functions
		are provided to set whether or not TinyXml will condense all white space
		into a single space or not. The default is to condense. Note changing this
		values is not thread safe.
	*/
	//##ModelId=4370A02B0278
	static void SetCondenseWhiteSpace( bool condense )		{ condenseWhiteSpace = condense; }

	/// Return the current white space setting.
	//##ModelId=4370A02B027B
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
	//##ModelId=4370A02B0282
	int Row() const			{ return location.row + 1; }
	//##ModelId=4370A02B0284
	int Column() const		{ return location.col + 1; }	///< See Row()

	//##ModelId=4370A02B0286
	void  SetUserData( void* user )			{ userData = user; }
	//##ModelId=4370A02B028D
	void* GetUserData()						{ return userData; }

	// Table that returs, for a given lead byte, the total number of bytes
	// in the UTF-8 sequence.
	//##ModelId=4370A02B028E
	static const int utf8ByteTable[256];

	//##ModelId=4370A02B0296
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
	//##ModelId=4370A02B0387
	class StringToBuffer
	{
	  public:
		//##ModelId=4370A02B0391
		StringToBuffer( const TIXML_STRING& str );
		//##ModelId=4370A02B0393
		~StringToBuffer();
		//##ModelId=4370A02B0394
		char* buffer;
	};

	//##ModelId=4370A02B02A0
	static const char*	SkipWhiteSpace( const char*, TiXmlEncoding encoding );
	//##ModelId=4370A02B02A4
	inline static bool	IsWhiteSpace( char c )		
	{ 
		return ( isspace( (unsigned char) c ) || c == '\n' || c == '\r' ); 
	}

	//##ModelId=4370A02B02AC
	virtual void StreamOut (TIXML_OSTREAM *) const = 0;

	#ifdef TIXML_USE_STL
	//##ModelId=4370A02B02B5
	    static bool	StreamWhiteSpace( TIXML_ISTREAM * in, TIXML_STRING * tag );
	//##ModelId=4370A02B02BE
	    static bool StreamTo( TIXML_ISTREAM * in, int character, TIXML_STRING * tag );
	#endif

	/*	Reads an XML name into the string provided. Returns
		a pointer just past the last character of the name,
		or 0 if the function has an error.
	*/
	//##ModelId=4370A02B02C9
	static const char* ReadName( const char* p, TIXML_STRING* name, TiXmlEncoding encoding );

	/*	Reads text. Returns a pointer past the given end tag.
		Wickedly complex options, but it keeps the (sensitive) code in one place.
	*/
	//##ModelId=4370A02B02D3
	static const char* ReadText(	const char* in,				// where to start
									TIXML_STRING* text,			// the string read
									bool ignoreWhiteSpace,		// whether to keep the white space
									const char* endTag,			// what ends this text
									bool ignoreCase,			// whether to ignore case in the end tag
									TiXmlEncoding encoding );	// the current encoding

	// If an entity has been found, transform it into a character.
	//##ModelId=4370A02B02E0
	static const char* GetEntity( const char* in, char* value, int* length, TiXmlEncoding encoding );

	// Get a character, while interpreting entities.
	// The length can be from 0 to 4 bytes.
	//##ModelId=4370A02B02EB
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
	//##ModelId=4370A02B02FC
	static void PutString( const TIXML_STRING& str, TIXML_OSTREAM* out );

	//##ModelId=4370A02B0305
	static void PutString( const TIXML_STRING& str, TIXML_STRING* out );

	// Return true if the next characters in the stream are any of the endTag sequences.
	// Ignore case only works for english, and should only be relied on when comparing
	// to Engilish words: StringEqual( p, "version", true ) is fine.
	//##ModelId=4370A02B0309
	static bool StringEqual(	const char* p,
								const char* endTag,
								bool ignoreCase,
								TiXmlEncoding encoding );

	//##ModelId=4370A02B0319
	static const char* errorString[ TIXML_ERROR_STRING_COUNT ];

	//##ModelId=4370A02B032E
	TiXmlCursor location;

    /// Field containing a generic user pointer
	//##ModelId=4370A02B0332
	void*			userData;
	
	// None of these methods are reliable for any language except English.
	// Good for approximation, not great for accuracy.
	//##ModelId=4370A02B0337
	static int IsAlpha( unsigned char anyByte, TiXmlEncoding encoding );
	//##ModelId=4370A02B0343
	static int IsAlphaNum( unsigned char anyByte, TiXmlEncoding encoding );
	//##ModelId=4370A02B034C
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
	//##ModelId=4370A02B0356
	static void ConvertUTF32ToUTF8( unsigned long input, char* output, int* length );

private:
	//##ModelId=4370A02B0360
	TiXmlBase( const TiXmlBase& );				// not implemented.
	//##ModelId=4370A02B0369
	void operator=( const TiXmlBase& base );	// not allowed.

	//##ModelId=4370A02B03A5
	struct Entity
	{
		//##ModelId=4370A02B03AF
		const char*     str;
		//##ModelId=4370A02B03B0
		unsigned int	strLength;
		//##ModelId=4370A02B03B9
		char		    chr;
	};
	enum
	{
		NUM_ENTITY = 5,
		MAX_ENTITY_LENGTH = 6

	};
	//##ModelId=4370A02B036C
	static Entity entity[ NUM_ENTITY ];
	//##ModelId=4370A02B0373
	static bool condenseWhiteSpace;
};


/** The parent class for everything in the Document Object Model.
	(Except for attributes).
	Nodes have siblings, a parent, and children. A node can be
	in a document, or stand on its own. The type of a TiXmlNode
	can be queried, and it can be cast to its more defined type.
*/
//##ModelId=4370A02D01AD
class TiXmlNode : public TiXmlBase
{
	friend class TiXmlDocument;
	friend class TiXmlElement;

public:
	#ifdef TIXML_USE_STL	

	    /** An input stream operator, for every class. Tolerant of newlines and
		    formatting, but doesn't expect them.
	    */
	//##ModelId=4370A02D037B
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
	//##ModelId=4370A02D0385
	    friend std::ostream& operator<< (std::ostream& out, const TiXmlNode& base);

		/// Appends the XML node or attribute to a std::string.
	//##ModelId=4370A02D0390
		friend std::string& operator<< (std::string& out, const TiXmlNode& base );

	#else
	    // Used internally, not part of the public API.
	    friend TIXML_OSTREAM& operator<< (TIXML_OSTREAM& out, const TiXmlNode& base);
	#endif

	/** The types of XML nodes supported by TinyXml. (All the
			unsupported types are picked up by UNKNOWN.)
	*/
	//##ModelId=43831BF80253
	enum NodeType
	{
		//##ModelId=43831BF80268
		DOCUMENT,
		//##ModelId=43831BF802E0
		ELEMENT,
		//##ModelId=43831BF802E1
		COMMENT,
		//##ModelId=43831BF802EA
		UNKNOWN,
		//##ModelId=43831BF802EB
		TEXT,
		//##ModelId=43831BF802F4
		DECLARATION,
		//##ModelId=43831BF802F5
		TYPECOUNT
	};

	//##ModelId=4370A02D01B8
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
	//##ModelId=4370A02D01C1
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
	//##ModelId=4370A02D01C3
	void SetValue(const char * _value) { value = _value;}

    #ifdef TIXML_USE_STL
	/// STL std::string form.
	//##ModelId=4370A02D01C5
	void SetValue( const std::string& _value )    
	{	  
		StringToBuffer buf( _value );
		SetValue( buf.buffer ? buf.buffer : "" );    	
	}	
	#endif

	/// Delete all the children of this node. Does not affect 'this'.
	//##ModelId=4370A02D01CC
	void Clear();

	/// One step up the DOM.
	//##ModelId=4370A02D01CD
	TiXmlNode* Parent()							{ return parent; }
	//##ModelId=4370A02D01D5
	const TiXmlNode* Parent() const				{ return parent; }

	//##ModelId=4370A02D01D7
	const TiXmlNode* FirstChild()	const	{ return firstChild; }		///< The first child of this node. Will be null if there are no children.
	//##ModelId=4370A02D01D9
	TiXmlNode* FirstChild()					{ return firstChild; }
	//##ModelId=4370A02D01DF
	const TiXmlNode* FirstChild( const char * value ) const;			///< The first child of this node with the matching 'value'. Will be null if none found.
	//##ModelId=4370A02D01EA
	TiXmlNode* FirstChild( const char * value );						///< The first child of this node with the matching 'value'. Will be null if none found.

	//##ModelId=4370A02D01EC
	const TiXmlNode* LastChild() const	{ return lastChild; }		/// The last child of this node. Will be null if there are no children.
	//##ModelId=4370A02D01EE
	TiXmlNode* LastChild()	{ return lastChild; }
	//##ModelId=4370A02D01F4
	const TiXmlNode* LastChild( const char * value ) const;			/// The last child of this node matching 'value'. Will be null if there are no children.
	//##ModelId=4370A02D01F7
	TiXmlNode* LastChild( const char * value );	

    #ifdef TIXML_USE_STL
	//##ModelId=4370A02D01FF
	const TiXmlNode* FirstChild( const std::string& _value ) const	{	return FirstChild (_value.c_str ());	}	///< STL std::string form.
	//##ModelId=4370A02D0202
	TiXmlNode* FirstChild( const std::string& _value )				{	return FirstChild (_value.c_str ());	}	///< STL std::string form.
	//##ModelId=4370A02D0209
	const TiXmlNode* LastChild( const std::string& _value ) const	{	return LastChild (_value.c_str ());	}	///< STL std::string form.
	//##ModelId=4370A02D020C
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
	//##ModelId=4370A02D0213
	const TiXmlNode* IterateChildren( const TiXmlNode* previous ) const;
	//##ModelId=4370A02D0216
	TiXmlNode* IterateChildren( TiXmlNode* previous );

	/// This flavor of IterateChildren searches for children with a particular 'value'
	//##ModelId=4370A02D021D
	const TiXmlNode* IterateChildren( const char * value, const TiXmlNode* previous ) const;
	//##ModelId=4370A02D0226
	TiXmlNode* IterateChildren( const char * value, TiXmlNode* previous );

    #ifdef TIXML_USE_STL
	//##ModelId=4370A02D0229
	const TiXmlNode* IterateChildren( const std::string& _value, const TiXmlNode* previous ) const	{	return IterateChildren (_value.c_str (), previous);	}	///< STL std::string form.
	//##ModelId=4370A02D0233
	TiXmlNode* IterateChildren( const std::string& _value, TiXmlNode* previous ) {	return IterateChildren (_value.c_str (), previous);	}	///< STL std::string form.
	#endif

	/** Add a new node related to this. Adds a child past the LastChild.
		Returns a pointer to the new object or NULL if an error occured.
	*/
	//##ModelId=4370A02D023B
	TiXmlNode* InsertEndChild( const TiXmlNode& addThis );


	/** Add a new node related to this. Adds a child past the LastChild.

		NOTE: the node to be added is passed by pointer, and will be
		henceforth owned (and deleted) by tinyXml. This method is efficient
		and avoids an extra copy, but should be used with care as it
		uses a different memory model than the other insert functions.

		@sa InsertEndChild
	*/
	//##ModelId=4370A02D023D
	TiXmlNode* LinkEndChild( TiXmlNode* addThis );

	/** Add a new node related to this. Adds a child before the specified child.
		Returns a pointer to the new object or NULL if an error occured.
	*/
	//##ModelId=4370A02D0245
	TiXmlNode* InsertBeforeChild( TiXmlNode* beforeThis, const TiXmlNode& addThis );

	/** Add a new node related to this. Adds a child after the specified child.
		Returns a pointer to the new object or NULL if an error occured.
	*/
	//##ModelId=4370A02D024E
	TiXmlNode* InsertAfterChild(  TiXmlNode* afterThis, const TiXmlNode& addThis );

	/** Replace a child of this node.
		Returns a pointer to the new object or NULL if an error occured.
	*/
	//##ModelId=4370A02D0251
	TiXmlNode* ReplaceChild( TiXmlNode* replaceThis, const TiXmlNode& withThis );

	/// Delete a child of this node.
	//##ModelId=4370A02D0259
	bool RemoveChild( TiXmlNode* removeThis );

	/// Navigate to a sibling node.
	//##ModelId=4370A02D025B
	const TiXmlNode* PreviousSibling() const			{ return prev; }
	//##ModelId=4370A02D0263
	TiXmlNode* PreviousSibling()						{ return prev; }

	/// Navigate to a sibling node.
	//##ModelId=4370A02D0264
	const TiXmlNode* PreviousSibling( const char * ) const;
	//##ModelId=4370A02D026C
	TiXmlNode* PreviousSibling( const char * );

    #ifdef TIXML_USE_STL
	//##ModelId=4370A02D026E
	const TiXmlNode* PreviousSibling( const std::string& _value ) const	{	return PreviousSibling (_value.c_str ());	}	///< STL std::string form.
	//##ModelId=4370A02D0276
	TiXmlNode* PreviousSibling( const std::string& _value ) 			{	return PreviousSibling (_value.c_str ());	}	///< STL std::string form.
	//##ModelId=4370A02D0278
	const TiXmlNode* NextSibling( const std::string& _value) const		{	return NextSibling (_value.c_str ());	}	///< STL std::string form.
	//##ModelId=4370A02D0281
	TiXmlNode* NextSibling( const std::string& _value) 					{	return NextSibling (_value.c_str ());	}	///< STL std::string form.
	#endif

	/// Navigate to a sibling node.
	//##ModelId=4370A02D0283
	const TiXmlNode* NextSibling() const				{ return next; }
	//##ModelId=4370A02D028A
	TiXmlNode* NextSibling()							{ return next; }

	/// Navigate to a sibling node with the given 'value'.
	//##ModelId=4370A02D028B
	const TiXmlNode* NextSibling( const char * ) const;
	//##ModelId=4370A02D028E
	TiXmlNode* NextSibling( const char * );

	/** Convenience function to get through elements.
		Calls NextSibling and ToElement. Will skip all non-Element
		nodes. Returns 0 if there is not another element.
	*/
	//##ModelId=4370A02D0295
	const TiXmlElement* NextSiblingElement() const;
	//##ModelId=4370A02D0297
	TiXmlElement* NextSiblingElement();

	/** Convenience function to get through elements.
		Calls NextSibling and ToElement. Will skip all non-Element
		nodes. Returns 0 if there is not another element.
	*/
	//##ModelId=4370A02D029E
	const TiXmlElement* NextSiblingElement( const char * ) const;
	//##ModelId=4370A02D02A1
	TiXmlElement* NextSiblingElement( const char * );

    #ifdef TIXML_USE_STL
	//##ModelId=4370A02D02A8
	const TiXmlElement* NextSiblingElement( const std::string& _value) const	{	return NextSiblingElement (_value.c_str ());	}	///< STL std::string form.
	//##ModelId=4370A02D02AB
	TiXmlElement* NextSiblingElement( const std::string& _value)				{	return NextSiblingElement (_value.c_str ());	}	///< STL std::string form.
	#endif

	/// Convenience function to get through elements.
	//##ModelId=4370A02D02B2
	const TiXmlElement* FirstChildElement()	const;
	//##ModelId=4370A02D02B4
	TiXmlElement* FirstChildElement();

	/// Convenience function to get through elements.
	//##ModelId=4370A02D02B5
	const TiXmlElement* FirstChildElement( const char * value ) const;
	//##ModelId=4370A02D02BE
	TiXmlElement* FirstChildElement( const char * value );

    #ifdef TIXML_USE_STL
	//##ModelId=4370A02D02C0
	const TiXmlElement* FirstChildElement( const std::string& _value ) const	{	return FirstChildElement (_value.c_str ());	}	///< STL std::string form.
	//##ModelId=4370A02D02C8
	TiXmlElement* FirstChildElement( const std::string& _value )				{	return FirstChildElement (_value.c_str ());	}	///< STL std::string form.
	#endif

	/** Query the type (as an enumerated value, above) of this node.
		The possible types are: DOCUMENT, ELEMENT, COMMENT,
								UNKNOWN, TEXT, and DECLARATION.
	*/
	//##ModelId=4370A02D02CA
	virtual int Type() const	{ return type; }

	/** Return a pointer to the Document this node lives in.
		Returns null if not in a document.
	*/
	//##ModelId=4370A02D02D1
	const TiXmlDocument* GetDocument() const;
	//##ModelId=4370A02D02D3
	TiXmlDocument* GetDocument();

	/// Returns true if this node has no children.
	//##ModelId=4370A02D02D4
	bool NoChildren() const						{ return !firstChild; }

	//##ModelId=4370A02D02DB
	const TiXmlDocument* ToDocument()	const		{ return ( this && type == DOCUMENT ) ? (const TiXmlDocument*) this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4370A02D02DD
	const TiXmlElement*  ToElement() const			{ return ( this && type == ELEMENT  ) ? (const TiXmlElement*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4370A02D02E4
	const TiXmlComment*  ToComment() const			{ return ( this && type == COMMENT  ) ? (const TiXmlComment*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4370A02D02E6
	const TiXmlUnknown*  ToUnknown() const			{ return ( this && type == UNKNOWN  ) ? (const TiXmlUnknown*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4370A02D02E8
	const TiXmlText*	   ToText()    const		{ return ( this && type == TEXT     ) ? (const TiXmlText*)     this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4370A02D02F0
	const TiXmlDeclaration* ToDeclaration() const	{ return ( this && type == DECLARATION ) ? (const TiXmlDeclaration*) this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.

	//##ModelId=4370A02D02F2
	TiXmlDocument* ToDocument()			{ return ( this && type == DOCUMENT ) ? (TiXmlDocument*) this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4370A02D02F3
	TiXmlElement*  ToElement()			{ return ( this && type == ELEMENT  ) ? (TiXmlElement*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4370A02D02F9
	TiXmlComment*  ToComment()			{ return ( this && type == COMMENT  ) ? (TiXmlComment*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4370A02D02FA
	TiXmlUnknown*  ToUnknown()			{ return ( this && type == UNKNOWN  ) ? (TiXmlUnknown*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4370A02D02FB
	TiXmlText*	   ToText()   			{ return ( this && type == TEXT     ) ? (TiXmlText*)     this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	//##ModelId=4370A02D0303
	TiXmlDeclaration* ToDeclaration()	{ return ( this && type == DECLARATION ) ? (TiXmlDeclaration*) this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.

	/** Create an exact duplicate of this node and return it. The memory must be deleted
		by the caller. 
	*/
	//##ModelId=4370A02D0304
	virtual TiXmlNode* Clone() const = 0;

protected:
	//##ModelId=4370A02D0306
	TiXmlNode( NodeType _type );

	// Copy to the allocated object. Shared functionality between Clone, Copy constructor,
	// and the assignment operator.
	//##ModelId=4370A02D030E
	void CopyTo( TiXmlNode* target ) const;

	#ifdef TIXML_USE_STL
	    // The real work of the input operator.
	//##ModelId=4370A02D0317
	    virtual void StreamIn( TIXML_ISTREAM* in, TIXML_STRING* tag ) = 0;
	#endif

	// Figure out what is at *p, and parse it. Returns null if it is not an xml node.
	//##ModelId=4370A02D031B
	TiXmlNode* Identify( const char* start, TiXmlEncoding encoding );

	// Internal Value function returning a TIXML_STRING
	//##ModelId=4370A02D0323
	const TIXML_STRING& SValue() const	{ return value ; }

	//##ModelId=4370A02D032E
	TiXmlNode*		parent;
	//##ModelId=4370A02D0336
	NodeType		type;

	//##ModelId=4370A02D033F
	TiXmlNode*		firstChild;
	//##ModelId=4370A02D0344
	TiXmlNode*		lastChild;

	//##ModelId=4370A02D034A
	TIXML_STRING	value;

	//##ModelId=4370A02D0356
	TiXmlNode*		prev;
	//##ModelId=4370A02D0360
	TiXmlNode*		next;

private:
	//##ModelId=4370A02D0367
	TiXmlNode( const TiXmlNode& );				// not implemented.
	//##ModelId=4370A02D0371
	void operator=( const TiXmlNode& base );	// not allowed.
};


/** An attribute is a name-value pair. Elements have an arbitrary
	number of attributes, each with a unique name.

	@note The attributes are not TiXmlNodes, since they are not
		  part of the tinyXML document object model. There are other
		  suggested ways to look at this problem.
*/
//##ModelId=4370A02E020C
class TiXmlAttribute : public TiXmlBase
{
	friend class TiXmlAttributeSet;

public:
	/// Construct an empty attribute.
	//##ModelId=4370A02E0217
	TiXmlAttribute() : TiXmlBase()
	{
		document = 0;
		prev = next = 0;
	}

	#ifdef TIXML_USE_STL
	/// std::string constructor.
	//##ModelId=4370A02E0218
	TiXmlAttribute( const std::string& _name, const std::string& _value )
	{
		name = _name;
		value = _value;
		document = 0;
		prev = next = 0;
	}
	#endif

	/// Construct an attribute with a name and value.
	//##ModelId=4370A02E0221
	TiXmlAttribute( const char * _name, const char * _value )
	{
		name = _name;
		value = _value;
		document = 0;
		prev = next = 0;
	}

	//##ModelId=4370A02E0224
	const char*		Name()  const		{ return name.c_str (); }		///< Return the name of this attribute.
	//##ModelId=4370A02E022B
	const char*		Value() const		{ return value.c_str (); }		///< Return the value of this attribute.
	//##ModelId=4370A02E022D
	const int       IntValue() const;									///< Return the value of this attribute, converted to an integer.
	//##ModelId=4370A02E0234
	const double	DoubleValue() const;								///< Return the value of this attribute, converted to a double.

	/** QueryIntValue examines the value string. It is an alternative to the
		IntValue() method with richer error checking.
		If the value is an integer, it is stored in 'value' and 
		the call returns TIXML_SUCCESS. If it is not
		an integer, it returns TIXML_WRONG_TYPE.

		A specialized but useful call. Note that for success it returns 0,
		which is the opposite of almost all other TinyXml calls.
	*/
	//##ModelId=4370A02E0236
	int QueryIntValue( int* value ) const;
	/// QueryDoubleValue examines the value string. See QueryIntValue().
	//##ModelId=4370A02E0239
	int QueryDoubleValue( double* value ) const;

	//##ModelId=4370A02E0240
	void SetName( const char* _name )	{ name = _name; }				///< Set the name of this attribute.
	//##ModelId=4370A02E0242
	void SetValue( const char* _value )	{ value = _value; }				///< Set the value.

	//##ModelId=4370A02E0249
	void SetIntValue( int value );										///< Set the value from an integer.
	//##ModelId=4370A02E024B
	void SetDoubleValue( double value );								///< Set the value from a double.

    #ifdef TIXML_USE_STL
	/// STL std::string form.
	//##ModelId=4370A02E0253
	void SetName( const std::string& _name )	
	{	
		StringToBuffer buf( _name );
		SetName ( buf.buffer ? buf.buffer : "error" );	
	}
	/// STL std::string form.	
	//##ModelId=4370A02E0255
	void SetValue( const std::string& _value )	
	{	
		StringToBuffer buf( _value );
		SetValue( buf.buffer ? buf.buffer : "error" );	
	}
	#endif

	/// Get the next sibling attribute in the DOM. Returns null at end.
	//##ModelId=4370A02E025D
	const TiXmlAttribute* Next() const;
	//##ModelId=4370A02E025F
	TiXmlAttribute* Next();
	/// Get the previous sibling attribute in the DOM. Returns null at beginning.
	//##ModelId=4370A02E0266
	const TiXmlAttribute* Previous() const;
	//##ModelId=4370A02E0268
	TiXmlAttribute* Previous();

	//##ModelId=4370A02E0269
	bool operator==( const TiXmlAttribute& rhs ) const { return rhs.name == name; }
	//##ModelId=4370A02E0270
	bool operator<( const TiXmlAttribute& rhs )	 const { return name < rhs.name; }
	//##ModelId=4370A02E0273
	bool operator>( const TiXmlAttribute& rhs )  const { return name > rhs.name; }

	/*	Attribute parsing starts: first letter of the name
						 returns: the next char after the value end quote
	*/
	//##ModelId=4370A02E027A
	virtual const char* Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding );

	// Prints this Attribute to a FILE stream.
	//##ModelId=4370A02E0284
	virtual void Print( FILE* cfile, int depth ) const;

	//##ModelId=4370A02E0288
	virtual void StreamOut( TIXML_OSTREAM * out ) const;
	// [internal use]
	// Set the document pointer so the attribute can report errors.
	//##ModelId=4370A02E028F
	void SetDocument( TiXmlDocument* doc )	{ document = doc; }

private:
	//##ModelId=4370A02E0291
	TiXmlAttribute( const TiXmlAttribute& );				// not implemented.
	//##ModelId=4370A02E0299
	void operator=( const TiXmlAttribute& base );	// not allowed.

	//##ModelId=4370A02E02A3
	TiXmlDocument*	document;	// A pointer back to a document, for error reporting.
	//##ModelId=4370A02E02A8
	TIXML_STRING name;
	//##ModelId=4370A02E02AD
	TIXML_STRING value;
	//##ModelId=4370A02E02B9
	TiXmlAttribute*	prev;
	//##ModelId=4370A02E02C3
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
//##ModelId=4370A02E039D
class TiXmlAttributeSet
{
public:
	//##ModelId=4370A02E03A7
	TiXmlAttributeSet();
	//##ModelId=4370A02E03A8
	~TiXmlAttributeSet();

	//##ModelId=4370A02E03A9
	void Add( TiXmlAttribute* attribute );
	//##ModelId=4370A02E03B2
	void Remove( TiXmlAttribute* attribute );

	//##ModelId=4370A02E03B4
	const TiXmlAttribute* First()	const	{ return ( sentinel.next == &sentinel ) ? 0 : sentinel.next; }
	//##ModelId=4370A02E03BC
	TiXmlAttribute* First()					{ return ( sentinel.next == &sentinel ) ? 0 : sentinel.next; }
	//##ModelId=4370A02E03BD
	const TiXmlAttribute* Last() const		{ return ( sentinel.prev == &sentinel ) ? 0 : sentinel.prev; }
	//##ModelId=4370A02E03BF
	TiXmlAttribute* Last()					{ return ( sentinel.prev == &sentinel ) ? 0 : sentinel.prev; }

	//##ModelId=4370A02E03C5
	const TiXmlAttribute*	Find( const char * name ) const;
	//##ModelId=4370A02E03C8
	TiXmlAttribute*	Find( const char * name );

private:
	//*ME:	Because of hidden/disabled copy-construktor in TiXmlAttribute (sentinel-element),
	//*ME:	this class must be also use a hidden/disabled copy-constructor !!!
	//##ModelId=4370A02E03CA
	TiXmlAttributeSet( const TiXmlAttributeSet& );	// not allowed
	//##ModelId=4370A02E03D0
	void operator=( const TiXmlAttributeSet& );	// not allowed (as TiXmlAttribute)

	//##ModelId=4370A02E03DA
	TiXmlAttribute sentinel;
};


/** The element is a container class. It has a value, the element name,
	and can contain other elements, text, comments, and unknowns.
	Elements also contain an arbitrary number of attributes.
*/
//##ModelId=4370A02F0238
class TiXmlElement : public TiXmlNode
{
public:
	/// Construct an element.
	//##ModelId=4370A02F023A
	TiXmlElement (const char * in_value);

	#ifdef TIXML_USE_STL
	/// std::string constructor.
	//##ModelId=4370A02F0243
	TiXmlElement( const std::string& _value );
	#endif

	//##ModelId=4370A02F0245
	TiXmlElement( const TiXmlElement& );

	//##ModelId=4370A02F024C
	void operator=( const TiXmlElement& base );

	//##ModelId=4370A02F024E
	virtual ~TiXmlElement();

	/** Given an attribute name, Attribute() returns the value
		for the attribute of that name, or null if none exists.
	*/
	//##ModelId=4370A02F0250
	const char* Attribute( const char* name ) const;

	/** Given an attribute name, Attribute() returns the value
		for the attribute of that name, or null if none exists.
		If the attribute exists and can be converted to an integer,
		the integer value will be put in the return 'i', if 'i'
		is non-null.
	*/
	//##ModelId=4370A02F0258
	const char* Attribute( const char* name, int* i ) const;

	/** Given an attribute name, Attribute() returns the value
		for the attribute of that name, or null if none exists.
		If the attribute exists and can be converted to an double,
		the double value will be put in the return 'd', if 'd'
		is non-null.
	*/
	//##ModelId=4370A02F0260
	const char* Attribute( const char* name, double* d ) const;

	/** QueryIntAttribute examines the attribute - it is an alternative to the
		Attribute() method with richer error checking.
		If the attribute is an integer, it is stored in 'value' and 
		the call returns TIXML_SUCCESS. If it is not
		an integer, it returns TIXML_WRONG_TYPE. If the attribute
		does not exist, then TIXML_NO_ATTRIBUTE is returned.
	*/	
	//##ModelId=4370A02F0264
	int QueryIntAttribute( const char* name, int* value ) const;
	/// QueryDoubleAttribute examines the attribute - see QueryIntAttribute().
	//##ModelId=4370A02F026D
	int QueryDoubleAttribute( const char* name, double* value ) const;
	/// QueryFloatAttribute examines the attribute - see QueryIntAttribute().
	//##ModelId=4370A02F0275
	int QueryDoubleAttribute( const char* name, float* value ) const {
		double d;
		int result = QueryDoubleAttribute( name, &d );
		*value = (float)d;
		return result;
	}

	/** Sets an attribute of name to a given value. The attribute
		will be created if it does not exist, or changed if it does.
	*/
	//##ModelId=4370A02F0279
	void SetAttribute( const char* name, const char * value );

    #ifdef TIXML_USE_STL
	//##ModelId=4370A02F0280
	const char* Attribute( const std::string& name ) const				{ return Attribute( name.c_str() ); }
	//##ModelId=4370A02F0288
	const char* Attribute( const std::string& name, int* i ) const		{ return Attribute( name.c_str(), i ); }
	//##ModelId=4370A02F028C
	const char* Attribute( const std::string& name, double* d ) const	{ return Attribute( name.c_str(), d ); }
	//##ModelId=4370A02F0295
	int QueryIntAttribute( const std::string& name, int* value ) const	{ return QueryIntAttribute( name.c_str(), value ); }
	//##ModelId=4370A02F029C
	int QueryDoubleAttribute( const std::string& name, double* value ) const { return QueryDoubleAttribute( name.c_str(), value ); }

	/// STL std::string form.
	//##ModelId=4370A02F02A0
	void SetAttribute( const std::string& name, const std::string& _value )	
	{	
		StringToBuffer n( name );
		StringToBuffer v( _value );
		if ( n.buffer && v.buffer )
			SetAttribute (n.buffer, v.buffer );	
	}	
	///< STL std::string form.
	//##ModelId=4370A02F02A8
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
	//##ModelId=4370A02F02B0
	void SetAttribute( const char * name, int value );

	/** Sets an attribute of name to a given value. The attribute
		will be created if it does not exist, or changed if it does.
	*/
	//##ModelId=4370A02F02B3
	void SetDoubleAttribute( const char * name, double value );

	/** Deletes an attribute with the given name.
	*/
	//##ModelId=4370A02F02BC
	void RemoveAttribute( const char * name );
    #ifdef TIXML_USE_STL
	//##ModelId=4370A02F02BE
	void RemoveAttribute( const std::string& name )	{	RemoveAttribute (name.c_str ());	}	///< STL std::string form.
	#endif

	//##ModelId=4370A02F02C5
	const TiXmlAttribute* FirstAttribute() const	{ return attributeSet.First(); }		///< Access the first attribute in this element.
	//##ModelId=4370A02F02C7
	TiXmlAttribute* FirstAttribute() 				{ return attributeSet.First(); }
	//##ModelId=4370A02F02CE
	const TiXmlAttribute* LastAttribute()	const 	{ return attributeSet.Last(); }		///< Access the last attribute in this element.
	//##ModelId=4370A02F02D0
	TiXmlAttribute* LastAttribute()					{ return attributeSet.Last(); }

	/// Creates a new Element and returns it - the returned element is a copy.
	//##ModelId=4370A02F02D1
	virtual TiXmlNode* Clone() const;
	// Print the Element to a FILE stream.
	//##ModelId=4370A02F02D8
	virtual void Print( FILE* cfile, int depth ) const;

	/*	Attribtue parsing starts: next char past '<'
						 returns: next char past '>'
	*/
	//##ModelId=4370A02F02DC
	virtual const char* Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding );

protected:

	//##ModelId=4370A02F02E5
	void CopyTo( TiXmlElement* target ) const;
	//##ModelId=4370A02F02ED
	void ClearThis();	// like clear, but initializes 'this' object as well

	// Used to be public [internal use]
	#ifdef TIXML_USE_STL
	//##ModelId=4370A02F02EE
	    virtual void StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag );
	#endif
	//##ModelId=4370A02F02F8
	virtual void StreamOut( TIXML_OSTREAM * out ) const;

	/*	[internal use]
		Reads the "value" of the element -- another element, or text.
		This should terminate with the current end tag.
	*/
	//##ModelId=4370A02F0300
	const char* ReadValue( const char* in, TiXmlParsingData* prevData, TiXmlEncoding encoding );

private:

	//##ModelId=4370A02F030C
	TiXmlAttributeSet attributeSet;
};


/**	An XML comment.
*/
//##ModelId=4370A02F03C9
class TiXmlComment : public TiXmlNode
{
public:
	/// Constructs an empty comment.
	//##ModelId=4370A02F03D3
	TiXmlComment() : TiXmlNode( TiXmlNode::COMMENT ) {}
	//##ModelId=4370A02F03D4
	TiXmlComment( const TiXmlComment& );
	//##ModelId=4370A02F03D6
	void operator=( const TiXmlComment& base );

	//##ModelId=4370A02F03DD
	virtual ~TiXmlComment()	{}

	/// Returns a copy of this Comment.
	//##ModelId=4370A02F03DF
	virtual TiXmlNode* Clone() const;
	/// Write this Comment to a FILE stream.
	//##ModelId=4370A02F03E1
	virtual void Print( FILE* cfile, int depth ) const;

	/*	Attribtue parsing starts: at the ! of the !--
						 returns: next char past '>'
	*/
	//##ModelId=4370A02F03E9
	virtual const char* Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding );

protected:
	//##ModelId=4370A030000B
	void CopyTo( TiXmlComment* target ) const;

	// used to be public
	#ifdef TIXML_USE_STL
	//##ModelId=4370A0300013
	    virtual void StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag );
	#endif
	//##ModelId=4370A0300017
	virtual void StreamOut( TIXML_OSTREAM * out ) const;

private:

};


/** XML text. Contained in an element.
*/
//##ModelId=4370A03000E6
class TiXmlText : public TiXmlNode
{
	friend class TiXmlElement;
public:
	/// Constructor.
	//##ModelId=4370A03000F1
	TiXmlText (const char * initValue) : TiXmlNode (TiXmlNode::TEXT)
	{
		SetValue( initValue );
	}
	//##ModelId=4370A03000FB
	virtual ~TiXmlText() {}

	#ifdef TIXML_USE_STL
	/// Constructor.
	//##ModelId=4370A03000FD
	TiXmlText( const std::string& initValue ) : TiXmlNode (TiXmlNode::TEXT)
	{
		SetValue( initValue );
	}
	#endif

	//##ModelId=4370A0300104
	TiXmlText( const TiXmlText& copy ) : TiXmlNode( TiXmlNode::TEXT )	{ copy.CopyTo( this ); }
	//##ModelId=4370A0300106
	void operator=( const TiXmlText& base )							 	{ base.CopyTo( this ); }

	/// Write this text object to a FILE stream.
	//##ModelId=4370A0300108
	virtual void Print( FILE* cfile, int depth ) const;

	//##ModelId=4370A0300111
	virtual const char* Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding );

protected :
	///  [internal use] Creates a new Element and returns it.
	//##ModelId=4370A030011A
	virtual TiXmlNode* Clone() const;
	//##ModelId=4370A0300123
	void CopyTo( TiXmlText* target ) const;

	//##ModelId=4370A0300126
	virtual void StreamOut ( TIXML_OSTREAM * out ) const;
	//##ModelId=4370A030012F
	bool Blank() const;	// returns true if all white space and new lines
	// [internal use]
	#ifdef TIXML_USE_STL
	//##ModelId=4370A0300131
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
//##ModelId=4370A0300264
class TiXmlDeclaration : public TiXmlNode
{
public:
	/// Construct an empty declaration.
	//##ModelId=4370A030026E
	TiXmlDeclaration()   : TiXmlNode( TiXmlNode::DECLARATION ) {}

#ifdef TIXML_USE_STL
	/// Constructor.
	//##ModelId=4370A030026F
	TiXmlDeclaration(	const std::string& _version,
						const std::string& _encoding,
						const std::string& _standalone );
#endif

	/// Construct.
	//##ModelId=4370A0300278
	TiXmlDeclaration(	const char* _version,
						const char* _encoding,
						const char* _standalone );

	//##ModelId=4370A030027C
	TiXmlDeclaration( const TiXmlDeclaration& copy );
	//##ModelId=4370A0300283
	void operator=( const TiXmlDeclaration& copy );

	//##ModelId=4370A0300285
	virtual ~TiXmlDeclaration()	{}

	/// Version. Will return an empty string if none was found.
	//##ModelId=4370A0300287
	const char *Version() const			{ return version.c_str (); }
	/// Encoding. Will return an empty string if none was found.
	//##ModelId=4370A030028D
	const char *Encoding() const		{ return encoding.c_str (); }
	/// Is this a standalone document?
	//##ModelId=4370A030028F
	const char *Standalone() const		{ return standalone.c_str (); }

	/// Creates a copy of this Declaration and returns it.
	//##ModelId=4370A0300291
	virtual TiXmlNode* Clone() const;
	/// Print this declaration to a FILE stream.
	//##ModelId=4370A0300297
	virtual void Print( FILE* cfile, int depth ) const;

	//##ModelId=4370A03002A0
	virtual const char* Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding );

protected:
	//##ModelId=4370A03002A5
	void CopyTo( TiXmlDeclaration* target ) const;
	// used to be public
	#ifdef TIXML_USE_STL
	//##ModelId=4370A03002AC
	    virtual void StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag );
	#endif
	//##ModelId=4370A03002B5
	virtual void StreamOut ( TIXML_OSTREAM * out) const;

private:

	//##ModelId=4370A03002BF
	TIXML_STRING version;
	//##ModelId=4370A03002C4
	TIXML_STRING encoding;
	//##ModelId=4370A03002C9
	TIXML_STRING standalone;
};


/** Any tag that tinyXml doesn't recognize is saved as an
	unknown. It is a tag of text, but should not be modified.
	It will be written back to the XML, unchanged, when the file
	is saved.

	DTD tags get thrown into TiXmlUnknowns.
*/
//##ModelId=4370A030037D
class TiXmlUnknown : public TiXmlNode
{
public:
	//##ModelId=4370A030037F
	TiXmlUnknown() : TiXmlNode( TiXmlNode::UNKNOWN )	{}
	//##ModelId=4370A0300387
	virtual ~TiXmlUnknown() {}

	//##ModelId=4370A0300389
	TiXmlUnknown( const TiXmlUnknown& copy ) : TiXmlNode( TiXmlNode::UNKNOWN )		{ copy.CopyTo( this ); }
	//##ModelId=4370A030038B
	void operator=( const TiXmlUnknown& copy )										{ copy.CopyTo( this ); }

	/// Creates a copy of this Unknown and returns it.
	//##ModelId=4370A0300391
	virtual TiXmlNode* Clone() const;
	/// Print this Unknown to a FILE stream.
	//##ModelId=4370A0300393
	virtual void Print( FILE* cfile, int depth ) const;

	//##ModelId=4370A030039B
	virtual const char* Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding );

protected:
	//##ModelId=4370A03003A5
	void CopyTo( TiXmlUnknown* target ) const;

	#ifdef TIXML_USE_STL
	//##ModelId=4370A03003A8
	    virtual void StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag );
	#endif
	//##ModelId=4370A03003B1
	virtual void StreamOut ( TIXML_OSTREAM * out ) const;

private:

};


/** Always the top level node. A document binds together all the
	XML pieces. It can be saved, loaded, and printed to the screen.
	The 'value' of a document node is the xml file name.
*/
//##ModelId=4370A03101DB
class TiXmlDocument : public TiXmlNode
{
public:
	/// Create an empty document, that has no name.
	//##ModelId=4370A03101E5
	TiXmlDocument();
	/// Create a document with a name. The name of the document is also the filename of the xml.
	//##ModelId=4370A03101E6
	TiXmlDocument( const char * documentName );

	#ifdef TIXML_USE_STL
	/// Constructor.
	//##ModelId=4370A03101E8
	TiXmlDocument( const std::string& documentName );
	#endif

	//##ModelId=4370A03101EF
	TiXmlDocument( const TiXmlDocument& copy );
	//##ModelId=4370A03101F1
	void operator=( const TiXmlDocument& copy );

	//##ModelId=4370A03101F3
	virtual ~TiXmlDocument() {}

	/** Load a file using the current document value.
		Returns true if successful. Will delete any existing
		document data before loading.
	*/
	//##ModelId=4370A03101F9
	bool LoadFile( TiXmlEncoding encoding = TIXML_DEFAULT_ENCODING );
	/// Save a file using the current document value. Returns true if successful.
	//##ModelId=4370A03101FB
	bool SaveFile() const;
	/// Load a file using the given filename. Returns true if successful.
	//##ModelId=4370A03101FD
	bool LoadFile( const char * filename, TiXmlEncoding encoding = TIXML_DEFAULT_ENCODING );
	/// Save a file using the given filename. Returns true if successful.
	//##ModelId=4370A0310205
	bool SaveFile( const char * filename ) const;

	#ifdef TIXML_USE_STL
	//##ModelId=4370A031020D
	bool LoadFile( const std::string& filename, TiXmlEncoding encoding = TIXML_DEFAULT_ENCODING )			///< STL std::string version.
	{
		StringToBuffer f( filename );
		return ( f.buffer && LoadFile( f.buffer, encoding ));
	}
	//##ModelId=4370A0310210
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
	//##ModelId=4370A0310218
	virtual const char* Parse( const char* p, TiXmlParsingData* data = 0, TiXmlEncoding encoding = TIXML_DEFAULT_ENCODING );

	/** Get the root element -- the only top level element -- of the document.
		In well formed XML, there should only be one. TinyXml is tolerant of
		multiple elements at the document level.
	*/
	//##ModelId=4370A0310221
	const TiXmlElement* RootElement() const		{ return FirstChildElement(); }
	//##ModelId=4370A0310223
	TiXmlElement* RootElement()					{ return FirstChildElement(); }

	/** If an error occurs, Error will be set to true. Also,
		- The ErrorId() will contain the integer identifier of the error (not generally useful)
		- The ErrorDesc() method will return the name of the error. (very useful)
		- The ErrorRow() and ErrorCol() will return the location of the error (if known)
	*/	
	//##ModelId=4370A0310224
	bool Error() const						{ return error; }

	/// Contains a textual (english) description of the error if one occurs.
	//##ModelId=4370A031022B
	const char * ErrorDesc() const	{ return errorDesc.c_str (); }

	/** Generally, you probably want the error string ( ErrorDesc() ). But if you
		prefer the ErrorId, this function will fetch it.
	*/
	//##ModelId=4370A031022D
	const int ErrorId()	const				{ return errorId; }

	/** Returns the location (if known) of the error. The first column is column 1, 
		and the first row is row 1. A value of 0 means the row and column wasn't applicable
		(memory errors, for example, have no row/column) or the parser lost the error. (An
		error in the error reporting, in that case.)

		@sa SetTabSize, Row, Column
	*/
	//##ModelId=4370A031022F
	int ErrorRow()	{ return errorLocation.row+1; }
	//##ModelId=4370A0310236
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
	//##ModelId=4370A0310237
	void SetTabSize( int _tabsize )		{ tabsize = _tabsize; }

	//##ModelId=4370A0310239
	int TabSize() const	{ return tabsize; }

	/** If you have handled the error, it can be reset with this call. The error
		state is automatically cleared if you Parse a new XML block.
	*/
	//##ModelId=4370A0310241
	void ClearError()						{	error = false; 
												errorId = 0; 
												errorDesc = ""; 
												errorLocation.row = errorLocation.col = 0; 
												//errorLocation.last = 0; 
											}

	/** Dump the document to standard out. */
	//##ModelId=4370A0310242
	void Print() const						{ Print( stdout, 0 ); }

	/// Print this Document to a FILE stream.
	//##ModelId=4370A0310244
	virtual void Print( FILE* cfile, int depth = 0 ) const;
	// [internal use]
	//##ModelId=4370A031024D
	void SetError( int err, const char* errorLocation, TiXmlParsingData* prevData, TiXmlEncoding encoding );

protected :
	//##ModelId=4370A0310257
	virtual void StreamOut ( TIXML_OSTREAM * out) const;
	// [internal use]
	//##ModelId=4370A031025E
	virtual TiXmlNode* Clone() const;
	#ifdef TIXML_USE_STL
	//##ModelId=4370A0310260
	    virtual void StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag );
	#endif

private:
	//##ModelId=4370A031026A
	void CopyTo( TiXmlDocument* target ) const;

	//##ModelId=4370A0310272
	bool error;
	//##ModelId=4370A0310273
	int  errorId;
	//##ModelId=4370A031027D
	TIXML_STRING errorDesc;
	//##ModelId=4370A0310281
	int tabsize;
	//##ModelId=4370A0310287
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
//##ModelId=4370A03103BD
class TiXmlHandle
{
public:
	/// Create a handle from any node (at any depth of the tree.) This can be a null pointer.
	//##ModelId=4370A03103C7
	TiXmlHandle( TiXmlNode* node )					{ this->node = node; }
	/// Copy constructor
	//##ModelId=4370A03103D1
	TiXmlHandle( const TiXmlHandle& ref )			{ this->node = ref.node; }
	//##ModelId=4370A03103D3
	TiXmlHandle operator=( const TiXmlHandle& ref ) { this->node = ref.node; return *this; }

	/// Return a handle to the first child node.
	//##ModelId=4370A03103D5
	TiXmlHandle FirstChild() const;
	/// Return a handle to the first child node with the given name.
	//##ModelId=4370A03103DC
	TiXmlHandle FirstChild( const char * value ) const;
	/// Return a handle to the first child element.
	//##ModelId=4370A03103DF
	TiXmlHandle FirstChildElement() const;
	/// Return a handle to the first child element with the given name.
	//##ModelId=4370A03103E5
	TiXmlHandle FirstChildElement( const char * value ) const;

	/** Return a handle to the "index" child with the given name. 
		The first child is 0, the second 1, etc.
	*/
	//##ModelId=4370A03103E8
	TiXmlHandle Child( const char* value, int index ) const;
	/** Return a handle to the "index" child. 
		The first child is 0, the second 1, etc.
	*/
	//##ModelId=4370A0320008
	TiXmlHandle Child( int index ) const;
	/** Return a handle to the "index" child element with the given name. 
		The first child element is 0, the second 1, etc. Note that only TiXmlElements
		are indexed: other types are not counted.
	*/
	//##ModelId=4370A032000B
	TiXmlHandle ChildElement( const char* value, int index ) const;
	/** Return a handle to the "index" child element. 
		The first child element is 0, the second 1, etc. Note that only TiXmlElements
		are indexed: other types are not counted.
	*/
	//##ModelId=4370A0320014
	TiXmlHandle ChildElement( int index ) const;

	#ifdef TIXML_USE_STL
	//##ModelId=4370A032001B
	TiXmlHandle FirstChild( const std::string& _value ) const				{ return FirstChild( _value.c_str() ); }
	//##ModelId=4370A032001E
	TiXmlHandle FirstChildElement( const std::string& _value ) const		{ return FirstChildElement( _value.c_str() ); }

	//##ModelId=4370A0320025
	TiXmlHandle Child( const std::string& _value, int index ) const			{ return Child( _value.c_str(), index ); }
	//##ModelId=4370A0320029
	TiXmlHandle ChildElement( const std::string& _value, int index ) const	{ return ChildElement( _value.c_str(), index ); }
	#endif

	/// Return the handle as a TiXmlNode. This may return null.
	//##ModelId=4370A0320031
	TiXmlNode* Node() const			{ return node; } 
	/// Return the handle as a TiXmlElement. This may return null.
	//##ModelId=4370A0320033
	TiXmlElement* Element() const	{ return ( ( node && node->ToElement() ) ? node->ToElement() : 0 ); }
	/// Return the handle as a TiXmlText. This may return null.
	//##ModelId=4370A0320039
	TiXmlText* Text() const			{ return ( ( node && node->ToText() ) ? node->ToText() : 0 ); }
	/// Return the handle as a TiXmlUnknown. This may return null;
	//##ModelId=4370A032003B
	TiXmlUnknown* Unknown() const			{ return ( ( node && node->ToUnknown() ) ? node->ToUnknown() : 0 ); }

private:
	//##ModelId=4370A0320043
	TiXmlNode* node;
};

#ifdef _MSC_VER
#pragma warning( default : 4530 )
#pragma warning( default : 4786 )
#endif

#endif

