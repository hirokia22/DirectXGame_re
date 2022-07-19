#pragma once
#include "WorldTransform.h"
#include<Model.h>
#include"DebugText.h"
#include"Input.h"
#include"PlayerBullet.h"
#include<memory>
#include<list>

/// <summary>
/// ���L����
/// </summary>

class Player {
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);
	/// <summary>
	///�X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �ړ�
	/// </summary>
	void Move();
	/// <summary>
	///�`��
	/// </summary>
	void Draw(ViewProjection viewProjection);

	/// <summary>
	/// �U��
	/// </summary>
	void Attack();
	
	//���[���h���W���擾
	Vector3 GetWorldPosition();
	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

	//�e���X�g���擾
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullet() { return bullets_; }
	//�e�̑傫��
	static const int kRadius = 1;
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldtransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	//�e
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

};