#include "pch.h"
#include "FMODAudioManager.h"
#include "Void/Platform/FMOD/Utils/FMODUtils.h"

namespace Void::Audio {
	FMODAudioManager::FMODAudioManager()
	{
		Initialize(100);
	}

	void FMODAudioManager::Initialize(unsigned int maxChannels)
	{
		FMOD_RESULT result;
		result = FMOD::System_Create(&m_System);
		VOID_ASSERT(result == FMOD_OK, "Failed to create the audio system.");

		result = m_System->init(maxChannels, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, (void*)0);
		VOID_ASSERT(result == FMOD_OK, "Failed to initialize the audio system.");

		result = m_System->set3DSettings(.5f, .5f, 0.1f);
		result = m_System->setGeometrySettings(1000.0f);
		VOID_ASSERT(result == FMOD_OK, "Failed to initialize the geometry settings");

		result = m_System->createGeometry(2000, 8000, &m_Geometry);
		VOID_ASSERT(result == FMOD_OK, "Failed to initialize the geometry");

		m_Library = new FMODAudioLibrary(m_System);
		m_ChannelsPool = new Pool<Channel>(maxChannels);

		{
			ChannelGroup* group = new ChannelGroup();
			m_ChannelGroups.push_back(group); // Master
			m_System->createChannelGroup("Master", &group->Group);
		}

		{
			ChannelGroup* group = new ChannelGroup();
			m_ChannelGroups.push_back(group); // Music
			m_System->createChannelGroup("Music", &group->Group);
		}

		{
			ChannelGroup* group = new ChannelGroup();
			m_ChannelGroups.push_back(group); // SFX
			m_System->createChannelGroup("SFX", &group->Group);
		}
	}

	void FMODAudioManager::Update()
	{
		m_System->update();
	}

	void FMODAudioManager::Destroy()
	{
		m_System->release();
	}

	void FMODAudioManager::LoadAudio(const char* filePath)
	{
		m_Library->LoadAudio(filePath);
	}

	void FMODAudioManager::LoadStream(const char* filePath)
	{
		m_Library->LoadStream(filePath);
	}

	void FMODAudioManager::Load3DAudio(const char* filePath, bool loop)
	{
		m_Library->Load3DAudio(filePath, loop);
	}

	unsigned int FMODAudioManager::PlayAudio(const char* filePath, int channelGroupIndex)
	{
		FMOD::Sound* sound = m_Library->GetSound(filePath);
		unsigned int channelIndex = m_ChannelsPool->Get();
		Channel* channel = m_ChannelsPool->GetPoolObject(channelIndex);
		m_System->playSound(sound, m_ChannelGroups[channelGroupIndex]->Group, false, &channel->FMODChannel);
		return channelIndex;
	}

	void FMODAudioManager::StopAudio(unsigned int channelIndex)
	{
		Channel* channel = m_ChannelsPool->GetPoolObject(channelIndex);
		channel->FMODChannel->stop();
		m_ChannelsPool->Release(channel);
	}

	void FMODAudioManager::SetListenerAttributes(const glm::vec3& position, const glm::vec3& velocity, const glm::vec3& forward, const glm::vec3& up)
	{
		FMOD_RESULT result;
		FMOD_VECTOR fpos = ToFMOD(position);
		FMOD_VECTOR fvel = ToFMOD(velocity);
		FMOD_VECTOR ffwd = ToFMOD(forward);
		FMOD_VECTOR fup  = ToFMOD(up);

		result = m_System->set3DListenerAttributes(0, &fpos, &fvel, &ffwd, &fup);

		VOID_ASSERT(result == FMOD_OK, "Error while setting 3D listener attribute.");
	}

	unsigned int FMODAudioManager::AddPolygon(float direct, float reverb, bool doublesided, const std::vector<glm::vec3>& vertices, const glm::vec3& position)
	{
		FMOD_RESULT result;
		int index;

		// Add the polygon
		std::vector<FMOD_VECTOR> fmodVertices(vertices.size());
		for (int i = 0; i < fmodVertices.size(); i++) 
			fmodVertices[i] = ToFMOD(vertices[i]);

		result = m_Geometry->addPolygon(direct, reverb, doublesided, fmodVertices.size(), fmodVertices.data(), &index);
		VOID_ASSERT(result == FMOD_OK, "Error while adding polygon.");

		// Set the position
		FMOD_VECTOR fmodPosition = ToFMOD(position);
		result = m_Geometry->setPosition(&fmodPosition);
		VOID_ASSERT(result == FMOD_OK, "Error while setting position.");

		glm::vec3 scale(1.f);
		FMOD_VECTOR fmodScale = ToFMOD(scale);
		result = m_Geometry->setScale(&fmodScale);
		VOID_ASSERT(result == FMOD_OK, "Error while setting scale.");

		m_Geometry->setActive(true);

		FMOD_VECTOR v;
		glm::vec3 g;
		for (int i = 0; i < fmodVertices.size(); i++)
		{
			m_Geometry->getPolygonVertex(index, i, &v);
			g = { v.x, v.y, v.z };
			printf("%.2f, %.2f, %.2f = %.2f, %.2f, %.2f\n", g.x, g.y, g.z,
				vertices[i].x, vertices[i].y, vertices[i].z);
		}

		return index;

		//int index;
		//FMOD_RESULT result;
		//int numVertices = vertices.size();

		//FMOD_VECTOR rect[4] = { {-8.f, 0.f,  0}, {-8.f, 7.f,  0}, {-2, 7, 0}, {-2, 0, 0} };

		//result = m_Geometry->addPolygon(0.9f, 0.9f, true, 4, rect, &index);
		////FMODCheckError(result);

		//FMOD_VECTOR v;
		//glm::vec3 g;

		//for (int i = 0; i < numVertices; i++)
		//{
		//	m_Geometry->getPolygonVertex(index, i, &v);
		//	g = { v.x, v.y, v.z };
		//	printf("%.2f, %.2f, %.2f = %.2f, %.2f, %.2f\n", g.x, g.y, g.z,
		//		vertices[i].x, vertices[i].y, vertices[i].z);
		//}

		//m_Geometry->setActive(true);
		//return index;
	}

	bool FMODAudioManager::IsValid(unsigned int channelID)
	{
		return m_ChannelsPool->GetPoolObject(channelID)->FMODChannel;
	}

	void FMODAudioManager::SetChannelAttributes(unsigned int channelID, const glm::vec3& position, const glm::vec3 velocity)
	{
		FMOD_RESULT result;
		FMOD_VECTOR fpos = ToFMOD(position);
		FMOD_VECTOR fvel = ToFMOD(velocity);
		result = m_ChannelsPool->GetPoolObject(channelID)->FMODChannel->set3DAttributes(&fpos, &fvel);
		VOID_ASSERT(result == FMOD_OK, "Error while setting 3D attribute.");
	}
}