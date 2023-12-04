#include "pch.h"
#include "OpenGLRenderer.h"
#include <Void/Platform/OpenGL/Debugging/OpenGLDebugger.h>
#include <Void/Rendering/Components/VertexLayout.h>
#include "Void/Rendering/Libraries/Shader/ShaderLibrary.h"
#include "Void/Rendering/Libraries/Texture/TextureLibrary.h"


namespace Void::Rendering {
	struct BatchLayout {
		glm::vec3 Position = glm::vec3(0);
		//glm::vec3 Normals = glm::vec3(0);
		//glm::vec2 TextureCoord = glm::vec2(0);
		//unsigned int TextureIndex[3];
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
		}
	};

	static BatchData m_RendererData;


	void OpenGLRenderer::Initialize()
	{
		m_RendererData.VertexArray = VertexArray::Create();

		m_RendererData.VertexBuffer.reset(VertexBuffer::Create(m_RendererData.MaxIndices * sizeof(BatchLayout)));

		VertexBufferLayout bufferLayout;
		bufferLayout.Push<float>(3);
		//bufferLayout.Push<float>(3);
		//bufferLayout.Push<float>(2);
		//bufferLayout.Push<unsigned int>(3);
		m_RendererData.VertexBuffer->SetVertexBufferLayout(bufferLayout);

		m_RendererData.IndexBuffer.reset(IndexBuffer::Create(m_RendererData.MaxIndices * sizeof(uint32_t)));

		m_RendererData.VertexArray->AddVertexBuffer(m_RendererData.VertexBuffer);
		m_RendererData.VertexArray->SetIndexBuffer(m_RendererData.IndexBuffer)
			;
		// Create array for vertices
		m_RendererData.VertexBufferBase = new BatchLayout[m_RendererData.MaxTriangles];

		// Create array for indices
		m_RendererData.IndexBufferBase = new uint32_t[m_RendererData.MaxIndices];
	}

	void OpenGLRenderer::Submit(VertexArray* vertexArray, const glm::mat4& modelMatrix, const std::vector<std::string>& textureNames, const std::string& shaderName)
	{
		m_Submissions[shaderName].push_back({ vertexArray, modelMatrix, textureNames });
	}

	void OpenGLRenderer::SubmitBlended(VertexArray* vertexArray, const glm::mat4& modelMatrix, const std::vector<std::string>& textureNames, const std::string& shaderName)
	{
		m_SubmissionsBlended[shaderName].push_back({ vertexArray, modelMatrix, textureNames });
	}

	void OpenGLRenderer::PrepareRender(const Camera* camera, const glm::mat4& transformMatrix)
	{
		m_RendererData.ViewProjectionMatrix = camera->GetProjection() * glm::inverse(transformMatrix);
		m_RendererData.ViewPosition = transformMatrix[3];
		PrepareRenderData();
	}

	void OpenGLRenderer::PrepareRender(const glm::mat4& viewProjectionMatrix, const glm::vec3 cameraPosition)
	{
		m_RendererData.ViewProjectionMatrix = viewProjectionMatrix;
		m_RendererData.ViewPosition = cameraPosition;
		PrepareRenderData();
	}

	void OpenGLRenderer::Render()
	{
		for (auto& pair : m_Submissions) {
			m_RendererData.Shader = ShaderLibrary::GetInstance()->Get(pair.first.c_str());
			m_RendererData.SetShaderSettings();
			for (auto& submission : pair.second) {
				IndexBuffer* indexBuffer = submission.VertexArray->GetIndexBuffer().get();
				VertexBuffer* vertexBuffer = submission.VertexArray->getVertexBuffers()[0].get();

				// Check if the batch is full based on Indices Count
				if (m_RendererData.GetIndexCount() + submission.VertexArray->GetIndexBuffer()->GetCount()
					> m_RendererData.MaxIndices)
					Flush();

				int newTextureCount = NewTexturesCount(submission.TextureNames);
				if (m_RendererData.TextureSlotsIndex + newTextureCount > m_RendererData.MaxTextureSlots - 1)
					Flush();

				// Check texture existence
				unsigned int textureIndices[3]{ -1 };
				for (unsigned int i = 0; i < 3; i++) {
					uint64_t textureIndex = -1;
					if (i >= submission.TextureNames.size())
						break;

					std::string textureName = submission.TextureNames[i];
					auto it = std::find(m_RendererData.TextureSlots.begin(), m_RendererData.TextureSlots.end(), textureName);
					if (it != m_RendererData.TextureSlots.end()) {
						textureIndex = std::distance(m_RendererData.TextureSlots.begin(), it);
					}

					if (textureIndex == -1) {
						textureIndex = m_RendererData.TextureSlotsIndex;
						m_RendererData.TextureSlots[m_RendererData.TextureSlotsIndex] = textureName;
						m_RendererData.TextureSlotsIndex++;
					}
					textureIndices[i] = textureIndex;
				}

				// Add vertexBuffer to batch vertexBuffer
				{
					const uint32_t count = vertexBuffer->GetSize() / sizeof(VertexLayout);
					VertexLayout* localVertexBuffer = (VertexLayout*)vertexBuffer->GetData();
					for (uint32_t i = 0; i < count; i++) {
						VertexLayout* currentLayout = localVertexBuffer + i;
						m_RendererData.VertexBufferPtr->Position = submission.ModelMatrix * glm::vec4(currentLayout->Position, 1.f);
						//m_RendererData.VertexBufferPtr->Normals = currentLayout->Normals;
						//m_RendererData.VertexBufferPtr->TextureCoord = currentLayout->TextureCoords;
						//m_RendererData.VertexBufferPtr->TextureIndex[0] = textureIndices[0];

						//glm::vec4 tempPos = m_RendererData.ViewProjectionMatrix * glm::vec4(m_RendererData.VertexBufferPtr->Position, 1.0f);
						//VOID_TRACE("Pos x vpm {0} - x: {1}, y: {2}, z: {3}, w: {4}", i, tempPos.x, tempPos.y, tempPos.z, tempPos.w);
						m_RendererData.VertexBufferPtr++;
					}
				}

				// Add indexBuffer to batch indexBuffer
				{
					const uint32_t count = indexBuffer->GetCount();
					const uint32_t* data = indexBuffer->GetIndices();
					//for (int i = 0; i < 100; i++)
					//	VOID_TRACE("Early indexbuffer check - {0}: {1}", i, *(data + i));
					//VOID_TRACE("Early indexbuffer check minus one - {0}: {1}", count - 1, *(data + count - 1));
					memcpy_s(m_RendererData.IndexBufferPtr, m_RendererData.MaxIndices, data, count * sizeof(uint32_t));
	/*				for (int i = 0; i < 100; i++)
						VOID_TRACE("Stored indexbuffer check - {0}: {1}", i, *(m_RendererData.IndexBufferBase + i));*/
					m_RendererData.IndexBufferPtr += count;
					//VOID_TRACE("ptr check: {0}", *m_RendererData.IndexBufferPtr);
					//VOID_TRACE("ptr check minus one: {0}", *(m_RendererData.IndexBufferPtr - 1));
				}
			}
			Flush();
		}
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
				{ return (a.ModelMatrix[3].z / a.ModelMatrix[3].w) > (b.ModelMatrix[3].z / b.ModelMatrix[3].w); });
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
	}

	void OpenGLRenderer::Flush()
	{
		m_RendererData.Shader->Bind();

		for (uint32_t i = 0; i < m_RendererData.TextureSlotsIndex; i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			TextureLibrary::GetInstance()->Get(m_RendererData.TextureSlots[i].c_str())->Bind();
		}

		m_RendererData.IndexBuffer->SetData(m_RendererData.IndexBufferBase, m_RendererData.GetIndexCount());
		m_RendererData.VertexBuffer->SetData(m_RendererData.VertexBufferBase, m_RendererData.GetVertexCount() * sizeof(BatchLayout));

		for (int i = 0; i < 100; i++) {
			VOID_TRACE("VertexData {0} - x: {1}, y: {2}, z: {3}", i, (m_RendererData.VertexBufferBase + i)->Position.x, (m_RendererData.VertexBufferBase + i)->Position.y, (m_RendererData.VertexBufferBase + i)->Position.z);
			///VOID_TRACE("IndexData {0} - index: {1}", i, *(m_RendererData.IndexBufferBase + i));
		}

		m_RendererData.VertexArray->Bind();
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glDrawElements(GL_TRIANGLES, m_RendererData.VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr));

		m_RendererData.IndexBufferPtr = m_RendererData.IndexBufferBase;
		m_RendererData.VertexBufferPtr = m_RendererData.VertexBufferBase;
	}
}









	//void OpenGLRenderer::Draw(VertexArray* vertexArray)
	//{
	//	glEnable(GL_DEPTH_TEST);
	//	GLCall(glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr));
	//}

	//void OpenGLRenderer::Clear()
	//{
	//	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	//}

	//void OpenGLRenderer::SetClearColor(const glm::vec4& color)
	//{
	//	GLCall(glClearColor(color.r, color.g, color.b, color.a));
	//}

	//void OpenGLRenderer::Initialize()
	//{
	//	// VertexArray
	//	m_RendererData.VertexArray = VertexArray::Create();

	//	// VertexBuffer 
	//	m_RendererData.VertexBuffer = VertexBuffer::Create(m_RendererData.MaxTriangles * sizeof(BatchVertexLayout));
	//	VertexBufferLayout bufferLayout;
	//	bufferLayout.Push<float>(3);
	//	bufferLayout.Push<float>(2);
	//	bufferLayout.Push<unsigned int>(1);
	//	m_RendererData.VertexBuffer->SetVertexBufferLayout(bufferLayout);
	//	m_RendererData.VertexArray->AddVertexBuffer(std::make_shared<VertexBuffer>(m_RendererData.VertexBuffer));

	//	// Create array for vertices
	//	m_RendererData.VertexLayoutBufferBase = new BatchVertexLayout[m_RendererData.MaxTriangles];

	//	// Create array for indices
	//	m_RendererData.IndexBufferBase = new uint32_t[m_RendererData.MaxIndices];

	//}

	//void OpenGLRenderer::BeginDraw(const glm::mat4& view, float fov, const glm::vec3& position)
	//{
	//	m_RendererData.IndexCount = 0;
	//	m_RendererData.VertexLayoutBufferPtr = m_RendererData.VertexLayoutBufferBase;
	//	m_RendererData.IndexBufferPtr = m_RendererData.IndexBufferBase;

	//	m_RendererData.TextureSlotsIndex = 0;
	//	m_RendererData.Shader = nullptr;
	//}

	//void OpenGLRenderer::Submit(VertexArray* vertexArray, std::string shaderPath, glm::mat4 modelMatrix)
	//{

	//}

	//void OpenGLRenderer::EndDraw()
	//{

	//}
