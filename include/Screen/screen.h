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
	                                                   _T("Left/Right: rotation, Space: switch state"));  // ��Ļ��ʼ��
	int screen_close(void);                // �ر���Ļ
	void screen_dispatch(void);              // ������Ϣ
	void screen_update(void);              // ��ʾ FrameBuffer

	// win32 event handler
	static LRESULT screen_events(HWND, UINT, WPARAM, LPARAM);
	unsigned char *getFrameBuffer() {
		return screen_fb;
	}

public:
	int screen_w = 0, screen_h = 0;
	int screen_mx = 0, screen_my = 0, screen_mb = 0;
	HWND screen_handle = NULL;    // ������ HWND
	HDC screen_dc = NULL;      // ���׵� HDC
	HBITMAP screen_hb = NULL;    // DIB
	HBITMAP screen_ob = NULL;    // �ϵ� BITMAP
	unsigned char *screen_fb = NULL;    // frame buffer
	long screen_pitch = 0;

	static int screen_exit;
	static int screen_keys[512];  // ��ǰ���̰���״̬
};


