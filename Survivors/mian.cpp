#include <graphics.h>
#include <string>

int idx_current_anim = 0;

const int PLAYER_ANIM_NUM = 5;

IMAGE img_player_left[PLAYER_ANIM_NUM + 1];
IMAGE img_player_right[PLAYER_ANIM_NUM + 1];

#pragma comment(lib, "MSIMG32.LIB")

inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

void LoadAnimation()
{
	for (size_t i = 1; i <= PLAYER_ANIM_NUM; i++)
	{
		std::wstring path = L"img/player_left" + std::to_wstring(i) + L".png";
		loadimage(&img_player_left[i], path.c_str());
	}

	for (size_t i = 1; i <= PLAYER_ANIM_NUM; i++)
	{
		std::wstring path = L"img/player_right" + std::to_wstring(i) + L".png";
		loadimage(&img_player_right[i], path.c_str());
	}
}

int main()
{
	initgraph(1280, 768);

	bool running = true;

	ExMessage msg;
	IMAGE img_background;

	loadimage(&img_background, _T("img/background.jpeg"));

	BeginBatchDraw();

	while (running)
	{
		DWORD start_time = GetTickCount();

		while (peekmessage(&msg))
		{

		}

		static int counter = 0;
		if (++counter % 5 == 0)
			idx_current_anim++;


		// 是动画循环播放
		idx_current_anim = idx_current_anim % PLAYER_ANIM_NUM;


		cleardevice();

		LoadAnimation();

		putimage(0, 0, &img_background);
		putimage_alpha(500, 500, &img_player_left[idx_current_anim]);

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 144)
		{
			Sleep(1000 / 144 - delta_time);
		}
	}

	EndBatchDraw();

	return 0;
}