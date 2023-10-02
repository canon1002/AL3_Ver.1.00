#include "Ground.h"


Ground::Ground() {}

Ground::~Ground() {

	// モデルデータの開放
	m_model.release();
}

void Ground::Initialize() {

	// 受け取ったデータをメンバ変数に格納
	m_model.reset(Model::CreateFromOBJ("ground", true));

	// ワールド変換の初期化
	m_worldTransform.Initialize();
	// 拡大縮小行列
	m_worldTransform.scale_ = {100.0f, 10.0f, 100.0f};
	// 平行移動行列(高さを-2として作成)
	m_worldTransform.translation_ = {0.0f, -2.0f, 0.0f};

	m_worldTransform.matWorld_.m[3][0] = 0.0f;
	m_worldTransform.matWorld_.m[3][1] = 0.0f;
	m_worldTransform.matWorld_.m[3][2] = 0.0f;
}

void Ground::Update() {

	// 行列を計算・転送
	m_worldTransform.UpdateMatrix();
}

void Ground::Draw(const ViewProjection& viewProjection) {

	// 3Dモデルを描画
	m_model->Draw(m_worldTransform, viewProjection);
}