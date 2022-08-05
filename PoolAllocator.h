#pragma once

template<class T, size_t MAXSIZE> class PoolAllocator
{
public:
	// コンストラクタ
	PoolAllocator() {
		buffer = new Element[MAXSIZE];
		for (auto i = 0; i < MAXSIZE - 1; i++) {
			buffer[i].next = buffer + i + 1;
		}
		buffer[MAXSIZE - 1].next = nullptr;

		// 最後に初期化した要素をhead側とする
		freeHead = buffer;
	}

	// デストラクタ
	~PoolAllocator() {
		delete[] buffer;
	}

	// 確保できない場合はnullptrを返す事。
	T* Alloc() {
		// 空きが無い場合はnullptrを返す
		if (freeHead == nullptr) {
			return nullptr;
		}

		// 確保済みで空いているものを返却する

		// NOTE: Tのコンストラクタを呼ぶとfreeHead->nextが壊れるので先にキャッシュ
		Element* next = freeHead->next;
		// bodyのメモリ空間を利用してElementを作る(placement new)
		T* elm = new(freeHead->body) T;
		freeHead = next;
		return elm;
	}

	void Free(T* addr) {
		if (addr == nullptr) {
			return;
		}

		// デストラクタを明示的に呼び出す
		addr->~T();

		// 開放するelementを空きリストの頭につける
		Element* elm = reinterpret_cast<Element*>(addr);
		elm->next = freeHead;
		freeHead = elm;
	}

private:
	union Element {
		char body[sizeof(T)]; // 1バイトの領域をsizeof(T)分確保
		Element* next; // 同一メモリ空間上に次の要素へのポインタを持たせる
	};

	Element* buffer;
	Element* freeHead;
};