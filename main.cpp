WNDCLASS wc{};

wc.lpfnwndProc = WindowProc;
wc.lpszClassName = L"CG2WindowClass"
wc.hInstance = GetModuleHandle(nullptr);
wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

RwgisterCllass(&wc);



#include<cstdint>

const int32_t kClientWidth = 1280;
const int32_t kClientHeight = 720;

RECT wrc = { 0,0,kClientWidth,kClientHeight };

AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);
