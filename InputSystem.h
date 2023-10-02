#pragma once

#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "WorldTransform.h"

enum ActCode {
	ACT = 1,
	SPECIAL,
	JUMP,
	AVOID,
	CANCEL,
	MENU,
	L_SELECT,
	R_SELECT,
	U_SELECT,
	D_SELECT,
	UI_SELECT,
	DASH,

	END = 64,
};

// 左右
enum InputLR {
	L,
	R,
};

// 方向
enum AxisVec {
	X,
	Y,
	Z,
};

struct AxisVec2 {
	int32_t x;
	int32_t y;
};

class InputSystem final {
private:


	InputSystem();
	~InputSystem();

public:

	enum TYPE { A, B };

	// コピーコンストラクタなどを禁止する
	InputSystem(const InputSystem& inputSystem) = delete;
	InputSystem& operator=(const InputSystem& inputSystem) = delete;

	static InputSystem* GetInstance() {
		static InputSystem instance;
		return &instance;
	}

	static void Finalize() {
		
	}

	void Initialize();
	void Update();
	void Draw();

	bool GetInputTrigger(ActCode act);
	bool GetInputStyck(InputLR lr,AxisVec vec, int32_t point);

	bool GetActionTrigger(ActCode act);
	bool GetActionLongPush(ActCode act);
	void CursorUpdate();
	Vector2 GetCursorPos();
	Vector2 GetCursorRad();

	void SetControllType(TYPE type);

private:

	// キーボードの入力を取得
	Input* input_ = nullptr;

	// カーソル関連
	WorldTransform m_cursorWorldTransform;
	Vector3 m_cursorPos = {60, 120, 0};
	Vector3 m_cursorVel = {6, 6, 0};
	// カーソルのスプライト
	std::unique_ptr<Sprite> m_cursorSprite_ = nullptr;
	// カーソルのテクスチャ
	uint32_t cursorTextureHandle_ = 0u;


public:	

	// input
	int32_t m_InputButton[ActCode::END];
	
	// スティック
	AxisVec2 stickPos_ = {0, 0};
	AxisVec2 rStickPos_ = {0, 0};

};
