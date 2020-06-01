

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <SFML/Audio.hpp>

using namespace sf;
void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

int main()
{
	VideoMode vm(1920, 1080);

	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

	//bg
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/background.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	//pohon
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	//lebah
	Texture textureBee;
	textureBee.loadFromFile("graphics/corona.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(-1000, 800);
	bool beeActive = false;
	float beeSpeed = 0.0f;

	//3 biji awan
	Texture textureCloud;
	Texture textureCloud2;
	textureCloud.loadFromFile("graphics/awan.png");
	textureCloud2.loadFromFile("graphics/cloud2.png");
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;

	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud2);
	spriteCloud3.setTexture(textureCloud);

	spriteCloud1.setPosition(-1000, 0);
	spriteCloud2.setPosition(-1000, 250);
	spriteCloud3.setPosition(-1000, 500);
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	Clock clock;

	//time bar bro
	RectangleShape timebar;
	float timebarlebar = 400;
	float timebartinggi = 80;
	timebar.setSize(Vector2f(timebarlebar, timebartinggi));
	timebar.setFillColor(Color::Red);
	timebar.setPosition((1920 / 2) - timebarlebar / 2, 980);

	Time gametotal;
	float sisawaktu = 6.0f;
	float timebarlebarpersekon = timebarlebar / sisawaktu;


	bool paused = true;

	//teks bro
	int skor = 0;
	sf::Text tulisanpesan;
	sf::Text papanskor;

	Font font;
	font.loadFromFile("font/wolland.ttf");
	tulisanpesan.setFont(font);
	papanskor.setFont(font);
	
	// tulisannya bro
	tulisanpesan.setString("Tekan Enter Untuk Mulai!");
	papanskor.setString("Score = 0");

	//ukuran font bro
	tulisanpesan.setCharacterSize(75);
	papanskor.setCharacterSize(75);

	//warna teks
	tulisanpesan.setFillColor(Color::White);
	papanskor.setFillColor(Color::White);

	//posisi teks
	FloatRect textrect = tulisanpesan.getLocalBounds();
	tulisanpesan.setOrigin(textrect.left + textrect.width / 2.0f, textrect.top + textrect.height / 2.0f);
	tulisanpesan.setPosition(1920 / 2.0f, 1080 / 2.0f);
	papanskor.setPosition(20, 20);

	// batang bukan titit
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");
	
	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		branches[i].setOrigin(220, 20);
	}

	//playernya bro
	Texture textureplayer;
	textureplayer.loadFromFile("graphics/playerkiri.png");
	Sprite spriteplayer;
	spriteplayer.setTexture(textureplayer);
	spriteplayer.setPosition(2000, 720);
	side playerside = side::LEFT;

	//playernya bro
	Texture textureplayer2;
	textureplayer2.loadFromFile("graphics/playerkanan.png");
	Sprite spriteplayer2;
	spriteplayer2.setTexture(textureplayer2);
	spriteplayer2.setPosition(580, 720);
	side playerside2 = side::RIGHT;

	//batu nisan bro
	Texture texturenisan;
	texturenisan.loadFromFile("graphics/rip.png");
	Sprite spritenisan;
	spritenisan.setTexture(texturenisan);
	spritenisan.setPosition(2000, 860);

	//kapak kuda
	Texture texturekapak;
	texturekapak.loadFromFile("graphics/kapak2.png");
	Sprite spritekapak;
	spritekapak.setTexture(texturekapak);
	spritekapak.setPosition(700, 770);
	const float kapakkanan = 1075;

	Texture texturekapak2;
	texturekapak2.loadFromFile("graphics/kapak.png");
	Sprite spritekapak2;
	spritekapak2.setTexture(texturekapak2);
	spritekapak2.setPosition(2000, 770);
	const float kapakkiri = 770;
	
	//sepotong kayu dahannya rimbung
	Texture texturekayu;
	texturekayu.loadFromFile("graphics/log.png");
	Sprite spritekayu;
	spritekayu.setTexture(texturekayu);
	spritekayu.setPosition(810, 720);
	bool kayuaktif = false;
	float speedkayux = 1000;
	float speedkayuy = -1000;
	bool accinput = false;

	//suara bro biar asik
	//baku hantam pohon
	SoundBuffer suarapukul;
	suarapukul.loadFromFile("sound/pukul.wav");
	Sound pukul;
	pukul.setBuffer(suarapukul);

	//suara mati
	SoundBuffer suaramati;
	suaramati.loadFromFile("sound/kalah.wav");
	Sound mati;
	mati.setBuffer(suaramati);

	
	while (window.isOpen())
	{
		/*input*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !paused)
			{
				accinput = true;
				spritekapak.setPosition(2000, spritekapak.getPosition().y);
				spritekapak2.setPosition(2000, spritekapak2.getPosition().y);
			}

		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		//start gim
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{ 
			paused = false;
			skor= 0;
			sisawaktu = 5;

			//batang ilang
			for (int i = 1; i < NUM_BRANCHES; i++)
			{
				branchPositions[i] = side::NONE;
			}
			spritenisan.setPosition(675, 2000);
			spriteplayer2.setPosition(600, 720);
			spriteplayer.setPosition(2000, 720);
			accinput = true;
		}
		
		if (accinput) 
		{
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				playerside = side::RIGHT;
				playerside2 = side::RIGHT;
				skor++;
				sisawaktu += (2 / skor) + .15;
				spritekapak2.setPosition(kapakkanan, spritekapak2.getPosition().y);
				spritekapak.setPosition(2000, 770);
				spriteplayer.setPosition(1200, 720);
				spriteplayer2.setPosition(2000, 720);
				updateBranches(skor);
				spritekayu.setPosition(810, 720);
				speedkayux = -5000;
				kayuaktif = true;
				accinput = false;
				pukul.play();
			}
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				playerside2 = side::LEFT;
				playerside= side::LEFT;
				skor++;
				sisawaktu += (2 / skor) + .15;
				spritekapak.setPosition(kapakkiri, spritekapak.getPosition().y);
				spritekapak2.setPosition(-1000, 770);
				spriteplayer2.setPosition(650, 720);
				spriteplayer.setPosition(-1000, 720);
				updateBranches(skor);
				spritekayu.setPosition(810, 720);
				speedkayux = 5000;
				kayuaktif = true;
				accinput = false;
				pukul.play();
			}
		}
		/*update scene*/
		if (!paused)
		{
			//ngukur time
			Time dt = clock.restart();

			sisawaktu -= dt.asSeconds();
			timebar.setSize(Vector2f(timebarlebarpersekon * sisawaktu, timebartinggi));

			if (sisawaktu <= 0.0f)
			{
				paused = true;
				tulisanpesan.setString("Waktu Abis Bro!!");
				FloatRect textrect = tulisanpesan.getLocalBounds();
				tulisanpesan.setOrigin(textrect.left + textrect.width / 2.0f, textrect.top + 
					textrect.height / 2.0f);
				tulisanpesan.setPosition(1920 / 2.0f, 1080 / 2.0f);
				mati.play();
			}
			/*draw the scene*/
			if (!beeActive)
			{
				srand((int)time(0) * 10);
				beeSpeed = (rand() % 200) + 200;

				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else {
				spriteBee.setPosition(
					spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
					spriteBee.getPosition().y
				);
				//After the bee crosses the left edge of the screen
				if (spriteBee.getPosition().x < -100) {
					//Set up a new bee
					beeActive = false;
				}
			}
			//gerakin awan
			 //Cloud1 
			if (!cloud1Active) {

				//Give the cloud a random speed
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200) + 50;

				//Give the cloud a random height
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition(-300, height);
				cloud1Active = true;

			}
			//gerak cloud1
			else {
				spriteCloud1.setPosition(
					spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),
					spriteCloud1.getPosition().y
				);
				//After the cloud crosses the right edge of the screen
				if (spriteCloud1.getPosition().x > 1950) {
					cloud1Active = false;
				}
			}

			//cloud2
			if (!cloud2Active) {

				//gacha posisi
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200) + 50;

				//gacha tinggi
				srand((int)time(0) * 20);
				float height = (rand() % 300) - 150;
				spriteCloud2.setPosition(-300, height);
				cloud2Active = true;

			}
			//gerakin cloud2
			else {
				spriteCloud2.setPosition(
					spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()),
					spriteCloud2.getPosition().y
				);
				//abis lewat layar
				if (spriteCloud2.getPosition().x > 1950) {
					cloud2Active = false;
				}
			}

			//Cloud3 
			if (!cloud3Active) {


				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200) + 50;


				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150;
				spriteCloud3.setPosition(-300, height);
				cloud3Active = true;

			}

			else {
				spriteCloud3.setPosition(
					spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),
					spriteCloud3.getPosition().y
				);

				if (spriteCloud3.getPosition().x > 1950) {
					cloud3Active = false;
				}
			}

			//apdet papanskor
			std::stringstream ss;
			ss << "Score =" << skor;
			papanskor.setString(ss.str());

			//apdet batang
			//Update the branch sprites
			for (int i = 0; i < NUM_BRANCHES; i++) {
				float height = i * 150;
				if (branchPositions[i] == side::LEFT) {
					//Move the sprite to the left side
					branches[i].setPosition(610, height);
					//Flip the sprite round the other way
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT) {
					//Move the sprite to the right side
					branches[i].setPosition(1330, height);
					//Set sprite rotation to normal
					branches[i].setRotation(0);
				}
				else {
					//Hide the branch
					branches[i].setPosition(3000, height);
				}
			}
			if (kayuaktif)
			{
				spritekayu.setPosition(spritekayu.getPosition().x + (speedkayux * dt.asSeconds()),
					spritekayu.getPosition().y + (speedkayuy * dt.asSeconds()));
				if (spritekayu.getPosition().x < -100 || spritekayu.getPosition().x>2000)
				{
					kayuaktif = false;
					spritekayu.setPosition(810, 720);
				}
			}
			//perintah kalo matek
			if (branchPositions[5] == playerside)
			{
				//matek
				paused = true;
				accinput = false;
				//nisan
				spritenisan.setPosition(525, 760);
				//ngilangin pleir
				spriteplayer.setPosition(2000, 660);
				spriteplayer2.setPosition(2000, 660);
				//ngilangin kapak
				spritekapak.setPosition(2000, 660);
				spritekapak2.setPosition(2000, 660);
				//ganti tulisan
				tulisanpesan.setString("Yah mati bro!!!");
				//tulisan ditengah
				FloatRect textRect = tulisanpesan.getLocalBounds();
				tulisanpesan.setOrigin(
					textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f
				);
				tulisanpesan.setPosition(1920 / 2.0f, 1080 / 2.0f);
				mati.play();
			}
		} 

		//end if pause
		window.clear();
		window.draw(spriteBackground);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		window.draw(spriteTree);
		window.draw(timebar);
		//Batang
		for (int i = 0; i < NUM_BRANCHES; i++) {
			window.draw(branches[i]);
		}
		window.draw(spriteplayer);
		window.draw(spriteplayer2);
		window.draw(spritekayu);
		window.draw(spritekapak);
		window.draw(spritekapak2);
		window.draw(spritenisan);
		window.draw(spriteBee);
		if (paused)
		{
			window.draw(tulisanpesan);
		}

		window.draw(papanskor);
		window.display();
	}

	return 0;
}

void updateBranches(int seed) {
	//Move all the branches down one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--) {
		branchPositions[j] = branchPositions[j - 1];
	}
	//Spawn a new branch at position 0 (top of the branch)
	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;
	}

}