#include "PlayerBullet.h"
#include <cassert>
void PlayerBullet::Initialize(Model* model, const Vector3& position) {
	//NULL|C^`FbN
	assert(model);

	model_ = model;
	//eNX`ÇÝÝ
	textureHandle_ = TextureManager::Load("black.png");

	worldtransform_.Initialize();
	worldtransform_.translation_ = position;
}

void PlayerBullet::Update() {
	// XP[Osñðé¾
	Matrix4 matScale = MathUtility::Matrix4Identity();
	matScale.m[0][0] = worldtransform_.scale_.x;
	matScale.m[1][1] = worldtransform_.scale_.y;
	matScale.m[2][2] = worldtransform_.scale_.z;
	// Z²ñ]sñðé¾
	Matrix4 matRotZ = MathUtility::Matrix4Identity();
	matRotZ.m[0][0] = cosf(worldtransform_.rotation_.z);
	matRotZ.m[0][1] = sinf(worldtransform_.rotation_.z);
	matRotZ.m[1][0] = -sinf(worldtransform_.rotation_.z);
	matRotZ.m[1][1] = cosf(worldtransform_.rotation_.z);
	// X²ñ]sñðé¾
	Matrix4 matRotX = MathUtility::Matrix4Identity();
	matRotX.m[1][1] = cosf(worldtransform_.rotation_.x);
	matRotX.m[1][2] = sinf(worldtransform_.rotation_.x);
	matRotX.m[2][1] = -sinf(worldtransform_.rotation_.x);
	matRotX.m[2][2] = cosf(worldtransform_.rotation_.x);
	// Y²ñ]sñðé¾
	Matrix4 matRotY = MathUtility::Matrix4Identity();
	matRotY.m[0][0] = cosf(worldtransform_.rotation_.y);
	matRotY.m[0][2] = -sinf(worldtransform_.rotation_.y);
	matRotY.m[2][0] = sinf(worldtransform_.rotation_.y);
	matRotY.m[2][2] = cosf(worldtransform_.rotation_.y);
	// ½sÚ®sñðé¾
	Matrix4 matTrans = MathUtility::Matrix4Identity();
	matTrans.m[3][0] = worldtransform_.translation_.x;
	matTrans.m[3][1] = worldtransform_.translation_.y;
	matTrans.m[3][2] = worldtransform_.translation_.z;
	worldtransform_.matWorld_ = MathUtility::Matrix4Identity();
	// [hsñÉY²ñ]sñð©¯é Ó1
	worldtransform_.matWorld_ *= matRotY;
	worldtransform_.matWorld_ *= matTrans;
	worldtransform_.TransferMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldtransform_, viewProjection, textureHandle_);
}
