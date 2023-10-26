#pragma once

static int s_componentCounter = 0;

template<class T>
int GetComponentID() {
	static int componentID = s_componentCounter++;
	return componentID;
}