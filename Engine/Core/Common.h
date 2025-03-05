#pragma once

#define WIN_LEAN_AND_MEAN
#define NOMINMAX        //민맥스 함수 있어??

#include <Windows.h>
#include<comdef.h>
//오류 메세지 출력 매크로 함수.//message는 와일드 캐릭터로 들어온다. //인라인함수로 안하면, 진짜 파일이름 나오기에, 매크로로 해서,,, 지정해줌
#define ShowErrorMessage(message, reason)           \
wchar_t buffer[256]={};                             \
swprintf_s(buffer,256,TEXT("[File: %s] \n [Line: %d] \n [Funtion: %s] \n [Message: %s] \n [Reason: %s]")        \
                                ,TEXT(__FILE__) , __LINE__, TEXT(__FUNCTION__), message, reason );                \
MessageBox(nullptr, buffer, TEXT("Error"), MB_OK);

//D3D 호출 실패 확인 매크로 함수	//매크로는 백슬래시 있어야 함.단 마지막줄앤 안씀.
// D3D 호출 실패 확인 매크로 함수.
#define ThrowIfFailed(result, message)                    \
if (FAILED(result))                                        \
{                                                        \
    _com_error error(result);                            \
   ShowErrorMessage(message, error.ErrorMessage());       \
    __debugbreak();                                        \
}                                                           