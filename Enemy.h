#pragma once
#include "WorldTransform.h"
#include"Model.h"
#include"EnemyBullet.h"
#include<memory>
#include<list>
/// <summary>
/// �G
/// </summary>
class Enemy {
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(const ViewProjection &viewProjection);

	/// <summary>
	/// �e����
	/// </summary>
	void Fire();

	//�s���t�F�[�Y
	enum class Phase {
		Approach,	//�ڋ�
		Leave,		//���E
	};

	//�ڋ߃t�F�[�Y�������֐�
	void InitializeApproach();
	
	//���ˊԊu
	static const int kFireInterval = 60;
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldtransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//�t�F�[�Y
	Phase phase_ = Phase::Approach;
	//�ڋ߃t�F�[�Y�̍X�V�֐�
	void UpdateApproach();
	//���E�t�F�[�Y�̍X�V�֐�
	void UpdateLeave();
	//�e
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	//���˃^�C�}�[
	int32_t fireTimer_ = 0;
};
