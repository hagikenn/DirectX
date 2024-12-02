#include "DirectXCommon.h"
#include<cassert>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

using namespace Microsoft::WRL;

void DirectXCommon::Initialize()
{
	//NULL検出
	assert(winApp);

	//メンバ変数に記録
	this->winApp = winApp;

}

//デバイスの生成
void DirectXCommon::CreateDevice()
{
	
	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));


#pragma region コマンドキュー

	//コマンドキュー生成
	Microsoft::WRL::ComPtr<ID3D12CommandQueue>commandQueue = nullptr;
	//ID3D12CommandQueue* commandQueue = nullptr;
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	hr = device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
	//生成できない場合
	assert(SUCCEEDED(hr));

#pragma endregion

#pragma region コマンドアロケータ
	//コマンドアロケータ生成
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator>commandAllocator = nullptr;
	//ID3D12CommandAllocator* commandAllocator = nullptr;
	hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
	//生成できない場合
	assert(SUCCEEDED(hr));

#pragma endregion

#pragma region コマンドリスト
	//コマンドリスト生成
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>commandList = nullptr;
	//ID3D12GraphicsCommandList* commandList = nullptr;
	hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList));
	//生成できない場合
	assert(SUCCEEDED(hr));
#pragma endregion
}

//スワップチェーンの生成
void DirectXCommon::CreateSwapChain()
{
	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));


#pragma region Swap Chainの生成
	//スワップチェイン生成
	Microsoft::WRL::ComPtr<IDXGISwapChain4>swapChain = nullptr;
	//IDXGISwapChain4* swapChain = nullptr;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	swapChainDesc.Width = WinApp::kClientWidth;
	swapChainDesc.Height = WinApp::kClientHeight;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	hr = dxgiFactory->CreateSwapChainForHwnd(commandQueue.Get(), winApp->GetHwnd(), &swapChainDesc, nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(swapChain.GetAddressOf()));
	assert(SUCCEEDED(hr));

	//SwapchainからResourceを引っ張ってくる
	Microsoft::WRL::ComPtr<ID3D12Resource>swapChainResource[2] = { nullptr };
	//ID3D12Resource* swapChainResource[2] = { nullptr };

	hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&swapChainResource[0]));
	assert(SUCCEEDED(hr));

	hr = swapChain->GetBuffer(1, IID_PPV_ARGS(&swapChainResource[1]));
	assert(SUCCEEDED(hr));
#pragma endregion
}

D3D12_CPU_DESCRIPTOR_HANDLE DirectXCommon::GetSRVCPUDescriptorHandle(uint32_t index)
{
	return GetCPUDescriptorHandle(srvDescriptorHeap, descriptorSizeSRV, index);
}
