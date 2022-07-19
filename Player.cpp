#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle) {
	//NULLポインタチェック
	assert(model);
	this->model_ = model;
	this->textureHandle_ = textureHandle;

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	worldtransform_.scale_ = { 2,2,2 };
	worldtransform_.Initialize();
	Matrix4 matScale;
}
void Player::Update() {
	Move();
	debugText_->SetPos(50, 150);
	debugText_->Printf("x:%f,y:%f,y:%f", worldtransform_.translation_.x,
		worldtransform_.translation_.y, worldtransform_.translation_.z);
	Attack();
	if (bullet_) {
		bullet_->Update();
	}
}
void Player::Move() {
	const float kCharacterSpeed = 0.2f;
	if (input_->PushKey(DIK_LEFT)) {
		if (worldtransform_.translation_.x >= -15) {
			worldtransform_.translation_.x -= kCharacterSpeed;
		}
	}
	else if (input_->PushKey(DIK_RIGHT)) {
		if (worldtransform_.translation_.x <= 15) {
			worldtransform_.translation_.x += kCharacterSpeed;
		}
	}
	if (input_->PushKey(DIK_UP)) {
		if (worldtransform_.translation_.y <= 15) {
			worldtransform_.translation_.y += kCharacterSpeed;
		}
	}
	else if (input_->PushKey(DIK_DOWN)) {
		if (worldtransform_.translation_.y >= -15) {
			worldtransform_.translation_.y -= kCharacterSpeed;
		}
	}
	// Aキーを押したら
	if (input_->PushKey(DIK_A))
	{
		// プラスに回転
		worldtransform_.rotation_.y += 0.05f;
	}
	// Dキーを押したら
	if (input_->PushKey(DIK_D))
	{
		// マイナスに回転
		worldtransform_.rotation_.y -= 0.05f;
	}
	// 行列の更新
	// Y軸回転行列を宣言
	Matrix4 matRotY = MathUtility::Matrix4Identity();
	matRotY.m[0][0] = cosf(worldtransform_.rotation_.y);
	matRotY.m[0][2] = -sinf(worldtransform_.rotation_.y);
	matRotY.m[2][0] = sinf(worldtransform_.rotation_.y);
	matRotY.m[2][2] = cosf(worldtransform_.rotation_.y);
	// 平行移動行列を宣言
	Matrix4 matTrans = MathUtility::Matrix4Identity();
	matTrans.m[3][0] = worldtransform_.translation_.x;
	matTrans.m[3][1] = worldtransform_.translation_.y;
	matTrans.m[3][2] = worldtransform_.translation_.z;
	worldtransform_.matWorld_ = MathUtility::Matrix4Identity();
	// ワールド行列にY軸回転行列をかける 注意1
	worldtransform_.matWorld_ *= matRotY;
	worldtransform_.matWorld_ *= matTrans;
	worldtransform_.TransferMatrix();
}
void Player::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldtransform_, viewProjection_, textureHandle_);
	if (bullet_) {
		bullet_->Draw(viewProjection_);
	}
}
void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		//弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldtransform_.translation_);

		//弾を登録する
		bullet_ = newBullet;
	}
}
