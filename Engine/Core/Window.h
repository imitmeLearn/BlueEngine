#pragma once
#include<Windows.h>
#include <string>
#include"Type.h"
namespace Blue
{
class Window	//윈도우 클래스
{
public:
	Window(uint32 width,uint32 height
	,const std::wstring& title

	,HINSTANCE instance
	,WNDPROC messageProcedure
	);
	~Window();
	void SetWidhHeight(uint32 width,uint32 height);

	//GETTER, SETTER
	inline const uint32 Width() const
	{
		return width;
	}
	inline const uint32 Height() const
	{
		return height;
	}
	inline  HWND Handle () const
	{
		return handle;
	}
	std::wstring Title() const
	{
		return title;
	}

private:

	uint32 width = 0;	//unsigned int width = 0;
	unsigned int height= 0;
	std::wstring title = nullptr;
	std::wstring className = TEXT("Engine Class");
	HWND handle = nullptr;
	HINSTANCE instance = nullptr;
};
}