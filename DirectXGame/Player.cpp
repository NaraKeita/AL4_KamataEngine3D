#include "Player.h"
#include<cassert>

void Player::Initialize(Model* model, uint32_t textureHandle/*, ViewProjection* viewProjection*/) {
	//NULLポインタをチェックする
	assert(model);
	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;
	// ワールド変換の初期化
	worldTransform_.Initialize();
}

void Player::Update() {
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}
