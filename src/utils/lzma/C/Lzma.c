#include "LzmaEnc.h"
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>

#define LZMA_ID				(('A'<<24)|('M'<<16)|('Z'<<8)|('L'))

#pragma pack(1)
typedef struct
{
	unsigned int	id;
	unsigned int	actualSize;		// always little endian
	unsigned int	lzmaSize;		// always little endian
	unsigned char	properties[5];
} lzma_header_t;
#pragma pack()


#define LZMA_ORIGINAL_HEADER_SIZE	13

//-----------------------------------------------------------------------------
// Encoding glue. Returns non-null Compressed buffer if successful.
// Caller must free.
//-----------------------------------------------------------------------------
unsigned char *LZMA_Compress(
	unsigned char	*pInput,
	unsigned int	inputSize,
	unsigned int	*pOutputSize,
	unsigned int	dictionarySize )
{
	*pOutputSize = 0;

	if ( inputSize <= sizeof( lzma_header_t ) )
	{
		// pointless
		return NULL;
	}

	dictionarySize = ( 1 << dictionarySize );

	// using same work buffer calcs as the SDK 105% + 64K
	unsigned outSize = inputSize/20 * 21 + (1<<16);
	unsigned char *pOutputBuffer = (unsigned char*)malloc( outSize );
	if ( !pOutputBuffer )
	{
		return NULL;
	}

	// compress, skipping past our header
	unsigned int compressedSize;
	int result = LzmaEncode( pInput, inputSize, pOutputBuffer + sizeof( lzma_header_t ), outSize - sizeof( lzma_header_t ), &compressedSize, dictionarySize );
	if ( result != SZE_OK )
	{
		free( pOutputBuffer );
		return NULL;
	}

	if ( compressedSize - LZMA_ORIGINAL_HEADER_SIZE + sizeof( lzma_header_t ) >= inputSize )
	{
		// compression got worse or stayed the same
		free( pOutputBuffer );
		return NULL;
	}

	// construct our header, strip theirs
	lzma_header_t *pHeader = (lzma_header_t *)pOutputBuffer;
	pHeader->id = LZMA_ID;
	pHeader->actualSize = inputSize;
	pHeader->lzmaSize = compressedSize - LZMA_ORIGINAL_HEADER_SIZE;
	memcpy( pHeader->properties, pOutputBuffer + sizeof( lzma_header_t ), 5 );

	// shift the compressed data into place
	memcpy( pOutputBuffer + sizeof( lzma_header_t ), pOutputBuffer + sizeof( lzma_header_t ) + LZMA_ORIGINAL_HEADER_SIZE, compressedSize - LZMA_ORIGINAL_HEADER_SIZE );

	// final output size is our header plus compressed bits
	*pOutputSize = sizeof( lzma_header_t ) + compressedSize - LZMA_ORIGINAL_HEADER_SIZE;

	return pOutputBuffer;
}

bool LZMA_IsCompressed( unsigned char *pInput )
{
	lzma_header_t *pHeader = (lzma_header_t *)pInput;
	if ( pHeader && pHeader->id == LZMA_ID )
	{
		return true;
	}

	// unrecognized
	return false;
}

unsigned int LZMA_GetActualSize( unsigned char *pInput )
{
	lzma_header_t *pHeader = (lzma_header_t *)pInput;
	if ( pHeader && pHeader->id == LZMA_ID )
	{
		return pHeader->actualSize;
	}

	// unrecognized
	return 0;
}