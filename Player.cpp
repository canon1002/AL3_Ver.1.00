#include "Player.h"

Player::Player() {}

Player::~Player() {

	// モデルデータの開放
	model_.release();

}

void Player::Initialize(Model* model,uint32_t tex) {

	// ワールド座標変換データの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	// テクスチャの初期化
	tex_ = tex;
	// モデルの初期化
	model_.reset(model);

}

void Player::Update() {

	// 行列を転送する
	worldTransform_.TransferMatrix();

}

void Player::Draw(ViewProjection& viewProjection) {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, tex_);

}