#ifndef __TEXTBOX__
#define __TEXTBOX__

#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

#define VERTS_IN_QUAD 4


class TextBox
{
	sf::Text mtext;
	const sf::Font& mfont;
	std::ostringstream mstream{};
	bool misSelected{ false };
	bool mhasLimit{ true };
	int mlimit{ 30 };
	sf::Vector2f mpos {0.f, 0.f};
	sf::Vector2u mboxSize { 0U, 0U };
	sf::Texture mboxTex;

	sf::VertexArray mtextboxVertices;

public:

	explicit TextBox(int size, sf::Color color, bool sel, const sf::Font& font, sf::Vector2f pos, sf::Vector2u boxSize = { 300U, 100U })
		: mfont(font), mtext(), mboxTex()
		, mpos(pos), mboxSize(boxSize)
	{
		mboxTex.loadFromFile("graphics/GUI/textbox/brassy_frame.png");
		mlimit = (int)((float)boxSize.x * (3.f / 50.f)) - 1;
		mtext.setFont(mfont);
		mtext.setCharacterSize(size);
		mtext.setFillColor(color);
		misSelected = sel;

		if (sel)
		{
			mtext.setString("_");
		}
		else
		{
			mtext.setString("");
		}

		mtextboxVertices.setPrimitiveType(sf::Quads);
		mtextboxVertices.resize(VERTS_IN_QUAD);
		
		mtextboxVertices[0].position = mpos;
		mtextboxVertices[1].position = { mpos.x + boxSize.x, mpos.y };
		mtextboxVertices[2].position = { mpos.x + boxSize.x, mpos.y + boxSize.y };
		mtextboxVertices[3].position = { mpos.x, mpos.y + boxSize.y };

		mtextboxVertices[0].texCoords = {0.f, 0.f};
		mtextboxVertices[1].texCoords = { 150.f, 0.f };
		mtextboxVertices[2].texCoords = { 150.f, 150.f };
		mtextboxVertices[3].texCoords = { 0.f, 150.f };


		this->setPosition(mpos);
	}
	void deleteLastChar()
	{
		if (mstream.str() == "_") { return; }
		std::string t = mstream.str();
		std::string newT = "";
		for (int i = 0; i < t.length()-1; i++)
		{
			newT += t[i];
		}
		mstream.str("");
		mstream << newT;

		mtext.setString(mstream.str() + R"(_)");
	}

	void setPosition(sf::Vector2f pos)
	{
		mpos = pos;
		mtext.setPosition({ mpos.x + 35.f, mpos.y + 35.f });
	}

	void setLimit(bool ToF, int lim)
	{
		mhasLimit = ToF;
		mlimit = lim;
	}

	void setLimit(bool ToF)
	{
		mhasLimit = ToF;

	}

	void setSelected(bool sel)
	{
		misSelected = sel;
		if (!sel)
		{
			std::string t = mstream.str();
			std::string newT = "";
			for (int i = 0; i < t.length() - 1; i++)
			{
				newT += t[i];
			}
			mtext.setString(newT);
		}

	}

	std::string getText()
	{

		mtext.getString();
	}

	void drawTo(sf::RenderWindow& window)
	{
		window.draw(mtextboxVertices, &mboxTex);
		window.draw(mtext);
	}

	void typedOn(sf::Event input)
	{
		if (misSelected)
		{
			int charTyped = input.text.unicode;
			if (charTyped < 128)
			{
				if (mhasLimit)
				{
					if (mtext.getString().getSize() <= mlimit)
					{
						if (charTyped == DELETE_KEY)
						{
							if (mtext.getString().getSize() > 1)
							{
								deleteLastChar();
							}
							else
							{

							}
						}
						else
						{
							inputLogic(charTyped);
						}
					}
					else if (mtext.getString().getSize() > mlimit && charTyped == DELETE_KEY)
					{
						deleteLastChar();
					}
				}
				else
				{
					if (charTyped == DELETE_KEY)
					{
						if (mtext.getString().getSize() > 1)
						{
							deleteLastChar();
						}
						else
						{

						}
					}
					else
					{
						inputLogic(charTyped);
					}
				}
			}
		}
	}

private:


	void inputLogic(int charTyped)
	{
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
		{
			mstream << static_cast<char>(charTyped);

		}
		else if (charTyped == DELETE_KEY)
		{
			deleteLastChar();
		}
		
		else if (charTyped == ENTER_KEY)
		{

		}
		else if (charTyped == ESCAPE_KEY)
		{

		}
		mtext.setString(mstream.str() + "_");
	}
};

#endif
