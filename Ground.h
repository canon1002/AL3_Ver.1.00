#pragma once
#include <Model.h>
#include <WorldTransform.h>

class Ground {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Ground();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Ground();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

private:
	// ワールド変換データ
	WorldTransform m_worldTransform;
	// モデル
	std::unique_ptr<Model> m_model = nullptr;
	// テクスチャ
	uint32_t m_textureHandle = 0u;

};
