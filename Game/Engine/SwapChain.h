#pragma once


// 교환사슬
// [외주 과정]
// - 현재 게임 세상에 있는 상황을 묘사
// - 어떤 공식으로 어떻게 계산할지 던져줌
// - GPU가 열심히 계산 ( 외주 )
// - 결과물을 받아서 화면에 그려준다.

// [ 외주 결과물 ] 을 어디서 받지?
// - 어떤 종이( Buffer )에 그려서 건내달라하자
// - 특수 종이를 만들어서 -> 처음에 건내주고 -> 결과물을 해당 종이에 받는다.
// - 우리 화면에 특수 종이를 출력한다.

// [?]
// - 그런데 화면에 현재 결과물 출력하는 와중에, 다음 화면도 외주 맡겨야함
// - 현재 화면 결과물은 이미 화면 출력에 사용중
// - 특수종이 2개 만들어서 하나는 그리고 하나는 외주 하자
// - 이게 바로 double buffering

// - [1~2]
// 현재화면 [1] <-> GPU 작업중 [2] BackBuffer


class SwapChain
{
public:
	void Init(const WindowInfo& _info, ComPtr<IDXGIFactory> _dxgi, ComPtr<ID3D12CommandQueue> _cmdQueue);
	void Present();
	void SwapIndex();

	ComPtr<IDXGISwapChain> GetSwapChain() { return m_swapChain; }
	ComPtr<ID3D12Resource> GetRenderTarget(int32 index) { return m_renderTargets[index]; }

	uint32 GetCurrentBackBufferIndex() { return m_backBufferIndex; }
	ComPtr<ID3D12Resource> GetCurrentBackBufferResource() { return m_renderTargets[m_backBufferIndex]; }
private:

	ComPtr<IDXGISwapChain>	m_swapChain;
	ComPtr<ID3D12Resource>	m_renderTargets[SWAP_CHAIN_BUFFER_COUNT];
	uint32					m_backBufferIndex = 0;
};

