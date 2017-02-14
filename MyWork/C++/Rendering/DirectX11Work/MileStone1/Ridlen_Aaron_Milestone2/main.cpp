// CGS HW Project A "Line Land".
// Author: L.Norri CD CGS, FullSail University

// Introduction:
// Welcome to the hardware project of the Computer Graphics Systems class.
// This assignment is fully guided but still requires significant effort on your part. 
// Future classes will demand the habits & foundation you develop right now!  
// It is CRITICAL that you follow each and every step. ESPECIALLY THE READING!!!

// TO BEGIN: Open the word document that acompanies this project and start from the top.

//************************************************************
//************ INCLUDES & DEFINES ****************************
//************************************************************

#include <iostream>
#include <ctime>
#include "XTime.h"
#include <Windows.h>
#include"Math.h"
using namespace std;

// BEGIN PART 1
// TODO: PART 1 STEP 1a
#define SAFE_RELEASE(p){if(p){p->Release();p=nullptr;}}
#include <d3d11.h>
#include <DirectXMath.h>
#pragma comment(lib,"d3d11.lib")
using namespace DirectX;
// TODO: PART 1 STEP 1b
struct Simple_Vertex
{
	float x, y;
};
// TODO: PART 2 STEP 6

#include "Trivial_PS.csh"
#include "Trivial_VS.csh"
#define BACKBUFFER_WIDTH	500
#define BACKBUFFER_HEIGHT	500

//************************************************************
//************ SIMPLE WINDOWS APP CLASS **********************
//************************************************************

class DEMO_APP
{	
	HINSTANCE						application;
	WNDPROC							appWndProc;
	HWND							window;
	// TODO: PART 1 STEP 2
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;
	ID3D11RenderTargetView* m_RTV;
	D3D11_VIEWPORT m_view;
	IDXGISwapChain* m_swap;
	ID3D11Texture2D * BackBuffer;
	ID3D11DepthStencilState * pDSState;
	ID3D11DepthStencilView* pDSV;
	// TODO: PART 2 STEP 2
	ID3D11Buffer* circle_buffer;
	ID3D11Buffer* circle_buffer_pretty;
	ID3D11InputLayout* m_layout;
	// BEGIN PART 5
	// TODO: PART 5 STEP 1
	
	// TODO: PART 2 STEP 4
	ID3D11VertexShader* _vertshader;
	ID3D11PixelShader* _pixelshader;
	// BEGIN PART 3
	// TODO: PART 3 STEP 1

	// TODO: PART 3 STEP 2b
	
	// TODO: PART 3 STEP 4a

public:
	// BEGIN PART 2
	// TODO: PART 2 STEP 1
	XTime m_time;
	struct Send_To_VRAM
	{
		XMFLOAT4 constantColor;
		XMFLOAT2 constantOffset;
		XMFLOAT2 padding;
	};
	Send_To_VRAM toshader;
	DEMO_APP(HINSTANCE hinst, WNDPROC proc);
	bool Run();
	bool ShutDown();
};

//************************************************************
//************ CREATION OF OBJECTS & RESOURCES ***************
//************************************************************

DEMO_APP::DEMO_APP(HINSTANCE hinst, WNDPROC proc)
{
	// ****************** BEGIN WARNING ***********************// 
	// WINDOWS CODE, I DON'T TEACH THIS YOU MUST KNOW IT ALREADY! 
	application = hinst; 
	appWndProc = proc; 

	WNDCLASSEX  wndClass;
    ZeroMemory( &wndClass, sizeof( wndClass ) );
    wndClass.cbSize         = sizeof( WNDCLASSEX );             
    wndClass.lpfnWndProc    = appWndProc;						
    wndClass.lpszClassName  = L"DirectXApplication";            
	wndClass.hInstance      = application;		               
    wndClass.hCursor        = LoadCursor( NULL, IDC_ARROW );    
    wndClass.hbrBackground  = ( HBRUSH )( COLOR_WINDOWFRAME ); 
	//wndClass.hIcon			= LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FSICON));
    RegisterClassEx( &wndClass );

	RECT window_size = { 0, 0, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT };
	AdjustWindowRect(&window_size, WS_OVERLAPPEDWINDOW, false);

	window = CreateWindow(	L"DirectXApplication", L"CGS Hardware Project",	WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME|WS_MAXIMIZEBOX), 
							CW_USEDEFAULT, CW_USEDEFAULT, window_size.right-window_size.left, window_size.bottom-window_size.top,					
							NULL, NULL,	application, this );												

    ShowWindow( window, SW_SHOW );
	//********************* END WARNING ************************//
	
	unsigned int flag = 0;
#if _DEBUG 

	flag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	// TODO: PART 1 STEP 3a
	DXGI_SWAP_CHAIN_DESC CHAIN;
	memset(&CHAIN, 0, sizeof(CHAIN));
	CHAIN.BufferCount = 1;
	CHAIN.BufferDesc.Width = BACKBUFFER_WIDTH;
	CHAIN.BufferDesc.Height = BACKBUFFER_HEIGHT;
	CHAIN.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	CHAIN.BufferDesc.RefreshRate.Numerator = 60;
	CHAIN.BufferDesc.RefreshRate.Denominator = 1;
	CHAIN.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	CHAIN.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	CHAIN.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	CHAIN.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
	CHAIN.OutputWindow = window;
	CHAIN.SampleDesc.Count = 1;
	CHAIN.SampleDesc.Quality = 0;
	CHAIN.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	CHAIN.Windowed = true;
	// TODO: PART 1 STEP 3b
   D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flag, NULL, NULL, D3D11_SDK_VERSION, &CHAIN, &m_swap, &m_device, NULL, &m_context);
	// TODO: PART 1 STEP 4
   m_swap->GetBuffer(0, _uuidof(BackBuffer), reinterpret_cast<void**>(&BackBuffer));
   m_device->CreateRenderTargetView(BackBuffer, NULL, &m_RTV);
	// TODO: PART 1 STEP 5
   m_view.Width = BACKBUFFER_WIDTH;
   m_view.Height = BACKBUFFER_HEIGHT;
   m_view.MinDepth = 0.0F;
   m_view.MaxDepth = 1.0F;
   m_view.TopLeftX = 0;
   m_view.TopLeftY = 0;
   
	// TODO: PART 2 STEP 3a
   Simple_Vertex points[361];
   for (unsigned int i = 0; i < 361; ++i)
   {
	  
		   points[i].x = cosf(PI * i / 180.0f);
		   points[i].y = sinf(PI * i / 180.0f);
	   

   }
	// BEGIN PART 4
	// TODO: PART 4 STEP 1

	// TODO: PART 2 STEP 3b
   D3D11_BUFFER_DESC VERTEX_DESC;
   VERTEX_DESC.Usage = D3D11_USAGE_IMMUTABLE;
   VERTEX_DESC.BindFlags = D3D11_BIND_VERTEX_BUFFER;
   VERTEX_DESC.CPUAccessFlags = NULL;
   VERTEX_DESC.MiscFlags = NULL;
   VERTEX_DESC.ByteWidth = sizeof(Simple_Vertex) * 361;
   VERTEX_DESC.StructureByteStride = sizeof(Simple_Vertex);
    // TODO: PART 2 STEP 3c
   D3D11_SUBRESOURCE_DATA _data;

   _data.SysMemPitch = 0;
   _data.SysMemSlicePitch = 0;
   _data.pSysMem = points;
	// TODO: PART 2 STEP 3d
   m_device->CreateBuffer(&VERTEX_DESC, &_data, &circle_buffer);


   D3D11_BUFFER_DESC VERTEX_DESC_SHADER;
   VERTEX_DESC.Usage = D3D11_USAGE_IMMUTABLE;
   VERTEX_DESC.BindFlags = D3D11_BIND_VERTEX_BUFFER;
   VERTEX_DESC.CPUAccessFlags = NULL;
   VERTEX_DESC.MiscFlags = NULL;
   VERTEX_DESC.ByteWidth = sizeof(Simple_Vertex) * 361;
   VERTEX_DESC.StructureByteStride = sizeof(Simple_Vertex);
   // TODO: PART 2 STEP 3c
   D3D11_SUBRESOURCE_DATA _dataShader;

   _data.SysMemPitch = 0;
   _data.SysMemSlicePitch = 0;
   _data.pSysMem = points;
   // TODO: PART 2 STEP 3d
   m_device->CreateBuffer(&VERTEX_DESC_SHADER, &_dataShader, &circle_buffer_pretty);
	// TODO: PART 5 STEP 2a
	
	// TODO: PART 5 STEP 2b
	
	// TODO: PART 5 STEP 3
		
	// TODO: PART 2 STEP 5
	// ADD SHADERS TO PROJECT, SET BUILD OPTIONS & COMPILE

	// TODO: PART 2 STEP 7
   m_device->CreatePixelShader(Trivial_PS, sizeof(Trivial_PS), NULL, &_pixelshader);
   m_device->CreateVertexShader(Trivial_VS, sizeof(Trivial_VS), NULL, &_vertshader);;
	// TODO: PART 2 STEP 8a
   D3D11_INPUT_ELEMENT_DESC vLayout[] =
   {
	   { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	  // { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
   };
	// TODO: PART 2 STEP 8b
   m_device->CreateInputLayout(vLayout, ARRAYSIZE(vLayout), Trivial_VS, sizeof(Trivial_VS), &m_layout);
   D3D11_BUFFER_DESC constbuff;
   constbuff.ByteWidth = sizeof(Send_To_VRAM);
   constbuff.Usage = D3D11_USAGE_DYNAMIC;
   constbuff.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
   constbuff.MiscFlags = NULL;
   constbuff.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
   constbuff.StructureByteStride = sizeof(Send_To_VRAM);
   m_device->CreateBuffer(&constbuff, NULL, &circle_buffer_pretty);
  
	// TODO: PART 3 STEP 3

	// TODO: PART 3 STEP 4b
   toshader.constantOffset.x = 0;
   toshader.constantOffset.y = 0;
   toshader.constantColor.x = 1;
   toshader.constantColor.y = 1;
   toshader.constantColor.z = 1;
   toshader.constantColor.w = 1;
}

//************************************************************
//************ EXECUTION *************************************
//************************************************************

bool DEMO_APP::Run()
{
	m_time.Signal();
	// TODO: PART 4 STEP 2	
	
	// TODO: PART 4 STEP 3
	
	// TODO: PART 4 STEP 5
	
	// END PART 4

	// TODO: PART 1 STEP 7a
	m_context->OMSetRenderTargets(1, &m_RTV, NULL);
	// TODO: PART 1 STEP 7b
	m_context->RSSetViewports(1, &m_view);
	// TODO: PART 1 STEP 7c
	float color[4] = { 0.0f,0.0f,1.0f,0.0f };
	m_context->ClearRenderTargetView(m_RTV, color);
	//m_context->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1, 0);
	// TODO: PART 5 STEP 4
	
	// TODO: PART 5 STEP 5
	
	// TODO: PART 5 STEP 6
	
	// TODO: PART 5 STEP 7
	
	// END PART 5
	
	// TODO: PART 3 STEP 5
	D3D11_MAPPED_SUBRESOURCE mapData;
	m_context->Map(circle_buffer_pretty, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mapData);
	memcpy_s(mapData.pData, sizeof(Send_To_VRAM), &toshader, sizeof(Send_To_VRAM));
	m_context->Unmap(circle_buffer_pretty, NULL);
	// TODO: PART 3 STEP 6
	m_context->VSSetConstantBuffers(0, 1, &circle_buffer_pretty);
	// TODO: PART 2 STEP 9a
	unsigned int stride = sizeof(Simple_Vertex);
	unsigned int offset_vert = 0;
	m_context->IASetVertexBuffers(0, 1, &circle_buffer, &stride, &offset_vert);
	
	// TODO: PART 2 STEP 9b
	m_context->PSSetShader(_pixelshader, NULL, 0);
	m_context->VSSetShader(_vertshader, NULL, 0);
	// TODO: PART 2 STEP 9c
	m_context->IASetInputLayout(m_layout);
	// TODO: PART 2 STEP 9d
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	// TODO: PART 2 STEP 10
	m_context->Draw(361, 0);
	// END PART 2

	// TODO: PART 1 STEP 8
	m_swap->Present(0, 0);
	// END OF PART 1
	return true; 
}

//************************************************************
//************ DESTRUCTION ***********************************
//************************************************************

bool DEMO_APP::ShutDown()
{
	// TODO: PART 1 STEP 6
	SAFE_RELEASE(m_device);
	SAFE_RELEASE(m_swap);
	
	SAFE_RELEASE(m_context);
	SAFE_RELEASE(m_RTV);
	SAFE_RELEASE(circle_buffer);
	SAFE_RELEASE(BackBuffer);
	UnregisterClass( L"DirectXApplication", application ); 
	return true;
}

//************************************************************
//************ WINDOWS RELATED *******************************
//************************************************************

// ****************** BEGIN WARNING ***********************// 
// WINDOWS CODE, I DON'T TEACH THIS YOU MUST KNOW IT ALREADY!
	
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,	int nCmdShow );						   
LRESULT CALLBACK WndProc(HWND hWnd,	UINT message, WPARAM wparam, LPARAM lparam );		
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE, LPTSTR, int )
{
	srand(unsigned int(time(0)));
	DEMO_APP myApp(hInstance,(WNDPROC)WndProc);	
    MSG msg; ZeroMemory( &msg, sizeof( msg ) );
    while ( msg.message != WM_QUIT && myApp.Run() )
    {	
	    if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        { 
            TranslateMessage( &msg );
            DispatchMessage( &msg ); 
        }
    }
	myApp.ShutDown(); 
	return 0; 
}
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    if(GetAsyncKeyState(VK_ESCAPE))
		message = WM_DESTROY;
    switch ( message )
    {
        case ( WM_DESTROY ): { PostQuitMessage( 0 ); }
        break;
    }
    return DefWindowProc( hWnd, message, wParam, lParam );
}
//********************* END WARNING ************************//