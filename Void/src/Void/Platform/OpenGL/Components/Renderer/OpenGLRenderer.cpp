#include "pch.h"
#include "OpenGLRenderer.h"
#include <Void/Platform/OpenGL/Debugging/OpenGLDebugger.h>
#include <Void/Rendering/Components/VertexLayout.h>
#include "Void/Rendering/Libraries/Shader/ShaderLibrary.h"
#include "Void/Rendering/Libraries/Texture/TextureLibrary.h"
#include <Void/Rendering/Libraries/Mesh/MeshLibrary.h>


namespace Void::Rendering {
	struct BatchLayout {
		glm::vec3 Position = glm::vec3(0);
		glm::vec3 Normals = glm::vec3(0);
		glm::vec2 TextureCoord = glm::vec2(0);
		glm::vec3 TextureIndex = glm::vec3(0);
		int ShowTexture = 1;
	};

	struct BatchData {
		// Limits
		static const uint32_t MaxTriangles = 40000;
		static const uint32_t MaxIndices = MaxTriangles * 3;
		static const uint32_t MaxTextureSlots = 32;

		// References
		VertexArray* VertexArray = nullptr;
		std::shared_ptr<VertexBuffer> VertexBuffer = nullptr;
		std::shared_ptr<IndexBuffer> IndexBuffer = nullptr;
		Shader* Shader = nullptr;

		Cubemap* CubemapTexture;

		// Shader settings
		glm::mat4 ViewProjectionMatrix = glm::mat4(0);
		glm::vec3 ViewPosition = glm::vec3(0);

		// Points to begin of the array
		BatchLayout* VertexBufferBase = nullptr;
		// Points to next free location in array
		BatchLayout* VertexBufferPtr = nullptr;

		// Points to begin of the array
		uint32_t* IndexBufferBase = nullptr;
		//Points to next free location in array
		uint32_t* IndexBufferPtr = nullptr;

		uint32_t GetVertexCount() { return uint32_t((uint8_t*)VertexBufferPtr - (uint8_t*)VertexBufferBase) / sizeof(BatchLayout); }
		uint32_t GetIndexCount() { return uint32_t((uint8_t*)IndexBufferPtr - (uint8_t*)IndexBufferBase) / sizeof(uint32_t); }

		// Textures
		std::array<std::string, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotsIndex = 0;

		void SetShaderSettings() {
			Shader->Bind();
			Shader->SetMatrix4("viewProjectionMatrix", ViewProjectionMatrix);
			Shader->SetVec3("viewPosition", ViewPosition);
			Shader->SetFloat("Time", Time::TimeSinceStartup());

			Shader->SetVec3("directionalLight.direction", glm::vec3(.2f, 0.f, -1.f ));
			Shader->SetVec3("directionalLight.ambient", glm::vec3( .1f, .1f, .1f ));
			Shader->SetVec3("directionalLight.diffuse", glm::vec3( .3f, .3f, .3f ));
			Shader->SetVec3("directionalLight.specular", glm::vec3( .2f, .2f, .2f ));

			// Texture
			CubemapTexture->Bind();
		}
	};

	static BatchData m_RendererData;


	void OpenGLRenderer::Initialize()
	{
		m_RendererData.VertexArray = VertexArray::Create();

		m_RendererData.VertexBuffer.reset(VertexBuffer::Create(m_RendererData.MaxIndices * sizeof(BatchLayout)));

		VertexBufferLayout bufferLayout;
		bufferLayout.Push<float>(3);
		bufferLayout.Push<float>(3);
		bufferLayout.Push<float>(2);
		bufferLayout.Push<unsigned int>(3);
		bufferLayout.Push<unsigned int>(1);
		m_RendererData.VertexBuffer->SetVertexBufferLayout(bufferLayout);

		m_RendererData.IndexBuffer.reset(IndexBuffer::Create(m_RendererData.MaxIndices * sizeof(uint32_t)));

		m_RendererData.VertexArray->AddVertexBuffer(m_RendererData.VertexBuffer);
		m_RendererData.VertexArray->SetIndexBuffer(m_RendererData.IndexBuffer);
		// Create array for vertices
		m_RendererData.VertexBufferBase = new BatchLayout[m_RendererData.MaxTriangles];

		// Create array for indices
		m_RendererData.IndexBufferBase = new uint32_t[m_RendererData.MaxIndices];
	}

	void OpenGLRenderer::Submit(VertexArray* vertexArray, const glm::mat4& modelMatrix, const std::vector<std::string>& textureNames, const std::string& shaderName, bool showTexture)
	{
		m_Submissions[shaderName].push_back({ vertexArray, modelMatrix, textureNames, showTexture });
	}

	void OpenGLRenderer::SubmitBlended(VertexArray* vertexArray, const glm::mat4& modelMatrix, const std::vector<std::string>& textureNames, const std::string& shaderName)
	{
		m_SubmissionsBlended[shaderName].push_back({ vertexArray, modelMatrix, textureNames });
	}

	void OpenGLRenderer::SubmitPointLight(const PointLightData& pointLight)
	{
		m_SubmissonsPointLight.push_back(pointLight);
	}

	void OpenGLRenderer::PrepareRender(const Camera* camera, const glm::mat4& transformMatrix)
	{
		m_RendererData.CubemapTexture = camera->GetSkybox() != "" ? TextureLibrary::GetInstance().GetCubemap(camera->GetSkybox().c_str()) : nullptr;
		m_RendererData.ViewProjectionMatrix = camera->GetProjection() * glm::inverse(transformMatrix);
		m_RendererData.ViewPosition = transformMatrix[3];
		PrepareRenderData();
	}

	void OpenGLRenderer::PrepareRender(const glm::mat4& viewProjectionMatrix, const glm::vec3& position, std::string skyboxTitle)
	{
		m_RendererData.CubemapTexture = skyboxTitle != "" ? TextureLibrary::GetInstance().GetCubemap(skyboxTitle.c_str()) : nullptr;
		m_RendererData.ViewProjectionMatrix = viewProjectionMatrix;
		m_RendererData.ViewPosition = position;
		PrepareRenderData();
	}

	void OpenGLRenderer::Render()
	{
		// Render non blended models
		for (const std::pair<std::string, std::vector<BatchSubmission>>& pair : m_Submissions) {
			ExecuteRender(pair);
		}

		// Render skybox
		if (m_RendererData.CubemapTexture != nullptr) {
			// Shader
			m_RendererData.Shader = ShaderLibrary::GetInstance()->Get("DefaultSkyboxShader");
			m_RendererData.SetShaderSettings();
			
			glm::mat4 modelMatrix = glm::translate(glm::mat4(1.f), m_RendererData.ViewPosition);
			m_RendererData.Shader->SetMatrix4("modelMatrix", modelMatrix);

			// VertexArray
			glDepthFunc(GL_LEQUAL);
			VertexArray* skyboxCube = MeshLibrary::GetInstance()->Get("Assets/Core/Models/Cube.obj")->Submeshes[0];
			skyboxCube->Bind();

			// Draw call
			skyboxCube->GetIndexBuffer().get()->Bind();
			GLCall(glDrawElements(GL_TRIANGLES, skyboxCube->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr));
			glDepthFunc(GL_LESS);
		}

		// Render blended models
		for (const std::pair<std::string, std::vector<BatchSubmission>>& pair : m_SubmissionsBlended) {
			ExecuteRender(pair);
		}
	}

	void OpenGLRenderer::ExecuteRender(const std::pair<std::string, std::vector<BatchSubmission>>& pair) {
		m_RendererData.Shader = ShaderLibrary::GetInstance()->Get(pair.first.c_str());
		m_RendererData.SetShaderSettings();

#define MAX_POINT_LIGHTS 1.f

		int PointLightSize = std::min((float)m_SubmissonsPointLight.size(), MAX_POINT_LIGHTS);
		for (int i = 0; i < PointLightSize; i++) {
			m_RendererData.Shader->SetVec3("pointLightData[" + std::to_string(i) + "].Position", m_SubmissonsPointLight[i].Position);
			m_RendererData.Shader->SetFloat("pointLightData[" + std::to_string(i) + "].Constant", m_SubmissonsPointLight[i].Constant);
			m_RendererData.Shader->SetFloat("pointLightData[" + std::to_string(i) + "].Linear", m_SubmissonsPointLight[i].Linear);
			m_RendererData.Shader->SetFloat("pointLightData[" + std::to_string(i) + "].Quadratic", m_SubmissonsPointLight[i].Quadratic);
			m_RendererData.Shader->SetVec3("pointLightData[" + std::to_string(i) + "].Ambient", m_SubmissonsPointLight[i].Ambient);
			m_RendererData.Shader->SetVec3("pointLightData[" + std::to_string(i) + "].Diffuse", m_SubmissonsPointLight[i].Diffuse);
		}


		for (auto& submission : pair.second) {
			IndexBuffer* indexBuffer = submission.VertexArray->GetIndexBuffer().get();
			VertexBuffer* vertexBuffer = submission.VertexArray->getVertexBuffers()[0].get();

			VertexLayout* vb = (VertexLayout*)vertexBuffer->GetData();

			// Check if the batch is full based on Indices Count
			if (m_RendererData.GetIndexCount() + indexBuffer->GetCount()
					> m_RendererData.MaxIndices)
				Flush();

			if (m_RendererData.GetVertexCount() + vertexBuffer->GetSize() / sizeof(VertexLayout)
					> m_RendererData.MaxTriangles)
				Flush();

			int newTextureCount = NewTexturesCount(submission.TextureNames);
			if (m_RendererData.TextureSlotsIndex + newTextureCount > m_RendererData.MaxTextureSlots - 1)
				Flush();


			// Check texture existence
			int textureIndices[3]{ -1, -1, -1 };
			for (unsigned int i = 0; i < 3; i++) {
				uint64_t textureIndex = -1;
				if (i >= submission.TextureNames.size())
					break;

				std::string textureName = submission.TextureNames[i];
				auto it = std::find(m_RendererData.TextureSlots.begin(), m_RendererData.TextureSlots.begin() + m_RendererData.TextureSlotsIndex, textureName);
				if (it != m_RendererData.TextureSlots.begin() + m_RendererData.TextureSlotsIndex) {
					textureIndex = std::distance(m_RendererData.TextureSlots.begin(), it);
				}

				if (textureIndex == -1) {
					textureIndex = m_RendererData.TextureSlotsIndex;
					m_RendererData.TextureSlots[m_RendererData.TextureSlotsIndex] = textureName;
					m_RendererData.TextureSlotsIndex++;
				}
				textureIndices[i] = textureIndex;
			}

			// Add indexBuffer to batch indexBuffer
			{
				for (int i = 0; i < indexBuffer->GetCount(); i++) {
					*m_RendererData.IndexBufferPtr = *(indexBuffer->GetIndices() + i) + m_RendererData.GetVertexCount();
					m_RendererData.IndexBufferPtr++;
				}
			}

			// Add vertexBuffer to batch vertexBuffer
			{
				const uint32_t count = vertexBuffer->GetSize() / sizeof(VertexLayout);
				VertexLayout* localVertexBuffer = (VertexLayout*)vertexBuffer->GetData();
				glm::mat3 ITModelMatrix = glm::transpose(glm::inverse(submission.ModelMatrix));
				for (uint32_t i = 0; i < count; i++) {
					VertexLayout* currentLayout = localVertexBuffer + i;
					m_RendererData.VertexBufferPtr->Position = submission.ModelMatrix * glm::vec4(currentLayout->Position, 1.f);
					m_RendererData.VertexBufferPtr->Normals = ITModelMatrix * currentLayout->Normals;
					m_RendererData.VertexBufferPtr->TextureCoord = currentLayout->TextureCoords;
					m_RendererData.VertexBufferPtr->TextureIndex[0] = textureIndices[0];
					m_RendererData.VertexBufferPtr->TextureIndex[1] = textureIndices[1];
					m_RendererData.VertexBufferPtr->ShowTexture = submission.ShowTexture;
					m_RendererData.VertexBufferPtr++;
				}
			}
		}
		Flush();
	}

	unsigned int OpenGLRenderer::NewTexturesCount(std::vector<std::string> textureNames)
	{
		unsigned int amount = 0;
		for (std::string textureName : textureNames) {
			auto it = std::find(m_RendererData.TextureSlots.begin(), m_RendererData.TextureSlots.end(), textureName);
			if (it == m_RendererData.TextureSlots.end())
				amount++;
		}
		return amount;
	}

	void OpenGLRenderer::PrepareRenderData()
	{
		m_RendererData.VertexBufferPtr = m_RendererData.VertexBufferBase;
		m_RendererData.IndexBufferPtr = m_RendererData.IndexBufferBase;

		m_RendererData.TextureSlotsIndex = 0;
		m_RendererData.Shader = nullptr;

		for (auto& pair : m_SubmissionsBlended) {
			std::sort(pair.second.begin(), pair.second.end(), [](BatchSubmission& a, BatchSubmission& b)
				{ return (a.ModelMatrix[3].z / a.ModelMatrix[3].w) < (b.ModelMatrix[3].z / b.ModelMatrix[3].w); });
		}
	}

	void OpenGLRenderer::Clear()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void OpenGLRenderer::SetClearColor(const glm::vec4& color)
	{
		GLCall(glClearColor(color.r, color.g, color.b, color.a));
	}

	void OpenGLRenderer::FinishRender()
	{
		Flush();
	}

	void OpenGLRenderer::ResetSubmissions()
	{
		m_Submissions.clear();
		m_SubmissionsBlended.clear();
		m_SubmissonsPointLight.clear();
	}

	void OpenGLRenderer::Flush()
	{
		m_RendererData.VertexArray->Bind();
		m_RendererData.Shader->Bind();

		for (uint32_t i = 0; i < m_RendererData.TextureSlotsIndex; i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			TextureLibrary::GetInstance().GetTexture(m_RendererData.TextureSlots[i].c_str())->Bind();
			m_RendererData.Shader->SetInt("Textures[" + std::to_string(i) + "]", i);
		}

		size_t indexCount = m_RendererData.GetIndexCount();
		size_t vertexCount = m_RendererData.GetVertexCount();

		m_RendererData.IndexBuffer->SetData(m_RendererData.IndexBufferBase, indexCount * sizeof(uint32_t));
		m_RendererData.VertexBuffer->SetData(m_RendererData.VertexBufferBase, vertexCount * sizeof(BatchLayout));

		GLCall(glEnable(GL_DEPTH_TEST));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		GLCall(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr));

		m_RendererData.IndexBufferPtr = m_RendererData.IndexBufferBase;
		m_RendererData.VertexBufferPtr = m_RendererData.VertexBufferBase;
		m_RendererData.TextureSlotsIndex = 0;
	}
}