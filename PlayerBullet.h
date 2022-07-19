#pragma once
#include <Model.h>
#include"WorldTransform.h"
/// <summary>
/// ���L�����̒e
/// </summary>
class PlayerBullet {
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name ="model">���f��</param>
	/// <param name ="position">�������W</param>
	void Initialize(Model* model, const Vector3& potision);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldtransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//���x
	Vector3 velocity_;
    //����
	static const int32_t kLifeTime = 60 * 5;
	//�f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;
};
