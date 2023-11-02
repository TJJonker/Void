#include "pch.h"
#include "LayerStack.h"

namespace Void {
	LayerStack::LayerStack()
	{
		m_Insert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for(Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Insert = m_Layers.emplace(m_Insert, layer);
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		m_Layers.emplace_back(layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		std::vector<Layer*>::iterator it = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_Insert--;
		}
	}

	void LayerStack::PopOverlay(Layer* layer)
	{
		std::vector<Layer*>::iterator it = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (it != m_Layers.end()) {
			m_Layers.erase(it);
		}
	}
}