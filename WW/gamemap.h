#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
#include <stdexcept>

#include "tinyxml/tinyxml.h"

#include "object.h"

namespace GameSpace
{
	/*
		@brief	����� �������� ������ ������� xml, ������������� Tiled
				����� �������� ������ ������
				���� ��� ���� ���������� � opaque �� ������� �� ��� �����������
				���� ��� ���� ���������� � transparent �� ������� �� ��� ���������
	*/
	class GameMap final
	{
		// ������ ������������ ��������
		std::list<Object> m_opaques;
		// ������ ���������� ��������
		std::list<Object> m_transparents;
		// ������ ����� ����������� ������� �� �� ��������
		// ���� ����
		sf::Color m_bgColor;

		/*
			@brief ������ ���� �� �������� � ����������� ���������� � ������ ����
			@param element �����, ������ ������
			@param attribName ��� ���������
			@ret   �����
		*/
		sf::Color getColorAttribute(TiXmlElement* element, const char* attribName);
		/*
		@brief ������ �������� ������ �� �������� � ����������� ���������� � ������ ����
		@param element �����, ������ ������
		@param attribName ��� ��������
		@ret   ������
		*/
		std::string getStrAttribute(TiXmlElement* element, const char* attribName);
	public:
		GameMap() = default;
		GameMap(const GameMap&) = default;
		GameMap& operator=(const GameMap&) = default;
		~GameMap() = default;
		/*
			@brief ��������� ����� �� xml �����
			@param mapFile ��� ����� � ������
		*/
		void loadFromFile(const std::string& mapFile);
		/*
			@brief ������������ �����
			@param render ����������� ������
		*/
		void draw(sf::RenderWindow& render) const;
		/*
			@brief ���������� ������� ����
			@ret   �������� �����
		*/
		const sf::Color& getBackground() const;
	};
}

#endif // !GAMEMAP_H
