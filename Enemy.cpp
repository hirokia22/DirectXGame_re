#include"Enemy.h"
#include<cassert>
void Enemy::Initialize(Model* model) {
	//NULL|C^`FbN
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("Enemy01.png");
	worldtransform_.Initialize();
	worldtransform_.translation_ = { 0,2,50 };
}
void Enemy::Update() {

	switch (phase_) {
	case Phase::Approach:
		UpdateApproach();
		break;
	case Phase::Leave:
		UpdateLeave();
		break;
	}

	//XP[Osñðé¾
	Matrix4 matScale = MathUtility::Matrix4Identity();
	matScale.m[0][0] = worldtransform_.scale_.x;
	matScale.m[1][1] = worldtransform_.scale_.y;
	matScale.m[2][2] = worldtransform_.scale_.z;
	
	//Z²ñ]sñðé¾
	Matrix4 matRotZ = MathUtility::Matrix4Identity();
	matRotZ.m[0][0] = cosf(worldtransform_.rotation_.z);
	matRotZ.m[0][1] = sinf(worldtransform_.rotation_.z);
	matRotZ.m[1][0] = -sinf(worldtransform_.rotation_.z);
	matRotZ.m[1][1] = cosf(worldtransform_.rotation_.z);

	//X²ñ]sñðé¾
	Matrix4 matRotX = MathUtility::Matrix4Identity();
	matRotX.m[1][1] = cosf(worldtransform_.rotation_.x);
	matRotX.m[1][2] = sinf(worldtransform_.rotation_.x);
	matRotX.m[2][1] = -sinf(worldtransform_.rotation_.x);
	matRotX.m[2][2] = cosf(worldtransform_.rotation_.x);

	//Y²ñ]sñðé¾
	Matrix4 matRotY = MathUtility::Matrix4Identity();
	matRotY.m[0][0] = cosf(worldtransform_.rotation_.y);
	matRotY.m[0][2] = -sinf(worldtransform_.rotation_.y);
	matRotY.m[2][0] = sinf(worldtransform_.rotation_.y);
	matRotY.m[2][2] = cosf(worldtransform_.rotation_.y);

	//½sÚ®sñðé¾
	Matrix4 matTrans = MathUtility::Matrix4Identity();
	matTrans.m[3][0] = worldtransform_.translation_.x;
	matTrans.m[3][1] = worldtransform_.translation_.y;
	matTrans.m[3][2] = worldtransform_.translation_.z;

	//[hsñ
	worldtransform_.matWorld_ = MathUtility::Matrix4Identity();
	worldtransform_.matWorld_ *= matScale;
	worldtransform_.matWorld_ *= matRotZ;
	worldtransform_.matWorld_ *= matRotX;
	worldtransform_.matWorld_ *= matRotY;
	worldtransform_.matWorld_ *= matTrans;

	//sñÌ]
	worldtransform_.TransferMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	//fÌ`æ
	model_->Draw(worldtransform_, viewProjection, textureHandle_);
}

void Enemy::UpdateApproach() {
	//Ú®(xNgðÁZ)
	worldtransform_.translation_ += Vector3(0, 0, -0.25f);
	//KèÌÊuÉBµ½ç£E
	if (worldtransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}
void Enemy::UpdateLeave() {
	//Ú®(xNgðÁZ)
	worldtransform_.translation_ += Vector3(-0.1f, -0.1f, -0.1f);
}