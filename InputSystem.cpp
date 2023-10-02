#include "InputSystem.h"
#include "Gamepad.h"
#include "ImGuiManager.h"
#include <assert.h>

InputSystem::InputSystem() {

	// キーの初期設定
	m_InputButton[ActCode::SPECIAL] = (int32_t)Gamepad::Button::RIGHT_SHOULDER;
	m_InputButton[ActCode::ACT] = (int32_t)Gamepad::Button::A;
	m_InputButton[ActCode::CANCEL] = (int32_t)Gamepad::Button::B;
	m_InputButton[ActCode::MENU] = (int32_t)Gamepad::Button::START;
	m_InputButton[ActCode::L_SELECT] = (int32_t(Gamepad::Button::LEFT));
	m_InputButton[ActCode::R_SELECT] = (int32_t(Gamepad::Button::RIGHT));
	m_InputButton[ActCode::U_SELECT] = (int32_t(Gamepad::Button::UP));
	m_InputButton[ActCode::D_SELECT] = (int32_t(Gamepad::Button::DOWN));
	m_InputButton[ActCode::UI_SELECT] = (int32_t(Gamepad::Button::X));
	m_InputButton[ActCode::DASH] = (int32_t)Gamepad::Button::RIGHT_THUMB;

	this->Initialize();
}

InputSystem::~InputSystem() {}

void InputSystem::Initialize() {

	input_ = Input::GetInstance();

	// �摜
	//cursorTextureHandle_ = TextureManager::Load("cursorImage.png");

	/*m_cursorSprite_.reset(Sprite::Create(
	    cursorTextureHandle_, {m_cursorPos.x, m_cursorPos.y}, {1.0f, 1.0f, 0.0f, 1.0f},
	    {0.5f, 0.5f}));
	m_cursorSprite_->SetSize({32.0f, 32.0f});*/
}

void InputSystem::Update() {

	// �Q�[���p�b�h�̃C���X�^���X��擾
	Gamepad::Input();

	// ゲームパッドのステイックの取得・更新
	stickPos_.x = Gamepad::getStick(Gamepad::Stick::LEFT_X);
	stickPos_.y = Gamepad::getStick(Gamepad::Stick::LEFT_Y);
	rStickPos_.x = Gamepad::getStick(Gamepad::Stick::RIGHT_X);
	rStickPos_.y = Gamepad::getStick(Gamepad::Stick::RIGHT_Y);

	// �J�[�\���̍X�V����
	// CursorUpdate();

	// �r���[�|�[�g
	//m_cursorSprite_->SetPosition({m_cursorPos.x, m_cursorPos.y});

#ifdef _DEBUG

	ImGui::Begin("Action");
	ImGui::Text("JUMP = %d", GetInputTrigger(ActCode::JUMP));
	ImGui::Text("DASH = %d", GetInputTrigger(ActCode::DASH));
	ImGui::Text("ACT = %d", GetInputTrigger(ActCode::ACT));
	ImGui::Text("MENU = %d", GetInputTrigger(ActCode::MENU));
	ImGui::Text("CANCEL = %d", GetInputTrigger(ActCode::CANCEL));
	ImGui::End();

	Gamepad::Draw();

#endif _DEBUG

}

void InputSystem::Draw() {

	// m_cursorSprite_->Draw();
}

bool InputSystem::GetInputTrigger(ActCode act) {

	for (int32_t i = 0; i < 15; i++) {

		if (m_InputButton[act] == i) {

			switch (i) {
			case 0:
				if (Gamepad::Pushed(Gamepad::Button::UP)) {
					return true;
				}
				break;
			case 1:
				if (Gamepad::Pushed(Gamepad::Button::DOWN)) {
					return true;
				}
				break;
			case 2:
				if (Gamepad::Pushed(Gamepad::Button::LEFT)) {
					return true;
				}
				break;
			case 3:
				if (Gamepad::Pushed(Gamepad::Button::RIGHT)) {
					return true;
				}
				break;
			case 4:
				if (Gamepad::Pushed(Gamepad::Button::START)) {
					return true;
				}
				break;
			case 5:
				if (Gamepad::Pushed(Gamepad::Button::BACK)) {
					return true;
				}
				break;
			case 6:
				if (Gamepad::Pushed(Gamepad::Button::LEFT_THUMB)) {
					return true;
				}
				break;
			case 7:
				if (Gamepad::Pushed(Gamepad::Button::RIGHT_THUMB)) {
					return true;
				}
				break;
			case 8:
				if (Gamepad::Pushed(Gamepad::Button::LEFT_SHOULDER)) {
					return true;
				}
				break;
			case 9:
				if (Gamepad::Pushed(Gamepad::Button::RIGHT_SHOULDER)) {
					return true;
				}
				break;
			case 12:
				if (Gamepad::Pushed(Gamepad::Button::A)) {
					return true;
				}
				break;
			case 13:
				if (Gamepad::Pushed(Gamepad::Button::B)) {
					return true;
				}
				break;
			case 14:
				if (Gamepad::Pushed(Gamepad::Button::X)) {
					return true;
				}
				break;
			case 15:
				if (Gamepad::Pushed(Gamepad::Button::Y)) {
					return true;
				}
				break;
			default: 

				return false;

			}
		}
	}

	return false;
}

bool InputSystem::GetInputStyck(InputLR lr,AxisVec vec, int32_t point) { 

	switch (vec) {
	case X:

		if (point > 0) {
			if (lr == L) {
				if (point < Gamepad::getStick(Gamepad::Stick::LEFT_X)) {
					return true;
				}
			} else if (lr == R) {
				if (point < Gamepad::getStick(Gamepad::Stick::RIGHT_X)) {
					return true;
				}
			}
		} else if (point < 0) {
			if (lr == L) {
				if (point > Gamepad::getStick(Gamepad::Stick::LEFT_X)) {
					return true;
				}
			} else if (lr == R) {
				if (point > Gamepad::getStick(Gamepad::Stick::RIGHT_X)) {
					return true;
				}
			}
		}

		break;
	case Y:

		if (point > 0) {
			if (lr == L) {
				if (point < Gamepad::getStick(Gamepad::Stick::LEFT_Y)) {
					return true;
				}
			} else if (lr == R) {
				if (point < Gamepad::getStick(Gamepad::Stick::RIGHT_Y)) {
					return true;
				}
			}
		} else if (point < 0) {
			if (lr == L) {
				if (point > Gamepad::getStick(Gamepad::Stick::LEFT_Y)) {
					return true;
				}
			} else if (lr == R) {
				if (point > Gamepad::getStick(Gamepad::Stick::RIGHT_Y)) {
					return true;
				}
			}
		}

		break;
	case Z:

		return false;

		break;

	default:
		
		return false;

		break;
	}

	return false;

}

bool InputSystem::GetActionTrigger(ActCode act) {

	switch (act) {

	case SPECIAL:

		for (int32_t i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::SPECIAL] == i) {
				switch (i) {
				case 0:
					if (Gamepad::Pushed(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::Pushed(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::Pushed(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::Pushed(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::Pushed(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::Pushed(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::Pushed(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::Pushed(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::Pushed(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::Pushed(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::Pushed(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case ACT:

		for (int i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::ACT] == i) {
				switch (i) {
				case 0:
					if (Gamepad::Pushed(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::Pushed(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::Pushed(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::Pushed(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::Pushed(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::Pushed(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::Pushed(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::Pushed(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::Pushed(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::Pushed(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::Pushed(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case MENU:

		for (int i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::MENU] == i) {
				switch (i) {
				case 0:
					if (Gamepad::Pushed(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::Pushed(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::Pushed(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::Pushed(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::Pushed(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::Pushed(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::Pushed(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::Pushed(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::Pushed(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::Pushed(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::Pushed(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case CANCEL:

		for (int i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::CANCEL] == i) {
				switch (i) {
				case 0:
					if (Gamepad::Pushed(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::Pushed(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::Pushed(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::Pushed(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::Pushed(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::Pushed(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::Pushed(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::Pushed(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::Pushed(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::Pushed(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::Pushed(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case L_SELECT:

		for (int i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::L_SELECT] == i) {
				switch (i) {
				case 0:
					if (Gamepad::Pushed(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::Pushed(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::Pushed(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::Pushed(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::Pushed(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::Pushed(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::Pushed(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::Pushed(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::Pushed(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::Pushed(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::Pushed(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case R_SELECT:

		for (int i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::R_SELECT] == i) {
				switch (i) {
				case 0:
					if (Gamepad::Pushed(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::Pushed(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::Pushed(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::Pushed(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::Pushed(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::Pushed(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::Pushed(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::Pushed(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::Pushed(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::Pushed(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::Pushed(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case U_SELECT:

		for (int i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::U_SELECT] == i) {
				switch (i) {
				case 0:
					if (Gamepad::Pushed(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::Pushed(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::Pushed(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::Pushed(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::Pushed(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::Pushed(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::Pushed(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::Pushed(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::Pushed(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::Pushed(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::Pushed(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case D_SELECT:

		for (int i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::D_SELECT] == i) {
				switch (i) {
				case 0:
					if (Gamepad::Pushed(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::Pushed(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::Pushed(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::Pushed(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::Pushed(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::Pushed(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::Pushed(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::Pushed(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::Pushed(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::Pushed(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::Pushed(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case UI_SELECT:

		for (int i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::UI_SELECT] == i) {
				switch (i) {
				case 0:
					if (Gamepad::Pushed(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::Pushed(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::Pushed(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::Pushed(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::Pushed(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::Pushed(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::Pushed(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::Pushed(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::Pushed(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::Pushed(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::Pushed(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::Pushed(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case END:

		return false;

		break;
	default:

		return false;

		break;
	}

	return false;
}

bool InputSystem::GetActionLongPush(ActCode act) {

	switch (act) {

	case SPECIAL:

		for (int i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::SPECIAL] == i) {
				switch (i) {
				case 0:
					if (Gamepad::LongPush(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::LongPush(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::LongPush(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::LongPush(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::LongPush(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::LongPush(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::LongPush(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::LongPush(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::LongPush(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case DASH:

		for (int i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::DASH] == i) {
				switch (i) {
				case 0:
					if (Gamepad::LongPush(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::LongPush(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::LongPush(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::LongPush(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::LongPush(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::LongPush(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::LongPush(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::LongPush(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::LongPush(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case ACT:

		for (int i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::ACT] == i) {
				switch (i) {
				case 0:
					if (Gamepad::LongPush(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::LongPush(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::LongPush(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::LongPush(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::LongPush(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::LongPush(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::LongPush(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::LongPush(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::LongPush(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case MENU:

		for (int i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::MENU] == i) {
				switch (i) {
				case 0:
					if (Gamepad::LongPush(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::LongPush(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::LongPush(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::LongPush(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::LongPush(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::LongPush(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::LongPush(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::LongPush(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::LongPush(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case CANCEL:

		for (int i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::CANCEL] == i) {
				switch (i) {
				case 0:
					if (Gamepad::LongPush(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::LongPush(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::LongPush(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::LongPush(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::LongPush(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::LongPush(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::LongPush(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::LongPush(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::LongPush(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case L_SELECT:

		for (int i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::L_SELECT] == i) {
				switch (i) {
				case 0:
					if (Gamepad::LongPush(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::LongPush(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::LongPush(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::LongPush(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::LongPush(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::LongPush(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::LongPush(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::LongPush(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::LongPush(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case R_SELECT:

		for (int i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::R_SELECT] == i) {
				switch (i) {
				case 0:
					if (Gamepad::LongPush(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::LongPush(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::LongPush(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::LongPush(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::LongPush(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::LongPush(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::LongPush(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::LongPush(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::LongPush(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case U_SELECT:

		for (int i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::U_SELECT] == i) {
				switch (i) {
				case 0:
					if (Gamepad::LongPush(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::LongPush(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::LongPush(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::LongPush(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::LongPush(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::LongPush(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::LongPush(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::LongPush(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::LongPush(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case D_SELECT:

		for (int i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::D_SELECT] == i) {
				switch (i) {
				case 0:
					if (Gamepad::LongPush(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::LongPush(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::LongPush(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::LongPush(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::LongPush(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::LongPush(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::LongPush(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::LongPush(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::LongPush(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case UI_SELECT:

		for (int i = 0; i < 16; i++) {

			if (m_InputButton[ActCode::UI_SELECT] == i) {
				switch (i) {
				case 0:
					if (Gamepad::LongPush(Gamepad::Button::UP)) {
						return true;
					}
					break;
				case 1:
					if (Gamepad::LongPush(Gamepad::Button::DOWN)) {
						return true;
					}
					break;
				case 2:
					if (Gamepad::LongPush(Gamepad::Button::LEFT)) {
						return true;
					}
					break;
				case 3:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT)) {
						return true;
					}
					break;
				case 4:
					if (Gamepad::LongPush(Gamepad::Button::START)) {
						return true;
					}
					break;
				case 5:
					if (Gamepad::LongPush(Gamepad::Button::BACK)) {
						return true;
					}
					break;
				case 6:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_THUMB)) {
						return true;
					}
					break;
				case 7:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_THUMB)) {
						return true;
					}
					break;
				case 8:
					if (Gamepad::LongPush(Gamepad::Button::LEFT_SHOULDER)) {
						return true;
					}
					break;
				case 9:
					if (Gamepad::LongPush(Gamepad::Button::RIGHT_SHOULDER)) {
						return true;
					}
					break;
				case 12:
					if (Gamepad::LongPush(Gamepad::Button::A)) {
						return true;
					}
					break;
				case 13:
					if (Gamepad::LongPush(Gamepad::Button::B)) {
						return true;
					}
					break;
				case 14:
					if (Gamepad::LongPush(Gamepad::Button::X)) {
						return true;
					}
					break;
				case 15:
					if (Gamepad::LongPush(Gamepad::Button::Y)) {
						return true;
					}
					break;
				}
			}
		}

		break;
	case END:

		break;
	default:

		break;
	}

	return false;
}

void InputSystem::CursorUpdate() {

	if (Gamepad::getStick(Gamepad::Stick::LEFT_X) >= 3000) {
		m_cursorPos.x += m_cursorVel.x;
	}
	if (Gamepad::getStick(Gamepad::Stick::LEFT_X) <= -3000) {
		m_cursorPos.x -= m_cursorVel.x;
	}
	if (Gamepad::getStick(Gamepad::Stick::LEFT_Y) >= 3000) {
		m_cursorPos.y -= m_cursorVel.y;
	}
	if (Gamepad::getStick(Gamepad::Stick::LEFT_Y) <= -3000) {
		m_cursorPos.y += m_cursorVel.y;
	}

	if (m_cursorPos.x < 10) {
		m_cursorPos.x = 10;
	}
	if (m_cursorPos.x > 1270) {
		m_cursorPos.x = 1270;
	}
	if (m_cursorPos.y < 10) {
		m_cursorPos.y = 10;
	}
	if (m_cursorPos.y > 710) {
		m_cursorPos.y = 710;
	}

	m_cursorSprite_->SetPosition({m_cursorPos.x, m_cursorPos.y});
}

Vector2 InputSystem::GetCursorPos() { return Vector2(m_cursorPos.x, m_cursorPos.y); }

Vector2 InputSystem::GetCursorRad() { return Vector2{16, 16}; }

void InputSystem::SetControllType(TYPE type) {

	switch (type) {
	case InputSystem::A:

		m_InputButton[ActCode::ACT] = (int)Gamepad::Button::A;
		m_InputButton[ActCode::CANCEL] = (int)Gamepad::Button::B;

		break;
	case InputSystem::B:

		m_InputButton[ActCode::ACT] = (int)Gamepad::Button::B;
		m_InputButton[ActCode::CANCEL] = (int)Gamepad::Button::A;

		break;
	default:

		break;
	}
}