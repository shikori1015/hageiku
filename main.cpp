/**************************************************************/
/* kadai04 ポリゴン描画 　　　　　　　　　　　　　　　　　　　*/
/* AT12A242 21 Shiori Segawa　　　　　　　　　　　　　　　　　*/
/**************************************************************/


//-------------------------------------------------------------------------------------------------------------------------------
//　ヘッダファイルの定義
//-------------------------------------------------------------------------------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Polygon.h"
#include "main.h"

//-------------------------------------------------------------------------------------------------------------------------------
//　構造体定義
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
//　マクロ定義
//-------------------------------------------------------------------------------------------------------------------------------
#define CLASS_NAME			"サンプル"
#define WINDOW_NAME			"ウィンドウ表示"
#define SCREEN_WIDTH		(1280/*800*/)
#define SCREEN_HEIGHT		(720/*600*/)

//-------------------------------------------------------------------------------------------------------------------------------
//　プロトタイプ宣言
//-------------------------------------------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
/*#ifdef _DEBUG
void DrawFPS(void);
#endi*/ 


// ------------------------------------------------------------------------------------------------------------------------------ -
//　グローバル変数
//-------------------------------------------------------------------------------------------------------------------------------
LPDIRECT3D9        g_pD3D = NULL;
LPDIRECT3DDEVICE9  g_pD3DDevice = NULL;

static int g_nAnimCount = 0;

//#ifdef _DEBUG
//LPD3DXFONT g_pFont = NULL;


//-------------------------------------------------------------------------------------------------------------------------------
//　メイン関数
//-------------------------------------------------------------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,					//int Main(void)と同じ
	LPSTR lpCmdLine, int nCmdShow)
{
	//構造体宣言
	WNDCLASSEX wcex = 
	{
		sizeof(WNDCLASSEX),								//構造体のサイズ
		CS_VREDRAW | CS_HREDRAW,						//スタイル
		WndProc,
		0,
		0,
		hInstance,
		NULL,											//アイコン
		LoadCursor(NULL, IDC_ARROW),					//カソル
		(HBRUSH)(COLOR_WINDOW + 1),						//背景
		NULL,											//
		CLASS_NAME,
		NULL
	};

	//もう一つ書き方の例
	//WNDCLASSEX wcex;
	//wcex.cbSize = sizeof(WNDCLASSEX);	など

	//OSにウィンドウを作ることを宣言する
	RegisterClassEx(&wcex);

	//ウィンドハンドル型
	HWND hWnd = CreateWindowEx
	(
		0,
		CLASS_NAME, 									//クラス名
		WINDOW_NAME,									//タイトル名
		WS_OVERLAPPEDWINDOW,							//ウィンドスタイル
		CW_USEDEFAULT,									//ウィンドの左上座標
		CW_USEDEFAULT,
		SCREEN_WIDTH,									//フレイムを含めたウィンドの幅高さ
		SCREEN_HEIGHT,
		NULL,											//親がない
		NULL,											//メニュがない
		hInstance,
		NULL
	);

	//ウィンド表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//メッセージループ
	MSG msg;		//メッセージを受け取る変数
	DWORD OldTime = 0;
	DWORD NowTime = 0;

	GetD3DDevice();
	Init(hInstance, hWnd, TRUE);

	//ゲームループの精度をよくする   ループ処理の終わった後にEndを書く
	timeBeginPeriod(1);
	
	//ゲームループの作成
	for (;;) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			//メッセージ処理
			if (msg.message == WM_QUIT) {
				break;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			//ゲーム処理
			//今の時間
			NowTime = timeGetTime();

			if ((NowTime - OldTime) >= (1000 / 60)) {
				//厳密には更新から描画までがゲーム処理
				//更新
				Update();
				//描画
				Draw();
				//前フレームの時間=今の時間
				OldTime = NowTime;
			}
		}
	}

	//timeBeginPeriodを終わる
	timeEndPeriod(1);

	Uninit();

	return (int)msg.wParam;
}


//-------------------------------------------------------------------------------------------------------------------------------
//　他の関数
//-------------------------------------------------------------------------------------------------------------------------------
//												↓追加情報
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg) 
	{
		
		case WM_DESTROY:								
			PostQuitMessage(0);							
			break;

		case WM_LBUTTONDOWN:
			SetFocus(hWnd);
			break;

		case WM_KEYDOWN:								
			switch (wParam)
			{
				case VK_ESCAPE:							
				{										
					int nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_DEFBUTTON2);
					if (nID == IDYES)
					{
						DestroyWindow(hWnd);
					}
					break;
				}
			}
			break;

		case WM_CLOSE:
		{
			int nID = MessageBox(hWnd, "終了しますか", "終了メッセージ", MB_YESNO | MB_DEFBUTTON2);
			if (nID = IDYES)
			{
				DestroyWindow(hWnd);
			}
			else
			{
				return 0;
			}
			break;
		}

		default:
			break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	
}

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//Direct3Dインターフェースの取得
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	D3DDISPLAYMODE d3ddm;

	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータ
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil =TRUE ;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//頂点処理はCPUで行う
	//D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	//デバイスの生成
	//ディスプレイアダプタを表すためのデバイスを作成
	//デバイスオブジェクトの生成
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{
		return FALSE;
	}

	InitPolygon();

	//レンダ―ステートの設定
	//αブレンドを行う
	//SRC　今から描くもの。つまりポリゴン。
	//DEST すでに描画されている画面のこと。
	//SRC_RGB * SRC_α + DEST_RGB * (1 - SRC_α)
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//テクスチャーステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	if (!InitPolygon())
	{
		MessageBox(hWnd, "ポリゴンの初期化ができませんでした", "エラー",MB_OK);
		return false;
	}

	return TRUE;
}
void Uninit(void)
{

	UninitPolygon();

	if (g_pD3DDevice != NULL)
	{//デバイスの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}
void Update(void)
{
	g_nAnimCount++;
}
void Draw(void)
{
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(32, 64, 192, 255), 1.0f, 0);

	//D3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))  //1フレームに1回
	{
		//ポリゴン描画
//		SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));
//		DrawPolygon(/*TEXTURE_WITCH, */0.0f, 0.0f, /*128.0f, 128.0f, 128, 128, */0, 0, 128, 128);
//		for (int i = 0; i < 5; i++)
//		{
//			SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 128 + 32 * i));
//			DrawPolygon(/*TEXTURE_KOBENICHAN, */200.0f + 32 * i, 100.0f,/*533 * 0.5f, 800.0*0.5f, 533, 800, */0, 0, 533, 800);
//		}
		

//		DrawPolygon(/*TEXTURE_COCOSOZAI, */400.0f, 100.0f, /*32.f*1.0f, 32.f*1.0f, 512, 512, */32 * 2, 32 * 3, 32, 32);

/*		SetPolygonTexture(TEXTURE_COCOSOZAI);
		SetPolygonScale(6.0f, 6.0f);
		DrawPolygon(400.f, 200.f, 32 * 2, 32 * 3, 32, 32);*/

		//ランニングマン
		SetPolygonTexture(TEXTURE_RUNNINGMAN);
		SetPolygonScale(1.0f, 1.0f);

		int patternNum = g_nAnimCount / 5 % 10;
		int patternH = patternNum % 5;
		int patternV = patternNum / 5;

		int tcx = patternH * 140;
		int tcy = patternH * 200;

		DrawPolygon(600.f, 300.f,tcx,tcy, 140, 200);

		g_pD3DDevice->EndScene();
	}

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	return g_pD3DDevice;
}
