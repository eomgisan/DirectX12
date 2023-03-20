#pragma once

class SwapChain;
class DescriptorHeap;


class CommandQueue
{
public:

	void Init(ComPtr<ID3D12Device> _device, shared_ptr<SwapChain> _swapChain, shared_ptr<DescriptorHeap> _descHeap);
	void WaitSync();

	void RenderBegin(const D3D12_VIEWPORT* _vp, const D3D12_RECT* _rect);
	void RenderEnd();

	ComPtr<ID3D12CommandQueue> GetCmdQueue() { return m_cmdQueue; }

	~CommandQueue();

private:

	// Command Queue : DX12에 등장
	// 외주를 요청할 때, 하나씩 요청하면 비효율적
	// [외주 목록]에 일감을 차곡차곡 기록했다 한번에 요청하자

	ComPtr<ID3D12CommandQueue>			m_cmdQueue;
	ComPtr<ID3D12CommandAllocator>		m_cmdAlloc;
	ComPtr<ID3D12GraphicsCommandList>	m_cmdList;


	// Fence : 울타리 ( 명령을 모두 수행할때까지 기다려주겠다 )
	// CPU / GPU 동기화를 위한 간단한 도구
	ComPtr<ID3D12Fence>					m_fence;
	uint32								m_fenceValue = 0;
	HANDLE								m_fenceEvent = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain>				m_swapChain;
	shared_ptr<DescriptorHeap>			m_descHeap;

};

