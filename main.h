#pragma once
#include <d3d11.h>

#pragma comment (lib, "d3d11.lib")

IDXGISwapChain* swapchain;
ID3D11Device* dev;
ID3D11DeviceContext* devcon;

void InitD3D(HWND hWnd);
void CleanD3D(void);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);