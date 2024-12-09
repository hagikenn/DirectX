#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include"WinApp.h"
#include<string>
#include<array>
#include<dxcapi.h>
#include"externals/DirectXTex/DirectXTex.h"

class DirectXCommon
{
public://メンバ関数
	//初期化
	void Initialize(WinApp* winApp);

private:
	//デバイスの生成
	void CreateDevice();
	//コマンド関連の初期化
	void CommandInitialize();
	//スワップチェーンの生成
	void CreateSwapChain();
	//深度バッファの生成
	void DepthBuffer();
	//各種デスクリプタヒープの生成
	void DescriptorHeap();
	//レンダーターゲットビューの初期化
	void RTVInitialize();
	//深度ステンシルビューの初期化
	void DSVInitialize();
	//フェンスの初期化
	void FenceInitialize();
	//ビューポート矩形の初期化
	void ViewPortRectangle();
	//シザリング矩形の初期化
	void ScissoringRectangle();
	//DXCコンパイラの生成
	void CreateCompiler();
	//ImGuiの初期化
	void ImGuiInitialize();


	///<summary>
	///デスクリプタヒープを生成する
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);

	///<summary>
	///指定番号のCPUデスクリプタハンドルを取得する
	/// </summary>
	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap,
		uint32_t descriptorSize, uint32_t index);

	///<summary>
	///指定番号のGPUデスクリプタハンドルを取得する
	/// </summary>
	static D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap,
		uint32_t descriptorSize, uint32_t index);

	///<summary>
	///SRVの指定番号のCPUデスクリプタハンドルを取得する
	/// </summary>
	D3D12_CPU_DESCRIPTOR_HANDLE GetSRVCPUDescriptorHandle(uint32_t index);

	///<summary>
	///SRVの指定番号のGPUデスクリプタハンドルを取得する
	/// </summary>
	D3D12_GPU_DESCRIPTOR_HANDLE GetSRVGPUDescriptorHandle(uint32_t index);



private:
	//コマンドキュー生成
	Microsoft::WRL::ComPtr<ID3D12CommandQueue>commandQueue = nullptr;

	//WindowAPI
	WinApp* winApp = nullptr;

	//DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device>device = nullptr;
	//DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory7>dxgiFactory;



#pragma region コマンドリスト
	//コマンドリスト生成
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>commandList = nullptr;
	
#pragma endregion

#pragma region スワップチェーンの生成
	//スワップチェイン生成
	Microsoft::WRL::ComPtr<IDXGISwapChain4>swapChain = nullptr;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};


	//SwapchainからResourceを引っ張ってくる
	Microsoft::WRL::ComPtr<ID3D12Resource>swapChainResource[2] = { nullptr };

#pragma endregion

#pragma region 各種デスクリプタヒープの生成
	
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>rtvDescriptorHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>srvDescriptorHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>dsvDescriptorHeap;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>dsvDescriptorHeap2;
	uint32_t descriptorSizeSRV;
	uint32_t descriptorSizeRTV;
	uint32_t descriptorSizeDSV;
	Microsoft::WRL::ComPtr<ID3D12Resource>textureResource2;
	Microsoft::WRL::ComPtr<ID3D12Resource>depthStencilResource2;
#pragma endregion

#pragma region レンダーターゲットビューの初期化
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};


	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];
#pragma endregion

#pragma region 深度ステンシルビューの初期化

	Microsoft::WRL::ComPtr<ID3D12Resource>depthStencilResource;
#pragma endregion

#pragma region フェンスの初期化
	//初期化で0でFenceを作る
	Microsoft::WRL::ComPtr<ID3D12Fence>fence = nullptr;
#pragma endregion

#pragma region DXCコンパイラの生成
	//DXCユーティリティの生成
	IDxcUtils* dxcUtils;
	//DXCコンパイラの生成
	IDxcCompiler3* dxcCompiler;
	//デフォルトインクルードハンドラの生成
	IDxcIncludeHandler* includeHandler;
#pragma endregion

	//スワップチェーンリソース
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 2>swapChainResource;


};

