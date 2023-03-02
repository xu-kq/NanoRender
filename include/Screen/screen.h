#pragma once
#include <iostream>
#include <tchar.h>
#include <Windows.h>

class Screen {
private:
	Screen() = default;
public:
	static Screen &Instance() {
		static Screen screen;
		return screen;
	}
	Screen &setting(int w, int h) {
		screen_init(w, h);
		return *this;
	}
	int screen_init(int w, int h, const TCHAR *title = _T("NanoRender (software render tutorial) - ")
	                                                   _T("Left/Right: rotation, Space: switch state"));  // 屏幕初始化
	int screen_close(void);                // 关闭屏幕
	void screen_dispatch(void);              // 处理消息
	void screen_update(void);              // 显示 FrameBuffer

	// win32 event handler
	static LRESULT screen_events(HWND, UINT, WPARAM, LPARAM);
	unsigned char *getFrameBuffer() {
		return screen_fb;
	}

public:
	int screen_w = 0, screen_h = 0;
	int screen_mx = 0, screen_my = 0, screen_mb = 0;
	HWND screen_handle = NULL;    // 主窗口 HWND
	HDC screen_dc = NULL;      // 配套的 HDC
	HBITMAP screen_hb = NULL;    // DIB
	HBITMAP screen_ob = NULL;    // 老的 BITMAP
	unsigned char *screen_fb = NULL;    // frame buffer
	long screen_pitch = 0;

	static int screen_exit;
	static int screen_keys[512];  // 当前键盘按下状态
};


