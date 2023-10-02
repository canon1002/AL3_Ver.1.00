#include "FollowCamera.h"
#include "MathTool.h"
#include "ImGuiManager.h"

FollowCamera::FollowCamera() {}

FollowCamera::~FollowCamera() {}

void FollowCamera::Initialize() {

	// 入力システムの取得
	inputSystem_ = InputSystem::GetInstance();

	// ビュープロジェクション
	viewProjection_.Initialize();

}

void FollowCamera::Update() {

	// カメラの回転
	if (inputSystem_->GetInputStyck(R, X, 1500) || inputSystem_->GetInputStyck(R, X, -1500) ||
	    inputSystem_->GetInputStyck(R, Y, 1500) || inputSystem_->GetInputStyck(R, Y, -1500)) {
	
		// 回転速度
		float rotateSpeed = 0.05f;
		// スティックの傾きに応じてカメラを回転させる
		viewProjection_.rotation_.y += ((float)inputSystem_->rStickPos_.x / 30000.0f) * rotateSpeed;
		
		// 一回転していたら回転量を0に戻す
		if (viewProjection_.rotation_.y <= -6.28 || viewProjection_.rotation_.y >= 6.28) {
			viewProjection_.rotation_.y = 0.0f;
		}
	}

	// 追従対象がいれば
	if (target_) {

		// 追従対象からカメラまでのオフセット(0度のときの値)
		Vector3 offset = {0.0f, 2.0f, -50.0f};
		//	
		Matrix4x4 rotateM4 =
		    MakeAffineMatrix({1.0f, 1.0f, 1.0f}, viewProjection_.rotation_, {0.0f, 0.0f, 0.0f});
		
		offset = TransformNomal(offset,rotateM4);

		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = Add(offset, target_->translation_);

	}

	ImGui::Begin("Follow");
	ImGui::SliderFloat3("Vrotate", &viewProjection_.rotation_.x, -16.0f, 16.0f);
	ImGui::SliderFloat3("Vtranslate", &viewProjection_.translation_.x, -1024.0f, 1024.0f);
	ImGui::End();

	// ビュー行列の更新
	viewProjection_.UpdateViewMatrix();
	viewProjection_.UpdateProjectionMatrix();
	viewProjection_.TransferMatrix();

}
