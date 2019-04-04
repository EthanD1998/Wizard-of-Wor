#include "pch.h"
#include "ScoreMenu.h"



ScoreMenu::ScoreMenu()
{
	score s;
	
	std::cout << "DisplayState ScoreMenu Created" << std::endl;
	font.loadFromFile("Fonts/Adore.ttf");
	
	sf::Text text("High Scores", font, 70);
	text.setFillColor(sf::Color::Red);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(420,60));
	texts.push_back(text);
	
	text = sf::Text("Press Enter to Save", font, 25);
	text.setFillColor(sf::Color::Blue);
	textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(420,500));
	texts.push_back(text);
	
	std::ifstream file("Levels/scores.csv");
	std::string value;
	
	while(file.good())
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 2; j++)
			{
				getline(file, value, ',');
				std::cout << value << std::endl;
				if(j == 0)
				{
					s.name = value;
				}
				else if(j == 1)
				{
					s.value = std::atoi(value.c_str());
				}
				
			}
				scores.push_back(s);
		}
	}
	
	sort();
	
	for(int i = 0; i < 3; i++)
	{
		s = scores.at(i);
		
		for(int j = 0; j < 2; j++)
		{
			if(j == 0)
			{
				text = sf::Text(s.name, font, 24);	
				text.setFillColor(sf::Color(79, 246, 255));
			}
			else
			{
				text = sf::Text(std::to_string(s.value), font, 24);					
				text.setFillColor(sf::Color(210, 255, 12));
			}
			
			textRect = text.getLocalBounds();
			text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			text.setPosition(sf::Vector2f(320 + j * 200, 200 + 50 * i));
			
			texts.push_back(text);
		}
	}
	
}

void ScoreMenu::swap(score* i, score* j)
{
	int temp;
	std::string t;
	
	temp = i->value;
	i->value = j->value;
	j->value = temp;
	
	t = i->name;
	i->name = j->name;
	j->name = t;
}

void ScoreMenu::sort() 
{
    for (size_t i = 1; i < scores.size(); ++i) {
        for (size_t j = 0; j < scores.size() - 1; ++j) {
            if (scores[j].value < scores[i].value) swap(&scores[j], &scores[i]);
        }
    }
}

ScoreMenu::~ScoreMenu()
{
}

void ScoreMenu::keyEvent(sf::Keyboard::Key& k)
{
	switch(k)
	{
		case sf::Keyboard::Enter:
				exists = false;
				break;
		case sf::Keyboard::BackSpace:
			{
				if(newName.size() != 0)
				{
					newName.pop_back();
					std::string v = "";
					for(int i=0; i < newName.size(); i++)
						v += newName.at(i);
					texts.at(2).setString(v);
				}
			}
			break;
	
		default:
			 
			break;
	}
}

void ScoreMenu::input(sf::Event::TextEvent t)
{
	if(newName.size() < 5)
	{
		
	std::string v = "";
	
	newName.push_back(static_cast<char>(t.unicode));
	
	for(int i=0; i < newName.size(); i++)
		v += newName.at(i);
		
	texts.at(2).setString(v);
	}
//    score.SetText(str);
}

void ScoreMenu::draw(sf::RenderWindow* target)
{
	for(int i = 0; i < texts.size(); i++)
	{
		target->draw(texts.at(i));
	}
}

DisplayState* ScoreMenu::nextState()
{
	return new StartMenu();
}


std::string ScoreMenu::type()
{
	return "ScoreMenu";
}

