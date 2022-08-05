#pragma once

template<class T, size_t MAXSIZE> class PoolAllocator
{
public:
	// �R���X�g���N�^
	PoolAllocator() {
		buffer = new Element[MAXSIZE];
		for (auto i = 0; i < MAXSIZE - 1; i++) {
			buffer[i].next = buffer + i + 1;
		}
		buffer[MAXSIZE - 1].next = nullptr;

		// �Ō�ɏ����������v�f��head���Ƃ���
		freeHead = buffer;
	}

	// �f�X�g���N�^
	~PoolAllocator() {
		delete[] buffer;
	}

	// �m�ۂł��Ȃ��ꍇ��nullptr��Ԃ����B
	T* Alloc() {
		// �󂫂������ꍇ��nullptr��Ԃ�
		if (freeHead == nullptr) {
			return nullptr;
		}

		// �m�ۍς݂ŋ󂢂Ă�����̂�ԋp����

		// NOTE: T�̃R���X�g���N�^���ĂԂ�freeHead->next������̂Ő�ɃL���b�V��
		Element* next = freeHead->next;
		// body�̃�������Ԃ𗘗p����Element�����(placement new)
		T* elm = new(freeHead->body) T;
		freeHead = next;
		return elm;
	}

	void Free(T* addr) {
		if (addr == nullptr) {
			return;
		}

		// �f�X�g���N�^�𖾎��I�ɌĂяo��
		addr->~T();

		// �J������element���󂫃��X�g�̓��ɂ���
		Element* elm = reinterpret_cast<Element*>(addr);
		elm->next = freeHead;
		freeHead = elm;
	}

private:
	union Element {
		char body[sizeof(T)]; // 1�o�C�g�̗̈��sizeof(T)���m��
		Element* next; // ���ꃁ������ԏ�Ɏ��̗v�f�ւ̃|�C���^����������
	};

	Element* buffer;
	Element* freeHead;
};