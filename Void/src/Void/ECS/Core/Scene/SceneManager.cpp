#include "pch.h"
#include "SceneManager.h"

namespace Void {
	void SceneManager::LoadScene(const char* filePath)
	{
		// Get Scene Data
		std::string data = File::Read(filePath);
		

		// Go through entities 
			// Get Entity name 

			// Get Components
				// Go through components 
					// Add them to the new entity
						// Set the data inside the component
	}

	void SceneManager::SaveScene(const char* filePath)
	{

	}
}