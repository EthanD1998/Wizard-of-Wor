#include "pch.h"
#include "ScoreMenu.h"


ScoreMenu::ScoreMenu(int playerScore)
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
	s.name = "_____";
	s.value = playerScore;
	scores.push_back(s);
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
		
		if(scoreIndex == -1 && s.value == playerScore && s.name == "_____")
		{
			scoreIndex = i;
			texts.at(2 + (i * 2)).setFillColor(sf::Color(225,20,147));
			
			text = sf::Text("_____", font, 24);
			text.setFillColor(sf::Color::White);
			textRect = text.getLocalBounds();
			text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height - 20 / 2.0f);
			text.setPosition(texts.at(2 + (i * 2)).getPosition());
			texts.push_back(text);
		}
	}

	alphabet = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','1','2','3','4','5','6','7','8','9','~','!','@','#','$','%','^','&','*','(',')','-','_','=','+',':',';','"','<','>','?','/','`' };
	
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

void ScoreMenu::writeScores()
{
	std::ofstream file;
	file.open("Levels/scores.csv");
	score s;
	
	
	for(int i=0; i < 3; i++)
	{
		s = scores.at(i);
		
		for(int j = 0; j < 2; j++)
		{
			if(j == 0)
			{
				file << s.name << ",";
			}
			else
			{
				file << std::to_string(s.value) << ",";
			}
		}
			
	}
	
	file.close();
}

void ScoreMenu::updateName()
{
	if (key == -1)
		key = alphabet.size() - 1;

	if (key == alphabet.size())
		key = 0;

	if (col == 5)
		col == 0;

	if (col == -1)
		col = 4;

	if (scoreIndex != -1)
	{
		newName[col] = alphabet.at(key);
		texts.at(2 + (scoreIndex * 2)).setString(newName);
		scores.at(scoreIndex).name = newName;
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
			writeScores();
			break;
		case sf::Keyboard::Up:
			key--;
			updateName();
			break;
		case sf::Keyboard::Down:
			key++;
			updateName();
			break;
		case sf::Keyboard::Left:
			key = 0;
			col--;
			break;
		case sf::Keyboard::Right:
			key = 0;
			col++;
			break;
	}
	
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