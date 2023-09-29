#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {

	// モデルデータの開放
	model_.release();

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// テクスチャ読み込み
	tex_ = TextureManager::Load("player/player.png");
	// モデル生成
	model_.reset(Model::CreateFromOBJ("player", true));
	// ワールド変換データの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	
	
	// デバッグカメラの生成・初期化
	debugCamera_ = std::make_unique<DebugCamera>(1280, 720);
	// 軸方向表示を有効化
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	// 天球クラスの生成・初期化
	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize();
	// 地面クラスの生成・初期化
	ground_ = std::make_unique<Ground>();
	ground_->Initialize();
	// 自キャラクラスの生成・初期化
	player_ = std::make_unique<Player>();
	player_->Initialize(model_.get(), tex_);

}

void GameScene::Update() {

	// デバッグカメラの更新
	debugCamera_->Update();

	// 天球の更新
	skydome_->Update();
	// 地面の更新
	ground_->Update();
	// 自キャラの更新
	player_->Update();

	// 行列を更新・転送する
	worldTransform_.UpdateMatrix();

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 天球の描画
	skydome_->Draw(debugCamera_->GetViewProjection());
	// 地面の描画
	ground_->Draw(debugCamera_->GetViewProjection());

	// 自キャラの描画
	player_->Draw(debugCamera_->GetViewProjection());

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
