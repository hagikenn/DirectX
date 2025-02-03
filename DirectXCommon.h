#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include"WinApp.h"
#include<string>
#include<array>
#include<dxcapi.h>
#include"externals/DirectXTex/DirectXTex.h"
#include <cassert>
#include "Logger.h"
#include <format>
#include "StringUtility.h"
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#include "externals/imgui/imgui.h"
#include "externals/imgui/imgui_impl_dx12.h"
#include "externals/imgui/imgui_impl_win32.h"
#include<chrono>
#include<thread>

class DirectXCommon
{
public://メンバ関数
	//初期化
	void Initialize(WinApp* winApp);
	
	//getter
	ID3D12Device* GetDevice()const { return device_.Get(); }
	ID3D12GraphicsCommandList* GetCommandList()  const { return commandList_.Get(); }
	ID3D12DescriptorHeap* GetSrvDescriptorHeap()const { return srvDescriptorHeap.Get(); }

	//描画前処理
	void PreDraw();

	//描画後処理
	void PostDraw();

	//シェーダーのコンパイル
	Microsoft::WRL::ComPtr<IDxcBlob>CompileShader(
		const std::wstring& filePath, const wchar_t* profile);

	/// <summary>
	/// バッファリソースの生成
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D12Resource>CreateBufferResource(size_t sizeInBytes);

	/// <summary>
	/// テクスチャリソースの生成
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D12Resource>CreateTextureResource(
	 const DirectX::TexMetadata& metadata);

	/// <summary>
	/// テクスチャデータの転送
	/// </summary>
	void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

	/// <summary>
	/// テクスチャファイルの読み込み
	/// </summary>
	/// <param name="filePath">テクスチャファイルのパス</param>
	/// <returns>画像イメージデータ</returns>
	static DirectX::ScratchImage LoadTexture(const std::string& filePath);

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

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>rtvDescriptorHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>srvDescriptorHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>dsvDescriptorHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>dsvDescriptorHeap2;
	uint32_t descriptorSizeSRV;
	uint32_t descriptorSizeRTV;
	uint32_t descriptorSizeDSV;

	//記録時間(FPS固定用)
	std::chrono::steady_clock::time_point reference_;

	void Finalize();

#pragma region Fenceの値を更新

	HANDLE fenceEvent;

#pragma endregion


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

	void log(const std::string& message) {
		OutputDebugStringA(message.c_str());
	}

	

	///<summary>
	///デスクリプタヒープを生成する
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);

	
	///<summary>
	///SRVの指定番号のCPUデスクリプタハンドルを取得する
	/// </summary>
	D3D12_CPU_DESCRIPTOR_HANDLE GetSRVCPUDescriptorHandle(uint32_t index);

	///<summary>
	///SRVの指定番号のGPUデスクリプタハンドルを取得する
	/// </summary>
	D3D12_GPU_DESCRIPTOR_HANDLE GetSRVGPUDescriptorHandle(uint32_t index);

	//FPS固定初期化
	void InitializeFixFPS();
	//FPS固定更新
	void UpdateFixFPS();


private:
	

	//WindowAPI
	WinApp* winApp = nullptr;



	
#pragma region デバイスの生成
	//使用するアダプタ用の変数。最初にnullptrを入れておく
	Microsoft::WRL::ComPtr<IDXGIAdapter4>useAdapter = nullptr;

	//DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory7>dxgiFactory;

#pragma endregion

#pragma region コマンド関連の初期化
	//コマンドリスト生成
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>commandList_ = nullptr;
	//コマンドキュー生成
	Microsoft::WRL::ComPtr<ID3D12CommandQueue>commandQueue = nullptr;
	//コマンドアロケータ生成
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator>commandAllocator = nullptr;
#pragma endregion

#pragma region スワップチェーンの生成
	//スワップチェイン生成
	Microsoft::WRL::ComPtr<IDXGISwapChain4>swapChain = nullptr;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

#pragma endregion

#pragma region 各種デスクリプタヒープの生成
	
	
	Microsoft::WRL::ComPtr<ID3D12Resource>textureResource2;
#pragma endregion

#pragma region レンダーターゲットビューの初期化
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];
	D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle;
	//SwapchainからResourceを引っ張ってくる
	Microsoft::WRL::ComPtr<ID3D12Resource>swapChainResource[2]={ nullptr };

#pragma endregion

#pragma region 深度ステンシルビューの初期化

	Microsoft::WRL::ComPtr<ID3D12Resource>depthStencilResource;
#pragma endregion

#pragma region フェンスの初期化
	//初期化で0でFenceを作る
	Microsoft::WRL::ComPtr<ID3D12Fence>fence = nullptr;
#pragma endregion

#pragma region DXCコンパイラの生成
	HRESULT hr;

	//DXCユーティリティの生成
	Microsoft::WRL::ComPtr<IDxcUtils> dxcUtils;
	//DXCコンパイラの生成
	Microsoft::WRL::ComPtr<IDxcCompiler3> dxcCompiler;
	//デフォルトインクルードハンドラの生成
	Microsoft::WRL::ComPtr<IDxcIncludeHandler> includeHandler;

#pragma endregion

#pragma region 描画前描画後処理
	//TransitionBarrierの設定
	D3D12_RESOURCE_BARRIER barrier{};
#pragma endregion




	//フェンス値
	UINT64 fenceValue = 0;


	//ビューポート矩形
	D3D12_VIEWPORT viewport;

	//シザリング矩形
	D3D12_RECT scissorRect{};

	//DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device>device_ = nullptr;


};

