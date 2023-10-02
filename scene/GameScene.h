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
#include "DebugCamera.h"

// 追加クラス
#include "InputSystem.h"
#include "Player.h"
#include "Skydome.h"
#include "Ground.h"
#include "FollowCamera.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	InputSystem* inputSystem_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	// ワールド座標変換データ
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;
	// モデル
	std::unique_ptr<Model> model_ = nullptr;
	// テクスチャ
	uint32_t tex_ = 0u;
	
	// デバッグカメラ
	std::unique_ptr<DebugCamera> debugCamera_ = nullptr;
	// デバッグカメラのオンオフ
	bool isDebugCameraActive_ = false;

	// 天球
	std::unique_ptr<Skydome> skydome_ = nullptr;
	// 地面
	std::unique_ptr<Ground> ground_ = nullptr;
	// 自キャラ
	std::unique_ptr<Player> player_ = nullptr;
	// 追従カメラ
	std::unique_ptr<FollowCamera> followCamera_ = nullptr;
	
};
