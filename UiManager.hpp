#pragma once

class Uibase; 

class UiManager
{
public:
	UiManager();
	~UiManager();

	void Initialize();

	void Update();

private:

	std::shared_ptr<Uibase> m_uibase; // Pointer to the base UI class

};

