#include "Skydome.h"
#include <assert.h>

Skydome::Skydome() {}

Skydome::~Skydome() { 

	// モデルデータの開放
	m_model.release();

}

void Skydome::Initialize() {

	// 受け取ったデータをメンバ変数に格納
	m_model.reset(Model::CreateFromOBJ("skydome", true));

	// ワールド変換の初期化
	m_worldTransform.Initialize();
	// 拡大縮小行列
	m_worldTransform.scale_ = {800.0f, 800.0f, 800.0f};

	m_worldTransform.matWorld_.m[3][0] = 0.0f;
	m_worldTransform.matWorld_.m[3][1] = 0.0f;
	m_worldTransform.matWorld_.m[3][2] = 0.0f;
}

void Skydome::Update() {

	// 行列を計算・転送
	m_worldTransform.UpdateMatrix();
}

void Skydome::Draw(const ViewProjection& viewProjection) {

	// 3Dモデルを描画
	m_model->Draw(m_worldTransform, viewProjection);
}