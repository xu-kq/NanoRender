#pragma once
#include <Windows.h>
#include <tchar.h>

class Screen {
public:
	int screen_init(int w, int h, const TCHAR *title);  // 屏幕初始化
	int screen_close(void);                // 关闭屏幕
	void screen_dispatch(void);              // 处理消息
	void screen_update(void);              // 显示 FrameBuffer

	// win32 event handler
	static LRESULT screen_events(HWND, UINT, WPARAM, LPARAM);
	unsigned char *get_frame_buffer() {
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


