#include "Player.h"
#include "MathTool.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "ImGuiManager.h"

Player::Player() {}

Player::~Player() {

	// モデルデータの開放
	model_.release();

}

void Player::Initialize(Model* model,uint32_t tex) {

	// 入力クラスの取得
	inputSystem_ = InputSystem::GetInstance();

	// ワールド座標変換データの初期化
	worldTransform_.Initialize();
	// 平行移動行列(高さを0.5として作成)
	worldTransform_.translation_ = {0.0f, 0.5f, 0.0f};
	// テクスチャの初期化
	tex_ = tex;
	// モデルの初期化
	model_.reset(model);


}

void Player::Update() {

	// 行列を更新・転送する
	//worldTransform_.UpdateMatrix();

	if (inputSystem_->GetInputStyck(L, X, 1500) || inputSystem_->GetInputStyck(L, X, -1500) ||
	    inputSystem_->GetInputStyck(L, Y, 1500) || inputSystem_->GetInputStyck(L, Y, -1500) ){

		// 速さ
		const float speed = 0.3f;
		// 移動量
		Vector3 move = {(float)inputSystem_->stickPos_.x, 0.0f, (float)inputSystem_->stickPos_.y};
		move = Nomalize(move);

		worldTransform_.rotation_.y = std::atan2(move.x, move.z);

		// 移動量に速さを反映
		move = Scalar(speed, move);
		// 移動ベクトルをカメラの角度分回転させる
		Matrix4x4 rotateM4 =
		    MakeAffineMatrix({1.0f, 1.0f, 1.0f}, viewProjection_->rotation_, {0.0f, 0.0f, 0.0f});
		move = TransformNomal(move, rotateM4);
		// 移動させる
		worldTransform_.translation_.x += move.x;
		worldTransform_.translation_.y += move.y;
		worldTransform_.translation_.z += move.z;

	}

	ImGui::Begin("Player");
	ImGui::SliderFloat3("scale", &worldTransform_.scale_.x, -2.0f, 2.0f);
	ImGui::SliderFloat3("rotate", &worldTransform_.rotation_.x, -16.0f, 16.0f);
	ImGui::SliderFloat3("translate", &worldTransform_.translation_.x, -1024.0f, 1024.0f);
	ImGui::End();

	// 行列を更新・転送する
	worldTransform_.UpdateMatrix();

}

void Player::Draw(const ViewProjection& viewProjection) {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, tex_);

}