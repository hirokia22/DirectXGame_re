#include "EnemyBullet.h"
#include <cassert>

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	//NULL�|�C���^�`�F�b�N
	assert(model);
	
	model_ = model;
	//�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("red.png");
	
	//���[���h�g�����X�t�H�[���̏�����
	worldtransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldtransform_.translation_ = position;
}

void EnemyBullet::Update() {
	//���W���ړ�������(1�t���[�����̈ړ��ʂ𑫂�����)
	worldtransform_.translation_ += velocity_;
	
	//���Ԍo�߂Ńf�X
	if (--deathTimer <= 0) {
		isDead_ = true;
	}

	//�X�P�[�����O�s���錾
	Matrix4 matScale = MathUtility::Matrix4Identity();
	matScale.m[0][0] = worldtransform_.scale_.x;
	matScale.m[1][1] = worldtransform_.scale_.y;
	matScale.m[2][2] = worldtransform_.scale_.z;

	//Z����]�s���錾
	Matrix4 matRotZ = MathUtility::Matrix4Identity();
	matRotZ.m[0][0] = cosf(worldtransform_.rotation_.z);
	matRotZ.m[0][1] = sinf(worldtransform_.rotation_.z);
	matRotZ.m[1][0] = -sinf(worldtransform_.rotation_.z);
	matRotZ.m[1][1] = cosf(worldtransform_.rotation_.z);

	//X����]�s���錾
	Matrix4 matRotX = MathUtility::Matrix4Identity();
	matRotX.m[1][1] = cosf(worldtransform_.rotation_.x);
	matRotX.m[1][2] = sinf(worldtransform_.rotation_.x);
	matRotX.m[2][1] = -sinf(worldtransform_.rotation_.x);
	matRotX.m[2][2] = cosf(worldtransform_.rotation_.x);

	//Y����]�s���錾
	Matrix4 matRotY = MathUtility::Matrix4Identity();
	matRotY.m[0][0] = cosf(worldtransform_.rotation_.y);
	matRotY.m[0][2] = -sinf(worldtransform_.rotation_.y);
	matRotY.m[2][0] = sinf(worldtransform_.rotation_.y);
	matRotY.m[2][2] = cosf(worldtransform_.rotation_.y);

	//���s�ړ��s���錾
	Matrix4 matTrans = MathUtility::Matrix4Identity();
	matTrans.m[3][0] = worldtransform_.translation_.x;
	matTrans.m[3][1] = worldtransform_.translation_.y;
	matTrans.m[3][2] = worldtransform_.translation_.z;

	//���[���h�s��
	worldtransform_.matWorld_ = MathUtility::Matrix4Identity();
	worldtransform_.matWorld_ *= matScale;
	worldtransform_.matWorld_ *= matRotZ;
	worldtransform_.matWorld_ *= matRotX;
	worldtransform_.matWorld_ *= matRotY;
	worldtransform_.matWorld_ *= matTrans;

	//�s��̓]��
	worldtransform_.TransferMatrix();
}
void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	//���f���̕`��
	model_->Draw(worldtransform_, viewProjection, textureHandle_);
}
void EnemyBullet::OnCollision() {
	isDead_ = true;
}

Vector3 EnemyBullet::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldtransform_.translation_.x;
	worldPos.y = worldtransform_.translation_.y;
	worldPos.z = worldtransform_.translation_.z;
	return worldPos;
}