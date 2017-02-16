
///////////////////////////////////////////
//                                       //
//       THIS IS THE WORK OF:            //
//     Programmer: Aaron Ridlen          //
//     Instructor: Larri Nori            //
//      Date:  AUGUST 2016               //
//                                       //
///////////////////////////////////////////

#include <iostream>
#include <ctime>
#include "XTime.h"
#include <Windows.h>
#include"Math.h"
using namespace std;


#define SAFE_RELEASE(p){if(p){p->Release();p=nullptr;}}
#include <d3d11.h>
#include <DirectXMath.h>
#pragma comment(lib,"d3d11.lib")
using namespace DirectX;

struct Simple_Vertex
{
	float x, y;
};

#include "Trivial_PS.csh"
#include "Trivial_VS.csh"
#include "Trivial_VS_GRID.csh"
#define BACKBUFFER_WIDTH	500
#define BACKBUFFER_HEIGHT	500

class DEMO_APP
{	
	HINSTANCE						application;
	WNDPROC							appWndProc;
	HWND							window;
	
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;
	ID3D11RenderTargetView* m_RTV;
	D3D11_VIEWPORT m_view;
	IDXGISwapChain* m_swap;
	ID3D11Texture2D * BackBuffer;
	ID3D11DepthStencilState * pDSState;
	ID3D11DepthStencilView* pDSV;
	
	ID3D11Buffer* circle_buffer;
	ID3D11Buffer* circle_buffer_pretty;
	ID3D11InputLayout* m_layout;
	
	ID3D11VertexShader* _vertshader;
	ID3D11PixelShader* _pixelshader;
	

public:
	
	XTime m_time;
	struct Send_To_VRAM
	{
		XMFLOAT4 constantColor;
		XMFLOAT2 constantOffset;
		XMFLOAT2 padding;
	};
	Send_To_VRAM toshader;
	float velX = 1.0f;
	float velY = 0.5f;
	ID3D11Buffer* grid_buffer;
	ID3D11InputLayout* grid_layout;
	ID3D11VertexShader* gridVSshader;
	DEMO_APP(HINSTANCE hinst, WNDPROC proc);
	bool Run();
	bool ShutDown();
};


DEMO_APP::DEMO_APP(HINSTANCE hinst, WNDPROC proc)
{
	
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

	
	unsigned int flag = 0;
#if _DEBUG 

	flag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	
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

   D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flag, NULL, NULL, D3D11_SDK_VERSION, &CHAIN, &m_swap, &m_device, NULL, &m_context);
	
   m_swap->GetBuffer(0, _uuidof(BackBuffer), reinterpret_cast<void**>(&BackBuffer));
   m_device->CreateRenderTargetView(BackBuffer, NULL, &m_RTV);
	
   m_view.Width = BACKBUFFER_WIDTH;
   m_view.Height = BACKBUFFER_HEIGHT;
   m_view.MinDepth = 0.0F;
   m_view.MaxDepth = 1.0F;
   m_view.TopLeftX = 0;
   m_view.TopLeftY = 0;
   

   Simple_Vertex points[361];
   for (unsigned int i = 0; i < 361; ++i)
   {
	  
		   points[i].x = cosf(PI * i / 180.0f)*0.2f;
		   points[i].y = sinf(PI * i / 180.0f)*0.2f;
	   

   }
   points[360] = points[0];
	
   D3D11_BUFFER_DESC VERTEX_DESC;
   VERTEX_DESC.Usage = D3D11_USAGE_IMMUTABLE;
   VERTEX_DESC.BindFlags = D3D11_BIND_VERTEX_BUFFER;
   VERTEX_DESC.CPUAccessFlags = NULL;
   VERTEX_DESC.MiscFlags = NULL;
   VERTEX_DESC.ByteWidth = sizeof(Simple_Vertex) * 361;
   VERTEX_DESC.StructureByteStride = sizeof(Simple_Vertex);
   
   D3D11_SUBRESOURCE_DATA _data;

   _data.SysMemPitch = 0;
   _data.SysMemSlicePitch = 0;
   _data.pSysMem = points;
	
   m_device->CreateBuffer(&VERTEX_DESC, &_data, &circle_buffer);


   D3D11_BUFFER_DESC VERTEX_DESC_SHADER;
   VERTEX_DESC.Usage = D3D11_USAGE_IMMUTABLE;
   VERTEX_DESC.BindFlags = D3D11_BIND_VERTEX_BUFFER;
   VERTEX_DESC.CPUAccessFlags = NULL;
   VERTEX_DESC.MiscFlags = NULL;
   VERTEX_DESC.ByteWidth = sizeof(Simple_Vertex) * 361;
   VERTEX_DESC.StructureByteStride = sizeof(Simple_Vertex);
  
   D3D11_SUBRESOURCE_DATA _dataShader;

   _data.SysMemPitch = 0;
   _data.SysMemSlicePitch = 0;
   _data.pSysMem = points;
  
   m_device->CreateBuffer(&VERTEX_DESC_SHADER, &_dataShader, &circle_buffer_pretty);
	
   m_device->CreatePixelShader(Trivial_PS, sizeof(Trivial_PS), NULL, &_pixelshader);
   m_device->CreateVertexShader(Trivial_VS, sizeof(Trivial_VS), NULL, &_vertshader);
	m_device->CreateVertexShader(Trivial_VS_GRID, sizeof(Trivial_VS_GRID), NULL, &gridVSshader);

   D3D11_INPUT_ELEMENT_DESC vLayout[] =
   {
	   { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	  // { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
   };

   m_device->CreateInputLayout(vLayout, ARRAYSIZE(vLayout), Trivial_VS, sizeof(Trivial_VS), &m_layout);
   m_device->CreateInputLayout(vLayout, 1, Trivial_VS_GRID, sizeof(Trivial_VS_GRID), &grid_layout);
   D3D11_BUFFER_DESC constbuff;
   constbuff.ByteWidth = sizeof(Send_To_VRAM);
   constbuff.Usage = D3D11_USAGE_DYNAMIC;
   constbuff.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
   constbuff.MiscFlags = NULL;
   constbuff.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
   constbuff.StructureByteStride = sizeof(Send_To_VRAM);
   m_device->CreateBuffer(&constbuff, NULL, &circle_buffer_pretty);
  
	
   toshader.constantOffset.x = 0;
   toshader.constantOffset.y = 0;
   toshader.constantColor.x = 1;
   toshader.constantColor.y = 1;
   toshader.constantColor.z = 1;
   toshader.constantColor.w = 1;
   
   /// 1) Create a grid using your struct, need a check, current position,number of boxes, and rate of change
   Simple_Vertex grid[1200];
   bool check = false;
   float currx = -1.0f;
   float curry = 1.0f;
   float rate = 0.1f;
   int boxescount = 0;
   /// 2) Loop through grid to determine where boxes need to be located while your check is active or not
  /// 3) increase position by rate
   for (unsigned int i = 0; i < 1200;)
   {
	   if (check)
	   {
		   grid[i].x = currx;
		   grid[i].y = curry;
		   i++;	   
		   grid[i].x = currx + rate; 
		   grid[i].y = curry;
		   i++;	   
		   grid[i].x = currx; 
		   grid[i].y = curry - rate;
		   i++;	   
		   grid[i].x = currx + rate;
		   grid[i].y = curry;
		   i++;	   
		   grid[i].x = currx + rate;
		   grid[i].y = curry - rate;
		   i++;	   
		   grid[i].x = currx;
		   grid[i].y = curry - rate;
		   i++;
	   }
	   currx += rate;
	   /// 4) Determined by your number of boxes decide when to change x to -1 and y-=rate else change your check
	   boxescount++;
	   if (boxescount % 20 == 0)
	   {
		   currx = -1.0f;
		   curry -= rate;
	   }
	   else
		   check = !check;
   }
   //Create the grid buffer 
   //use zero memory!!
   D3D11_BUFFER_DESC grid_Desc;
   ZeroMemory(&grid_Desc, sizeof(D3D11_BUFFER_DESC));
   grid_Desc.Usage = D3D11_USAGE_IMMUTABLE;
   grid_Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
   grid_Desc.CPUAccessFlags = NULL;
   grid_Desc.ByteWidth = sizeof(Simple_Vertex) * 1200;

   D3D11_SUBRESOURCE_DATA gridData;
   gridData.pSysMem = grid;
   gridData.SysMemPitch = 0;
   gridData.SysMemSlicePitch = 0;

   m_device->CreateBuffer(&grid_Desc, &gridData, &grid_buffer);
}


bool DEMO_APP::Run()
{
	m_time.Signal();
	
	// 1) shader offsets need to increment by their velocity based on time 
	toshader.constantOffset.x += (velX * (float)m_time.Delta());
	toshader.constantOffset.y += (velY * (float)m_time.Delta());
	// 2) Check to see if it goes pass the border
	float borderline = 0.8f;
	if (toshader.constantOffset.x >= borderline)
	{
		velX = -velX;
		toshader.constantOffset.x = borderline;
	}
	if (toshader.constantOffset.y >= borderline)
	{
		velY = -velY;
		toshader.constantOffset.y = borderline;
	}
	if (toshader.constantOffset.x <= -borderline)
	{
		velX = -velX;
		toshader.constantOffset.x = -borderline;
	}
	if (toshader.constantOffset.y <= -borderline)
	{
		velY = -velY;
		toshader.constantOffset.y = -borderline;
	}
	
	m_context->OMSetRenderTargets(1, &m_RTV, NULL);

	m_context->RSSetViewports(1, &m_view);
	
	float color[4] = { 0.0f,0.0f,1.0f,0.0f };
	m_context->ClearRenderTargetView(m_RTV, color);
	//m_context->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1, 0);

	D3D11_MAPPED_SUBRESOURCE mapData;
	m_context->Map(circle_buffer_pretty, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mapData);
	memcpy_s(mapData.pData, sizeof(Send_To_VRAM), &toshader, sizeof(Send_To_VRAM));
	m_context->Unmap(circle_buffer_pretty, NULL);
	
	m_context->VSSetConstantBuffers(0, 1, &circle_buffer_pretty);

	unsigned int gridstride = sizeof(Simple_Vertex);
	unsigned int gridoffset = 0;
	m_context->IASetVertexBuffers(0, 1, &grid_buffer, &gridstride, &gridoffset);

	m_context->VSSetShader(gridVSshader, NULL, 0);
	m_context->PSSetShader(_pixelshader, NULL, 0);

	m_context->IASetInputLayout(grid_layout);

	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_context->Draw(1200, 0);

	
	unsigned int stride = sizeof(Simple_Vertex);
	unsigned int offset_vert = 0;
	m_context->IASetVertexBuffers(0, 1, &circle_buffer, &stride, &offset_vert);
	

	m_context->PSSetShader(_pixelshader, NULL, 0);
	m_context->VSSetShader(_vertshader, NULL, 0);

	m_context->IASetInputLayout(m_layout);
	
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	
	m_context->Draw(361, 0);
	
	m_swap->Present(0, 0);
	
	return true; 
}


bool DEMO_APP::ShutDown()
{

	SAFE_RELEASE(m_device);
	SAFE_RELEASE(m_swap);
	
	SAFE_RELEASE(m_context);
	SAFE_RELEASE(m_RTV);
	SAFE_RELEASE(circle_buffer);
	SAFE_RELEASE(BackBuffer);
	SAFE_RELEASE(gridVSshader);
	SAFE_RELEASE(grid_layout);
	SAFE_RELEASE(grid_buffer);
	UnregisterClass( L"DirectXApplication", application ); 
	return true;
}

	
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
