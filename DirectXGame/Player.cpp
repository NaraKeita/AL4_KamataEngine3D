#include "Player.h"
#include "Affine.h"
#include<cassert>



void Player::Initialize(Model* model, uint32_t textureHandle/*, ViewProjection* viewProjection*/) {
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
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

	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	//キャラクターの移動速さ
	const float kCharacterSpeed = 2.0f;

	//押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	// 押した方向で移動ベクトルを変更（上下）
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}

	//座標移動（ベクトルの加算）
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;

	//アフィン変換行列の作成
	//Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate);
	/*MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);*/
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();

	ImGui::Begin("Debug1");
	//flo
	ImGui::InputFloat3("InputFloat3", &worldTransform_.translation_.x);
	ImGui::SliderFloat3("SliderFloat3", &worldTransform_.translation_.x, -10.0f, 10.0f);
	ImGui::End();

	// 移動限界座標
	const float kMoveLimitX = 35;
	const float kMoveLimitY = 19;

	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	worldTransform_.UpdateMatrix();

}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}
