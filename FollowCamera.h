#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "InputSystem.h"

/// <summary>
/// 追従カメラ
/// </summary>
class FollowCamera {
public:

	FollowCamera();
	~FollowCamera();

	void Initialize();
	void Update();

	void SetTarget(const WorldTransform* target) { target_ = target; }

	ViewProjection& GetViewProjection() { return viewProjection_; }

private:

	// 入力システム
	InputSystem* inputSystem_ = nullptr;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	// 追跡対象
	const WorldTransform* target_ = nullptr;

};
