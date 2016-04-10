#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <list>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <functional>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <tinyxml.h>

#include "object.h"
#include "animation.h"
#include "hud.h"

namespace GameSpace
{
	//////////////////////////////////////////////////////////////////////////
	// ����� - ��������� ������������
	//////////////////////////////////////////////////////////////////////////
	class ContactDispatcher : public b2ContactListener
	{
		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;
	};
	//////////////////////////////////////////////////////////////////////////
	// ����� �������� ����
	//////////////////////////////////////////////////////////////////////////
	class World final
	{
		ContactDispatcher m_contactDispatcher;

		std::unique_ptr<b2World> m_physWorld;

		std::list<std::shared_ptr<Object>> m_gameObjects;

		std::string m_lastLevel;

		World(const World& other) = delete;
		World& operator=(const World& other) = delete;

		/*
			@brief ������ �������� �� XML ��������
			@param element XML �������
			@param name �������� ��������
			@ret   ��������
		*/
		std::string readValFromXML(TiXmlElement* element, const std::string& name);
		/*
			@brief ������� �������� �� XML ��������
			@param rootElement �������� XML �������
			@ret   ��������
		*/
		Animation readAnimationFromXML(TiXmlElement* rootElement);
		/*
			@brief ������ HUD �� XML ��������
			@param rootElement �������� �������, ����������� HUD
			@ret   ������ HUD
		*/
		HUD readHUDFromXML(TiXmlElement* rootElement);
		/*
			@brief ��������� �������� ������ � ���������� ��� � ���
			@param playerCfg ����, ���������� ������
			@param leftX ����� ����
			@param bottomY ������ ����
		*/
		void loadPlayerFromFile(const std::string& playerCfg, int leftX, int bottomY);
		/*
			@brief	������� ��� �������� ����
					���������� ����� ����������
		*/
		std::function<void(sf::RenderWindow&)> m_controlView;
		/*
			@brief ������� ��� ��������� �������������� ������� ������������
		*/
		std::function<void(sf::RenderWindow&)> m_drawHUD;
		/*
			@brief �������� ������ �� �������
		*/
		std::function<bool()> m_playerWin;
		/*
			@brief �������� ������ �� ��������
		*/
		std::function<bool()> m_playerFail;
		/*
			@brief ���� ������� ����
		*/
		sf::Color m_mapBgColor;
		/*
			@brief �������� ����������� �������
		*/
		float m_timeWarp;
		/*
			@brief ��������� ������ �����
			@param element ������� � ������� ���� ��������
			@param name ��� ��������
			@ret   ����
		*/
		sf::Color readColorFromXML(TiXmlElement* element, const std::string& name);
		/*
			@brief ��������� ������ �������
			@param element ������� �� ����������
			@param data �������������� ������������� ������
		*/
		void readPropFromXML(TiXmlElement* element, std::map<std::string, std::string>& data);
		/*
			@brief ��������� �������� ����� �� tmx �����
			@param mapCfg ����-�����
		*/
		void loadMapFromFile(const std::string& mapCfg);
	public:
		World() = default;
		~World() = default;
		/*
			@brief ��������� �������� ������
			@param level ���� � �������
		*/
		void loadFromFile(const std::string& level);
		/*
			@brief ��������� ���������� �������� �������
			@param delta ������������ �������� ������� � ��������
		*/
		void runGameTiming(float delta);
		/*
			@brief ��������� ���������� ��������
		*/
		void runDrawing(sf::RenderWindow& render);
		/*
			@brief �������� �� ��������
			@ret   ������� �� �������
		*/
		bool isWin();
		/*
			@brief �������� �� ���������
			@ret   �������� �� �������
		*/
		bool isFail();
		/*
			@brief ���������� ����, �� �������� ��� �������� �������
			@ret   ���� � ������
		*/
		const std::string& getLastLevel() const;
	};
	//////////////////////////////////////////////////////////////////////////
}

#endif // !WORLD_H