#pragma once

namespace Void {

	/// <summary>
	/// interface for poolable objects.
	/// </summary>
	struct IPoolObject {
		// ID of the object.
		unsigned int ID;
		
		// Resets the poolable object. 
		virtual void Reset() = 0;
	};
}