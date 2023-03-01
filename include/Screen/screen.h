#pragma once
#include <Windows.h>
#include <tchar.h>

class Screen {
public:
	int screen_init(int w, int h, const TCHAR *title);  // ��Ļ��ʼ��
	int screen_close(void);                // �ر���Ļ
	void screen_dispatch(void);              // ������Ϣ
	void screen_update(void);              // ��ʾ FrameBuffer

	// win32 event handler
	static LRESULT screen_events(HWND, UINT, WPARAM, LPARAM);
	unsigned char *get_frame_buffer() {
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


