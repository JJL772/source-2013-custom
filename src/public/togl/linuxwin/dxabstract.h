//========= Copyright Valve Corporation, All rights reserved. ============//
//                       TOGL CODE LICENSE
//
//  Copyright 2011-2014 Valve Corporation
//  All Rights Reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//
// dxabstract.h
//
//==================================================================================================
#ifndef DXABSTRACT_H
#define DXABSTRACT_H

#ifdef DX_TO_GL_ABSTRACTION

#include "togl/rendermechanism.h"

#include "tier0/platform.h"
#include "tier0/dbg.h"
#include "tier1/utlmap.h"

// DXVK headers
#define TOVK
#include "common/dxvk/d3d9.h"

// turn this on to get refcount logging from IUnknown
#define	IUNKNOWN_ALLOC_SPEW 0
#define	IUNKNOWN_ALLOC_SPEW_MARK_ALL 0	


TOGL_INTERFACE void toglGetClientRect( VD3DHWND hWnd, RECT *destRect );


struct TOGL_CLASS IUnknown
{
	int	m_refcount[2];
	bool m_mark;
		
	IUnknown()
	{
		m_refcount[0] = 1;
		m_refcount[1] = 0;
		m_mark = (IUNKNOWN_ALLOC_SPEW_MARK_ALL != 0);	// either all are marked, or only the ones that have SetMark(true) called on them

		#if IUNKNOWN_ALLOC_SPEW
			if (m_mark)
			{
				GLMPRINTF(("-A- IUnew (%08x) refc -> (%d,%d) ",this,m_refcount[0],m_refcount[1]));
			}
		#endif
	};
				
	virtual	~IUnknown()
	{
		#if IUNKNOWN_ALLOC_SPEW
			if (m_mark)
			{
				GLMPRINTF(("-A- IUdel (%08x) ",this ));
			}
		#endif
	};
		
	void	AddRef( int which=0, char *comment = NULL )
	{
		Assert( which >= 0 );
		Assert( which < 2 );
		m_refcount[which]++;
			
		#if IUNKNOWN_ALLOC_SPEW
			if (m_mark)
			{
				GLMPRINTF(("-A- IUAddRef  (%08x,%d) refc -> (%d,%d) [%s]",this,which,m_refcount[0],m_refcount[1],comment?comment:"..."))	;
				if (!comment)
				{
					GLMPRINTF((""))	;	// place to hang a breakpoint
				}
			}
		#endif
	};
		
	ULONG __stdcall	Release( int which=0, char *comment = NULL )
	{
		Assert( which >= 0 );
		Assert( which < 2 );
			
		//int oldrefcs[2] = { m_refcount[0], m_refcount[1] };
		bool deleting = false;
			
		m_refcount[which]--;
		if ( (!m_refcount[0]) && (!m_refcount[1]) )
		{
			deleting = true;
		}
			
		#if IUNKNOWN_ALLOC_SPEW
			if (m_mark)
			{
				GLMPRINTF(("-A- IURelease (%08x,%d) refc -> (%d,%d) [%s] %s",this,which,m_refcount[0],m_refcount[1],comment?comment:"...",deleting?"->DELETING":""));
				if (!comment)
				{
					GLMPRINTF((""))	;	// place to hang a breakpoint
				}
			}
		#endif

		if (deleting)
		{
			if (m_mark)
			{
				GLMPRINTF((""))	;		// place to hang a breakpoint
			}
			delete this;
			return 0;
		}
		else
		{
			return m_refcount[0];
		}
	};
		
	void	SetMark( bool markValue, char *comment=NULL )
	{
		#if IUNKNOWN_ALLOC_SPEW
			if (!m_mark && markValue)	// leading edge detect
			{
				// print the same thing that the constructor would have printed if it had been marked from the beginning
				// i.e. it's anticipated that callers asking for marking will do so right at create time
				GLMPRINTF(("-A- IUSetMark (%08x) refc -> (%d,%d) (%s) ",this,m_refcount[0],m_refcount[1],comment?comment:"..."));
			}
		#endif

		m_mark = markValue;
	}
};

// ------------------------------------------------------------------------------------------------------------------------------ //
// INTERFACES
// ------------------------------------------------------------------------------------------------------------------------------ //

struct TOGL_CLASS IDirect3DResource9 : public IUnknown
{
	//IDirect3DDevice9	*m_device;		// parent device
	__IDirect3DResource9* m_resource;
	D3DRESOURCETYPE		m_restype;
	
	DWORD SetPriority(DWORD PriorityNew);
};

struct TOGL_CLASS IDirect3DBaseTexture9 : public IDirect3DResource9						// "A Texture.."
{
	D3DSURFACE_DESC			m_descZero;			// desc of top level.
	//CGLMTex					*m_tex;				// a CGLMTex can represent all forms of tex
	__IDirect3DBaseTexture9* m_tex;

	virtual					~IDirect3DBaseTexture9();
	D3DRESOURCETYPE	TOGLMETHODCALLTYPE GetType();
	DWORD TOGLMETHODCALLTYPE GetLevelCount();
	HRESULT TOGLMETHODCALLTYPE GetLevelDesc(UINT Level,D3DSURFACE_DESC *pDesc);
};

struct TOGL_CLASS IDirect3DTexture9 : public IDirect3DBaseTexture9							// "Texture 2D"
{	
	//IDirect3DSurface9 *m_surfZero;				// surf of top level.
	__IDirect3DTexture9* m_tex;
	virtual ~IDirect3DTexture9();
	HRESULT TOGLMETHODCALLTYPE LockRect(UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
	HRESULT TOGLMETHODCALLTYPE UnlockRect(UINT Level);
	HRESULT TOGLMETHODCALLTYPE GetSurfaceLevel(UINT Level,IDirect3DSurface9** ppSurfaceLevel);
};

struct TOGL_CLASS IDirect3DCubeTexture9 : public IDirect3DBaseTexture9						// "Texture Cube Map"
{
	//IDirect3DSurface9		*m_surfZero[6];			// surfs of top level.
	__IDirect3DCubeTexture9* m_tex;
	void* m_pad[5];
	
	virtual ~IDirect3DCubeTexture9();
	HRESULT TOGLMETHODCALLTYPE GetCubeMapSurface(D3DCUBEMAP_FACES FaceType,UINT Level,IDirect3DSurface9** ppCubeMapSurface);
	HRESULT TOGLMETHODCALLTYPE GetLevelDesc(UINT Level,D3DSURFACE_DESC *pDesc);
};

struct TOGL_CLASS IDirect3DVolumeTexture9 : public IDirect3DBaseTexture9					// "Texture 3D"
{
	//IDirect3DSurface9		*m_surfZero;			// surf of top level.
	__IDirect3DVolumeTexture9* m_tex;
	D3DVOLUME_DESC			m_volDescZero;			// volume desc top level
	virtual ~IDirect3DVolumeTexture9();
	HRESULT TOGLMETHODCALLTYPE LockBox(UINT Level,D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags);
	HRESULT TOGLMETHODCALLTYPE UnlockBox(UINT Level);
	HRESULT	TOGLMETHODCALLTYPE GetLevelDesc( UINT level, D3DVOLUME_DESC *pDesc );
};


// for the moment, a "D3D surface" is modeled as a GLM tex, a face, and a mip.
// no Create method, these are filled in by the various create surface methods.	

struct TOGL_CLASS IDirect3DSurface9 : public IDirect3DResource9
{
	virtual ~IDirect3DSurface9();
	HRESULT TOGLMETHODCALLTYPE LockRect(D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
	HRESULT TOGLMETHODCALLTYPE UnlockRect();
	 HRESULT TOGLMETHODCALLTYPE GetDesc(D3DSURFACE_DESC *pDesc);

	D3DSURFACE_DESC			m_desc;
	//CGLMTex					*m_tex;
	__IDirect3DSurface9* m_tex;
	int						m_face;
	int						m_mip;
};

struct TOGL_CLASS IDirect3D9 : public IUnknown
{
	virtual	~IDirect3D9();

	UINT	TOGLMETHODCALLTYPE GetAdapterCount();

	HRESULT TOGLMETHODCALLTYPE GetDeviceCaps				(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps);
	HRESULT TOGLMETHODCALLTYPE GetAdapterIdentifier			(UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier);
	HRESULT TOGLMETHODCALLTYPE CheckDeviceFormat			(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat);
	UINT	TOGLMETHODCALLTYPE GetAdapterModeCount			(UINT Adapter,D3DFORMAT Format);
	HRESULT TOGLMETHODCALLTYPE EnumAdapterModes				(UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode);
	HRESULT TOGLMETHODCALLTYPE CheckDeviceType				(UINT Adapter,D3DDEVTYPE DevType,D3DFORMAT AdapterFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed);
	HRESULT TOGLMETHODCALLTYPE GetAdapterDisplayMode		(UINT Adapter,D3DDISPLAYMODE* pMode);
	HRESULT TOGLMETHODCALLTYPE CheckDepthStencilMatch		(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat);
	HRESULT TOGLMETHODCALLTYPE CheckDeviceMultiSampleType	(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels);

	HRESULT TOGLMETHODCALLTYPE CreateDevice					(UINT Adapter,D3DDEVTYPE DeviceType,VD3DHWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface);
};

struct TOGL_CLASS IDirect3DVertexDeclaration9 : public IUnknown
{
	//IDirect3DDevice9		*m_device;
	__IDirect3DVertexDeclaration9* m_decl;
	uint					m_elemCount;
	D3DVERTEXELEMENT9_GL	m_elements[ MAX_D3DVERTEXELEMENTS ];
		
	uint8					m_VertexAttribDescToStreamIndex[256];
				
	virtual					~IDirect3DVertexDeclaration9();
};

struct TOGL_CLASS IDirect3DQuery9 : public IDirect3DResource9	//was IUnknown
{
	D3DQUERYTYPE			m_type;		// D3DQUERYTYPE_OCCLUSION or D3DQUERYTYPE_EVENT
	GLMContext				*m_ctx;
	//CGLMQuery				*m_query;
	__IDirect3DQuery9* m_query;
	
	uint					m_nIssueStartThreadID, m_nIssueEndThreadID;
	uint					m_nIssueStartDrawCallIndex, m_nIssueEndDrawCallIndex;
	uint					m_nIssueStartFrameIndex, m_nIssueEndFrameIndex;
	uint					m_nIssueStartQueryCreationCounter, m_nIssueEndQueryCreationCounter;
			
	virtual					~IDirect3DQuery9();

    HRESULT					Issue(DWORD dwIssueFlags);
    HRESULT					GetData(void* pData,DWORD dwSize,DWORD dwGetDataFlags);
};

struct TOGL_CLASS IDirect3DVertexBuffer9 : public IDirect3DResource9	//was IUnknown
{
	//GLMContext				*m_ctx;
	__IDirect3DVertexBuffer9* m_vb;
	CGLMBuffer				*m_vtxBuffer;
	D3DVERTEXBUFFER_DESC	m_vtxDesc;		// to satisfy GetDesc
		
	virtual					~IDirect3DVertexBuffer9();
    HRESULT					Lock(UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags);
    HRESULT					Unlock();
	void					UnlockActualSize( uint nActualSize, const void *pActualData = NULL );
};

struct TOGL_CLASS IDirect3DIndexBuffer9 : public IDirect3DResource9	//was IUnknown
{
	__IDirect3DIndexBuffer9* m_ib;
	//GLMContext				*m_ctx;
	CGLMBuffer				*m_idxBuffer;
	D3DINDEXBUFFER_DESC		m_idxDesc;		// to satisfy GetDesc
		
	virtual					~IDirect3DIndexBuffer9();

    HRESULT					Lock(UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags);
    HRESULT					Unlock();
	void					UnlockActualSize( uint nActualSize, const void *pActualData = NULL );

    HRESULT					GetDesc(D3DINDEXBUFFER_DESC *pDesc);
};

struct TOGL_CLASS IDirect3DPixelShader9 : public IDirect3DResource9	//was IUnknown
{
	__IDirect3DPixelShader9* m_shader;
	//CGLMProgram				*m_pixProgram;
	uint					m_pixHighWater;		// count of active constant slots referenced by shader.
	uint					m_pixSamplerMask;	// (1<<n) mask of samplers referemnced by this pixel shader
												// this can help FlushSamplers avoid SRGB flipping on textures not being referenced...
	uint					m_pixSamplerTypes;  // SAMPLER_TYPE_2D, etc.
	uint					m_pixFragDataMask;  // (1<<n) mask of gl_FragData[n] referenced by this pixel shader
	
	virtual					~IDirect3DPixelShader9();
};

struct TOGL_CLASS IDirect3DVertexShader9 : public IDirect3DResource9	//was IUnknown
{
	__IDirect3DVertexShader9* m_shader;
	//CGLMProgram				*m_vtxProgram;
	uint					m_vtxHighWater;		// count of active constant slots referenced by shader.
	uint					m_vtxHighWaterBone;
	unsigned char			m_vtxAttribMap[16];	// high nibble is usage, low nibble is usageindex, array position is attrib number
	uint					m_maxVertexAttrs;
	
	virtual					~IDirect3DVertexShader9();
};

#ifdef _MSC_VER
	typedef class TOGL_CLASS CUtlMemory<D3DMATRIX> CD3DMATRIXAllocator;
	typedef class TOGL_CLASS CUtlVector<D3DMATRIX, CD3DMATRIXAllocator> CD3DMATRIXStack;
#else
	typedef class CUtlMemory<D3DMATRIX> CD3DMATRIXAllocator;
	typedef class CUtlVector<D3DMATRIX, CD3DMATRIXAllocator> CD3DMATRIXStack;
#endif

struct TOGL_CLASS ID3DXMatrixStack //: public IUnknown
{
	int	m_refcount[2];
	bool m_mark;
	CD3DMATRIXStack	m_stack;
	int						m_stackTop;	// top of stack is at the highest index, this is that index.  push increases, pop decreases.

	ID3DXMatrixStack();
	void  AddRef( int which=0, char *comment = NULL );
	ULONG Release( int which=0, char *comment = NULL );
	
	HRESULT	Create( void );
	
	D3DXMATRIX* GetTop();
	void Push();
	void Pop();
	void LoadIdentity();
	void LoadMatrix( const D3DXMATRIX *pMat );
	void MultMatrix( const D3DXMATRIX *pMat );
	void MultMatrixLocal( const D3DXMATRIX *pMat );
	HRESULT ScaleLocal(FLOAT x, FLOAT y, FLOAT z);

	// Left multiply the current matrix with the computed rotation
	// matrix, counterclockwise about the given axis with the given angle.
	// (rotation is about the local origin of the object)
	HRESULT RotateAxisLocal(CONST D3DXVECTOR3* pV, FLOAT Angle);

	// Left multiply the current matrix with the computed translation
	// matrix. (transformation is about the local origin of the object)
	HRESULT TranslateLocal(FLOAT x, FLOAT y, FLOAT z);
};

typedef ID3DXMatrixStack* LPD3DXMATRIXSTACK;

struct RenderTargetState_t
{
	void clear() { V_memset( this, 0, sizeof( *this ) ); }

	CGLMTex *m_pRenderTargets[4];
	CGLMTex *m_pDepthStencil;

	inline bool RefersTo( CGLMTex * pSurf ) const
	{
		for ( uint i = 0; i < 4; i++ )
			if ( m_pRenderTargets[i] == pSurf )
				return true;

		if ( m_pDepthStencil == pSurf )
			return true;

		return false;
	}

	static inline bool LessFunc( const RenderTargetState_t &lhs, const RenderTargetState_t &rhs ) 
	{
		COMPILE_TIME_ASSERT( sizeof( lhs.m_pRenderTargets[0] ) == sizeof( uint32 ) );
		uint64 lhs0 = reinterpret_cast<const uint64 *>(lhs.m_pRenderTargets)[0];
		uint64 rhs0 = reinterpret_cast<const uint64 *>(rhs.m_pRenderTargets)[0];
		if ( lhs0 < rhs0 )
			return true;
		else if ( lhs0 == rhs0 )
		{
			uint64 lhs1 = reinterpret_cast<const uint64 *>(lhs.m_pRenderTargets)[1];
			uint64 rhs1 = reinterpret_cast<const uint64 *>(rhs.m_pRenderTargets)[1];
			if ( lhs1 < rhs1 )
				return true;
			else if ( lhs1 == rhs1 )
			{
				return lhs.m_pDepthStencil < rhs.m_pDepthStencil;
			}
		}
		return false;
	}

	inline bool operator < ( const RenderTargetState_t &rhs ) const
	{
		return LessFunc( *this, rhs );
	}
};

typedef CUtlMap< RenderTargetState_t, CGLMFBO *> CGLMFBOMap;

class simple_bitmap;

struct TOGL_CLASS IDirect3DDevice9 : public IUnknown
{
	friend class GLMContext;
	friend struct IDirect3DBaseTexture9;
	friend struct IDirect3DTexture9;
	friend struct IDirect3DCubeTexture9;
	friend struct IDirect3DVolumeTexture9;
	friend struct IDirect3DSurface9;
	friend struct IDirect3DVertexBuffer9;
	friend struct IDirect3DIndexBuffer9;
	friend struct IDirect3DPixelShader9;
	friend struct IDirect3DVertexShader9;
	friend struct IDirect3DQuery9;
	friend struct IDirect3DVertexDeclaration9;

	IDirect3DDevice9();
	virtual	~IDirect3DDevice9();
	
	// Create call invoked from IDirect3D9
	HRESULT	TOGLMETHODCALLTYPE Create( IDirect3DDevice9Params *params );
	
	//
	// Basics
	//
	HRESULT TOGLMETHODCALLTYPE Reset(D3DPRESENT_PARAMETERS* pPresentationParameters);
	HRESULT TOGLMETHODCALLTYPE SetViewport(CONST D3DVIEWPORT9* pViewport);
	HRESULT TOGLMETHODCALLTYPE GetViewport(D3DVIEWPORT9* pViewport);
    HRESULT TOGLMETHODCALLTYPE BeginScene();
	HRESULT TOGLMETHODCALLTYPE Clear(DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil);
    HRESULT TOGLMETHODCALLTYPE EndScene();
    HRESULT TOGLMETHODCALLTYPE Present(CONST RECT* pSourceRect,CONST RECT* pDestRect,VD3DHWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion);

	// textures
	HRESULT TOGLMETHODCALLTYPE CreateTexture(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,VD3DHANDLE* pSharedHandle, char *debugLabel=NULL);
    HRESULT TOGLMETHODCALLTYPE CreateCubeTexture(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,VD3DHANDLE* pSharedHandle, char *debugLabel=NULL);
    HRESULT TOGLMETHODCALLTYPE CreateVolumeTexture(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,VD3DHANDLE* pSharedHandle, char *debugLabel=NULL);
	
	FORCEINLINE HRESULT TOGLMETHODCALLTYPE SetTexture(DWORD Stage,IDirect3DBaseTexture9* pTexture);
	HRESULT TOGLMETHODCALLTYPE SetTextureNonInline(DWORD Stage,IDirect3DBaseTexture9* pTexture);

    HRESULT TOGLMETHODCALLTYPE GetTexture(DWORD Stage,IDirect3DBaseTexture9** ppTexture);

	// render targets, color and depthstencil, surfaces, blit
    HRESULT TOGLMETHODCALLTYPE CreateRenderTarget(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,VD3DHANDLE* pSharedHandle, char *debugLabel=NULL);
    HRESULT TOGLMETHODCALLTYPE SetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget);
    HRESULT TOGLMETHODCALLTYPE GetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget);

    HRESULT TOGLMETHODCALLTYPE CreateOffscreenPlainSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,VD3DHANDLE* pSharedHandle);

    HRESULT TOGLMETHODCALLTYPE CreateDepthStencilSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,VD3DHANDLE* pSharedHandle);
    HRESULT TOGLMETHODCALLTYPE SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil);
    HRESULT TOGLMETHODCALLTYPE GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface);

	HRESULT TOGLMETHODCALLTYPE GetRenderTargetData(IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface);	// ? is anyone using this ?
    HRESULT TOGLMETHODCALLTYPE GetFrontBufferData(UINT iSwapChain,IDirect3DSurface9* pDestSurface);
    HRESULT TOGLMETHODCALLTYPE StretchRect(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter);

	// pixel shaders
    HRESULT TOGLMETHODCALLTYPE CreatePixelShader(CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader, const char *pShaderName, char *debugLabel = NULL, const uint32 *pCentroidMask = NULL );

	FORCEINLINE HRESULT TOGLMETHODCALLTYPE SetPixelShader(IDirect3DPixelShader9* pShader);
	HRESULT TOGLMETHODCALLTYPE SetPixelShaderNonInline(IDirect3DPixelShader9* pShader);
    
	FORCEINLINE HRESULT TOGLMETHODCALLTYPE SetPixelShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount);
	HRESULT TOGLMETHODCALLTYPE SetPixelShaderConstantFNonInline(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount);

    HRESULT TOGLMETHODCALLTYPE SetPixelShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount);
    HRESULT TOGLMETHODCALLTYPE SetPixelShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount);

	// vertex shaders
    HRESULT TOGLMETHODCALLTYPE CreateVertexShader(CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader, const char *pShaderName, char *debugLabel = NULL);

	FORCEINLINE HRESULT TOGLMETHODCALLTYPE SetVertexShader(IDirect3DVertexShader9* pShader);
    HRESULT TOGLMETHODCALLTYPE SetVertexShaderNonInline(IDirect3DVertexShader9* pShader);
    
	FORCEINLINE HRESULT TOGLMETHODCALLTYPE SetVertexShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount);
	HRESULT TOGLMETHODCALLTYPE SetVertexShaderConstantFNonInline(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount);

    FORCEINLINE HRESULT TOGLMETHODCALLTYPE SetVertexShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount);
	HRESULT TOGLMETHODCALLTYPE SetVertexShaderConstantBNonInline(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount);

	FORCEINLINE HRESULT TOGLMETHODCALLTYPE SetVertexShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount);
    HRESULT TOGLMETHODCALLTYPE SetVertexShaderConstantINonInline(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount);

	// POSIX only - preheating for a specific vertex/pixel shader pair - trigger GLSL link inside GLM
	HRESULT TOGLMETHODCALLTYPE LinkShaderPair( IDirect3DVertexShader9* vs, IDirect3DPixelShader9* ps );
	HRESULT TOGLMETHODCALLTYPE ValidateShaderPair( IDirect3DVertexShader9* vs, IDirect3DPixelShader9* ps );
	HRESULT TOGLMETHODCALLTYPE QueryShaderPair( int index, GLMShaderPairInfo *infoOut );
	
	// vertex buffers
    HRESULT TOGLMETHODCALLTYPE CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl);
	
	FORCEINLINE HRESULT TOGLMETHODCALLTYPE SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl);
	HRESULT TOGLMETHODCALLTYPE SetVertexDeclarationNonInline(IDirect3DVertexDeclaration9* pDecl);

    HRESULT TOGLMETHODCALLTYPE SetFVF(DWORD FVF);		// we might not be using these ?
	HRESULT TOGLMETHODCALLTYPE GetFVF(DWORD* pFVF);

    HRESULT CreateVertexBuffer(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,VD3DHANDLE* pSharedHandle);
    
	FORCEINLINE HRESULT TOGLMETHODCALLTYPE SetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride);
	HRESULT SetStreamSourceNonInline(UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride);
		
	// index buffers
    HRESULT TOGLMETHODCALLTYPE CreateIndexBuffer(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,VD3DHANDLE* pSharedHandle);
    
	FORCEINLINE HRESULT TOGLMETHODCALLTYPE SetIndices(IDirect3DIndexBuffer9* pIndexData);
	HRESULT TOGLMETHODCALLTYPE SetIndicesNonInline(IDirect3DIndexBuffer9* pIndexData);

	// State management.
    FORCEINLINE HRESULT TOGLMETHODCALLTYPE SetRenderStateInline(D3DRENDERSTATETYPE State,DWORD Value);
	FORCEINLINE HRESULT TOGLMETHODCALLTYPE SetRenderStateConstInline(D3DRENDERSTATETYPE State,DWORD Value);
	HRESULT TOGLMETHODCALLTYPE SetRenderState(D3DRENDERSTATETYPE State,DWORD Value);

    FORCEINLINE HRESULT TOGLMETHODCALLTYPE SetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value);
	HRESULT TOGLMETHODCALLTYPE SetSamplerStateNonInline(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value);

	FORCEINLINE void TOGLMETHODCALLTYPE SetSamplerStates(DWORD Sampler, DWORD AddressU, DWORD AddressV, DWORD AddressW, DWORD MinFilter, DWORD MagFilter, DWORD MipFilter );
	void TOGLMETHODCALLTYPE SetSamplerStatesNonInline(DWORD Sampler, DWORD AddressU, DWORD AddressV, DWORD AddressW, DWORD MinFilter, DWORD MagFilter, DWORD MipFilter );

	// Draw.
    HRESULT TOGLMETHODCALLTYPE DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount);
    HRESULT TOGLMETHODCALLTYPE DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount);
	HRESULT TOGLMETHODCALLTYPE DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride);

	// misc
    BOOL TOGLMETHODCALLTYPE ShowCursor(BOOL bShow);
    HRESULT TOGLMETHODCALLTYPE ValidateDevice(DWORD* pNumPasses);
    HRESULT TOGLMETHODCALLTYPE SetMaterial(CONST D3DMATERIAL9* pMaterial);
    HRESULT TOGLMETHODCALLTYPE LightEnable(DWORD Index,BOOL Enable);
    HRESULT TOGLMETHODCALLTYPE SetScissorRect(CONST RECT* pRect);
	HRESULT TOGLMETHODCALLTYPE CreateQuery(D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery);
    HRESULT TOGLMETHODCALLTYPE GetDeviceCaps(D3DCAPS9* pCaps);
    HRESULT TOGLMETHODCALLTYPE TestCooperativeLevel();
    HRESULT TOGLMETHODCALLTYPE EvictManagedResources();
    HRESULT TOGLMETHODCALLTYPE SetLight(DWORD Index,CONST D3DLIGHT9*);
    void TOGLMETHODCALLTYPE SetGammaRamp(UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp);
	

	void TOGLMETHODCALLTYPE SaveGLState();
	void TOGLMETHODCALLTYPE RestoreGLState();

	// Talk to JasonM about this one. It's tricky in GL.
    HRESULT TOGLMETHODCALLTYPE SetClipPlane(DWORD Index,CONST float* pPlane);

	//
	//
	// **** FIXED FUNCTION STUFF - None of this stuff needs support in GL.
	//
	//
    HRESULT TOGLMETHODCALLTYPE SetTransform(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix);
    HRESULT TOGLMETHODCALLTYPE SetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value);

	void TOGLMETHODCALLTYPE AcquireThreadOwnership( );
	void TOGLMETHODCALLTYPE ReleaseThreadOwnership( );
	inline DWORD TOGLMETHODCALLTYPE GetCurrentOwnerThreadId() const { return m_ctx->m_nCurOwnerThreadId; }

	FORCEINLINE void TOGLMETHODCALLTYPE SetMaxUsedVertexShaderConstantsHint( uint nMaxReg );
	void TOGLMETHODCALLTYPE SetMaxUsedVertexShaderConstantsHintNonInline( uint nMaxReg );

	void DumpStatsToConsole( const CCommand *pArgs );

#if GLMDEBUG
	void DumpTextures( const CCommand *pArgs );
#endif
		
private:
	IDirect3DDevice9( const IDirect3DDevice9& );
	IDirect3DDevice9& operator= ( const IDirect3DDevice9& );
	// Flushing changes to GL
	void FlushClipPlaneEquation();
	void InitStates();
	void FullFlushStates();
	void UpdateBoundFBO();
	void ResetFBOMap();
	void ScrubFBOMap( CGLMTex *pTex );
	
	// response to retired objects (when refcount goes to zero and they self-delete..)
	void ReleasedVertexDeclaration( IDirect3DVertexDeclaration9 *pDecl );
	void ReleasedTexture( IDirect3DBaseTexture9 *baseTex );			// called from texture destructor - need to scrub samplers	
	void ReleasedCGLMTex( CGLMTex *pTex );
	void ReleasedSurface( IDirect3DSurface9 *surface );				// called from any surface destructor - need to scrub RT table if an RT
	void ReleasedPixelShader( IDirect3DPixelShader9 *pixelShader );		// called from IDirect3DPixelShader9 destructor
	void ReleasedVertexShader( IDirect3DVertexShader9 *vertexShader );	// called from IDirect3DVertexShader9 destructor
	void ReleasedVertexBuffer( IDirect3DVertexBuffer9 *vertexBuffer );	// called from IDirect3DVertexBuffer9 destructor
	void ReleasedIndexBuffer( IDirect3DIndexBuffer9 *indexBuffer );		// called from IDirect3DIndexBuffer9 destructor
	void ReleasedQuery( IDirect3DQuery9 *query );					// called from IDirect3DQuery9 destructor
			
	// Member variables

	DWORD						m_nValidMarker;
public:
	IDirect3DDevice9Params	m_params;						// mirror of the creation inputs
private:
	__IDirect3DDevice9* m_device;
};

FORCEINLINE HRESULT TOGLMETHODCALLTYPE IDirect3DDevice9::SetSamplerState( DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value )
{
	m_device->SetSamplerState(sampler, type, Value);
}

FORCEINLINE void TOGLMETHODCALLTYPE IDirect3DDevice9::SetSamplerStates(
	DWORD Sampler, DWORD AddressU, DWORD AddressV, DWORD AddressW,
	DWORD MinFilter, DWORD MagFilter, DWORD MipFilter )
{
	m_device->SetSamplerStates(Sampler, AddressU, AddressV, AddressW, MinFilter, MagFilter, MipFilter);
}

FORCEINLINE HRESULT TOGLMETHODCALLTYPE IDirect3DDevice9::SetTexture(DWORD Stage,IDirect3DBaseTexture9* pTexture)
{
	m_device->SetTexture(Stage, pTexture->m_tex);
}

inline GLenum D3DCompareFuncToGL( DWORD function )
{
	switch ( function )
	{
		case D3DCMP_NEVER		: return GL_NEVER;				// Always fail the test.
		case D3DCMP_LESS		: return GL_LESS;				// Accept the new pixel if its value is less than the value of the current pixel.
		case D3DCMP_EQUAL		: return GL_EQUAL;				// Accept the new pixel if its value equals the value of the current pixel.
		case D3DCMP_LESSEQUAL	: return GL_LEQUAL;				// Accept the new pixel if its value is less than or equal to the value of the current pixel. **
		case D3DCMP_GREATER		: return GL_GREATER;			// Accept the new pixel if its value is greater than the value of the current pixel.
		case D3DCMP_NOTEQUAL	: return GL_NOTEQUAL;			// Accept the new pixel if its value does not equal the value of the current pixel.
		case D3DCMP_GREATEREQUAL: return GL_GEQUAL;				// Accept the new pixel if its value is greater than or equal to the value of the current pixel.
		case D3DCMP_ALWAYS		: return GL_ALWAYS;				// Always pass the test.
		default					: DXABSTRACT_BREAK_ON_ERROR(); return 0xFFFFFFFF;
	}
}

FORCEINLINE GLenum D3DBlendOperationToGL( DWORD operation )
{
	switch (operation)
	{
		case	D3DBLENDOP_ADD			: return GL_FUNC_ADD;				// The result is the destination added to the source. Result = Source + Destination
		case	D3DBLENDOP_SUBTRACT		: return GL_FUNC_SUBTRACT;			// The result is the destination subtracted from to the source. Result = Source - Destination
		case	D3DBLENDOP_REVSUBTRACT	: return GL_FUNC_REVERSE_SUBTRACT;	// The result is the source subtracted from the destination. Result = Destination - Source
		case	D3DBLENDOP_MIN			: return GL_MIN;					// The result is the minimum of the source and destination. Result = MIN(Source, Destination)
		case	D3DBLENDOP_MAX			: return GL_MAX;					// The result is the maximum of the source and destination. Result = MAX(Source, Destination)
		default:
			DXABSTRACT_BREAK_ON_ERROR();
			return 0xFFFFFFFF;
		break;
	}
}

FORCEINLINE GLenum D3DBlendFactorToGL( DWORD equation )
{
	switch (equation)
	{
		case	D3DBLEND_ZERO			: return GL_ZERO;					// Blend factor is (0, 0, 0, 0).
		case	D3DBLEND_ONE			: return GL_ONE;					// Blend factor is (1, 1, 1, 1).
		case	D3DBLEND_SRCCOLOR		: return GL_SRC_COLOR;				// Blend factor is (Rs, Gs, Bs, As).
		case	D3DBLEND_INVSRCCOLOR	: return GL_ONE_MINUS_SRC_COLOR;	// Blend factor is (1 - Rs, 1 - Gs, 1 - Bs, 1 - As).
		case	D3DBLEND_SRCALPHA		: return GL_SRC_ALPHA;				// Blend factor is (As, As, As, As).
		case	D3DBLEND_INVSRCALPHA	: return GL_ONE_MINUS_SRC_ALPHA;	// Blend factor is ( 1 - As, 1 - As, 1 - As, 1 - As).
		case	D3DBLEND_DESTALPHA		: return GL_DST_ALPHA;				// Blend factor is (Ad Ad Ad Ad).
		case	D3DBLEND_INVDESTALPHA	: return GL_ONE_MINUS_DST_ALPHA;	// Blend factor is (1 - Ad 1 - Ad 1 - Ad 1 - Ad).
		case	D3DBLEND_DESTCOLOR		: return GL_DST_COLOR;				// Blend factor is (Rd, Gd, Bd, Ad).
		case	D3DBLEND_INVDESTCOLOR	: return GL_ONE_MINUS_DST_COLOR;	// Blend factor is (1 - Rd, 1 - Gd, 1 - Bd, 1 - Ad).
		case	D3DBLEND_SRCALPHASAT	: return GL_SRC_ALPHA_SATURATE;		// Blend factor is (f, f, f, 1); where f = min(As, 1 - Ad).

		/*
			// these are weird.... break if we hit them
			case	D3DBLEND_BOTHSRCALPHA	: Assert(0); return GL_ZERO;		// Obsolete. Starting with DirectX 6, you can achieve the same effect by setting the source and destination blend factors to D3DBLEND_SRCALPHA and D3DBLEND_INVSRCALPHA in separate calls.
			case	D3DBLEND_BOTHINVSRCALPHA: Assert(0); return GL_ZERO;		// Source blend factor is (1 - As, 1 - As, 1 - As, 1 - As), and destination blend factor is (As, As, As, As); the destination blend selection is overridden. This blend mode is supported only for the D3DRS_SRCBLEND render state.
			case	D3DBLEND_BLENDFACTOR	: Assert(0); return GL_ZERO;		// Constant color blending factor used by the frame-buffer blender. This blend mode is supported only if D3DPBLENDCAPS_BLENDFACTOR is set in the SrcBlendCaps or DestBlendCaps members of D3DCAPS9.
		
		dxabstract.h has not heard of these, so let them hit the debugger if they come through
			case	D3DBLEND_INVBLENDFACTOR:	//Inverted constant color-blending factor used by the frame-buffer blender. This blend mode is supported only if the D3DPBLENDCAPS_BLENDFACTOR bit is set in the SrcBlendCaps or DestBlendCaps members of D3DCAPS9.
			case	D3DBLEND_SRCCOLOR2:		// Blend factor is (PSOutColor[1]r, PSOutColor[1]g, PSOutColor[1]b, not used).	This flag is available in Direct3D 9Ex only.
			case	D3DBLEND_INVSRCCOLOR2:	// Blend factor is (1 - PSOutColor[1]r, 1 - PSOutColor[1]g, 1 - PSOutColor[1]b, not used)). This flag is available in Direct3D 9Ex only.
		*/
		default:
			DXABSTRACT_BREAK_ON_ERROR();
			return 0xFFFFFFFF;
		break;
	}
}


FORCEINLINE GLenum D3DStencilOpToGL( DWORD operation )
{
	switch( operation )
	{
		case D3DSTENCILOP_KEEP		: return GL_KEEP;
		case D3DSTENCILOP_ZERO		: return GL_ZERO;
		case D3DSTENCILOP_REPLACE	: return GL_REPLACE;
		case D3DSTENCILOP_INCRSAT	: return GL_INCR;
		case D3DSTENCILOP_DECRSAT	: return GL_DECR;
		case D3DSTENCILOP_INVERT	: return GL_INVERT;
		case D3DSTENCILOP_INCR		: return GL_INCR_WRAP_EXT;
		case D3DSTENCILOP_DECR		: return GL_DECR_WRAP_EXT;
		default						: DXABSTRACT_BREAK_ON_ERROR(); return 0xFFFFFFFF;
	}
}

FORCEINLINE HRESULT TOGLMETHODCALLTYPE IDirect3DDevice9::SetRenderStateInline( D3DRENDERSTATETYPE State, DWORD Value )
{
	m_device->SetRenderState(State, Value);
}

FORCEINLINE HRESULT TOGLMETHODCALLTYPE IDirect3DDevice9::SetRenderStateConstInline( D3DRENDERSTATETYPE State, DWORD Value )
{
	// State is a compile time constant - luckily no need to do anything special to get the compiler to optimize this case.
	return SetRenderState( State, Value );
}

FORCEINLINE HRESULT TOGLMETHODCALLTYPE IDirect3DDevice9::SetIndices(IDirect3DIndexBuffer9* pIndexData)
{
	m_device->SetIndices(pIndexData->m_ib);
}

FORCEINLINE HRESULT TOGLMETHODCALLTYPE IDirect3DDevice9::SetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride)
{
	return m_device->SetStreamSource(StreamNumber, pStreamData->m_vb, OffsetInBytes, Stride);
}

FORCEINLINE HRESULT TOGLMETHODCALLTYPE IDirect3DDevice9::SetVertexShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount)	// groups of 4 floats!
{
	return m_device->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
#if GLMDEBUG || GL_BATCH_PERF_ANALYSIS
	return SetVertexShaderConstantFNonInline( StartRegister, pConstantData, Vector4fCount );
#else
	TOGL_NULL_DEVICE_CHECK;
	Assert( GetCurrentOwnerThreadId() == ThreadGetCurrentId() );
	m_ctx->SetProgramParametersF( kGLMVertexProgram, StartRegister, (float *)pConstantData, Vector4fCount );
	return S_OK;
#endif
}

FORCEINLINE HRESULT TOGLMETHODCALLTYPE IDirect3DDevice9::SetVertexShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount)
{
	return m_device->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
#if GLMDEBUG || GL_BATCH_PERF_ANALYSIS
	return SetVertexShaderConstantBNonInline( StartRegister, pConstantData, BoolCount );
#else
	TOGL_NULL_DEVICE_CHECK;
	Assert( GetCurrentOwnerThreadId() == ThreadGetCurrentId() );
	m_ctx->SetProgramParametersB( kGLMVertexProgram, StartRegister, (int *)pConstantData, BoolCount );
	return S_OK;
#endif
}

FORCEINLINE HRESULT IDirect3DDevice9::SetVertexShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount)		// groups of 4 ints!
{
	return m_device->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
#if GLMDEBUG || GL_BATCH_PERF_ANALYSIS
	return SetVertexShaderConstantINonInline( StartRegister, pConstantData, Vector4iCount );
#else
	TOGL_NULL_DEVICE_CHECK;
	Assert( GetCurrentOwnerThreadId() == ThreadGetCurrentId() );
	m_ctx->SetProgramParametersI( kGLMVertexProgram, StartRegister, (int *)pConstantData, Vector4iCount );
	return S_OK;
#endif
}

FORCEINLINE HRESULT TOGLMETHODCALLTYPE IDirect3DDevice9::SetPixelShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount)
{
	return m_device->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
#if GLMDEBUG || GL_BATCH_PERF_ANALYSIS
	return SetPixelShaderConstantFNonInline(StartRegister, pConstantData, Vector4fCount);
#else
	TOGL_NULL_DEVICE_CHECK;
	Assert( GetCurrentOwnerThreadId() == ThreadGetCurrentId() );
	m_ctx->SetProgramParametersF( kGLMFragmentProgram, StartRegister, (float *)pConstantData, Vector4fCount );
	return S_OK;
#endif
}

HRESULT IDirect3DDevice9::SetVertexShader(IDirect3DVertexShader9* pShader)
{
	return m_device->SetVertexShader(pShader->m_shader);
#if GLMDEBUG || GL_BATCH_PERF_ANALYSIS
	return SetVertexShaderNonInline(pShader);
#else
	Assert( GetCurrentOwnerThreadId() == ThreadGetCurrentId() );
	m_ctx->SetVertexProgram( pShader ? pShader->m_vtxProgram : NULL );
	m_vertexShader = pShader;
	return S_OK;
#endif
}

FORCEINLINE HRESULT TOGLMETHODCALLTYPE IDirect3DDevice9::SetPixelShader(IDirect3DPixelShader9* pShader)
{
	return m_device->SetPixelShader(pShader->m_shader);
#if GLMDEBUG || GL_BATCH_PERF_ANALYSIS
	return SetPixelShaderNonInline(pShader);
#else
	Assert( GetCurrentOwnerThreadId() == ThreadGetCurrentId() );
	m_ctx->SetFragmentProgram( pShader ? pShader->m_pixProgram : NULL );
	m_pixelShader = pShader;
	return S_OK;
#endif
}

FORCEINLINE HRESULT IDirect3DDevice9::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)
{
	return m_device->SetVertexDeclaration(pDecl->m_decl);
#if GLMDEBUG || GL_BATCH_PERF_ANALYSIS
	return SetVertexDeclarationNonInline(pDecl);
#else
	Assert( GetCurrentOwnerThreadId() == ThreadGetCurrentId() );
	m_pVertDecl = pDecl;
	return S_OK;
#endif
}

FORCEINLINE void IDirect3DDevice9::SetMaxUsedVertexShaderConstantsHint( uint nMaxReg )
{
	return m_device->SetMaxUsedVertexShaderConstantsHint(nMaxReg);
#if GLMDEBUG || GL_BATCH_PERF_ANALYSIS
	return SetMaxUsedVertexShaderConstantsHintNonInline( nMaxReg );
#else
	Assert( GetCurrentOwnerThreadId() == ThreadGetCurrentId() );
	m_ctx->SetMaxUsedVertexShaderConstantsHint( nMaxReg );
#endif
}

// ------------------------------------------------------------------------------------------------------------------------------ //
// D3DX
// ------------------------------------------------------------------------------------------------------------------------------ //
struct ID3DXInclude
{
	virtual HRESULT Open(D3DXINCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes);
	virtual HRESULT Close(LPCVOID pData);
};
typedef ID3DXInclude* LPD3DXINCLUDE;


struct TOGL_CLASS ID3DXBuffer : public IUnknown
{
	void* GetBufferPointer();
	DWORD GetBufferSize();
};

typedef ID3DXBuffer* LPD3DXBUFFER;

class ID3DXConstantTable : public IUnknown
{
};
typedef ID3DXConstantTable* LPD3DXCONSTANTTABLE;

TOGL_INTERFACE const char* D3DXGetPixelShaderProfile( IDirect3DDevice9 *pDevice );

TOGL_INTERFACE D3DXMATRIX* D3DXMatrixMultiply( D3DXMATRIX *pOut, CONST D3DXMATRIX *pM1, CONST D3DXMATRIX *pM2 );
TOGL_INTERFACE D3DXVECTOR3* D3DXVec3TransformCoord( D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV, CONST D3DXMATRIX *pM );

TOGL_INTERFACE HRESULT D3DXCreateMatrixStack( DWORD Flags, LPD3DXMATRIXSTACK* ppStack);
TOGL_INTERFACE void D3DXMatrixIdentity( D3DXMATRIX * );

TOGL_INTERFACE D3DXINLINE D3DXVECTOR3* D3DXVec3Subtract( D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV1, CONST D3DXVECTOR3 *pV2 )
{
	pOut->x = pV1->x - pV2->x;
	pOut->y = pV1->y - pV2->y;
	pOut->z = pV1->z - pV2->z;
	return pOut;
}

TOGL_INTERFACE D3DXINLINE D3DXVECTOR3* D3DXVec3Cross( D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV1, CONST D3DXVECTOR3 *pV2 )
{
	D3DXVECTOR3 v;

	v.x = pV1->y * pV2->z - pV1->z * pV2->y;
	v.y = pV1->z * pV2->x - pV1->x * pV2->z;
	v.z = pV1->x * pV2->y - pV1->y * pV2->x;

	*pOut = v;
	return pOut;
}

TOGL_INTERFACE D3DXINLINE FLOAT D3DXVec3Dot( CONST D3DXVECTOR3 *pV1, CONST D3DXVECTOR3 *pV2 )
{
	return pV1->x * pV2->x + pV1->y * pV2->y + pV1->z * pV2->z;
}

TOGL_INTERFACE D3DXMATRIX* D3DXMatrixInverse( D3DXMATRIX *pOut, FLOAT *pDeterminant, CONST D3DXMATRIX *pM );

TOGL_INTERFACE D3DXMATRIX* D3DXMatrixTranspose( D3DXMATRIX *pOut, CONST D3DXMATRIX *pM );

TOGL_INTERFACE D3DXPLANE* D3DXPlaneNormalize( D3DXPLANE *pOut, CONST D3DXPLANE *pP);

TOGL_INTERFACE D3DXVECTOR4* D3DXVec4Transform( D3DXVECTOR4 *pOut, CONST D3DXVECTOR4 *pV, CONST D3DXMATRIX *pM );


TOGL_INTERFACE D3DXVECTOR4* D3DXVec4Normalize( D3DXVECTOR4 *pOut, CONST D3DXVECTOR4 *pV );

TOGL_INTERFACE D3DXMATRIX* D3DXMatrixTranslation( D3DXMATRIX *pOut, FLOAT x, FLOAT y, FLOAT z );

// Build an ortho projection matrix. (right-handed)
TOGL_INTERFACE D3DXMATRIX* D3DXMatrixOrthoOffCenterRH( D3DXMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn,FLOAT zf );

TOGL_INTERFACE D3DXMATRIX* D3DXMatrixPerspectiveRH( D3DXMATRIX *pOut, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf );

TOGL_INTERFACE D3DXMATRIX* D3DXMatrixPerspectiveOffCenterRH( D3DXMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn, FLOAT zf );

// Transform a plane by a matrix.  The vector (a,b,c) must be normal.
// M should be the inverse transpose of the transformation desired.
TOGL_INTERFACE D3DXPLANE* D3DXPlaneTransform( D3DXPLANE *pOut, CONST D3DXPLANE *pP, CONST D3DXMATRIX *pM );

TOGL_INTERFACE IDirect3D9 *Direct3DCreate9(UINT SDKVersion);

TOGL_INTERFACE void D3DPERF_SetOptions( DWORD dwOptions );

TOGL_INTERFACE HRESULT D3DXCompileShader(
	LPCSTR                          pSrcData,
	UINT                            SrcDataLen,
	CONST D3DXMACRO*                pDefines,
	LPD3DXINCLUDE                   pInclude,
	LPCSTR                          pFunctionName,
	LPCSTR                          pProfile,
	DWORD                           Flags,
	LPD3DXBUFFER*                   ppShader,
	LPD3DXBUFFER*                   ppErrorMsgs,
	LPD3DXCONSTANTTABLE*            ppConstantTable);

// fake D3D usage constant for SRGB tex creation
#define D3DUSAGE_TEXTURE_SRGB (0x80000000L)

#else

	//USE_ACTUAL_DX
	#ifndef WIN32
	#error sorry man
	#endif

	#ifdef _X360
		#include "d3d9.h"
		#include "d3dx9.h"
	#else
		#include <windows.h>
		#include "../../dx9sdk/include/d3d9.h"
		#include "../../dx9sdk/include/d3dx9.h"
	#endif
	typedef HWND VD3DHWND;

#endif // DX_TO_GL_ABSTRACTION

#endif // DXABSTRACT_H
