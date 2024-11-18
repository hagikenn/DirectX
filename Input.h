#pragma once
#include<windows.h>
#include <dinput.h>
#include<wrl.h>
#define DIRECTNPUT_VERSION 0x800//DirectInputのバージョン指定
#include"WinApp.h"


class Input
{
public:
	//namespace省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

	void Initialize(WinApp* winApp);
	void Update();

	bool PushKey(BYTE keyNumber);
	bool TriggerKey(BYTE keyNumber);

private:
	
	//キーボードデバイスの生成
	ComPtr<IDirectInputDevice8> keyboard = nullptr;

	//DirectInputのインスタンス
	ComPtr<IDirectInput8>directInput=nullptr;

	//全キーの入力情報を取得する
	BYTE key[256] = {};

	//前回の全キーの状態
	BYTE keyPre[256] = {};

	//WindowsAPI
	WinApp* winApp_ = nullptr;

};

