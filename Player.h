#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <memory>

// 追加クラス
#include "InputSystem.h"

class Player {
public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	Player();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="tex">テクスチャ</param>
	void Initialize(Model* model, uint32_t tex);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

	WorldTransform& GetWorldTransform() { return worldTransform_; }
	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

private: // メンバ変数

	InputSystem* inputSystem_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// ワールド座標変換データ
	WorldTransform worldTransform_;
	// モデル
	std::unique_ptr<Model> model_ = nullptr;
	// テクスチャ
	uint32_t tex_ = 0u;

	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

};
