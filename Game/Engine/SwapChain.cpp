#include "pch.h"
#include "SwapChain.h"

void SwapChain::Init(const WindowInfo& _info, ComPtr<IDXGIFactory> _dxgi, ComPtr<ID3D12CommandQueue> _cmdQueue)
{
	// ������ ���� ���� ������
	m_swapChain.Reset();

	DXGI_SWAP_CHAIN_DESC sd;

	sd.BufferDesc.Width = static_cast<uint32>(_info.width); // ������ �ػ� �ʺ�
	sd.BufferDesc.Height = static_cast<uint32>(_info.height); // ������ �ػ� ����
	sd.BufferDesc.RefreshRate.Numerator = 60; // ȭ�� ���� ����
	sd.BufferDesc.RefreshRate.Denominator = 1; // ȭ�� ���� ����
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // ������ ���÷��� ����
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = 1; // ��Ƽ ���ø� OFF
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // �ĸ� ���ۿ� �������� �� 
	sd.BufferCount = SWAP_CHAIN_BUFFER_COUNT; // ����+�ĸ� ����
	sd.OutputWindow = _info.hwnd;
	sd.Windowed = _info.windowed;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // ���� �ĸ� ���� ��ü �� ���� ������ ���� ����
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	_dxgi->CreateSwapChain(_cmdQueue.Get(), &sd, &m_swapChain);

	for (int32 i = 0; i < SWAP_CHAIN_BUFFER_COUNT; i++)
		m_swapChain->GetBuffer(i, IID_PPV_ARGS(&m_renderTargets[i]));
}

void SwapChain::Present()
{
	// Present the frame.
	m_swapChain->Present(0, 0);
}

void SwapChain::SwapIndex()
{
	m_backBufferIndex = (m_backBufferIndex + 1) % SWAP_CHAIN_BUFFER_COUNT;
}