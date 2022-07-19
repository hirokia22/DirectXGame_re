#include"Enemy.h"
#include<cassert>
#include"Player.h"
using namespace MathUtility;
void Enemy::Initialize(Model* model) {
	//NULLポインタチェック
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("Enemy01.png");
	worldtransform_.Initialize();
	worldtransform_.translation_ = { 10,2,50 };
	//接近フェーズ初期化
	InitializeApproach();
}

void Enemy::InitializeApproach() {
	fireTimer_ = kFireInterval;
}
void Enemy::Update() {
	//デスフラグのたった弾を削除
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
		});
	switch (phase_) {
	case Phase::Approach:
		UpdateApproach();
		break;
	case Phase::Leave:
		UpdateLeave();
		break;
	}

	//スケーリング行列を宣言
	Matrix4 matScale = MathUtility::Matrix4Identity();
	matScale.m[0][0] = worldtransform_.scale_.x;
	matScale.m[1][1] = worldtransform_.scale_.y;
	matScale.m[2][2] = worldtransform_.scale_.z;
	
	//Z軸回転行列を宣言
	Matrix4 matRotZ = MathUtility::Matrix4Identity();
	matRotZ.m[0][0] = cosf(worldtransform_.rotation_.z);
	matRotZ.m[0][1] = sinf(worldtransform_.rotation_.z);
	matRotZ.m[1][0] = -sinf(worldtransform_.rotation_.z);
	matRotZ.m[1][1] = cosf(worldtransform_.rotation_.z);

	//X軸回転行列を宣言
	Matrix4 matRotX = MathUtility::Matrix4Identity();
	matRotX.m[1][1] = cosf(worldtransform_.rotation_.x);
	matRotX.m[1][2] = sinf(worldtransform_.rotation_.x);
	matRotX.m[2][1] = -sinf(worldtransform_.rotation_.x);
	matRotX.m[2][2] = cosf(worldtransform_.rotation_.x);

	//Y軸回転行列を宣言
	Matrix4 matRotY = MathUtility::Matrix4Identity();
	matRotY.m[0][0] = cosf(worldtransform_.rotation_.y);
	matRotY.m[0][2] = -sinf(worldtransform_.rotation_.y);
	matRotY.m[2][0] = sinf(worldtransform_.rotation_.y);
	matRotY.m[2][2] = cosf(worldtransform_.rotation_.y);

	//平行移動行列を宣言
	Matrix4 matTrans = MathUtility::Matrix4Identity();
	matTrans.m[3][0] = worldtransform_.translation_.x;
	matTrans.m[3][1] = worldtransform_.translation_.y;
	matTrans.m[3][2] = worldtransform_.translation_.z;

	//ワールド行列
	worldtransform_.matWorld_ = MathUtility::Matrix4Identity();
	worldtransform_.matWorld_ *= matScale;
	worldtransform_.matWorld_ *= matRotZ;
	worldtransform_.matWorld_ *= matRotX;
	worldtransform_.matWorld_ *= matRotY;
	worldtransform_.matWorld_ *= matTrans;

	//行列の転送
	worldtransform_.TransferMatrix();

	//弾の更新処理
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	//モデルの描画
	model_->Draw(worldtransform_, viewProjection, textureHandle_);

	//弾の描画
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::UpdateApproach() {
	//移動(ベクトルを加算)
	worldtransform_.translation_ += Vector3(0, 0, -0.25f);
	//規定の位置に到達したら離脱
	if (worldtransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
	//発射タイマーカウントダウン
	fireTimer_--;
	//指定時間に達した
	if (fireTimer_ <= 0) {
		//弾を発射
		Fire();
		//発射タイマーを初期化
		fireTimer_ = kFireInterval;
	}
}
void Enemy::UpdateLeave() {
	//移動(ベクトルを加算)
	worldtransform_.translation_ += Vector3(-0.1f, -0.1f, -0.1f);
}
void Enemy::Fire() {
	//弾の速度
	const float kBulletSpeed = 1.0f;

	Vector3 playerPos = player_->GetWorldPosition();
	Vector3 enemyPos = GetWorldPosition();
	Vector3 velocity = playerPos - enemyPos;
	MathUtility::Vector3Normalize(velocity);
	velocity *= kBulletSpeed;

	//弾を生成し、初期化
	std::unique_ptr<EnemyBullet> newBullet =
		std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldtransform_.translation_, velocity);
	//弾を登録する
	bullets_.push_back(std::move(newBullet));
}
Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];
	return worldPos;
}