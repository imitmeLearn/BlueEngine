﻿#pragma once
#include "Texture.h"
#include "Core/Type.h"
#include <d3d11.h>

namespace Blue
{
class RenderTexture: public Texture
{
public:
	RenderTexture(uint32 width = 0,uint32 height = 0);
	virtual ~RenderTexture();
	//GETTER - RendertargetView
	ID3D11RenderTargetView* GetRenderTarget() const
	{
		return renderTargetView;
	}

	ID3D11RenderTargetView** GetRenderTargetAddress()
	{
		return &renderTargetView;
	}

	//GETTER - Depth stencil view
	ID3D11DepthStencilView* DepthStencilView()
	{
		return depthStencilView;
	}
private:
	ID3D11RenderTargetView* renderTargetView = nullptr;
	ID3D11DepthStencilView* depthStencilView = nullptr;
};
}