#include "pch.h"
#include "Engine.h"
#include "Material.h"

void Engine::Init(const WindowInfo& info)
{
	_window = info;	

	// 그려질 화면 크기를 설정
	_viewport = { 0, 0, static_cast<FLOAT>(info.width), static_cast<FLOAT>(info.height), 0.0f, 1.0f };
	_scissorRect = CD3DX12_RECT(0, 0, info.width, info.height);


	//---------------------------------------
	//포인터생성 ( 동적할당으로 만드는 과정 )
	//---------------------------------------
	_device = make_shared<Device>();
	_cmdQueue = make_shared<CommandQueue>();
	_swapChain = make_shared<SwapChain>();
	_rootSignature = make_shared<RootSignature>();
	_tableDescHeap = make_shared<TableDescriptorHeap>();
	_depthStencilBuffer = make_shared<DepthStencilBuffer>();


	_input = make_shared<Input>();
	_timer = make_shared<Timer>();

	//------
	//초기화
	//------
	_device->Init();
	_cmdQueue->Init(_device->GetDevice(), _swapChain);
	_swapChain->Init(info, _device->GetDevice(), _device->GetDXGI(), _cmdQueue->GetCmdQueue());
	_rootSignature->Init();
	_tableDescHeap->Init(256);
	_depthStencilBuffer->Init(_window);

	_input->Init(info.hwnd);
	_timer->Init();

	CreateConstantBuffer(CBV_REGISTER::b0, sizeof(Transform), 256);
	CreateConstantBuffer(CBV_REGISTER::b1, sizeof(MaterialParams), 256);

	ResizeWindow(info.width, info.height);
}

void Engine::Render()
{
	RenderBegin();

	// TODO : 나머지 물체들 그려준다

	RenderEnd();
}

void Engine::Update()
{
	_input->Update();
	_timer->Update();
	ShowFPS();
}

void Engine::RenderBegin()
{
	_cmdQueue->RenderBegin(&_viewport, &_scissorRect);
}

void Engine::RenderEnd()
{
	_cmdQueue->RenderEnd();
}

void Engine::ResizeWindow(int32 width, int32 height)
{
	_window.width = width;
	_window.height = height;

	RECT rect = { 0, 0, width, height };
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	::SetWindowPos(_window.hwnd, 0, 100, 100, width, height, 0);

	_depthStencilBuffer->Init(_window);
}

void Engine::ShowFPS()
{
	uint32 fps = FPS;
	WCHAR text[100] = L"";
	::wsprintf(text, L"FPS : %d", fps);

	::SetWindowText(_window.hwnd, text);
}

void Engine::CreateConstantBuffer(CBV_REGISTER reg, uint32 buffersize, uint32 count)
{
	uint8 typeInt = static_cast<uint8>(reg);
	// 이 assert가 필요한 이유
	// b0 b1 b2 ... 순서대로 CB를 만들어야하기 때문에
	assert(_constantBuffers.size() == typeInt);

	shared_ptr<ConstantBuffer> buffer = make_shared<ConstantBuffer>();
	buffer->Init(reg, buffersize, count);
	_constantBuffers.push_back(buffer);
}
