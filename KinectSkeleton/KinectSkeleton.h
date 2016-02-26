#pragma once

#include "resource.h"
#include <Windows.h>
#include <NuiApi.h>
#include <d2d1.h>

class CKinectSkeleton
{
	static const int		cScreenWidth = 320;
	static const int		cScreenHeight = 240;

	static const int		cStatusMessageMaxLen = MAX_PATH*2;

public:
	CKinectSkeleton();
	~CKinectSkeleton();
	
	static LRESULT CALLBACK MessageRouter(HWND hWnd, UINT message, WPARAM, wParam, LPARAM lParam);
	LRESULT CALLBACK	DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	int						Run(HINSTANCE hInstance, int nCmdShow);
private:
	HWND					m_hWnd;
	bool					m_bSeatedMode;

	//current Kinect Sensor
	INuiSensor*				m_pNuiSensor;

	ID2D1HwndRenderTarget*	m_pRenderTarget;
	ID2D1SolidColorBrush*	m_pBrushJointTracked;
	ID2D1SolidColorBrush*	m_pBrushJointInferred;
	ID2D1SolidColorBrush*	m_pBrushBoneTracked;
	ID2D1SolidColorBrush*	m_pBrushBoneInferred;
	D2D1_POINT_2F			m_Points[NUI_SKELETON_POSITION_COUNT];

	ID2D1Factory*			m_pD2DFactory;

	HANDLE					m_pSkeletonStreamHandle;
	HANDLE					m_hNextSkeletonEvent;
	
	void					Update();

	HRESULT					CreateFirstConnected();

	void					ProcessSkeleton();

	HRESULT					EnsureDirect2DResources();

	void					DiscardDirect2DResources();

	void					DrawBone(const NUI_SKELETON_DATA & skel, NUI_SKELETON_POSITION_INDEX bone0, NUI_SKELETON_POSITION_INDEX bone1);

	void					DrawSkeleton(const NUI_SKELETON_DATA &skel, int windowWidth, int windowHeight);

	D2D1_POINT_2F			SkeletonToScreen(Vector4 skeletonPoint, int width, int height);

	void					SetStatusMessage(WCHAR* szMessage);
};