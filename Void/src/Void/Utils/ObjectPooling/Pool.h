#include "IPoolObject.h"
#include <type_traits>
#include <vector>
#include <vector>
#include <queue>
#include <Void/Core/Core.h>
#pragma once

namespace Void {

	/// <summary>
	/// Object pool structure for easy access to pre instantiated objects.
	/// </summary>
	/// <typeparam name="T">Poolable object.</typeparam>
	template<typename T>
	class Pool {
		static_assert(std::is_base_of<IPoolObject, T>::value, "T must be derived from PoolObject");

	private:
		// List of all objects.
		std::vector<T*> m_Pool;
		// List of active objects, referenced to m_Pool.
		std::vector<unsigned int> m_ActivePool;
		// Queue of active objects, referenced to m_Pool.
		std::queue<unsigned int> m_PassivePool;

	public:
		/// <summary>
		/// Creates a pool with a set amount of preinstantiated objects.
		/// </summary>
		/// <param name="amountOfObjects">Amount of preinstantiated objects.</param>
		Pool(unsigned int amountOfObjects) {
			for (unsigned int i = 0; i < amountOfObjects; ++i) {
				AddObjectToPool();
			}
		}

		/// <summary>
		/// Retrieves an object, ready to use.
		/// </summary>
		/// <returns>An object, ready to use.</returns>
		unsigned int Get() { 
			if (m_PassivePool.empty()) {
				AddObjectToPool();
			}
			
			unsigned int index = m_PassivePool.front();
			m_PassivePool.pop();
			m_ActivePool.push_back(index);
			return index;
		}

		/// <summary>
		/// Retrieves an object from the pool.
		/// </summary>
		/// <param name="id">Id of the object that should be returned.</param>
		/// <returns>An object from the pool with the corresponding ID.</returns>
		T* GetPoolObject(unsigned int id) const {
			VOID_ASSERT(id < m_Pool.size(), "ID exceeds pool boundaries.");
			return m_Pool[id];
		}

		/// <summary>
		/// Returns a list of indexes, containing the id's of the active objects.
		/// </summary>
		/// <returns></returns>
		std::vector<unsigned int> GetActivePool() const {
			return m_ActivePool;
		}

		/// <summary>
		/// Releases an object back into the pool and resets it.
		/// </summary>
		/// <param name="object">Object to be returned into the pool.</param>
		void Release(T* object) {
			object->Reset();
			m_PassivePool.push(object->ID);
			std::vector<unsigned int>::iterator it = std::find(m_ActivePool.begin(), m_ActivePool.end(), object->m_ID);
			m_ActivePool.erase(it);
		}

	private:
		/// <summary>
		/// Instantiates an object and adds it to the pool.
		/// </summary>
		void AddObjectToPool() {
			T* object = new T();
			m_Pool.push_back(object);
			object->ID = m_Pool.size() - 1;
			m_PassivePool.push(object->ID);
		}
	};
}