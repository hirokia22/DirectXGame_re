#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle) {
	//NULL�|�C���^�`�F�b�N
	assert(model);
	this->model_ = model;
	this->textureHandle_ = textureHandle;

	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	worldtransform_.scale_ = { 2,2,2 };
	worldtransform_.Initialize();
	Matrix4 matScale;
}
void Player::Update() {
	//�f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});
	Move();
	debugText_->SetPos(50, 150);
	debugText_->Printf("x:%f,y:%f,y:%f", worldtransform_.translation_.x,
		worldtransform_.translation_.y, worldtransform_.translation_.z);
	Attack();
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
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
	// A�L�[����������
	if (input_->PushKey(DIK_A))
	{
		// �v���X�ɉ�]
		worldtransform_.rotation_.y += 0.05f;
	}
	// D�L�[����������
	if (input_->PushKey(DIK_D))
	{
		// �}�C�i�X�ɉ�]
		worldtransform_.rotation_.y -= 0.05f;
	}
	// �s��̍X�V
	// Y����]�s���錾
	Matrix4 matRotY = MathUtility::Matrix4Identity();
	matRotY.m[0][0] = cosf(worldtransform_.rotation_.y);
	matRotY.m[0][2] = -sinf(worldtransform_.rotation_.y);
	matRotY.m[2][0] = sinf(worldtransform_.rotation_.y);
	matRotY.m[2][2] = cosf(worldtransform_.rotation_.y);
	// ���s�ړ��s���錾
	Matrix4 matTrans = MathUtility::Matrix4Identity();
	matTrans.m[3][0] = worldtransform_.translation_.x;
	matTrans.m[3][1] = worldtransform_.translation_.y;
	matTrans.m[3][2] = worldtransform_.translation_.z;
	worldtransform_.matWorld_ = MathUtility::Matrix4Identity();
	// ���[���h�s���Y����]�s��������� ����1
	worldtransform_.matWorld_ *= matRotY;
	worldtransform_.matWorld_ *= matTrans;
	worldtransform_.TransferMatrix();
}
void Player::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldtransform_, viewProjection_, textureHandle_);
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
}
void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		//�e�̑��x
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		//���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
		velocity = MathUtility::Vector3TransformNormal(velocity, worldtransform_.matWorld_);
		//�e�𐶐����A������
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, worldtransform_.translation_, velocity);

		//�e��o�^����
		bullets_.push_back(std::move(newBullet));
	}
}
Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];
	return worldPos;
}
void Player::OnCollision() {}
