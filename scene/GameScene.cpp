#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>
#include "ImGuiManager.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

	// モデルデータの開放
	model_.release();

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// 入力クラスの取得
	inputSystem_ = InputSystem::GetInstance();

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
	// デバッグカメラのオンオフ
	isDebugCameraActive_ = false;
	// 軸方向表示を有効化
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	// 天球クラスの生成・初期化
	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize();
	// 地面クラスの生成・初期化
	ground_ = std::make_unique<Ground>();
	ground_->Initialize();
	// 自キャラクラスの生成・初期化
	player_ = std::make_unique<Player>();
	player_->Initialize(model_.get(), tex_);
	// 追従カメラの生成・初期化
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();
	followCamera_->SetTarget(&player_->GetWorldTransform());
	// 追従カメラのビュープロジェクションをプレイヤーに渡す
	player_->SetViewProjection(&followCamera_->GetViewProjection());
}

void GameScene::Update() {

	// 天球の更新
	skydome_->Update();
	// 地面の更新
	ground_->Update();
	// 自キャラの更新
	player_->Update();

	// 行列を更新・転送する
	worldTransform_.UpdateMatrix();

	// ゲームパッドのSTARTボタンを押すとデバッグカメラに切り替え
	if (inputSystem_->GetInputTrigger(MENU)) {
		isDebugCameraActive_ = true;
	}

	// カメラ切り替え
	if (isDebugCameraActive_) {

		// デバッグカメラの更新
		debugCamera_->Update();
		// 追従カメラのビュー行列をコピー
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		// 追従カメラのプロジェクション行列をコピー
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	
	} else {
	
		// 追従カメラの更新
		followCamera_->Update();
		// 追従カメラのビュー行列をコピー
		viewProjection_.matView = followCamera_->GetViewProjection().matView;
		// 追従カメラのプロジェクション行列をコピー
		//viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	}

	ImGui::Begin("GameScene");
	ImGui::SliderFloat3("scale", &worldTransform_.scale_.x, -2.0f, 2.0f);
	ImGui::SliderFloat3("rotate", &worldTransform_.rotation_.x, -16.0f, 16.0f);
	ImGui::SliderFloat3("translate", &worldTransform_.translation_.x, -1024.0f, 1024.0f);
	ImGui::SliderFloat3("Vrotate", &viewProjection_.rotation_.x, -16.0f, 16.0f);
	ImGui::SliderFloat3("Vtranslate", &viewProjection_.translation_.x, -1024.0f, 1024.0f);
	ImGui::End();

	

	


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
	skydome_->Draw(viewProjection_);
	// 地面の描画
	ground_->Draw(viewProjection_);

	// 自キャラの描画
	player_->Draw(viewProjection_);

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
