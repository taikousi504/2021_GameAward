#pragma once
#include<vector>
#include<d3d12.h>
#include<DirectXMath.h>
#include<wrl.h>
using namespace Microsoft::WRL;




//DirectX12で描画するために使用する構造体
#pragma region シェーダーに送る情報
//頂点バッファで送る情報
#pragma region 頂点構造体



struct Vertex
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 uv;//ポリゴンのどこら辺かをあらわすもの　ポリゴン上の座標
	DirectX::XMFLOAT3 normal;
};

struct OBJAnimationVertex
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 uv;
	DirectX::XMFLOAT3 normal;
	UINT boneNumber;
};


struct SpriteVertex
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 uv;
};

 
struct PointVertex
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 scale;
	DirectX::XMFLOAT4 color;

};



#pragma region PMD


struct PMDVertex
{
#pragma pack(2)

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 uv;
	unsigned short bone[2];
	unsigned char boneWeight;
	unsigned char edgeFlg;

#pragma pack()
};

struct PMDHeader
{
	float version;
	char modelName[20];
	char comment[256];
};
#pragma endregion

#pragma endregion


#pragma region 定数構造体

struct ConstBufferData
{
	DirectX::XMFLOAT4 color;
	DirectX::XMMATRIX mat;
	DirectX::XMMATRIX normalMat;
	DirectX::XMFLOAT4 mulColor;
	DirectX::XMFLOAT4 addColor;
	DirectX::XMFLOAT4 subColor;
	float ex;
	DirectX::XMMATRIX worldMat;
	DirectX::XMMATRIX boneMat[20];
};

struct CommonConstData
{
	//float4にするかパック詰めないと送れない(float4以外の変数と次の変数の間に入り込む)からfloat4にしてる
	DirectX::XMFLOAT4 lightColor;
	DirectX::XMFLOAT4 light;
	DirectX::XMFLOAT4 cameraPos;
	DirectX::XMMATRIX lightMat;//ライト用行列
};

struct SpriteConstBufferData
{
	DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT4 addColor;
	DirectX::XMMATRIX mat;
};

struct PointConstBufferData
{
	DirectX::XMMATRIX mat;
	DirectX::XMMATRIX billboardMat;
};


#pragma region OBJ


struct Material
{
	DirectX::XMFLOAT3 ambient;
	DirectX::XMFLOAT3 diffuse;
	DirectX::XMFLOAT3 specular;
	float alpha;
	std::string materialName;
	std::string textureName;

	Material()
	{
		ambient = { 0.3f,0.3f,0.3f };
		diffuse = { 1.0f,1.0f,1.0f};
		specular = { 0.0f,0.0f,0.0f };
		alpha = 1.0f;
	}
};

struct MaterialConstBuffData
{
	DirectX::XMFLOAT3 ambient;
	float pad1;
	DirectX::XMFLOAT3 diffuse;
	float pad2;
	DirectX::XMFLOAT3 specular;
	float alpha;
};
#pragma endregion



#pragma endregion

#pragma region テクスチャ

//テクスチャバッファで送る情報
struct RGBA
{
	unsigned char r, g, b, a;
};

#pragma endregion

#pragma region テクスチャ類

#pragma region 自力読み込み

#pragma pack(2)
//BMPを読み込み時に使用
struct BMPData
{
	char fileType[2];//ファイル形式
	long length;//ファイルサイズ
	short areaOne;//予備領域1
	short areaTwo;//予備領域2
	unsigned long offset;//ファイル先頭から画像データまでのオフセット

	unsigned long size;//サイズ
	unsigned long width;//横
	unsigned long height;//縦
	short plane;//プレーン数
	short bit;//色ビット数
	unsigned long compression;//圧縮形式
	unsigned long imageSize;//画像データサイズ
	long meterX;//水平解像度
	long meterY;//垂直解像度
	unsigned long parret;//格納パレット
	unsigned long important;//重要色素
	std::vector<RGBA> rgbaData;
};
#pragma pack()


#pragma endregion

#pragma region スプライトフォント
struct SpriteFontData
{
	int widthLineNum;//横一行の文字数
	int heightLineNum;//横一行の文字数
	int fontSizeX;
	int fontSizeY;
};

#pragma endregion


#pragma endregion

#pragma region バッファ類

struct WorldMatData 
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 angle;
	DirectX::XMFLOAT3 scale;
};

#pragma region 汎用バッファセット

//バッファー、Mapするための変数、ビューのセット
#pragma region 頂点

struct VertexBufferSet
{
	ComPtr<ID3D12Resource> vertexBuffer;
	Vertex* vertexMap;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
	std::string materialName;
};

struct PMDVertexBufferSet
{
	ComPtr<ID3D12Resource> vertexBuffer;
	PMDVertex* vertexMap;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
};
#pragma endregion


struct IndexBufferSet
{
	ComPtr<ID3D12Resource> indexBuffer;
	unsigned short* indexMap;
	D3D12_INDEX_BUFFER_VIEW indexBufferView;
};

struct ConstBufferSet
{
	//書き換え多くなるから仮に配列使ってない

	//objのモデルごとに変更できるようにするために配列
	std::vector<ComPtr<ID3D12Resource>> constBuffer;
};

struct TextureBufferSet
{
	//書き換え多くなるから仮に配列使ってない

	//.obj内のオブジェクトごとにテクスチャ違う可能性あるから配列
	std::vector<ComPtr<ID3D12Resource>> textureBuff;
};


#pragma endregion

#pragma region ユーザーバッファ
//
////これいらん?
//struct UserVertexBufferSet
//{
//	ComPtr<ID3D12Resource> vertexBuffer;
//	void* vertexMap;
//	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
//};
//
//
//struct UserConstBufferSet
//{
//	ComPtr<ID3D12Resource> constBuffer;
//	void* constMaps;
//};

#pragma endregion


struct DepthBufferSet
{
	ComPtr<ID3D12Resource> depthBuffer;
};

//
//struct Object3DVertData
//{
//	PolyData polyData;
//	std::vector<Vertex> vertices;
//	std::vector<unsigned short> indices;
//	VertexBufferSet vertSet;
//	IndexBufferSet indexSet;
//};
//
//struct Object3DHeapData 
//{
//	std::vector<ComPtr<ID3D12Resource>> constBuffer;
//	ComPtr<ID3D12Resource> textureBuffer;
//	std::vector<DirectX::XMVECTOR>position;
//	DirectX::XMFLOAT3 angle;
//	DirectX::XMFLOAT3 scale;
//};
//
//
//struct Object2DData
//{
//	VertexBufferSet vertSet;
//	ComPtr<ID3D12Resource> constSet;
//	ComPtr<ID3D12Resource> textureBuffer;
//	DirectX::XMVECTOR position;
//	DirectX::XMFLOAT3 angle;
//	DirectX::XMFLOAT3 scale;
//
//};

#pragma region ポストエフェクト
struct PostEffectConstData 
{
	DirectX::XMMATRIX worldMat;
};

#pragma endregion


#pragma endregion


#pragma region システム系
struct CameraData
{
	float fovY;
	float nearNumber;
	float farNumber;
	//初期位置
	DirectX::XMFLOAT3 eye;
	DirectX::XMFLOAT3 target;
	DirectX::XMFLOAT3 up;
	//現在位置(行列で計算するやつ)
	DirectX::XMFLOAT3 nowEye;
	DirectX::XMFLOAT3 nowTarget;
	DirectX::XMFLOAT3 nowUp;
	DirectX::XMFLOAT3 eyeAngle;
	DirectX::XMFLOAT3 targetAngle;
	DirectX::XMFLOAT3 upAngle;
};
#pragma endregion



#pragma region パイプラインとルートシグネチャ
//struct PipelineSet
//{
//	ComPtr<ID3D12RootSignature> rootSignature;
//	ComPtr<ID3D12PipelineState> pipelineState;
//	ComPtr<ID3DBlob> errorBlob;
//};
#pragma endregion

