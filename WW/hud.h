#ifndef HUD_H
#define HUD_H

#include <vector>
#include <stdexcept>
#include <cassert>

#include <SFML/Graphics.hpp>

namespace GameSpace
{
	/*
		@brief �������� �� ����������� ����������������� ����������
	*/
	class HUD final
	{
		sf::Font m_font;
		int m_fontSize;

		sf::Texture m_texture;
		
		sf::IntRect m_liveRect;
		sf::IntRect m_coinRect;
	public:
		/*
			@brief ������� ����������� ������ � ������ ���������� � ������
			@param source �������� �����������
			@param liveXoffset ���������� � ������� ������ �� �����������
			@param liveYoffset ���������� � ������� ������ �� �����������
			@param liveWidth ������ ������� ������
			@param liveHeight ������ ������� ������
			@param font ���� � ����� �������
			@param coinXoffset
			@param coinYoffset
			@param coinWidth ������
			@param coinHeight ������
		*/
		HUD(const std::string& font, int fontSize, const sf::Image& source,
			const sf::IntRect& liveRect, const sf::IntRect& coinRect);

		HUD(const HUD& other) = default;
		HUD& operator=(const HUD& other) = default;
		~HUD() = default;
		/*
			@brief ������������ HUD
			@param render ������ ��� ���������
			@param curLive ���������� ������
			@param totalLive ����� ������
			@param coin ���������� �����
		*/
		void draw(sf::RenderWindow& render, int curLive, int totalLive, int coin);
	};
}

#endif // !HUD_H
