#pragma once
#include<windows.h>
#include <dinput.h>
#include<wrl.h>
#define DIRECTNPUT_VERSION 0x800//DirectInputのバージョン指定
#include<dinput.h>

class Input
{
public:
	//namespace省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;


	void Initialize(HINSTANCE hInstance, HWND hwnd);
	void Update();

	
private:
	
	//キーボードデバイスの生成
	ComPtr<IDirectInputDevice8> keyboard = nullptr;

	//全キーの入力情報を取得する
	BYTE key[256] = {};

};

