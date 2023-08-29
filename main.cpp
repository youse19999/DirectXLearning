#include <Windows.h>
#include <windowsx.h>
#include "main.h"

LRESULT CALLBACK WindowProc(HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    HWND hWnd;

    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = "OnichanClass";
    RegisterClassEx(&wc);
    hWnd = CreateWindowEx(NULL,
        "OnichanClass",
        "OnichanEngine",
        WS_OVERLAPPEDWINDOW,
        300,
        300,
        500,
        400,
        NULL,
        NULL,
        hInstance,
        NULL);
    ShowWindow(hWnd, nCmdShow);
    InitD3D(hWnd);
    MSG msg = { 0 };
    while (TRUE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                break;
        }
        else
        {
            
        }
    }
    return msg.wParam;
}
void RenderFrame(void)
{
    float clear_color[] = { 0.0, 0.0, 0.5, 1.0 };
    devcon->ClearRenderTargetView(backbuffer, clear_color);
    swapchain->Present(0, 0);
}
void InitD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC scd;
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hWnd;
    scd.SampleDesc.Count = 4;
    scd.Windowed = TRUE;
    D3D11CreateDeviceAndSwapChain(NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        NULL,
        NULL,
        NULL,
        D3D11_SDK_VERSION,
        &scd,
        &swapchain,
        &dev,
        NULL,
        &devcon);
    ID3D11Texture2D* pBackBuffer;
    swapchain->GetBuffer(0u, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
    pBackBuffer->Release();
    devcon->OMSetRenderTargets(1, &backbuffer, NULL);
    RenderFrame();
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = 35;
    viewport.Height = 35;

    devcon->RSSetViewports(1, &viewport);
}
void CleanD3D()
{
    swapchain->Release();
    dev->Release();
    backbuffer->Release();
    devcon->Release();
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
        {
            CleanD3D();
            PostQuitMessage(0);
            return 0;
        } break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}
